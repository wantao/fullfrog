#include "sh_filelog.h"
#include "log_config_mgr.h"

int main()
{
    np_log_config_mgr::Clog_config_mgr::CreateInstance();
    np_log_config_mgr::Clog_config_mgr::Instance().Init();
    USER_LOG_DEBUG("test log!!!");
    int a = 10;
    USER_FAST_LOG_DEBUG("a:%d",a);
    return 0;
}