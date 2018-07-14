 #pragma once

#include <string>

typedef unsigned int uint;
typedef unsigned long ulong;
typedef ulong Date;

uint Year(Date date);
uint Month(Date date);
uint Day(Date date);
uint MonthSize(uint year, uint month);
Date DatePack(uint year, uint month, uint day);
void DateUnpack(Date date, uint* year, uint* month, uint* day);
bool IsDateValid(Date date);
Date DateAdd(Date date, int years, int months, int days);
Date DateInterval(Date begin, Date end);
std::string DateToStr(Date date, char separator);
