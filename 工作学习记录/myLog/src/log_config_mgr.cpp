#include "log_config_mgr.h"
#include <iostream>
#include <fstream>
#include "sh_filelog.h"
#include "MarkupSTL.h"


#if (defined(WIN32) || defined(WIN64))
#include <direct.h>
#endif

namespace np_log_config_mgr {

    Clog_config_mgr::Clog_config_mgr()
    {

    }
    Clog_config_mgr::~Clog_config_mgr()
    {
        if (m_LogObjects.size() > 0) {
            mapLogObject::iterator it_logObject = m_LogObjects.begin();
            for (; it_logObject != m_LogObjects.end(); it_logObject++) {
                if (it_logObject->second != NULL) {
                    delete it_logObject->second;
                    it_logObject->second = NULL;
                }
            }
            m_LogObjects.clear();
        }
    }

    void Clog_config_mgr::Init()
    {
        _loadConfig();
    }

    void Clog_config_mgr::_loadConfig()
    {
        char currentDir[255];
        GetCurrentDirectory(255,currentDir);  //得到当前工作路径

        std::string szPath;
        szPath = currentDir;
        szPath += "/config/log_config.xml";

        CMarkupSTL oxml;
        if (!oxml.Load(szPath.c_str()) ){
            std::cerr<<"cannot load "<<szPath<<std::endl;
            assert(false);
            return;
        }

        if (!oxml.FindElem("root") ){
            std::cerr<<"can not find root node "<<szPath<<std::endl;
            assert(false);
            return;
        }

        if (!oxml.IntoElem()){
            std::cerr<<"can not into root node "<<szPath<<std::endl;
            assert(false);
            return;
        }

        if (!oxml.FindElem("logtype") ){
            std::cerr<<"can not find logtype node "<<szPath<<std::endl;
            assert(false);
            return;
        }

        if (!oxml.IntoElem()){
            std::cerr<<"can not into logtype node "<<szPath<<std::endl;
            assert(false);
            return;
        }

        while (oxml.FindElem("type")) {
            int logId = atoi(oxml.GetAttrib("id").c_str());
            logConfigStruct logConfigStructData;
            logConfigStructData.name = oxml.GetAttrib("name");
            logConfigStructData.folder_name = oxml.GetAttrib("folder_name");
            logConfigStructData.log_head = oxml.GetAttrib("log_file_head");
            logConfigStructData.log_tail = oxml.GetAttrib("log_file_trail");
            m_LogConfigs[logId] = logConfigStructData;
            
            if (!oxml.IntoElem()){
                std::cerr<<"can not into type node "<<szPath<<std::endl;
                assert(false);
                return;
            }

            mapLogTypeStruct mapLogTypeStructTmp;

            while (oxml.FindElem("item")) {
                logTypeStruct logTypeStructData;
                std::string& logType = oxml.GetAttrib("key");
                transform(logType.begin(),logType.end(),logType.begin(),tolower);
                if (logType == "debug") {
                    logTypeStructData.type = sg_n_debug;    
                } else if (logType == "info") {
                    logTypeStructData.type = sg_n_info;
                } else if (logType == "warn") {
                    logTypeStructData.type = sg_n_warn;
                } else if (logType == "error") {
                    logTypeStructData.type = sg_n_error;
                } else if (logType == "fatal") {
                    logTypeStructData.type = sg_n_fatal;
                }
                std::string& valueType = oxml.GetAttrib("value");
                transform(valueType.begin(),valueType.end(),valueType.begin(),tolower);
                if (valueType == "yes") {
                    logTypeStructData.isRecord = true;
                }
                mapLogTypeStructTmp[logTypeStructData.type] = logTypeStructData;
            }

            if (mapLogTypeStructTmp.size() > 0) {
                m_NameLogTypes[logId] = mapLogTypeStructTmp;
            }

            oxml.OutOfElem();
            //创建日志目录
            if (!createDir(logConfigStructData.folder_name)) {
                std::cerr<<"createDir failure"<<std::endl;
                assert(false);
            }
            //获取日志文件路径
            std::string logFilePath = getLogFilePath(logConfigStructData.folder_name,logConfigStructData.log_head,logConfigStructData.log_tail);
            //创建日志文件
            if (!createFile(logFilePath)) {
                std::cerr<<"createFile failure"<<std::endl;
                assert(false);    
            }
            Csh_log_object* pLogObject = generateLogObjectByPath(logFilePath);
            if (pLogObject == NULL) {
                std::cerr<<"new Csh_log_object error"<<std::endl;
                assert(false);
            }
            m_LogObjects[logId] = pLogObject;
        }
        oxml.OutOfElem();
        oxml.OutOfElem();
    }

