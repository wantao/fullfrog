#include "gate_client_session_manager.h"

CGateClientSessionManager g_CGateClientSessionManager;

CGateClientSessionManager::CGateClientSessionManager()
{
    m_client_session_map.clear();
}
CGateClientSessionManager::~CGateClientSessionManager()
{
    m_client_session_map.clear();
}

bool CGateClientSessionManager::AddClientSession(const UINT32& fd,CGateClientSession* &pClientSession)
{
    return m_client_session_map.insert(std::pair<UINT32,CGateClientSession*>(fd,pClientSession)).second;
}

void CGateClientSessionManager::DelClientSession(const UINT32& fd)
{
    GateClientSessionMap::iterator it = m_client_session_map.find(fd);
    if (m_client_session_map.end() != it) {
	it->second->FreeBufferevent();
	delete it->second;
        m_client_session_map.erase(it);
    }
}

const int CGateClientSessionManager::GetClientSessionNum() const 
{
	return m_client_session_map.size();
}
