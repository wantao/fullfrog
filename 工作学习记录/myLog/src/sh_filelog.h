#ifndef __SHARE_FILE_LOG_H__
#define __SHARE_FILE_LOG_H__

#include <string>
#include <sstream>


//////////////////////////////////////////////////////////////////////////
/// 下面的这三部分宏定义，如果改变需要重新编译库
//////////////////////////////////////////////////////////////////////////
// 日志等级名称
#define  sg_debug       "debug"
#define  sg_info        "info"
#define  sg_warn        "warn"
#define  sg_error       "error"
#define  sg_fatal       "fatal"

//每个日志等级名称对应的id值
#define  sg_n_debug     0
#define  sg_n_info      1
#define  sg_n_warn      2
#define  sg_n_error     3
#define  sg_n_fatal     4
//////////////////////////////////////////////////////////////////////////

namespace share
{
typedef void* SHARE_FILE_LOG_HANDLE;

static const char* sg_log_id_text[] = {
    sg_debug, //index=sg_n_debug
    sg_info,  //index=sg_n_info
    sg_warn,  //index=sg_n_warn
    sg_error, //index=sg_n_error
    sg_fatal, //index=sg_n_fatal
};

//////////////////////////////////////////////////////////////////////////
//// log, 简单的文本日志；数据库日志
//////////////////////////////////////////////////////////////////////////

/* 下面是一个配置例子。
<root>
    <!--
    日志类型对应的日志目录，日志文件名称头和尾
    每类日志对应的记录级别
    日志类型id，最好按照从小到大往下排序。[0-65535]。不能有重复
    日志名称name 也不能有重复
    -->
    <logtype>
        <type id="0" name="ShareLog"    folder_name="ShareLog"   log_file_head="share"  log_file_trail=".log">
            <item key="debug" value="yes" />
            <item key="info"  value="yes" />
            <item key="warn"  value="yes" />
            <item key="error" value="yes" />
            <item key="fatal" value="yes" />
        </type>

        <type id="2" name="UserLog"     folder_name="UserLog"    log_file_head="user"   log_file_trail=".log">
            <item key="debug" value="yes" />
            <item key="info"  value="yes" />
            <item key="warn"  value="yes" />
            <item key="error" value="yes" />
            <item key="fatal" value="yes" />
        </type>

    </logtype>

</root>

*/

// 检查是否写这个类型、等级的日志
// 如果需要写，则返回这个指向这个log对象的句柄
extern SHARE_FILE_LOG_HANDLE ShareFileLogCheckLog(const unsigned int nLogTypeIndex, const int nLogLevel);

//写文本日志
extern void ShareFileLog(SHARE_FILE_LOG_HANDLE hLog, const char* lpcszLog);

//重新加载文本日志等级配置
extern void ReloadShareFileLogLevel();

}

//系统独占默认的日志类型
#define  sg_default_log_type_share  0
#define  sg_default_log_type_user   1
#define  sg_default_log_type_memory 2
#define  sg_default_log_type_sql    3


//FAST_FLOG使用。定义一条日志的最大字节长度， 这个值可以根据实际情况修改
#define  FAST_LOG_BUFFER_SIZE 1024
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// 系统定义 FLOG，一般不能修改。即使修改，也应该保持宏的参数类型以及数量一致
//////////////////////////////////////////////////////////////////////////
#define  FLOG(logtype, loglevel, lpmsg) do{\
    share::SHARE_FILE_LOG_HANDLE pLog = share::ShareFileLogCheckLog(logtype,loglevel);\
    if (NULL == pLog) break;\
    std::ostringstream oss; \
    oss<<"["<<share::sg_log_id_text[loglevel]<<"]"\
    <<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]:"<<lpmsg;\
    share::ShareFileLog(pLog, oss.str().c_str());}while(0);

//////////////////////////////////////////////////////////////////////////
/// 系统定义 FLOG，一般不能修改。可以修改，但应该保持宏的参数类型以及数量一致
//////////////////////////////////////////////////////////////////////////
#define FAST_FLOG(logtype, loglevel, fmt, ...) do{\
    share::SHARE_FILE_LOG_HANDLE pLog = share::ShareFileLogCheckLog(logtype,loglevel);\
    if (NULL == pLog) break;\
    char szLogBuffer[FAST_LOG_BUFFER_SIZE];\
    snprintf(szLogBuffer, sizeof(szLogBuffer)-1, "[%s][%s][%d]:"fmt, \
    share::sg_log_id_text[loglevel], __FILE__, __LINE__, ## __VA_ARGS__);\
    share::ShareFileLog(pLog, szLogBuffer);}while(0);

