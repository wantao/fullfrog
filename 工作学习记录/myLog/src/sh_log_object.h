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
    std::ofstream   m_logFileStream;          //log�ļ���
    std::string     m_logFilePath;          //log�ļ�·��
    //std::map<int,int>  m_level_value_map;   //��Ӧ����־�ļ��ȼ��Ƿ���Ҫд�ļ� 
};

#endif