#include "sh_filelog.h"
#include "log_config_mgr.h"
#include "sh_log_object.h"

namespace share {
// ����Ƿ�д������͡��ȼ�����־
// �����Ҫд���򷵻����ָ�����log����ľ��
SHARE_FILE_LOG_HANDLE ShareFileLogCheckLog(const unsigned int nLogTypeIndex, const int nLogLevel)
{
    //��ȡ��־��������map
    const np_log_config_mgr::mapNameLogTypeStruct& nameLogTypes = np_log_config_mgr::Clog_config_mgr::Instance().getNameLogTypes();
    if (nameLogTypes.size() <= 0) {
        return NULL;
    }
    //�õ�����־�����Ӧ����־����map
    np_log_config_mgr::mapNameLogTypeStruct::const_iterator it_nameLogTypes = nameLogTypes.find(nLogTypeIndex);
    if (nameLogTypes.end() == it_nameLogTypes) {
        return NULL;
    }
    if (it_nameLogTypes->second.size() <= 0) {
        return NULL;
    }
    //�жϸ���־�����Ƿ���Ҫд
    const np_log_config_mgr::mapLogTypeStruct& logTypes = it_nameLogTypes->second;
    if (logTypes.size() <= 0) {
        return NULL;
    }
    np_log_config_mgr::mapLogTypeStruct::const_iterator it_LogType = logTypes.find(nLogLevel);
    if (logTypes.end() == it_LogType) {
        return NULL;
    }
    if (!it_LogType->second.isRecord) {
        return NULL;
    }
    //��ȡ��־����map
    np_log_config_mgr::mapLogObject& logObjects = np_log_config_mgr::Clog_config_mgr::Instance().getLogObjects();
    if (logObjects.size() <= 0) {
        return NULL;
    }
    np_log_config_mgr::mapLogObject::iterator it_logObjects = logObjects.find(nLogTypeIndex);
    if (logObjects.end() == it_logObjects) {
        return NULL;
    }
    //�ж��Ƿ���ͬһ��
    UINT64 now_t = (UINT64)time(NULL);
    if (!np_log_config_mgr::Clog_config_mgr::Instance().isOnSameDay(it_logObjects->second->GetGenerateTime(),now_t)) {
        //����ͬһ��
        //�õ��µ���־·��
        const np_log_config_mgr::mapLogConfigStruct& logConfigs = np_log_config_mgr::Clog_config_mgr::Instance().getLogConfigs();
        if (logConfigs.size() <= 0) {
            return NULL;
        }
        np_log_config_mgr::mapLogConfigStruct::const_iterator it_logConfigs = logConfigs.find(nLogTypeIndex);
        if (logConfigs.end() == it_logConfigs) {
            return NULL;
        }
        std::string newLogFilePath = np_log_config_mgr::Clog_config_mgr::Instance().getLogFilePath(it_logConfigs->second.folder_name,it_logConfigs->second.log_head,it_logConfigs->second.log_tail);
        //���·����µ���־����
        Csh_log_object* pLogObject = np_log_config_mgr::Clog_config_mgr::Instance().generateLogObjectByPath(newLogFilePath);
        if (pLogObject == NULL) {
            std::cerr<<"new Csh_log_object error in ShareFileLogCheckLog"<<std::endl;
            return NULL;
        }
        //�滻ԭ������־����
        delete it_logObjects->second;
        it_logObjects->second = pLogObject;             
    }
    
    return (SHARE_FILE_LOG_HANDLE)it_logObjects->second;

}

//д�ı���־
void ShareFileLog(SHARE_FILE_LOG_HANDLE hLog, const char* lpcszLog)
{
    if (hLog != NULL) {
        Csh_log_object *pLog = (Csh_log_object *)hLog;
        std::ostringstream oss;
        oss<<"["<<np_log_config_mgr::Clog_config_mgr::Instance().getCurDateTime("%H:%M:%S")<<"]"<<lpcszLog;
        pLog->RecordLog(oss.str().c_str());
    }
}

//���¼����ı���־�ȼ�����
void ReloadShareFileLogLevel()
{

}

};