#define RAW_FAST_LOG(logtype, loglevel, fmt, ...)  do{\
    share::SHARE_FILE_LOG_HANDLE pLog = share::ShareFileLogCheckLog(logtype,loglevel);\
    if (NULL == pLog) break;\
    char szLogBuffer[FAST_LOG_BUFFER_SIZE];\
    snprintf(szLogBuffer, sizeof(szLogBuffer)-1, fmt, ## __VA_ARGS__);\
    share::ShareFileLog(pLog, szLogBuffer);}while(0);

//////////////////////////////////////////////////////////////////////////
/// 本库预定义好的几个日志宏
#define SHARE_LOG_DEBUG(lpmsg) FLOG(sg_default_log_type_share, sg_n_debug, lpmsg)
#define SHARE_LOG_INFO(lpmsg) FLOG(sg_default_log_type_share, sg_n_info, lpmsg)
#define SHARE_LOG_WARN(lpmsg) FLOG(sg_default_log_type_share, sg_n_warn, lpmsg)
#define SHARE_LOG_ERROR(lpmsg) FLOG(sg_default_log_type_share, sg_n_error, lpmsg)
#define SHARE_LOG_FATAL(lpmsg) FLOG(sg_default_log_type_share, sg_n_fatal, lpmsg)

#define USER_LOG_DEBUG(lpmsg) FLOG(sg_default_log_type_user, sg_n_debug, lpmsg)
#define USER_LOG_INFO(lpmsg) FLOG(sg_default_log_type_user, sg_n_info, lpmsg)
#define USER_LOG_WARN(lpmsg) FLOG(sg_default_log_type_user, sg_n_warn, lpmsg)
#define USER_LOG_ERROR(lpmsg) FLOG(sg_default_log_type_user, sg_n_error, lpmsg)
#define USER_LOG_FATAL(lpmsg) FLOG(sg_default_log_type_user, sg_n_fatal, lpmsg)

#define SHARE_FAST_LOG_DEBUG(fmt, ...) FAST_FLOG(sg_default_log_type_share, sg_n_debug, fmt, ## __VA_ARGS__)
#define SHARE_FAST_LOG_INFO(fmt, ...) FAST_FLOG(sg_default_log_type_share, sg_n_info, fmt, ## __VA_ARGS__)
#define SHARE_FAST_LOG_WARN(fmt, ...) FAST_FLOG(sg_default_log_type_share, sg_n_warn, fmt, ## __VA_ARGS__)
#define SHARE_FAST_LOG_ERROR(fmt, ...) FAST_FLOG(sg_default_log_type_share, sg_n_error, fmt, ##__VA_ARGS__)
#define SHARE_FAST_LOG_FATAL(fmt, ...) FAST_FLOG(sg_default_log_type_share, sg_n_fatal, fmt, ##__VA_ARGS__)

#define USER_FAST_LOG_DEBUG(fmt, ...) FAST_FLOG(sg_default_log_type_user, sg_n_debug, fmt, ##__VA_ARGS__)
#define USER_FAST_LOG_INFO(fmt, ...) FAST_FLOG(sg_default_log_type_user, sg_n_info, fmt, ##__VA_ARGS__)
#define USER_FAST_LOG_WARN(fmt, ...) FAST_FLOG(sg_default_log_type_user, sg_n_warn, fmt, ##__VA_ARGS__)
#define USER_FAST_LOG_ERROR(fmt, ...) FAST_FLOG(sg_default_log_type_user, sg_n_error, fmt, ##__VA_ARGS__)
#define USER_FAST_LOG_FATAL(fmt, ...) FAST_FLOG(sg_default_log_type_user, sg_n_fatal, fmt, ##__VA_ARGS__)


#define MEMORY_FAST_LOG(fmt, ...) FAST_FLOG(sg_default_log_type_memory, sg_n_info, fmt, ##__VA_ARGS__)

#define SQL_LOG_DEBUG(lpmsg)        FLOG(sg_default_log_type_sql, sg_n_debug, lpmsg)
#define SQL_LOG_INFO(lpmsg)        FLOG(sg_default_log_type_sql, sg_n_info, lpmsg)
#define SQL_LOG_WARN(lpmsg)        FLOG(sg_default_log_type_sql, sg_n_warn, lpmsg)
#define SQL_LOG_ERROR(lpmsg)        FLOG(sg_default_log_type_sql, sg_n_error, lpmsg)
#define SQL_LOG_FATAL(lpmsg)        FLOG(sg_default_log_type_sql, sg_n_fatal, lpmsg)
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// 用户可以在这里增加自己定义的日志类型。增加的类型，必须在配置文件 share_log_config.xml 里有配置

//////////////////////////////////////////////////////////////////////////


#endif //__SHARE_FILE_LOG_H__

