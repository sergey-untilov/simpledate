#pragma once

#include <string>

typedef int TDate;

class Date {
    private:
        TDate tdate;

        static void addDays(int& y, int& m, int& d, int days);
        static void addMonths(int& y, int&m, int& d, int months);
        static void addYears(int& y, int&m, int& d, int years);

    public:
        Date();
        Date(int year, int month, int day);

        static int monthSize(int year, int month);
        static Date now();
        static Date diff(const Date& begin, const Date& end);

        int year() const;
        int month() const;
        int day() const;
        TDate getTDate() const;
        bool isValid() const;
        std::string toString(char separator) const;

        Date& setDate(int year, int month, int day);
        Date& shift(int years, int months, int days);
        Date& monthBegin();
        Date& monthEnd();
        Date& quarterBegin();
        Date& quarterEnd();
        Date& yearBegin();
        Date& yearEnd();
        Date& invert();

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

template <typename T>
inline bool operator< (const Date& lv, const T rv) {
    return lv.getTDate() < rv;
}
template <typename T>
inline bool operator> (const Date& lv, const T rv) { return rv < lv; }
template <typename T>
inline bool operator<=(const Date& lv, const T rv) { return !(lv > rv); }
template <typename T>
inline bool operator>=(const Date& lv, const T rv) { return !(lv < rv); }
template <typename T>
inline bool operator==(const Date& lv, const T rv) {
    return lv.getTDate() == rv;
}
template <typename T>
inline bool operator!=(const Date& lv, const T rv) { return !(lv == rv);}
