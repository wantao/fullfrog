#include <time.h>       /* time_t, struct tm, time, localtime */
#include "sh_systemtime.h"
#include <assert.h>

namespace share
{
    CDateTime::CDateTime(time_t t)
    {
        assert(t > 0);
        localtime_s(&m_time,&t);
    }

    time_t CDateTime::GetTimeValue() const 
    {
        const ::tm* tmp = &m_time;
        return mktime(const_cast<::tm*>(tmp));
    }

    void CDateTime::SetTimeValue(time_t t)
    {
        assert(t > 0);
        localtime_s(&m_time,&t);
        assert(_CheckYearIsRight() == true);
    }

    INT64 CDateTime::operator - (const CDateTime &datetime)
    {
        return GetTimeValue() - datetime.GetTimeValue();
    }

    INT64 CDateTime::DiffSecond(const CDateTime &datetime)
    {
        return GetTimeValue() - datetime.GetTimeValue();
    }

    INT64 CDateTime::DiffMinute(const CDateTime &datetime)
    {
        return (GetTimeValue() - datetime.GetTimeValue())/60;
    }

    INT64 CDateTime::DiffHour(const CDateTime &datetime)
    {
        return (GetTimeValue() - datetime.GetTimeValue())/3600;
    }

    INT64 CDateTime::DiffDay(const CDateTime &datetime)
    {
        return (GetTimeValue() - datetime.GetTimeValue())/86400;
    }

    INT64 CDateTime::DiffWeek(const CDateTime &datetime)
    {
        return (GetTimeValue() - datetime.GetTimeValue())/(86400*7);
    }

    INT32 CDateTime::DiffMonth(const CDateTime &datetime)
    {
        return (GetYear() - datetime.GetYear())*12 + (GetMonth() - datetime.GetMonth());
    }

    INT32 CDateTime::DiffYear(const CDateTime &datetime)
    {
        return GetYear() - datetime.GetYear();
    }

    CDateTime & CDateTime::IncYear(UINT32 year)
    {
        m_time.tm_year += year;
        assert(_CheckYearIsRight() == true);
        return *this;
    }

    CDateTime & CDateTime::DecYear(UINT32 year)
    {
        assert(m_time.tm_year >= year);
        m_time.tm_year -= year;
        assert(_CheckYearIsRight() == true);
        return *this;
    }

    CDateTime & CDateTime::IncMonth(UINT32 month)
    {
        m_time.tm_year += (m_time.tm_mon + month)/12;
        m_time.tm_mon = (m_time.tm_mon + month)%12;
        UINT32 month_days = GetDaysOfYearMonth(GetYear(),GetMonth());
        if (m_time.tm_mday > month_days) {
            m_time.tm_mon += 1;
            if (m_time.tm_mon >= 12) {
                m_time.tm_mon = 0;
            }
            m_time.tm_mday -= month_days;
        }
        assert(_CheckYearIsRight() == true);
        return *this;
    }

    CDateTime & CDateTime::DecMonth(UINT32 month)
    {
        for (UINT32 i = 1; i <= month; i++) {
            m_time.tm_mon -= 1;
            if (m_time.tm_mon < 0) {
                m_time.tm_mon = 11;
                m_time.tm_year -= 1;
            }
        }
        UINT32 month_days = GetDaysOfYearMonth(GetYear(),GetMonth());
        if (m_time.tm_mday > month_days) {
            m_time.tm_mon += 1;
            if (m_time.tm_mon >= 12) {
                m_time.tm_mon = 0;
            }
            m_time.tm_mday -= month_days;
        }
        assert((_CheckYearIsRight() == true));
        return *this;
    }

    CDateTime & CDateTime::IncDay(UINT32 day)
    {
        time_t tmp = GetTimeValue() + day*86400;
        SetTimeValue(tmp);
        return *this;
    }

    CDateTime & CDateTime::DecDay(UINT32 day)
    {
        time_t tmp = GetTimeValue() - day*86400;
        SetTimeValue(tmp); 
        return *this;
    }

    CDateTime & CDateTime::IncHour(UINT32 hour)
    {
        time_t tmp = GetTimeValue() + hour*3600;
        SetTimeValue(tmp);
        return *this;     
    }

    CDateTime & CDateTime::DecHour(UINT32 hour)
    {
        time_t tmp = GetTimeValue() - hour*3600;
        SetTimeValue(tmp);
        return *this;
    }

