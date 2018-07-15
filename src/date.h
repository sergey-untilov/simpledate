 #pragma once

#include <string>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef ulong Date;

Date DateNow();
uint Year(Date date);
uint Month(Date date);
uint Day(Date date);
uint MonthSize(uint year, uint month);
Date DatePack(uint year, uint month, uint day);
void DateUnpack(Date date, uint* year, uint* month, uint* day);
bool IsDateValid(Date date);
Date DateAdd(Date date, int years, int months, int days);
Date MonthBegin(Date date);
Date MonthEnd(Date date);
Date QuarterBegin(Date date);
Date QuarterEnd(Date date);
Date YearBegin(Date date);
Date YearEnd(Date date);
Date DateInterval(Date begin, Date end);
std::string DateToStr(Date date, char separator);