    bool Clog_config_mgr::createDir(const std::string& folderName)
    {
        if (folderName.size() <= 0) {
            std::cerr<<"folderName is Null in createDir"<<std::endl;
            return false;
        }
        char currentDir[255];
        GetCurrentDirectory(255,currentDir);  //得到当前工作路径
        std::string fullPath = currentDir;
        if (fullPath.size() <= 0) {
            std::cerr<<"GetCurrentDirectory failure in createDir"<<std::endl;
            return false;
        }
        fullPath += "\\" + folderName;
        //目录是否存在
        if(access(fullPath.c_str(),0) == -1) {//不存在
            if (_mkdir(fullPath.c_str()) == 0) {
                return true;
            } 
            std::cerr<<"createDir failure errno:"<<errno<<" strerror:"<<strerror(errno)<<std::endl;
            return false;
        } 
        return true;
    }

    std::string Clog_config_mgr::getLogFilePath(const std::string& folderName,const std::string& logHead,const std::string& logTail)
    {
        if (folderName.size() <= 0) {
            std::cerr<<"folderName is Null in getLogFilePath"<<std::endl;
            assert(false);
        }
        if (logHead.size() <= 0) {
            std::cerr<<"logHead is Null in getLogFilePath"<<std::endl;
            assert(false);
        }
        if (logTail.size() <= 0) {
            std::cerr<<"logTail is Null in getLogFilePath"<<std::endl;
            assert(false);
        }
        char currentDir[255];
        GetCurrentDirectory(255,currentDir);  //得到当前工作路径
        std::string fullPath = currentDir;
        if (fullPath.size() <= 0) {
            std::cerr<<"GetCurrentDirectory failure in getLogFilePath"<<std::endl;
            assert(false);
        }
        fullPath += "\\" + folderName; 
        fullPath += "\\";
        std::string fileName = logHead + "_";
        fileName += getCurDateTime("%Y-%m-%d") + ".log";
        fullPath += fileName;
        return fullPath;
    }

    bool Clog_config_mgr::createFile(const std::string& logFilePath)
    {
        if (logFilePath.size() <= 0) {
            std::cerr<<"logFilePath is Null in createFile"<<std::endl;
            assert(false);     
        }
        std::ofstream of;
        of.open(logFilePath.c_str());
        of.close();
        return true;    
    }

    std::string Clog_config_mgr::getCurDateTime(const char* format)
    {
        time_t ttime = time(NULL);
        struct tm* datetime = localtime(&ttime);
        char datetime_str[64];
        strftime(datetime_str, sizeof(datetime_str), format, datetime);
        return datetime_str;
    }

    mapLogObject& Clog_config_mgr::getLogObjects()
    {
        return m_LogObjects;
    }

    const mapLogConfigStruct& Clog_config_mgr::getLogConfigs()
    {
        return m_LogConfigs;
    }

    const mapNameLogTypeStruct& Clog_config_mgr::getNameLogTypes()
    {
        return m_NameLogTypes;
    }

    bool Clog_config_mgr::isOnSameDay(UINT64 pre_t,UINT64 now_t) 
    {
        if (pre_t/86400 == now_t/86400) {
            return true;
        }
        return false;
    }

    Csh_log_object* Clog_config_mgr::generateLogObjectByPath(std::string& logFilePath)
    {
        Csh_log_object* pLogObject = new Csh_log_object(logFilePath);
        if (pLogObject == NULL) {
            std::cerr<<"new Csh_log_object error in generateLogObjectByPath"<<std::endl;
        }
        return pLogObject;
    }
};

