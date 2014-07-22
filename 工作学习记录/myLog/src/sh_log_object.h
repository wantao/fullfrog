#ifndef __SH_LOG_OBJECT_H__
#define __SH_LOG_OBJECT_H__

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "sh_type.h"

class Csh_log_object
{
public:
    Csh_log_object(const std::string& logFilePath);
    ~Csh_log_object();
    void RecordLog(const char* lpcszLog);
    UINT64 GetGenerateTime();
protected:
private:
    std::ofstream   m_logFileStream;          //log文件流
    std::string     m_logFilePath;          //log文件路径
    UINT64          m_generateTime;         //log对象生成的时间
    //std::map<int,int>  m_level_value_map;   //对应的日志文件等级是否需要写文件 
};

#endif