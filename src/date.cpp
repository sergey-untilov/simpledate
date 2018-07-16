#include <cassert>
#include <string>
#include <ctime>
#include "date.h"

static TDate _makeTDate(int year, int month, int day);
static Date _diff(const Date& begin, const Date& end);

Date::Date() : tdate(0) {}

Date::Date(int year, int month, int day) {
    tdate = _makeTDate(year, month, day);
}

int Date::year() const {
    return tdate / 10000;
}

int Date::month() const {
    return tdate / 100 % 100;
}

int Date::day() const {
    return tdate % 100;
}

TDate Date::getTDate() const {
    return tdate;
}

int Date::monthSize(int year, int month) {
    assert(month >= 1 && month <= 12);
    if (month == 2 && year % 4 == 0)
        return 29;
    static const int monSize[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return monSize[month - 1];
}

Date Date::now() {
    std::time_t rawtime = std::time(nullptr);
    std::tm* tm = std::localtime(&rawtime);
    Date date(1900 + tm->tm_year, tm->tm_mon, tm->tm_mday);
    return date;
}

bool Date::isValid() const {
    int y = year();
    int m = month();
    int d = day();
    if (m < 1 || m > 12)
        return false;
    if (d < 1)
        return false;
    int monSize = Date::monthSize(y, m);
    if (d > monSize)
        return false;
    return true;
}

Date Date::diff(const Date& end) const {
    return _diff(*this, end);
}

std::string Date::toString(char separator) const {
    char buffer[11];
    sprintf(buffer, "%04d%c%02d%c%02d",
        year(), separator, month(), separator, day());
    return buffer;
}

Date& Date::setDate(int year, int month, int day) {
    tdate = _makeTDate(year, month, day);
    return *this;
}

Date& Date::shift(int years, int months, int days) {
    int y = year();
    int m = month();
    int d = day();

    years += months / 12;
    months %= 12;

    if (years < 0 && abs(years) > y) {
        tdate = 0;
        return *this;
    }

    y += years;

    if (months > 0 && m + months > 12) {
        y++;
        m += months - 12;
    } else if (months < 0 && abs(months) > m) {
        m += 12 - months;
    } else
        m += months;

    while(days) {
        int monSize = Date::monthSize(y, m);
        if (days < 0 && abs(days) >= d) {
            if (m == 1) {
                if (!y)
                    return *this;
                days += d;
                y--;
                m = 12;
                d = 31;
            } else {
                days += d;
                m--;
                d = Date::monthSize(y, m);
            }
        } else if (days + d > monSize) {
            days = days < d ? 0 : days - d;
            if (m == 12) {
                y++;
                m = 1;
                d = 1;
            } else {
                m++;
                d = 1;
            }
        } else {
            d += days;
            days = 0;
        }
    }

    setDate(y, m, d);
    return *this;
}

Date& Date::monthBegin() {
    setDate(year(), month(), 1);
    return *this;
}

Date& Date::monthEnd() {
    int y = year();
    int m = month();
    int d = Date::monthSize(y, m);
    setDate(y, m, d);
    return *this;
}

Date& Date::quarterBegin() {
    int y = year();
    int m = month();
    if (m < 1 || m > 12)
        return *this;
    static const int firstMonthInQuarter[] = {1,1,1,4,4,4,7,7,7,10,10,10};
    setDate(y, firstMonthInQuarter[m - 1], 1);
    return *this;
}

Date& Date::quarterEnd() {
    int y = year();
    int m = month();
    if (m < 1 || m > 12)
        return *this;
    static const int lastMonthInQuarter[] = {3,3,3,6,6,6,9,9,9,12,12,12};
    m = lastMonthInQuarter[m - 1];
    int d = Date::monthSize(y, m);
    setDate(y, m, d);
    return *this;
}

Date& Date::yearBegin() {
    setDate(year(), 1, 1);
    return *this;
}

Date& Date::yearEnd() {
    setDate(year(), 12, 31);
    return *this;
}

Date& Date::operator=(const Date& rv) {
    if (this != &rv)
        this->tdate = rv.tdate;
    return *this;
}

Date& Date::operator=(const TDate tdate) {
    this->tdate = tdate;
    return *this;
}

Date& Date::operator++() {
    shift(0, 0, 1);
    return *this;

}

Date Date::operator++(int) {
    Date tmp = *this;
    shift(0, 0, 1);
    return tmp;
}

Date& Date::operator--() {
    shift(0, 0, -1);
    return *this;
}

Date Date::operator--(int days) {
    Date tmp = *this;
    shift(0, 0, -1);
    return tmp;
}

Date& Date::operator+=(int days) {
    shift(0, 0, days);
    return *this;
}

Date& Date::operator-=(int days) {
    shift(0, 0, -days);
    return *this;
}

Date& Date::operator+=(const Date& rv) {
    shift(rv.year(), rv.month(), rv.day());
    return *this;
}

Date& Date::operator-=(const Date& rv) {
    shift(-rv.year(), -rv.month(), -rv.day());
    return *this;
}

Date operator+(Date lv, const Date& rv) {
    lv += rv;
    return lv;
}
Date operator-(Date lv, const Date& rv) {
    lv -= rv;
    return lv;
}
Date operator+(Date lv, const int days) {
    lv += days;
    return lv;
}
Date operator-(Date lv, const int days) {
    lv -= days;
    return lv;
}

static TDate _makeTDate(int year, int month, int day) {
    return year * 10000 + month * 100 + day;
}

static Date _diff(const Date& begin, const Date& end) {
    uint beginYear = begin.year();
    uint beginMonth = begin.month();
    uint beginDay = begin.day();
    uint endYear = end.year();
    uint endMonth = end.month();
    uint endDay = end.day();

    uint year = endYear - beginYear;
    if (year && endMonth < beginMonth)
        year--;

    uint month = (endMonth >= beginMonth)
        ? endMonth - beginMonth
        : endMonth + beginMonth - 12;

    bool isBothLastDayInFebruary =
        endMonth == 2 && beginMonth == 2 && endYear != beginYear
        && endDay == Date::monthSize(endYear, endMonth)
        && beginDay == Date::monthSize(beginYear, beginMonth);

    if (month && endDay < beginDay && !isBothLastDayInFebruary)
        month--;

    uint day = 0;
    if (!isBothLastDayInFebruary) {
        if (endDay >= beginDay)
            day = endDay - beginDay;
        else {
            uint monSize = Date::monthSize(beginYear, beginMonth);
            day = endDay + beginDay - monSize;
        }
    }

    Date date(year, month, day);
    return date;
}

