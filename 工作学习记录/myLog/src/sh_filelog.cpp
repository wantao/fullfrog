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
    const np_log_config_mgr::mapLogObject& logObjects = np_log_config_mgr::Clog_config_mgr::Instance().getLogObjects();
    if (logObjects.size() <= 0) {
        return NULL;
    }
    np_log_config_mgr::mapLogObject::const_iterator it_logObjects = logObjects.find(nLogTypeIndex);
    if (logObjects.end() == it_logObjects) {
        return NULL;
    }
    return (SHARE_FILE_LOG_HANDLE)it_logObjects->second;
}

//д�ı���־
void ShareFileLog(SHARE_FILE_LOG_HANDLE hLog, const char* lpcszLog)
{
    if (hLog != NULL) {
        Csh_log_object *pLog = (Csh_log_object *)hLog;
        std::ostringstream oss;
        oss<<"["<<np_log_config_mgr::Clog_config_mgr::Instance().getCurDateTime("%H:%M:%S")<<"]";
        pLog->RecordLog(oss.str().c_str());
        pLog->RecordLog(lpcszLog);
    }
}

//���¼����ı���־�ȼ�����
void ReloadShareFileLogLevel()
{

}

};