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
* 将一个数字转化为字符串
* @param pBuf : 转化后的字符存储空间
* @param buflen : 字符存储空间的最大长度
* @param dwNum : 将被转化的数字
* @return 转化后字符串使用的空间长度
*/
template <UINT32 bufLen>
inline INT  i2a(char (&buf)[bufLen],INT nNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, "%d", nNum);
}
std::string i2a(INT nNum);

/**
* @brief
* 将无符号整型转换为字符串
* @param pBuf : 转化后的字符存储空间
* @param buflen : 字符存储空间的最大长度
* @param dwNum : 将被转化的数字
* @return 转化后字符串使用的空间长度
*/
template <UINT32 bufLen>
inline INT  u2a(char (&buf)[bufLen],UINT dwNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, "%u", dwNum);
}
std::string u2a(UINT dwNum);

/**
* @brief
* 将64位有符号整型转换为字符串
* @param pBuf : 转化后的字符存储空间
* @param buflen : 字符存储空间的最大长度
* @param dwNum : 将被转化的数字
* @return 转化后字符串使用的空间长度
*/
template <UINT32 bufLen>
inline INT  i2a64(char (&buf)[bufLen], INT64 qNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, FORMAT_I64, qNum);
}
std::string i2a64(INT64 qNum);

/**
* @brief
* 将有64位无符号整型转换为字符串
* @param pBuf : 转化后的字符存储空间
* @param buflen : 字符存储空间的最大长度
* @param dwNum : 将被转化的数字
* @return 转化后字符串使用的空间长度
*/
template <UINT32 bufLen>
inline INT  u2a64(char (&buf)[bufLen], UINT64 dqNum)
{
    return buf[bufLen-1]='\0', snprintf(buf, bufLen-1, FORMAT_U64, dqNum);
}
std::string u2a64(UINT64 dqNum);

/**
* @brief
* 将字符串转化为浮点数
* @param nptr : 将被转化的以0结尾的字符串
* @param endptr : [输出参数]若不为NULL，则遇到无法转化的字符从这里返回其指针
* @return 获取的浮点数
*/
inline double str2d(const char *nptr, char **endptr)
{
    assert(nptr && endptr);
    return ::strtod(nptr, endptr);
}

/**
* @brief
* 将字符串转换为32位有符号数字
* @param pStr : 要转换的字符串
* @return 转化数字的值
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
* 将字符串转换为32位有符号数字
* @param pStr : 要转换的字符串
* @return 转化数字的值
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
* 将字符串转换为64位有符号数字
* @param pStr : 要转换的字符串
* @return 转化数字的值
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
* 将字符串转换为32位无符号数字
* @param pStr : 要转换的字符串
* @return 转化数字的值，如果pStr=NULL会抛出异常
*/
UINT32 a2u(const char* pStr);
UINT32 a2u(const std::string& s);

/**
* @brief
* 将字符串转换为64位无符号数字
* @param pStr : 要转换的字符串
* @return 转化数字的值，如果pStr=NULL会抛出异常
*/
UINT64 a2u64(const char* pStr); 
UINT64 a2u64(const std::string& s);

/**
* @brief
* 将二进制Buffer转换为字符串,
* @param pBuf    二进制Buffer指针
* @param bufLen  二进制Buffer长度
* @param pSplitter 输出的二进制数据间隔符
* @param lineLen 一行的长度
* @return void
*/
std::string s2hex(const unsigned char *pBuf, UINT32 bufLen, const char *pSplitter = "", INT32 lineLen = -1);

/**
* @brief
* 将一个整数转换为十六进制字符串,
* @param dwNum    二进制Buffer指针
* @return string 转换后的结果
*/
std::string i2hex(INT num);

/**
* @brief
* Split a string by whitespace ( ' ' || '\n' ||  '\t' ||  '\r'， '\0')
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
//stricmp()函数，在linux下用strcasecmp()函数替换。
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
* time_t 值转换 字符串时间xxxx-xx-xx xx:xx:xx
*/
std::string time2str(time_t t);

/**
* @brief
* time_t 值转换 字符串时间xxxx-xx-xx
*/
std::string time2datestr(time_t t);

/**
* @brief
* 字符串时间xxxx-xx-xx xx:xx:xx 转换 为time_t 值
*/
time_t str2time(const std::string& strDT);

/**
* @brief
* 函数返回本地日历时间. 可重入线程安全
*/
struct ::tm * localtime_safe(struct tm *result, const time_t *timep);

//////////////////////////////////////////////////////////////////////////
//// Directory
//////////////////////////////////////////////////////////////////////////
/**
* @brief
* 列举目标目录下的所有文件名称,
* @param files [out] : 转化后的文件集合
* @param pszDir : 目标目录
* @param pszFilter : 文件后缀通配符号
* @param bIncludeChildDir 是否包括子目录
* @return 返回文件的数量
*/
size_t EnumFiles(std::vector<std::string>&files, const char* pszDir, const char* pszFilter, bool bIncludeChildDir=false);

