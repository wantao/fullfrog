#ifndef __SHARE_COMMON_H__
#define __SHARE_COMMON_H__

#include "sh_include.h"
#include "sh_define.h"
#include "sh_type.h"

namespace share
{

template<bool> struct STATIC_CHECK;
template<>     struct STATIC_CHECK<true>{};
// eg
// static STATIC_CHECK< protoc::global_var::PLAYER_EXTEND_DATA_MAX_SIZE < BUILD_BLOB_DATA_MAX_SIZE >   __static_check_1;

/// fromat string
template <UINT32 bufLen>
inline INT SafeSprintf(char (&Destination)[bufLen], const char *format, ...)
{
    va_list args;
    va_start(args,format);
#if (defined(WIN32) || defined(WIN64))
    INT n = _vsnprintf(Destination, sizeof(Destination)-1, format, args);
#else
    INT n = vsnprintf(Destination, sizeof(Destination)-1, format, args);
#endif
    va_end(args);
    Destination[sizeof(Destination)-1] = '\0';
    return n;
}

/**
* @brief
* ��һ������ת��Ϊ�ַ���
* @param pBuf : ת������ַ��洢�ռ�
* @param buflen : �ַ��洢�ռ����󳤶�
* @param dwNum : ����ת��������
* @return ת�����ַ���ʹ�õĿռ䳤��
*/
template <UINT32 bufLen>
inline INT  i2a(char (&buf)[bufLen],INT nNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, "%d", nNum);
}
std::string i2a(INT nNum);

/**
* @brief
* ���޷�������ת��Ϊ�ַ���
* @param pBuf : ת������ַ��洢�ռ�
* @param buflen : �ַ��洢�ռ����󳤶�
* @param dwNum : ����ת��������
* @return ת�����ַ���ʹ�õĿռ䳤��
*/
template <UINT32 bufLen>
inline INT  u2a(char (&buf)[bufLen],UINT dwNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, "%u", dwNum);
}
std::string u2a(UINT dwNum);

/**
* @brief
* ��64λ�з�������ת��Ϊ�ַ���
* @param pBuf : ת������ַ��洢�ռ�
* @param buflen : �ַ��洢�ռ����󳤶�
* @param dwNum : ����ת��������
* @return ת�����ַ���ʹ�õĿռ䳤��
*/
template <UINT32 bufLen>
inline INT  i2a64(char (&buf)[bufLen], INT64 qNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, FORMAT_I64, qNum);
}
std::string i2a64(INT64 qNum);

/**
* @brief
* ����64λ�޷�������ת��Ϊ�ַ���
* @param pBuf : ת������ַ��洢�ռ�
* @param buflen : �ַ��洢�ռ����󳤶�
* @param dwNum : ����ת��������
* @return ת�����ַ���ʹ�õĿռ䳤��
*/
template <UINT32 bufLen>
inline INT  u2a64(char (&buf)[bufLen], UINT64 dqNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, FORMAT_U64, dqNum);
}
std::string u2a64(UINT64 dqNum);

/**
* @brief
* ���ַ���ת��Ϊ������
* @param nptr : ����ת������0��β���ַ���
* @param endptr : [�������]����ΪNULL���������޷�ת�����ַ������ﷵ����ָ��
* @return ��ȡ�ĸ�����
*/
inline double str2d(const char *nptr, char **endptr)
{
    assert(nptr && endptr);
    return ::strtod(nptr, endptr);
}

/**
* @brief
* ���ַ���ת��Ϊ32λ�з�������
* @param pStr : Ҫת�����ַ���
* @return ת�����ֵ�ֵ
*/
inline INT a2i(const char* pStr)
{
    assert(pStr);
    return NULL == pStr ? 0 : atoi(pStr);
}
inline INT a2i(const std::string& s)
{
    return atoi(s.c_str());
}

/**
* @brief
* ���ַ���ת��Ϊ32λ�з�������
* @param pStr : Ҫת�����ַ���
* @return ת�����ֵ�ֵ
*/
inline LONG a2l(const char* pStr)
{
    assert(pStr);
    return NULL==pStr ? 0 : atol(pStr);
}
inline LONG a2l(const std::string& s)
{
    return atol(s.c_str());
}

