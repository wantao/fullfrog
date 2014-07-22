#ifndef __LOG_CONFIG_MGR_H
#define __LOG_CONFIG_MGR_H
#include "sh_log_object.h"
#include "sh_include.h"
#include "sh_common.h"

namespace np_log_config_mgr{

    struct logConfigStruct 
    {
        logConfigStruct():name(""),folder_name(""),log_head(""),log_tail("") {}
        std::string name;   //��־����
        std::string folder_name;    //��־����Ŀ¼��
        std::string log_head;   //��־ǰ׺
        std::string log_tail;   //��־��׺
    };

    struct logTypeStruct
    {
        logTypeStruct():type(0),isRecord(false) {}
        unsigned int type;   //��־����
        bool    isRecord;   //�Ƿ��¼��������־
    };

    typedef std::map<unsigned int,Csh_log_object*> mapLogObject; //<��־����-����־����ָ��>

    typedef std::map<unsigned int,logConfigStruct> mapLogConfigStruct;//<��־����-����־����>

    typedef std::map<unsigned int,logTypeStruct> mapLogTypeStruct;//<��־����-����־���ͽṹ>

    typedef std::map<unsigned int,mapLogTypeStruct> mapNameLogTypeStruct;//<��־����-����־���ͽṹ>

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