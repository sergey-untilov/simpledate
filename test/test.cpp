#include "../src/date.h"
#include "test.h"

int main(void) {

    Test test;
    test.start();

    Date now = DateNow();

    Date date = DatePack(1980, 1, 1);

    uint year, month, day;
    DateUnpack(date, &year, &month, &day);
    test.assert_true("Year", year == 1980);
    test.assert_true("Month", month == 1);
    test.assert_true("Day", day == 1);

    date = DateAdd(date, 0, 0, 1);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1980 && month == 1 && day == 2);

    date = DateAdd(date, 0, 1, 0);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1980 && month == 2 && day == 2);

    date = DateAdd(date, 1, 0, 0);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1981 && month == 2 && day == 2);

    date = DateAdd(date, -1, 0, 0);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1980 && month == 2 && day == 2);

    date = DateAdd(date, 0, -1, 0);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1980 && month == 1 && day == 2);

    date = DateAdd(date, 0, 0, -1);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1980 && month == 1 && day == 1);

    date = DateAdd(date, 0, 0, -1);
    DateUnpack(date, &year, &month, &day);
    test.assert_true(DateToStr(date, '-'),
                     year == 1979 && month == 12 && day == 31);

    Date dateBegin = DatePack(1980, 1, 1);
    Date dateEnd = DatePack(1980, 1, 1);
    Date diff = DateInterval(dateBegin, dateEnd);
    DateUnpack(diff, &year, &month, &day);
    test.assert_true("DateInterval", year == 0 && month == 0 && day == 0);

    dateBegin = DatePack(1980, 1, 1);
    dateEnd = DatePack(1981, 2, 2);
    diff = DateInterval(dateBegin, dateEnd);
    DateUnpack(diff, &year, &month, &day);
    test.assert_true("DateInterval", year == 1 && month == 1 && day == 1);

    dateBegin = DatePack(1980, 2, 29);
    dateEnd = DatePack(1981, 2, 28);
    diff = DateInterval(dateBegin, dateEnd);
    DateUnpack(diff, &year, &month, &day);
    test.assert_true("DateInterval", year == 1 && month == 0 && day == 0);

    date = DatePack(1980, 4, 23);
    date = MonthBegin(date);
    DateUnpack(date, &year, &month, &day);
    test.assert_true("MonthBegin", year == 1980 && month == 4 && day == 1);

    date = DatePack(1980, 4, 23);
    date = MonthEnd(date);
    DateUnpack(date, &year, &month, &day);
    test.assert_true("MonthEnd", year == 1980 && month == 4 && day == 30);

    date = DatePack(1980, 3, 3);
    date = QuarterBegin(date);
    DateUnpack(date, &year, &month, &day);
    test.assert_true("QuarterBegin", year == 1980 && month == 1 && day == 1);

    date = DatePack(1980, 2, 1);
    date = QuarterEnd(date);
    DateUnpack(date, &year, &month, &day);
    test.assert_true("QuarterEnd", year == 1980 && month == 3 && day == 31);

    date = DatePack(1980, 4, 23);
    date = YearBegin(date);
    DateUnpack(date, &year, &month, &day);
    test.assert_true("YearBegin", year == 1980 && month == 1 && day == 1);

    date = DatePack(1980, 4, 23);
    date = YearEnd(date);
    DateUnpack(date, &year, &month, &day);
    test.assert_true("YearEnd", year == 1980 && month == 12 && day == 31);

    test.finish();

    std::getchar();

    return test.getFailed();
}
