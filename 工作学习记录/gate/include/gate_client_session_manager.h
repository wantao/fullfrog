#ifndef __GATE_CLIENT_SESSION_MANAGER_H__
#define __GATE_CLIENT_SESSION_MANAGER_H__

#include "sh_common.h"
#include "gate_client_session.h"

typedef std::map<UINT32,CGateClientSession*> GateClientSessionMap;


class CGateClientSessionManager
{
public:
    CGateClientSessionManager();
   ~CGateClientSessionManager();
    bool AddClientSession(const UINT32& fd,CGateClientSession* &pClientSession);
    void DelClientSession(const UINT32& fd); 
    const int GetClientSessionNum() const;
protected:
private:
    GateClientSessionMap m_client_session_map;
};

extern CGateClientSessionManager g_CGateClientSessionManager;

#endif
