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
    std::ofstream   m_logFileStream;          //log�ļ���
    std::string     m_logFilePath;          //log�ļ�·��
    UINT64          m_generateTime;         //log�������ɵ�ʱ��
    //std::map<int,int>  m_level_value_map;   //��Ӧ����־�ļ��ȼ��Ƿ���Ҫд�ļ� 
};

#endif