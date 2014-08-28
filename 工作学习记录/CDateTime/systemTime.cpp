#include <time.h>
#include <stdio.h>
#include <iostream>
#include "sh_systemtime.h"

using namespace std;
int main(void)
{
    share::CDateTime dt1(time(NULL));
    share::CDateTime dt2(time(NULL));
    dt1.SetDateTime(2014,6,30,12,50,40);
    dt2.SetDateTime(2015,7,31,12,43,23);
    printf("dt1.DiffSecond(dt2):%d\n",dt1.DiffSecond(dt2));
    printf("dt1.DiffMinute(dt2):%d\n",dt1.DiffMinute(dt2));
    printf("dt1.DiffHour(dt2):%d\n",dt1.DiffHour(dt2));
    printf("dt1.DiffDay(dt2):%d\n",dt1.DiffDay(dt2));
    printf("dt1.DiffWeek(dt2):%d\n",dt1.DiffWeek(dt2));
    printf("dt1.DiffMonth(dt2):%d\n",dt1.DiffMonth(dt2));
    printf("dt1.DiffYear(dt2):%d\n",dt1.DiffYear(dt2));
    dt1.IncMonth(11);
    printf("dt1.IncMonth(8):%s\n",dt1.ToString().c_str());
    dt2.DecMonth(8);
    printf("dt2.DecMonth(8):%s\n",dt2.ToString().c_str());
    Sleep(1000*1000);
    return 0;
}