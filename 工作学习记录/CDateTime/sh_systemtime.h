#ifndef __SHARE_SYSTEM_TIME_H__
#define __SHARE_SYSTEM_TIME_H__

#include <iostream>
#include "sh_type.h"

#if (defined(WIN32) || defined(WIN64))
#include <windows.h>
#endif


using namespace std;

#if !(defined(WIN32) || defined(WIN64))
#include   <sys/times.h> 
#endif

namespace share
{

//////////////////////////////////////////////////////////////////////////
//// System Time
//////////////////////////////////////////////////////////////////////////
/**
* @defgroup grouptime 时间操作
* @{
*/
class CDateTime;

/**
* @brief 获取代表当前日期时间(调用此函数的此时此刻)的CDateTime
* @return 代表当前日期时间(调用此函数的此时此刻)的CDateTime
*/

CDateTime Now();

/**
* @brief 日期时间类,代表1970年午夜到2037年之间的某一个时间
*
*/
class  CDateTime
{
public:
    /**
    * @brief 构造一个CDateTime类,构造出来的时间为1970-1-1午夜
    */
    CDateTime(time_t t);


    /**
    * @brief 获取本类所代表的日期时间的time_t值
    * @return 返回的time_t值
    */
    time_t GetTimeValue() const;

    /**
    * @brief 设置本类所代表的日期时间
    * @param t 设置的日期时间
    * @return void
    */
    void SetTimeValue(time_t t);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的秒数
    * @param datetime 一个日期时间
    * @return 差距的秒数
    */
    INT64 operator - (const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的秒数
    * @param datetime 一个日期时间
    * @return 差距的秒数
    */
    INT64 DiffSecond(const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的分钟数,差距少于1分钟的不计算在内
    * @param datetime 一个日期时间
    * @return 差距的分钟数
    */
    INT64 DiffMinute(const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的小时数,差距少于1小时的不计算在内
    * @param datetime 一个日期时间
    * @return 差距的小时数
    */
    INT64 DiffHour(const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的天数,差距少于1天的不计算在内
    * @param datetime 一个日期时间
    * @return 差距的天数
    */
    INT64 DiffDay(const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的星期数,差距少于1星期的不计算在内
    * @param datetime 一个日期时间
    * @return 差距的星期数
    */
    INT64 DiffWeek(const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的月份,差距少于1个月的不计算在内
    * @param datetime 一个日期时间
    * @return 差距的月数
    */
    INT32 DiffMonth(const CDateTime &datetime);

    /**
    * @brief 获取本类所代表的日期时间与datetime所代表的日期时间差距的年数,差距少于1年的不计算在内
    * @param datetime 一个日期时间
    * @return 差距的年数
    */
    INT32 DiffYear(const CDateTime &datetime);

    /**
    * @brief 增加本类所代表的日期时间的年数
    * @param year 增加的年数
    * @return 新的日期时间
    */
    CDateTime & IncYear(UINT32 year = 1);

    /**
    * @brief 减少本类所代表的日期时间的年数
    * @param year 减少的年数
    * @return 新的日期时间
    */
    CDateTime & DecYear(UINT32 year = 1);

    /**
    * @brief 增加本类所代表的日期时间的月数
    * @param month 增加的月数
    * @return 新的日期时间
    */
    CDateTime & IncMonth(UINT32 month = 1);

    /**
    * @brief 减少本类所代表的日期时间的月数
    * @param month 减少的月数
    * @return 新的日期时间
    */
    CDateTime & DecMonth(UINT32 month = 1);

    /**
    * @brief 增加本类所代表的日期时间的天数
    * @param day 增加的天数
    * @return 新的日期时间
    */
    CDateTime & IncDay(UINT32 day = 1);

    /**
    * @brief 减少本类所代表的日期时间的天数
    * @param day 减少的天数
    * @return 新的日期时间
    */
    CDateTime & DecDay(UINT32 day = 1);

    /**
    * @brief 增加本类所代表的日期时间的小时数
    * @param hour 增加的小时数
    * @return 新的日期时间
    */
    CDateTime & IncHour(UINT32 hour = 1);

    /**
    * @brief 减少本类所代表的日期时间的小时数
    * @param hour 减少的小时数
    * @return 新的日期时间
    */
    CDateTime & DecHour(UINT32 hour = 1);

    /**
    * @brief 增加本类所代表的日期时间的分钟数
    * @param minute 增加的分钟数
    * @return 新的日期时间
    */
    CDateTime & IncMinute(UINT32 minute = 1);

    /**
    * @brief 减少本类所代表的日期时间的分钟数
    * @param minute 减少的分钟数
    * @return 新的日期时间
    */
    CDateTime & DecMinute(UINT32 minute = 1);

    /**
    * @brief 增加本类所代表的日期时间的秒数
    * @param second 增加的秒数
    * @return 新的日期时间
    */
    CDateTime & IncSecond(UINT32 second = 1);

    /**
    * @brief 减少本类所代表的日期时间的秒数
    * @param second 减少的秒数
    * @return 新的日期时间
    */
    CDateTime & DecSecond(UINT32 second = 1);

    /**
    * @brief 增加本类所代表的日期时间的星期数
    * @param week 增加的星期数
    * @return 新的日期时间
    */
    CDateTime & IncWeek(UINT32 week = 1);

    /**
    * @brief 减少本类所代表的日期时间的星期数
    * @param week 减少的星期数
    * @return 新的日期时间
    */
    CDateTime & DecWeek(UINT32 week = 1);



    /**
    * @brief 设置本类所代表的日期时间
    * @param year 设置的年份[1970-2037]
    * @param month 设定的此年的哪个月[1-12]
    * @param day 设定的此月的第几天[1-31]
    * @param hours 设定的此天的第几小时[0-23]
    * @param minutes 设定的此小时的第几分钟[0-59]
    * @param seconds 设定的此分钟的第几秒[0-59]
    * @return 是否设置成功,false为没有设置成功
    */
    bool SetDateTime(UINT32 year, UINT32 month, UINT32 day, UINT32 hours, UINT32 minutes, UINT32 seconds);

    /**
    * @brief 设置本类所代表的日期,时间不变
    * @param year 设置的年份[1970-2037]
    * @param month 设定的此年的哪个月[1-12]
    * @param day 设定的此月的第几天[1-31]
    * @return 是否设置成功,false为没有设置成功
    */
    bool SetDate(UINT32 year, UINT32 month, UINT32 day);

    /**
    * @brief 设置本类所代表的时间,日期不变
    * @param hours 设定的此天的第几小时[0-23]
    * @param minutes 设定的此小时的第几分钟[0-59]
    * @param seconds 设定的此分钟的第几秒[0-59]
    * @return 是否设置成功,false为没有设置成功
    */
    bool SetTime(UINT32 hours, UINT32 minutes, UINT32 seconds);

    /**
    * @brief 获取本类所代表的年份
    * @return 获取的年份
    */
    UINT32 GetYear() const;

    /**
    * @brief 获取本类所代表的日期时间所在的年份的第几个月
    * @return 获取的月份
    */
    UINT32 GetMonth() const;

    /**
    * @brief 获取本类所代表的日期时间所在的月份的第几天
    * @return 获取的天数
    */
    UINT32 GetDay();

    /**
    * @brief 获取本类所代表的日期时间所在的天的第几个小时
    * @return 获取的小时数
    */
    UINT32 GetHour();

    /**
    * @brief 获取本类所代表的日期时间所在的小时的分钟数
    * @return 获取的分钟数
    */
    UINT32 GetMinute();

    /**
    * @brief 设置本类所代表的日期时间所在的分钟的秒数
    * @return 获取的秒数
    */
    UINT32 GetSecond();

    /**
    * @brief 设置本类所代表的日期时间所在的星期数
    * @return 获取星期数 [0,6]
    */
    UINT32 GetWeek();

    /**
    * @brief 获取格式化后的日期时间字符串
    * @param format 格式化的格式
    * 具体格式:
    * ......
    * ......
    * @return 格式化后的日期时间字符串
    */
    std::string ToString();

    /**
    * @brief 检测此年是否为闰年
    * @param year 检测的年
    * @return 检测的结构,TRUE为是闰年,FALSE不为闰年
    */
    bool IsLeapYear(UINT32 year);

    /**
    * @brief 获取某年某月有多少天
    * @param year 年份[1970-2037]
    * @param month 月份[1-12]
    * @return 该年该月有多少天
    **/
    UINT32 GetDaysOfYearMonth(UINT32 year,UINT32 month);

private:
    /**
        //检查最终的年份是否合法
    **/
    bool _CheckYearIsRight();
private:
    ::tm m_time;

};





/**
* @brief
* 计算机系统启动到目前为止所经历的时间（此函数有效时间为系统启动后49.7天内）
* @return 计算机系统启动到目前为止所经历的时间，如果该值不可获得，返回－1
*/
inline ULONG  GetTickCount()
{
#if (defined(WIN32) || defined(WIN64))
    return ::GetTickCount();
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif //
}

UINT64  GetSystemTime();

/**
* @brief
* 挂起当前线程的执行直到milliseconds毫秒后
* @param milliseconds : 指示睡眠的时间
* @return void
*/
inline void  MillSleep(UINT32 milliseconds)
{
#if (defined(WIN32) || defined(WIN64))
    ::Sleep((DWORD)milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}


/**
* @brief
* 获取当前的微妙时间
* @return 当前的微妙时间
*/
inline UINT64  TimeMicroSec()
{
    return GetSystemTime();
}

/**
* @brief
* 获取当前的毫秒时间
* @return 当前的毫秒时间
*/
inline UINT64  TimeMilliSec()
{
    return GetSystemTime()/1000LL;
}

/**
* @brief
* 获取当前的秒时间
* @return 当前的秒时间
*/
inline UINT64  TimeSecs()
{
    return GetSystemTime()/1000000LL;
}

/** @} */


}

#endif //__SHARE_SYSTEM_TIME_H__

