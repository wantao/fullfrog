#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

static unsigned int g_thread_counts = 20;
static unsigned int g_one_thread_loop_connect_count = 100;
static char* g_server_ip = "192.168.242.129";
static unsigned int g_server_port = 9995;

#define MAX_BUFF_SIZE 1024


int tcp_connect(char* server_ip, unsigned int server_port)
{
    int sockfd = -1;
    struct sockaddr_in server_addr;
    struct hostent *host;
    if ((host = gethostbyname(server_ip)) == NULL)
    {
        printf("get host by name error,server_ip:%s\n",server_ip);
        return sockfd;
    }
    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("create_socketfd error\n");
    }
    else
    {
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        if (connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) == -1)
        {
            printf("cannot connect server,server_ip:%s,port:%d\n",server_ip,server_port);
            close(sockfd);
            return -1;
        }
    }
    return sockfd;

}

void recvData(int fd)
{
    char buf[MAX_BUFF_SIZE] = {0};
    int nbytes = 0;
    if ((nbytes = recv(fd,buf,MAX_BUFF_SIZE,0)) == -1)
    {
        printf("recvData error,fd:%d,strerror:%s\n",fd,strerror(errno));
        return;
    }
    buf[nbytes] = '\0';
    printf("client fd:%d,recv data:%s\n",fd,buf);
    //close(fd);
}

void sendData(int fd)
{
    char sendBuf[32] = {0};
    sprintf(sendBuf,"%d %s\n",fd,"testData");
    int sendlen = send(fd,sendBuf,strlen(sendBuf),0);
    if (sendlen <= 0)
    {
        printf("fd:%d send data error\n");
    }
}

void* tcp_connect_func(void* pArg)
{
    int j = 0;
    for (; j < g_one_thread_loop_connect_count; j++)
    {
        int fd = 0;
        fd = tcp_connect(g_server_ip,g_server_port);
        if (fd > 0)
        {
            sendData(fd);
            recvData(fd);
        }
        else
        {
            printf("tcp_connect failure\n");
        }
    }

}

void create_thread()
{
    pthread_t id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    int nret = pthread_create(&id,&attr,tcp_connect_func,NULL);
    if (nret != 0)
    {
        printf("pthread_create failure\n");
    }
    pthread_attr_destroy(&attr);
}

int main(void)
{
    int i = 0;
    for (; i < g_thread_counts; i++)
    {
        create_thread();
    }
    while (1)
    {
        sleep(2);
    }
    return 0;
}
