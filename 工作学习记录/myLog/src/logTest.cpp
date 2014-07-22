#include "sh_filelog.h"
#include "log_config_mgr.h"

int main()
{
    np_log_config_mgr::Clog_config_mgr::CreateInstance();
    np_log_config_mgr::Clog_config_mgr::Instance().Init();
    while (1) {
        USER_LOG_DEBUG("test log!!!");
        int a = 10;
        USER_FAST_LOG_DEBUG("a:%d",a);
        USER_FAST_LOG_ERROR("error!!!");
        USER_FAST_LOG_FATAL("fatal!!!");
        USER_LOG_INFO("info!!!");
        USER_LOG_WARN("warn!!!");

        SHARE_LOG_DEBUG("shareDebug!!!");
        SHARE_LOG_INFO("shareInfo!!!");
        SHARE_LOG_WARN("shareWarn!!!");
        SHARE_LOG_FATAL("shareFatal!!!");
        SHARE_LOG_ERROR("shareError!!!");
        
        Sleep(2000);
    }

    np_log_config_mgr::Clog_config_mgr::DestroyInstance();
    return 0;
}