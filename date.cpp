#include <cassert>
#include <stdlib.h>
#include <string>
#include "date.h"

uint Year(Date date) {
    return date / 10000;
}

uint Month(Date date) {
    return date / 100 % 100;
}

uint Day(Date date) {
    return date % 100;
}

uint MonthSize(uint year, uint month) {
    assert(month >= 1 && month <= 12);
    if (month == 2 && year % 4 == 0)
        return 29;
    static uint monthSize[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return monthSize[month - 1];
}

Date DatePack(uint year, uint month, uint day) {
    return year * 10000 + month * 100 + day;
}

void DateUnpack(Date date, uint* year, uint* month, uint* day) {
    if (year)
        *year = Year(date);
    if (month)
        *month = Month(date);
    if (day)
        *day = Day(date);
}

bool IsDateValid(Date date) {
    uint year = Year(date);
    uint month = Month(date);
    uint day = Day(date);
    if (month < 1 || month > 12)
        return false;
    if (day < 1)
        return false;
    uint monthSize = MonthSize(year, month);
    if (day > monthSize)
        return false;
    return true;
}

Date DateAdd(Date date, int years, int months, int days) {
    uint year = Year(date);
    uint month = Month(date);
    uint day = Day(date);

    years += months / 12;
    months %= 12;

    if (years < 0 && abs(years) > year)
        return 0;

    year += years;

    if (months > 0 && month + months > 12) {
        year++;
        month += months - 12;
    } else if (months < 0 && abs(months) > month ) {
        month += 12 - months;
    } else
        month += months;

    while(days) {
        uint monthSize = MonthSize(year, month);
        if (days < 0 && abs(days) >= day) {
            if (month == 1) {
                if (!year)
                    return 0;
                days += day;
                year--;
                month = 12;
                day = 31;
            } else {
                days += day;
                month--;
                day = MonthSize(year, month);
            }
        } else if (days + day > monthSize) {
            days = days < day ? 0 : days - day;
            if (month == 12) {
                year++;
                month = 1;
                day = 1;
            } else {
                month++;
                day = 1;
            }
        } else {
            day += days;
            days = 0;
        }
    }

    date = DatePack(year, month, day);
    return date;
}

Date DateInterval(Date begin, Date end) {
    uint beginYear = Year(begin);
    uint beginMonth = Month(begin);
    uint beginDay = Day(begin);
    uint endYear = Year(end);
    uint endMonth = Month(end);
    uint endDay = Day(end);

    uint year = endYear - beginYear;
    if (year && endMonth < beginMonth)
        year--;

    uint month = (endMonth >= beginMonth)
        ? endMonth - beginMonth
        : endMonth + beginMonth - 12;

    bool isBothLastDayInFebruary =
        endMonth == 2 && beginMonth == 2 && endYear != beginYear
        && endDay == MonthSize(endYear, endMonth)
        && beginDay == MonthSize(beginYear, beginMonth);

    if (month && endDay < beginDay && !isBothLastDayInFebruary)
        month--;

    uint day = 0;
    if (!isBothLastDayInFebruary) {
        if (endDay >= beginDay)
            day = endDay - beginDay;
        else {
            uint monthSize = MonthSize(beginYear, beginMonth);
            day = endDay + beginDay - monthSize;
        }
    }

    return DatePack(year, month, day);
}

std::string DateToStr(Date date, char separator) {
    char buffer[11];
    sprintf(buffer, "%04d%c%02d%c%02d",
        Year(date), separator, Month(date), separator, Day(date));
    return std::string(buffer);
}
