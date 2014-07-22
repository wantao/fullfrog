#ifndef __LOG_CONFIG_MGR_H
#define __LOG_CONFIG_MGR_H
#include "sh_log_object.h"
#include "sh_include.h"
#include "sh_common.h"

namespace np_log_config_mgr{

    struct logConfigStruct 
    {
        logConfigStruct():name(""),folder_name(""),log_head(""),log_tail("") {}
        std::string name;   //日志种类
        std::string folder_name;    //日志所在目录名
        std::string log_head;   //日志前缀
        std::string log_tail;   //日志后缀
    };

    struct logTypeStruct
    {
        logTypeStruct():type(0),isRecord(false) {}
        unsigned int type;   //日志类型
        bool    isRecord;   //是否记录该类型日志
    };

    typedef std::map<unsigned int,Csh_log_object*> mapLogObject; //<日志种类-》日志对象指针>

    typedef std::map<unsigned int,logConfigStruct> mapLogConfigStruct;//<日志种类-》日志配置>

    typedef std::map<unsigned int,logTypeStruct> mapLogTypeStruct;//<日志类型-》日志类型结构>

    typedef std::map<unsigned int,mapLogTypeStruct> mapNameLogTypeStruct;//<日志种类-》日志类型结构>

    class Clog_config_mgr:public share::CSingleton<Clog_config_mgr>
    {
    public:
        Clog_config_mgr();
        ~Clog_config_mgr();
        void Init();
        bool createDir(const std::string& folderName);
        bool createFile(const std::string& logFilePath);
        std::string getCurDateTime(const char* format);
        std::string getLogFilePath(const std::string& folderName,const std::string& logHead,const std::string& logTail);
        mapLogObject& getLogObjects();
        const mapLogConfigStruct& getLogConfigs();
        const mapNameLogTypeStruct& getNameLogTypes();
        bool isOnSameDay(UINT64 pre_t,UINT64 now_t);
        Csh_log_object* generateLogObjectByPath(std::string& logFilePath);
    protected:
    private:
         mapLogObject m_LogObjects;
         mapLogConfigStruct m_LogConfigs;
         mapNameLogTypeStruct m_NameLogTypes;
         
        void _loadConfig();
    };

};


#endif