/**
* @brief
* 判断当前目录是否存在
* @return true/false
*/
bool IsDirectoryExist(const char* lpdirectory);

/**
* @brief
* 获得当前目录
* @note 返回的结果存放到 输出参数 lpdir
* @return 能获得目录返回true，否则返回false
*/
bool GetCurrentDirectory(char* lpdir, const int size);

/**
* @brief
* 创建目录
* @return 成功创建返回ture，否则返回false
*/
bool CreateDirectory(const char* lpdir);

/**
* @brief
* 获得当前执行文件的路径
* @return 返回路径
*/
const char* GetCurrentExeDirectory();


/**
* @brief
* 从文件路径获得文件名称
* @return 返回文件名称
*/
std::string GetFileNameByFilePath(const char* pFilePath);

/**
* @brief
* 从文件路径获得文件名称
* @return 返回文件名称
*/

/**
* @brief
*  获得当前执行文件的名称
* @return 返回文件名称
*/
std::string GetExecuteFile();

/**
* @brief
* 获得当前执行文件的路径
* @return 返回路径
*/
std::string GetCurrentExeFullPath();

/**
* @brief
* 获得一个crc32编码
* @return crc32编码
*/
UINT32 GetCrc32Code(UINT32 crc, unsigned char *buf, size_t len);


/**
* 函数介绍：得到闭区间[nMin，nMax]上的随机整数
* 返回值  ：闭区间[nMin，nMax]上的随机整数, 如果a>b, 返回b
*/
INT32 RandInt(INT32 a, INT32 b);


//////////////////////////////////////////////////////////////////////////
//// special id format 
//////////////////////////////////////////////////////////////////////////
// 字符串形式的id 格式类型
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
* 字符id 转 32 位整数. 
* @param strID 一个字符串id 有以下取值格式:
* b表示一个字节，w表示2个字节，d表示4个字节
* 格式1      "w-w"   G_STRID_FORMAT_WW
* 格式2      "b-b-w"  G_STRID_FORMAT_BBW
* 格式3      "b-b-b-b"  G_STRID_FORMAT_BBBB
* @param strFormat 上面3种格式
* @return 返回一个64位的整数
*/
UINT32 StrID2UInt32(const std::string& strID, const STR_ID_FORMAT_TYPE strFormat);

/**
* 64 位整数 转 字符id . 
* @param dwID 32位的无符号整数:
* b表示一个字节，w表示2个字节，d表示4个字节
* 格式1      "w-w"   G_STRID_FORMAT_WW
* 格式2      "b-b-w"  G_STRID_FORMAT_BBW
* 格式3      "b-b-b-b"  G_STRID_FORMAT_BBBB
* @param strFormat 上面3种格式
* @return 返回一个字符串ID
*/
std::string UInt322StrID(UINT32 dwID, const STR_ID_FORMAT_TYPE strFormat);

/**
* 字符id 转 64 位整数. 
* @param strID 一个字符串id 有以下取值格式:
* b表示一个字节，w表示2个字节，d表示4个字节
* 格式1      "d-d"   G_STRID_FORMAT_DD
* 格式2      "w-w-d"  G_STRID_FORMAT_WWD
* 格式3      "b-b-w-d"  G_STRID_FORMAT_BBWD
* 格式4      "w-w-w-w"   G_STRID_FORMAT_WWWW
* 格式5      "b-b-w-w-w"  G_STRID_FORMAT_BBWWW
* 格式6      "b-b-b-b-w-w"  G_STRID_FORMAT_BBBBWW
* @param strFormat 上面6种格式
* @return 返回一个64位的整数
*/
UINT64 StrID2UInt64(const std::string& strID, const STR_ID_FORMAT_TYPE strFormat);

/**
* 64 位整数 转 字符id . 
* @param qwID 64位的无符号整数:
* b表示一个字节，w表示2个字节，d表示4个字节
* 格式1      "d-d"   G_STRID_FORMAT_DD
* 格式2      "w-w-d"  G_STRID_FORMAT_WWD
* 格式3      "b-b-w-d"  G_STRID_FORMAT_BBWD
* 格式4      "w-w-w-w"   G_STRID_FORMAT_WWWW
* 格式5      "b-b-w-w-w"  G_STRID_FORMAT_BBWWW
* 格式6      "b-b-b-b-w-w"  G_STRID_FORMAT_BBBBWW
* @param strFormat 上面6种格式
* @return 返回一个字符串ID
*/
std::string UInt642StrID(UINT64 qwID, const STR_ID_FORMAT_TYPE strFormat);





//////////////////////////////////////////////////////////////////////////
//// 字符集转换
std::wstring ANSI2Unicode( const char* str);

std::string Unicode2ANSI( const wchar_t* str );

std::wstring UTF82Unicode( const char* str );

std::string Unicode2UTF8( const wchar_t* str );

std::string ANSIToUTF8(const char* str);

std::string UTF8ToANSI(const char* str);
//////////////////////////////////////////////////////////////////////////


// 辅助类
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
* 单件类型
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


// 检查模块运行时间。毫秒
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

