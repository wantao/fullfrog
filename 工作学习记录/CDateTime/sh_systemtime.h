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
* @defgroup grouptime ʱ�����
* @{
*/
class CDateTime;

/**
* @brief ��ȡ����ǰ����ʱ��(���ô˺����Ĵ�ʱ�˿�)��CDateTime
* @return ����ǰ����ʱ��(���ô˺����Ĵ�ʱ�˿�)��CDateTime
*/

CDateTime Now();

/**
* @brief ����ʱ����,����1970����ҹ��2037��֮���ĳһ��ʱ��
*
*/
class  CDateTime
{
public:
    /**
    * @brief ����һ��CDateTime��,���������ʱ��Ϊ1970-1-1��ҹ
    */
    CDateTime(time_t t);


    /**
    * @brief ��ȡ���������������ʱ���time_tֵ
    * @return ���ص�time_tֵ
    */
    time_t GetTimeValue() const;

    /**
    * @brief ���ñ��������������ʱ��
    * @param t ���õ�����ʱ��
    * @return void
    */
    void SetTimeValue(time_t t);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ���������
    * @param datetime һ������ʱ��
    * @return ��������
    */
    INT64 operator - (const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ���������
    * @param datetime һ������ʱ��
    * @return ��������
    */
    INT64 DiffSecond(const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ����ķ�����,�������1���ӵĲ���������
    * @param datetime һ������ʱ��
    * @return ���ķ�����
    */
    INT64 DiffMinute(const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ�����Сʱ��,�������1Сʱ�Ĳ���������
    * @param datetime һ������ʱ��
    * @return ����Сʱ��
    */
    INT64 DiffHour(const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ���������,�������1��Ĳ���������
    * @param datetime һ������ʱ��
    * @return ��������
    */
    INT64 DiffDay(const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ�����������,�������1���ڵĲ���������
    * @param datetime һ������ʱ��
    * @return ����������
    */
    INT64 DiffWeek(const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ������·�,�������1���µĲ���������
    * @param datetime һ������ʱ��
    * @return ��������
    */
    INT32 DiffMonth(const CDateTime &datetime);

    /**
    * @brief ��ȡ���������������ʱ����datetime�����������ʱ���������,�������1��Ĳ���������
    * @param datetime һ������ʱ��
    * @return ��������
    */
    INT32 DiffYear(const CDateTime &datetime);

    /**
    * @brief ���ӱ��������������ʱ�������
    * @param year ���ӵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & IncYear(UINT32 year = 1);

    /**
    * @brief ���ٱ��������������ʱ�������
    * @param year ���ٵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & DecYear(UINT32 year = 1);

    /**
    * @brief ���ӱ��������������ʱ�������
    * @param month ���ӵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & IncMonth(UINT32 month = 1);

    /**
    * @brief ���ٱ��������������ʱ�������
    * @param month ���ٵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & DecMonth(UINT32 month = 1);

    /**
    * @brief ���ӱ��������������ʱ�������
    * @param day ���ӵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & IncDay(UINT32 day = 1);

    /**
    * @brief ���ٱ��������������ʱ�������
    * @param day ���ٵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & DecDay(UINT32 day = 1);

    /**
    * @brief ���ӱ��������������ʱ���Сʱ��
    * @param hour ���ӵ�Сʱ��
    * @return �µ�����ʱ��
    */
    CDateTime & IncHour(UINT32 hour = 1);

    /**
    * @brief ���ٱ��������������ʱ���Сʱ��
    * @param hour ���ٵ�Сʱ��
    * @return �µ�����ʱ��
    */
    CDateTime & DecHour(UINT32 hour = 1);

    /**
    * @brief ���ӱ��������������ʱ��ķ�����
    * @param minute ���ӵķ�����
    * @return �µ�����ʱ��
    */
    CDateTime & IncMinute(UINT32 minute = 1);

    /**
    * @brief ���ٱ��������������ʱ��ķ�����
    * @param minute ���ٵķ�����
    * @return �µ�����ʱ��
    */
    CDateTime & DecMinute(UINT32 minute = 1);

    /**
    * @brief ���ӱ��������������ʱ�������
    * @param second ���ӵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & IncSecond(UINT32 second = 1);

    /**
    * @brief ���ٱ��������������ʱ�������
    * @param second ���ٵ�����
    * @return �µ�����ʱ��
    */
    CDateTime & DecSecond(UINT32 second = 1);

    /**
    * @brief ���ӱ��������������ʱ���������
    * @param week ���ӵ�������
    * @return �µ�����ʱ��
    */
    CDateTime & IncWeek(UINT32 week = 1);

    /**
    * @brief ���ٱ��������������ʱ���������
    * @param week ���ٵ�������
    * @return �µ�����ʱ��
    */
    CDateTime & DecWeek(UINT32 week = 1);



    /**
    * @brief ���ñ��������������ʱ��
    * @param year ���õ����[1970-2037]
    * @param month �趨�Ĵ�����ĸ���[1-12]
    * @param day �趨�Ĵ��µĵڼ���[1-31]
    * @param hours �趨�Ĵ���ĵڼ�Сʱ[0-23]
    * @param minutes �趨�Ĵ�Сʱ�ĵڼ�����[0-59]
    * @param seconds �趨�Ĵ˷��ӵĵڼ���[0-59]
    * @return �Ƿ����óɹ�,falseΪû�����óɹ�
    */
    bool SetDateTime(UINT32 year, UINT32 month, UINT32 day, UINT32 hours, UINT32 minutes, UINT32 seconds);

    /**
    * @brief ���ñ��������������,ʱ�䲻��
    * @param year ���õ����[1970-2037]
    * @param month �趨�Ĵ�����ĸ���[1-12]
    * @param day �趨�Ĵ��µĵڼ���[1-31]
    * @return �Ƿ����óɹ�,falseΪû�����óɹ�
    */
    bool SetDate(UINT32 year, UINT32 month, UINT32 day);

    /**
    * @brief ���ñ����������ʱ��,���ڲ���
    * @param hours �趨�Ĵ���ĵڼ�Сʱ[0-23]
    * @param minutes �趨�Ĵ�Сʱ�ĵڼ�����[0-59]
    * @param seconds �趨�Ĵ˷��ӵĵڼ���[0-59]
    * @return �Ƿ����óɹ�,falseΪû�����óɹ�
    */
    bool SetTime(UINT32 hours, UINT32 minutes, UINT32 seconds);

    /**
    * @brief ��ȡ��������������
    * @return ��ȡ�����
    */
    UINT32 GetYear() const;

    /**
    * @brief ��ȡ���������������ʱ�����ڵ���ݵĵڼ�����
    * @return ��ȡ���·�
    */
    UINT32 GetMonth() const;

    /**
    * @brief ��ȡ���������������ʱ�����ڵ��·ݵĵڼ���
    * @return ��ȡ������
    */
    UINT32 GetDay();

    /**
    * @brief ��ȡ���������������ʱ�����ڵ���ĵڼ���Сʱ
    * @return ��ȡ��Сʱ��
    */
    UINT32 GetHour();

    /**
    * @brief ��ȡ���������������ʱ�����ڵ�Сʱ�ķ�����
    * @return ��ȡ�ķ�����
    */
    UINT32 GetMinute();

    /**
    * @brief ���ñ��������������ʱ�����ڵķ��ӵ�����
    * @return ��ȡ������
    */
    UINT32 GetSecond();

    /**
    * @brief ���ñ��������������ʱ�����ڵ�������
    * @return ��ȡ������ [0,6]
    */
    UINT32 GetWeek();

    /**
    * @brief ��ȡ��ʽ���������ʱ���ַ���
    * @param format ��ʽ���ĸ�ʽ
    * �����ʽ:
    * ......
    * ......
    * @return ��ʽ���������ʱ���ַ���
    */
    std::string ToString();

    /**
    * @brief �������Ƿ�Ϊ����
    * @param year ������
    * @return ���Ľṹ,TRUEΪ������,FALSE��Ϊ����
    */
    bool IsLeapYear(UINT32 year);

    /**
    * @brief ��ȡĳ��ĳ���ж�����
    * @param year ���[1970-2037]
    * @param month �·�[1-12]
    * @return ��������ж�����
    **/
    UINT32 GetDaysOfYearMonth(UINT32 year,UINT32 month);

private:
    /**
        //������յ�����Ƿ�Ϸ�
    **/
    bool _CheckYearIsRight();
private:
    ::tm m_time;

};





/**
* @brief
* �����ϵͳ������ĿǰΪֹ��������ʱ�䣨�˺�����Чʱ��Ϊϵͳ������49.7���ڣ�
* @return �����ϵͳ������ĿǰΪֹ��������ʱ�䣬�����ֵ���ɻ�ã����أ�1
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
* ����ǰ�̵߳�ִ��ֱ��milliseconds�����
* @param milliseconds : ָʾ˯�ߵ�ʱ��
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
* ��ȡ��ǰ��΢��ʱ��
* @return ��ǰ��΢��ʱ��
*/
inline UINT64  TimeMicroSec()
{
    return GetSystemTime();
}

/**
* @brief
* ��ȡ��ǰ�ĺ���ʱ��
* @return ��ǰ�ĺ���ʱ��
*/
inline UINT64  TimeMilliSec()
{
    return GetSystemTime()/1000LL;
}

/**
* @brief
* ��ȡ��ǰ����ʱ��
* @return ��ǰ����ʱ��
*/
inline UINT64  TimeSecs()
{
    return GetSystemTime()/1000000LL;
}

/** @} */


}

#endif //__SHARE_SYSTEM_TIME_H__

