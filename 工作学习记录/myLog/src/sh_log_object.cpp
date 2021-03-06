#include "sh_log_object.h"

Csh_log_object::Csh_log_object(const std::string& logFilePath)
{
    m_logFilePath = logFilePath;
    setlocale(LC_ALL,"Chinese-simplified");// 设置中文环境 
    m_logFileStream.open(m_logFilePath.c_str(),std::ios::app);
    setlocale(LC_ALL,"C");// 还原
    if (!m_logFileStream.is_open()) {
        std::cerr<<"open file "<<logFilePath<<" failure"<<std::endl;
        exit(1);
    }
    m_generateTime = (UINT64)time(NULL);
}

Csh_log_object::~Csh_log_object()
{
    if (m_logFileStream.is_open()) {
        m_logFileStream.close();    
    }
}

void Csh_log_object::RecordLog(const char* lpcszLog)
{
    m_logFileStream << lpcszLog << std::endl;
}

UINT64 Csh_log_object::GetGenerateTime()
{
    return m_generateTime;
}