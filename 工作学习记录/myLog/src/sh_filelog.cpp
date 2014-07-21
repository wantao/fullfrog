#include "sh_filelog.h"
#include "log_config_mgr.h"
#include "sh_log_object.h"

namespace share {
// 检查是否写这个类型、等级的日志
// 如果需要写，则返回这个指向这个log对象的句柄
SHARE_FILE_LOG_HANDLE ShareFileLogCheckLog(const unsigned int nLogTypeIndex, const int nLogLevel)
{
    //获取日志种类类型map
    const np_log_config_mgr::mapNameLogTypeStruct& nameLogTypes = np_log_config_mgr::Clog_config_mgr::Instance().getNameLogTypes();
    if (nameLogTypes.size() <= 0) {
        return NULL;
    }
    //得到该日志种类对应的日志类型map
    np_log_config_mgr::mapNameLogTypeStruct::const_iterator it_nameLogTypes = nameLogTypes.find(nLogTypeIndex);
    if (nameLogTypes.end() == it_nameLogTypes) {
        return NULL;
    }
    if (it_nameLogTypes->second.size() <= 0) {
        return NULL;
    }
    //判断该日志类型是否需要写
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
    //获取日志对象map
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

//写文本日志
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

//重新加载文本日志等级配置
void ReloadShareFileLogLevel()
{

}

};