    CDateTime & CDateTime::IncMinute(UINT32 minute)
    {
        time_t tmp = GetTimeValue() + minute*60;
        SetTimeValue(tmp);
        return *this;
    }

    CDateTime & CDateTime::DecMinute(UINT32 minute)
    {
        time_t tmp = GetTimeValue() - minute*60;
        SetTimeValue(tmp);
        return *this;
    }

    CDateTime & CDateTime::IncSecond(UINT32 second)
    {
        time_t tmp = GetTimeValue() + second;
        SetTimeValue(tmp);
        return *this;
    }

    CDateTime & CDateTime::DecSecond(UINT32 second)
    {
        time_t tmp = GetTimeValue() - second;
        SetTimeValue(tmp);
        return *this;
    }

    CDateTime & CDateTime::IncWeek(UINT32 week)
    {
        time_t tmp = GetTimeValue() + week*86400*7;
        SetTimeValue(tmp);
        return *this;   
    }

    CDateTime & CDateTime::DecWeek(UINT32 week)
    {
        time_t tmp = GetTimeValue() - week*86400*7;
        SetTimeValue(tmp);
        return *this;
    }

    bool CDateTime::SetDateTime(UINT32 year, UINT32 month, UINT32 day, UINT32 hours, UINT32 minutes, UINT32 seconds)
    {
        if (SetDate(year,month,day)) {
            return SetTime(hours,minutes,seconds);
        }
        return false;
    }

    bool CDateTime::SetDate(UINT32 year, UINT32 month, UINT32 day)
    {
        if (!(year >= 1970 && year <= 2037) || \
            !(month >= 1 && month <= 12) || \
            !(day >= 1 && day <= 31)) {
                return false;
        }
        time_t rawtime;
        struct tm timeinfo;
        time(&rawtime);
        localtime_s(&timeinfo,&rawtime);
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month-1;
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = m_time.tm_hour;
        timeinfo.tm_min = m_time.tm_min;
        timeinfo.tm_sec = m_time.tm_sec;
         
        rawtime = mktime(&timeinfo);
        SetTimeValue(rawtime);
        return true;
    }

    bool CDateTime::SetTime(UINT32 hours, UINT32 minutes, UINT32 seconds)
    {
       if (!(hours >= 0 && hours <= 23) || \
            !(minutes >= 0 && minutes <= 59) || \
            !(seconds >= 0 && seconds <= 59)) {
                return false;
       }
       m_time.tm_hour = hours;
       m_time.tm_min = minutes;
       m_time.tm_sec = seconds;
       return true;
    }

    UINT32 CDateTime::GetYear() const
    {
        return (1900 + m_time.tm_year);
    }

    UINT32 CDateTime::GetMonth() const
    {
        return (m_time.tm_mon + 1);
    }

    UINT32 CDateTime::GetDay()
    {
        return m_time.tm_mday;   
    }

    UINT32 CDateTime::GetHour()
    {
        return m_time.tm_hour;
    }

    UINT32 CDateTime::GetMinute()
    {
        return m_time.tm_min;
    }

    UINT32 CDateTime::GetSecond()
    {
        return m_time.tm_sec;
    }

    UINT32 CDateTime::GetWeek()
    {
        return m_time.tm_wday;
    }

    std::string CDateTime::ToString()
    {
        char retBuf[32] = {0};
        strftime(retBuf,32,"%Y-%m-%d %H-%M-%S",&m_time);
        return retBuf;
    }

    bool CDateTime::IsLeapYear(UINT32 year)
    {
        if ((year%4 == 0 && year%100 != 0) || year%400 == 0) {
            return true;
        }
        return false;
    }

    UINT32 CDateTime::GetDaysOfYearMonth(UINT32 year,UINT32 month)
    {
        assert((year >= 1970 && year <= 2037) && (month >= 1 && month <= 12));
        if (month == 1 || month == 3 || month == 5 || month == 7 || \
            month == 8 || month == 9 || month == 10 || month == 12) {
            return 31;
        } else if (month == 2) {
            if (IsLeapYear(year)) {
                return 29;
            }
            return 28;
        }
        return 30;
    }

    bool CDateTime::_CheckYearIsRight()
    {
        UINT32 year = GetYear();
        if (year >= 1970 && year <= 2037) {
            return true;
        }
        return false;
    }

}

