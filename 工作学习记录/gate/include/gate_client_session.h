#ifndef __GATE_CLIENT_SESSION_H__
#define __GATE_CLIENT_SESSION_H__

#include <event2/bufferevent.h>
#include <string>
#include "sh_type.h"
#include <iostream>

using namespace std;

#define MAX_TAKE_SIZE_ONCE 4096
#define MSG_HEADER_SIZE sizeof(INT32)
#define MSG_TYPE_SIZE   sizeof(INT32) 

enum E_GATE_MSG_TYPE
{
    E_GATE_LOGIN_REQ = 1,
    E_GAET_LOGIN_ACK = 2,
};

extern void ConnReadCb(struct bufferevent *bev, void *user_data);
extern void ConnWriteCb(struct bufferevent *bev, void *user_data);
extern void ConnEventCb(struct bufferevent *bev, short events, void *user_data);

class CGateClientSession
{
public:
    friend void ConnReadCb(struct bufferevent *bev, void *user_data);
    friend void ConnWriteCb(struct bufferevent *bev, void *user_data);
    friend void ConnEventCb(struct bufferevent *bev, short events, void *user_data);
    CGateClientSession();
    virtual ~CGateClientSession();
   
    void MsgProcess(const void* data,const UINT32& size);
    void dataReset();
    void SendToClient(const void* msgData,const INT32& msgSize);
    void Setbufferevent(struct bufferevent *bev); 
    void FreeBufferevent();
    void SetFd(const UINT32 fd);
    const UINT32 GetFd() const;
protected:
private:
    UINT32 m_recv_count;//������Ϣͷ������Ϣ��ı�־��1��������Ϣͷ��2��������Ϣ��
    UINT32 m_need_recv_size;//��Ҫ���յ���Ϣ���size
    std::string m_actual_recv_data;//ʵ�ʽ��յ�������
    struct bufferevent *m_bev_ptr;//���ӵ�bufferevent
    UINT32 m_fd;
};

#endif
