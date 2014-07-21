#ifndef __SH_LOG_OBJECT_H__
#define __SH_LOG_OBJECT_H__

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

class Csh_log_object
{
public:
    Csh_log_object(const std::string& logFilePath);
    ~Csh_log_object();
    void RecordLog(const char* lpcszLog);
protected:
private:
    std::ofstream   m_logFileStream;          //log文件流
    std::string     m_logFilePath;          //log文件路径
    //std::map<int,int>  m_level_value_map;   //对应的日志文件等级是否需要写文件 
};

#endif