/**
* @brief
* ���ַ���ת��Ϊ64λ�з�������
* @param pStr : Ҫת�����ַ���
* @return ת�����ֵ�ֵ
*/
inline INT64 a2i64(const char* pStr)
{
    assert(pStr);
#if (defined(WIN32) || defined(WIN64))
    return NULL==pStr ? 0 : _atoi64(pStr);
#else
    return NULL==pStr ? 0 : atoll(pStr);
#endif
}
inline INT64 a2i64(const std::string& s)
{
#if (defined(WIN32) || defined(WIN64))
    return _atoi64(s.c_str());
#else
    return atoll(s.c_str());
#endif
}

/**
* @brief
* ���ַ���ת��Ϊ32λ�޷�������
* @param pStr : Ҫת�����ַ���
* @return ת�����ֵ�ֵ�����pStr=NULL���׳��쳣
*/
UINT32 a2u(const char* pStr);
UINT32 a2u(const std::string& s);

/**
* @brief
* ���ַ���ת��Ϊ64λ�޷�������
* @param pStr : Ҫת�����ַ���
* @return ת�����ֵ�ֵ�����pStr=NULL���׳��쳣
*/
UINT64 a2u64(const char* pStr); 
UINT64 a2u64(const std::string& s);

/**
* @brief
* ��������Bufferת��Ϊ�ַ���,
* @param pBuf    ������Bufferָ��
* @param bufLen  ������Buffer����
* @param pSplitter ����Ķ��������ݼ����
* @param lineLen һ�еĳ���
* @return void
*/
std::string s2hex(const unsigned char *pBuf, UINT32 bufLen, const char *pSplitter = "", INT32 lineLen = -1);

/**
* @brief
* ��һ������ת��Ϊʮ�������ַ���,
* @param dwNum    ������Bufferָ��
* @return string ת����Ľ��
*/
std::string i2hex(INT num);

/**
* @brief
* Split a string by whitespace ( ' ' || '\n' ||  '\t' ||  '\r'�� '\0')
* @param[out] v a vector of strings, each of which is a substring of the string
*/
size_t split(std::vector<std::string>& v, const std::string& s);


/**
* @brief
* Split a string by a character
* @param[out] v a vector of strings, each of which is a substring of the string
*/
size_t split(std::vector<std::string>& v, const std::string& s, std::string::value_type separator);

/**
* @brief
* Split a string by another string
* @param[in] separator The string separator to Split the string on
* @param[out] v a vector of strings, each of which is a substring of the string
*/
size_t split(std::vector<std::string>& v, const std::string& s, std::string separator);

/**
* @brief
* Convert the string to lowercase
* return self
*/
std::string& lower(std::string& s);

/**
* @brief
* Convert the string to uppercase
* return self
*/
std::string& upper(std::string& s);

/**
* @brief
* Trim the string
*/
char* trim(char* src);

/**
* @brief
* Trim the string and copy the result to des
*/
void copytrim(std::string& des, const std::string& src);

//////////////////////////////////////////////////////////////////////////
//stricmp()��������linux����strcasecmp()�����滻��
inline INT stricmp(const char *s1, const char *s2)
{
#if (defined(WIN32) || defined(WIN64))
    return ::stricmp(s1, s2);
#else
    return strcasecmp(s1, s2);
#endif
}

/**
* @brief
* time_t ֵת�� �ַ���ʱ��xxxx-xx-xx xx:xx:xx
*/
std::string time2str(time_t t);

/**
* @brief
* time_t ֵת�� �ַ���ʱ��xxxx-xx-xx
*/
std::string time2datestr(time_t t);

/**
* @brief
* �ַ���ʱ��xxxx-xx-xx xx:xx:xx ת�� Ϊtime_t ֵ
*/
time_t str2time(const std::string& strDT);

/**
* @brief
* �������ر�������ʱ��. �������̰߳�ȫ
*/
struct ::tm * localtime_safe(struct tm *result, const time_t *timep);

//////////////////////////////////////////////////////////////////////////
//// Directory
//////////////////////////////////////////////////////////////////////////
/**
* @brief
* �о�Ŀ��Ŀ¼�µ������ļ�����,
* @param files [out] : ת������ļ�����
* @param pszDir : Ŀ��Ŀ¼
* @param pszFilter : �ļ���׺ͨ�����
* @param bIncludeChildDir �Ƿ������Ŀ¼
* @return �����ļ�������
*/
size_t EnumFiles(std::vector<std::string>&files, const char* pszDir, const char* pszFilter, bool bIncludeChildDir=false);

