#pragma once

#include <string>

typedef unsigned long TDate;

class Date {
    private:
        TDate tdate;

    public:
        Date();
        Date(int year, int month, int day);

        static int monthSize(int year, int month);
        static Date now();

        int year() const;
        int month() const;
        int day() const;
        TDate getTDate() const;
        bool isValid() const;
        Date diff(const Date&) const;
        std::string toString(char separator) const;

        Date& setDate(int year, int month, int day);
        Date& shift(int years, int months, int days);
        Date& monthBegin();
        Date& monthEnd();
        Date& quarterBegin();
        Date& quarterEnd();
        Date& yearBegin();
        Date& yearEnd();

        Date& operator=(const Date& rv);
        Date& operator=(const TDate tdate);
        Date& operator++();
        Date  operator++(int);
        Date& operator--();
        Date  operator--(int);
        Date& operator+=(int);
        Date& operator-=(int);
        Date& operator+=(const Date&);
        Date& operator-=(const Date&);

        friend Date operator+(Date lv, const Date& rv);
        friend Date operator-(Date lv, const Date& rv);
        friend Date operator+(Date lv, const int days);
        friend Date operator-(Date lv, const int days);
};

inline bool operator< (const Date& lv, const Date& rv) {
    return lv.getTDate() < rv.getTDate();
}
inline bool operator> (const Date& lv, const Date& rv) { return rv < lv; }
inline bool operator<=(const Date& lv, const Date& rv) { return !(lv > rv); }
inline bool operator>=(const Date& lv, const Date& rv) { return !(lv < rv); }

inline bool operator==(const Date& lv, const Date& rv) {
    return lv.getTDate() == rv.getTDate();
}
inline bool operator!=(const Date& lv, const Date& rv) { return !(lv == rv);}
