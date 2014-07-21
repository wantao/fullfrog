#ifndef __SHARE_FILE_LOG_H__
#define __SHARE_FILE_LOG_H__

#include <string>
#include <sstream>


//////////////////////////////////////////////////////////////////////////
/// ������������ֺ궨�壬����ı���Ҫ���±����
//////////////////////////////////////////////////////////////////////////
// ��־�ȼ�����
#define  sg_debug       "debug"
#define  sg_info        "info"
#define  sg_warn        "warn"
#define  sg_error       "error"
#define  sg_fatal       "fatal"

//ÿ����־�ȼ����ƶ�Ӧ��idֵ
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
//// log, �򵥵��ı���־�����ݿ���־
//////////////////////////////////////////////////////////////////////////

/* ������һ���������ӡ�
<root>
    <!--
    ��־���Ͷ�Ӧ����־Ŀ¼����־�ļ�����ͷ��β
    ÿ����־��Ӧ�ļ�¼����
    ��־����id����ð��մ�С������������[0-65535]���������ظ�
    ��־����name Ҳ�������ظ�
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

// ����Ƿ�д������͡��ȼ�����־
// �����Ҫд���򷵻����ָ�����log����ľ��
extern SHARE_FILE_LOG_HANDLE ShareFileLogCheckLog(const unsigned int nLogTypeIndex, const int nLogLevel);

//д�ı���־
extern void ShareFileLog(SHARE_FILE_LOG_HANDLE hLog, const char* lpcszLog);

//���¼����ı���־�ȼ�����
extern void ReloadShareFileLogLevel();

}

//ϵͳ��ռĬ�ϵ���־����
#define  sg_default_log_type_share  0
#define  sg_default_log_type_user   1
#define  sg_default_log_type_memory 2
#define  sg_default_log_type_sql    3


//FAST_FLOGʹ�á�����һ����־������ֽڳ��ȣ� ���ֵ���Ը���ʵ������޸�
#define  FAST_LOG_BUFFER_SIZE 1024
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// ϵͳ���� FLOG��һ�㲻���޸ġ���ʹ�޸ģ�ҲӦ�ñ��ֺ�Ĳ��������Լ�����һ��
//////////////////////////////////////////////////////////////////////////
#define  FLOG(logtype, loglevel, lpmsg) do{\
    share::SHARE_FILE_LOG_HANDLE pLog = share::ShareFileLogCheckLog(logtype,loglevel);\
    if (NULL == pLog) break;\
    std::ostringstream oss; \
    oss<<"["<<share::sg_log_id_text[loglevel]<<"]"\
    <<"["<<__FILE__<<"]"<<"["<<__LINE__<<"]:"<<lpmsg;\
    share::ShareFileLog(pLog, oss.str().c_str());}while(0);

//////////////////////////////////////////////////////////////////////////
/// ϵͳ���� FLOG��һ�㲻���޸ġ������޸ģ���Ӧ�ñ��ֺ�Ĳ��������Լ�����һ��
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
/// ����Ԥ����õļ�����־��
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
/// �û����������������Լ��������־���͡����ӵ����ͣ������������ļ� share_log_config.xml ��������

//////////////////////////////////////////////////////////////////////////


#endif //__SHARE_FILE_LOG_H__