/**
* @brief
* �жϵ�ǰĿ¼�Ƿ����
* @return true/false
*/
bool IsDirectoryExist(const char* lpdirectory);

/**
* @brief
* ��õ�ǰĿ¼
* @note ���صĽ����ŵ� ������� lpdir
* @return �ܻ��Ŀ¼����true�����򷵻�false
*/
bool GetCurrentDirectory(char* lpdir, const int size);

/**
* @brief
* ����Ŀ¼
* @return �ɹ���������ture�����򷵻�false
*/
bool CreateDirectory(const char* lpdir);

/**
* @brief
* ��õ�ǰִ���ļ���·��
* @return ����·��
*/
const char* GetCurrentExeDirectory();


/**
* @brief
* ���ļ�·������ļ�����
* @return �����ļ�����
*/
std::string GetFileNameByFilePath(const char* pFilePath);

/**
* @brief
* ���ļ�·������ļ�����
* @return �����ļ�����
*/

/**
* @brief
*  ��õ�ǰִ���ļ�������
* @return �����ļ�����
*/
std::string GetExecuteFile();

/**
* @brief
* ��õ�ǰִ���ļ���·��
* @return ����·��
*/
std::string GetCurrentExeFullPath();

/**
* @brief
* ���һ��crc32����
* @return crc32����
*/
UINT32 GetCrc32Code(UINT32 crc, unsigned char *buf, size_t len);


/**
* �������ܣ��õ�������[nMin��nMax]�ϵ��������
* ����ֵ  ��������[nMin��nMax]�ϵ��������, ���a>b, ����b
*/
INT32 RandInt(INT32 a, INT32 b);


//////////////////////////////////////////////////////////////////////////
//// special id format 
//////////////////////////////////////////////////////////////////////////
// �ַ�����ʽ��id ��ʽ����
enum STR_ID_FORMAT_TYPE
{
    G_STRID_FORMAT_DD       =1,   //"d_d";
    G_STRID_FORMAT_WWD      =2,   //"w-w-d"
    G_STRID_FORMAT_BBWD     =3,   //"b-b-w-d"
    G_STRID_FORMAT_WWWW     =4,   //"w-w-w-w"
    G_STRID_FORMAT_BBWWW    =5,   //"b-b-w-w-w"
    G_STRID_FORMAT_BBBBWW   =6,   //"b-b-b-b-w-w"
    G_STRID_FORMAT_WW       =7,   //"w-w"
    G_STRID_FORMAT_BBW      =8,   //"b-b-w"
    G_STRID_FORMAT_BBBB     =9,   //"b-b-b-b"
};

/**
* �ַ�id ת 32 λ����. 
* @param strID һ���ַ���id ������ȡֵ��ʽ:
* b��ʾһ���ֽڣ�w��ʾ2���ֽڣ�d��ʾ4���ֽ�
* ��ʽ1      "w-w"   G_STRID_FORMAT_WW
* ��ʽ2      "b-b-w"  G_STRID_FORMAT_BBW
* ��ʽ3      "b-b-b-b"  G_STRID_FORMAT_BBBB
* @param strFormat ����3�ָ�ʽ
* @return ����һ��64λ������
*/
UINT32 StrID2UInt32(const std::string& strID, const STR_ID_FORMAT_TYPE strFormat);

/**
* 64 λ���� ת �ַ�id . 
* @param dwID 32λ���޷�������:
* b��ʾһ���ֽڣ�w��ʾ2���ֽڣ�d��ʾ4���ֽ�
* ��ʽ1      "w-w"   G_STRID_FORMAT_WW
* ��ʽ2      "b-b-w"  G_STRID_FORMAT_BBW
* ��ʽ3      "b-b-b-b"  G_STRID_FORMAT_BBBB
* @param strFormat ����3�ָ�ʽ
* @return ����һ���ַ���ID
*/
std::string UInt322StrID(UINT32 dwID, const STR_ID_FORMAT_TYPE strFormat);

