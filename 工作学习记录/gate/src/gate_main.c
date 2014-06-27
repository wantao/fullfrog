/*
  This exmple program provides a trivial server program that listens for TCP
  connections on port 9995.  When they arrive, it writes a short message to
  each client connection, and closes each connection once it is flushed.

  Where possible, it exits cleanly in response to a SIGINT (ctrl-c).
*/


#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include "protoPlug.h"
#include "gate_client_session.h"
#include "gate_client_session_manager.h"
//#include <event2/buffer_compat.h>
//#include "evbuffer-internal.h"


static const char MESSAGE[] = "Hello, World!\n";

static const int PORT = 9995;
static void listener_cb(struct evconnlistener *, evutil_socket_t,
    struct sockaddr *, int socklen, void *);
static void signal_cb(evutil_socket_t, short, void *);



static void
listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
        struct event_base *base = (struct event_base *)user_data;
        struct bufferevent *bev;

        bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        if (!bev) {
                fprintf(stderr, "Error constructing bufferevent!");
                event_base_loopbreak(base);
                return;
        }
    	struct timeval readcb_delay = {20,0};
    	struct timeval writecb_delay = {20,0};
    	bufferevent_set_timeouts(bev,&readcb_delay,&writecb_delay);
        
	CGateClientSession * p_CGateClientSession = new CGateClientSession;
	if (NULL != p_CGateClientSession) {
        	bufferevent_setcb(bev, ConnReadCb,ConnWriteCb,ConnEventCb,p_CGateClientSession);
        	bufferevent_enable(bev, EV_WRITE|EV_READ|EV_TIMEOUT|EV_ET|EV_PERSIST);
		p_CGateClientSession->Setbufferevent(bev);
		p_CGateClientSession->SetFd(fd);
        	//bufferevent_disable(bev, EV_READ);

        	//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
		g_CGateClientSessionManager.AddClientSession(fd,p_CGateClientSession);
	}
	printf("clientSessionNum:%d\n",g_CGateClientSessionManager.GetClientSessionNum());
}

static void
signal_cb(evutil_socket_t sig, short events, void *user_data)
{
        struct event_base *base = (struct event_base *)user_data;
        struct timeval delay = { 2, 0 };

        printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

    	event_base_loopexit(base, &delay);
}
 


int 
main(int argc, char **argv)
{
	struct event_base *base;
	struct evconnlistener *listener;
	struct event *signal_event;

	struct sockaddr_in sin;
#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	base = event_base_new();
	if (!base) {
		fprintf(stderr, "Could not initialize libevent!\n");
		return 1;
	}

    	const char* method = event_base_get_method(base);
    	printf("method:%s\n",method);
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base,
	    LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
	    (struct sockaddr*)&sin,
	    sizeof(sin));

	if (!listener) {
		fprintf(stderr, "Could not create a listener!\n");
		return 1;
	}

	signal_event = evsignal_new(base, SIGINT, signal_cb, (void *)base);

	if (!signal_event || event_add(signal_event, NULL)<0) {
		fprintf(stderr, "Could not create/add a signal event!\n");
		return 1;
	}

	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_free(signal_event);
	event_base_free(base);

	printf("done\n");
	return 0;
}
