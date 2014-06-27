#include <errno.h>
#include "gate_client_session.h"
#include "protoPlug.h"
#include <event2/buffer.h>
#include "sh_common.h"
#include "gate_client_session_manager.h"



void ConnReadCb(struct bufferevent *bev, void *user_data)
{
    CGateClientSession* p_CGateClientSession = (CGateClientSession*)user_data;
    struct evbuffer *input =bufferevent_get_input(bev);
    char dataBuf[MAX_TAKE_SIZE_ONCE+1] = {0};
    char headBuf[MSG_HEADER_SIZE+1] = {0};
    int buffSize = evbuffer_get_length(input);
    if (buffSize > 0){
	//p_CGateClientSession->m_bev_ptr = bev;	
        if (p_CGateClientSession->m_recv_count == 1) {
            //消息头size
            int msgSize = bufferevent_read(bev,headBuf,MSG_HEADER_SIZE);
            if (msgSize == MSG_HEADER_SIZE) {
		msgSize = *headBuf;
		if (msgSize > 0) {
                	p_CGateClientSession->m_actual_recv_data.append(headBuf,MSG_HEADER_SIZE);
                	p_CGateClientSession->m_need_recv_size = msgSize;
			int msgBodySize = p_CGateClientSession->m_need_recv_size - MSG_HEADER_SIZE;
			if (msgBodySize > 0) {
                		int actualReadSize = bufferevent_read(bev,dataBuf,msgBodySize);
                		if (actualReadSize > 0 && actualReadSize < msgBodySize) {
                    			p_CGateClientSession->m_recv_count += 1;
                			p_CGateClientSession->m_actual_recv_data.append(dataBuf,actualReadSize);
                		} else if (actualReadSize > 0 && actualReadSize == msgBodySize) {
                			p_CGateClientSession->m_actual_recv_data.append(dataBuf,actualReadSize);
                			//一次就把消息收全的情况
                			if (p_CGateClientSession->m_actual_recv_data.size() == p_CGateClientSession->m_need_recv_size) {
                    				p_CGateClientSession->MsgProcess(p_CGateClientSession->m_actual_recv_data.c_str(),p_CGateClientSession->m_need_recv_size);
                			}
				} else {
					g_CGateClientSessionManager.DelClientSession(p_CGateClientSession->GetFd());
				}
			} else {
				g_CGateClientSessionManager.DelClientSession(p_CGateClientSession->GetFd());
			}	
		} else {
			g_CGateClientSessionManager.DelClientSession(p_CGateClientSession->GetFd());
		}
            } else {
			g_CGateClientSessionManager.DelClientSession(p_CGateClientSession->GetFd());
	    }

        } else {//需多次才能把消息收全
            int actualReadSize = bufferevent_read(bev,dataBuf,p_CGateClientSession->m_need_recv_size-p_CGateClientSession->m_actual_recv_data.size());
            if (actualReadSize > 0) {
                p_CGateClientSession->m_actual_recv_data.append(dataBuf,actualReadSize);
                if (p_CGateClientSession->m_actual_recv_data.size() == p_CGateClientSession->m_need_recv_size) {
                    p_CGateClientSession->MsgProcess(p_CGateClientSession->m_actual_recv_data.c_str(),p_CGateClientSession->m_need_recv_size);
                }
            } else {
		g_CGateClientSessionManager.DelClientSession(p_CGateClientSession->GetFd());
	    } 
        }
    }
}


void ConnWriteCb(struct bufferevent *bev, void *user_data)
{

}

void ConnEventCb(struct bufferevent *bev, short events, void *user_data)
{
    	if (events & BEV_EVENT_EOF) {
            cerr<<"Connection closed."<<endl;
        } else if (events & BEV_EVENT_ERROR) {
            cerr<<"Got an error on the connection:"<<strerror(errno)<<endl;
        }   
        else if (events & BEV_EVENT_TIMEOUT){
            cerr<<"got an timeout:"<<strerror(errno)<<endl;
        }
        else{       
            cerr<<"other event error"<<endl;
        }
        // None of the other events can happen here, since we haven't enabled
        // timeouts 
        //bufferevent_free(bev);
	CGateClientSession* p_CGateClientSession = (CGateClientSession*)user_data;
	g_CGateClientSessionManager.DelClientSession(p_CGateClientSession->GetFd());
}

void CGateClientSession::FreeBufferevent()
{
	bufferevent_free(m_bev_ptr);
}

void CGateClientSession::SetFd(const UINT32 fd)
{
	m_fd = fd;
}

const UINT32 CGateClientSession::GetFd() const
{
	return m_fd;
}

void CGateClientSession::Setbufferevent(struct bufferevent *bev)
{
	m_bev_ptr = bev;
}


CGateClientSession::CGateClientSession()
{
	m_recv_count = 1;
	m_need_recv_size = 0;
	m_actual_recv_data.clear();
	m_bev_ptr = NULL;
}

void CGateClientSession::dataReset()
{
	m_recv_count = 1;
        m_need_recv_size = 0;
        m_actual_recv_data.clear();
}


CGateClientSession::~CGateClientSession()
{
}

void CGateClientSession::MsgProcess(const void* data,const UINT32& size)
{
    cout<<"data:"<<data<<endl;
    INT32 msgType = *((const char*)(data+MSG_HEADER_SIZE));
    cout <<"msgType:"<<msgType<<endl;
    switch(msgType) {
        case E_GATE_LOGIN_REQ:
            OnRecvLoginReq(this,(const unsigned char*)(data+MSG_HEADER_SIZE+MSG_TYPE_SIZE),size-MSG_HEADER_SIZE-MSG_TYPE_SIZE);
            break;
        default:
            cout<<"unkown Req"<<msgType<<endl;
	    g_CGateClientSessionManager.DelClientSession(m_fd);
            break;

    }
}
void CGateClientSession::SendToClient(const void* msgData,const INT32& msgSize)
{
    INT ret = bufferevent_write(m_bev_ptr, msgData, msgSize);
    dataReset(); 
    if (ret != 0) {
        cout<<"bufferevent_write error"<<endl;
    }  
}