/**
* �ַ�id ת 64 λ����. 
* @param strID һ���ַ���id ������ȡֵ��ʽ:
* b��ʾһ���ֽڣ�w��ʾ2���ֽڣ�d��ʾ4���ֽ�
* ��ʽ1      "d-d"   G_STRID_FORMAT_DD
* ��ʽ2      "w-w-d"  G_STRID_FORMAT_WWD
* ��ʽ3      "b-b-w-d"  G_STRID_FORMAT_BBWD
* ��ʽ4      "w-w-w-w"   G_STRID_FORMAT_WWWW
* ��ʽ5      "b-b-w-w-w"  G_STRID_FORMAT_BBWWW
* ��ʽ6      "b-b-b-b-w-w"  G_STRID_FORMAT_BBBBWW
* @param strFormat ����6�ָ�ʽ
* @return ����һ��64λ������
*/
UINT64 StrID2UInt64(const std::string& strID, const STR_ID_FORMAT_TYPE strFormat);

/**
* 64 λ���� ת �ַ�id . 
* @param qwID 64λ���޷�������:
* b��ʾһ���ֽڣ�w��ʾ2���ֽڣ�d��ʾ4���ֽ�
* ��ʽ1      "d-d"   G_STRID_FORMAT_DD
* ��ʽ2      "w-w-d"  G_STRID_FORMAT_WWD
* ��ʽ3      "b-b-w-d"  G_STRID_FORMAT_BBWD
* ��ʽ4      "w-w-w-w"   G_STRID_FORMAT_WWWW
* ��ʽ5      "b-b-w-w-w"  G_STRID_FORMAT_BBWWW
* ��ʽ6      "b-b-b-b-w-w"  G_STRID_FORMAT_BBBBWW
* @param strFormat ����6�ָ�ʽ
* @return ����һ���ַ���ID
*/
std::string UInt642StrID(UINT64 qwID, const STR_ID_FORMAT_TYPE strFormat);





//////////////////////////////////////////////////////////////////////////
//// �ַ���ת��
std::wstring ANSI2Unicode( const char* str);

std::string Unicode2ANSI( const wchar_t* str );

std::wstring UTF82Unicode( const char* str );

std::string Unicode2UTF8( const wchar_t* str );

std::string ANSIToUTF8(const char* str);

std::string UTF8ToANSI(const char* str);
//////////////////////////////////////////////////////////////////////////


// ������
//  (C) Copyright Beman Dawes 1999-2003. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/utility for documentation.
//  Private copy constructor and copy assignment ensure classes derived from
//  class noncopyable cannot be copied.
//  Contributed by Dave Abrahams
class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}
private:  // emphasize the following members are private
    noncopyable( const noncopyable& );
    const noncopyable& operator=( const noncopyable& );
};


/**
* @brief
* ��������
*/
template<class T>
class CSingleton : public noncopyable
{
public:
    static bool CreateInstance()
    {
        if (NULL == m_instance)
        {
            m_instance = new(std::nothrow)T();
            if (NULL == m_instance)
                return false;
        }
        return true;
    }

    inline static T& Instance()
    {
        return *m_instance;
    }

    inline static T& InstanceEx()
    {
        if (NULL == m_instance)
            m_instance = new T();
        return *m_instance;
    }

    static void DestroyInstance()
    {
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        if (m_instance)
        {
            delete m_instance;
            m_instance = 0;
        }
    }

protected:
    CSingleton(){}
    static T* m_instance;
};

template<class T> T* CSingleton<T>::m_instance = NULL;


// ���ģ������ʱ�䡣����
class CCheckRunTime : public noncopyable
{
public:
    CCheckRunTime(const char* pszModuleName, ULONG dwLimitTick);
    ~CCheckRunTime();

private:
    CCheckRunTime();

private:
    const char*     m_pszModuleName;
    ULONG          m_dwLimitTick;
    ULONG          m_dwBeginTick;
};


/// \brief A template for setting a flag on a variable as long as the
/// object that set it is in scope.  Flag resets when object goes
/// out of scope.  Works on anything that looks like bool.

template <class T = bool>
class AutoFlag
{
public:
    /// \brief Constructor: sets ref to true.
    AutoFlag(T& ref) :referent_(ref)
    {
        referent_ = true;
    }

    /// \brief Destructor: sets referent passed to ctor to false.
    ~AutoFlag()
    {
        referent_ = false;
    }

private:
    T& referent_;
};



}

#endif //__SHARE_COMMON_H__

