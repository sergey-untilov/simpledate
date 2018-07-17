#include "../src/date.h"
#include "test.h"

int main(void) {

    Test test;
    test.start();

    Date now = Date::now();
    cout << now.toString('-') << endl;

    Date date(1980, 1, 1);
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 1 && date.day() == 1);

    date += 1;
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 1 && date.day() == 2);

    date.shift(0, 1, 0);
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 2 && date.day() == 2);

    date.shift(1, 0, 0);
    test.assert_true(
        date.toString('-'),
        date.year() == 1981 && date.month() == 2 && date.day() == 2);

    date.shift(-1, 0, 0);
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 2 && date.day() == 2);

    date.shift(0, -1, 0);
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 1 && date.day() == 2);

    date--;
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 1 && date.day() == 1);

    date -= 1;
    test.assert_true(
        date.toString('-'),
        date.year() == 1979 && date.month() == 12 && date.day() == 31);

    Date dateBegin(1980, 1, 1);
    Date dateEnd(1980, 1, 1);
    Date diff = dateBegin.diff(dateEnd);
    test.assert_true(
        diff.toString('-'),
        !diff.year() && !diff.month() && !diff.day());

    dateEnd.setDate(1981, 2, 2);
    diff = dateBegin.diff(dateEnd);
    test.assert_true(
        diff.toString('-'),
        diff.year() == 1 && diff.month() == 1 && diff.day() == 1);

    dateBegin.setDate(1980, 2, 29);
    dateEnd.setDate(1981, 2, 28);
    diff = dateBegin.diff(dateEnd);
    test.assert_true(
        diff.toString('-'),
        diff.year() == 1 && diff.month() == 0 && diff.day() == 0);

    date.setDate(1980, 4, 23);
    date.monthBegin();
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 4 && date.day() == 1);

    date.setDate(1980, 4, 23);
    date.monthEnd();
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 4 && date.day() == 30);

    date.setDate(1980, 3, 3);
    date.quarterBegin();
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 1 && date.day() == 1);

    date.setDate(1980, 2, 1);
    date.quarterEnd();
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 3 && date.day() == 31);

    date.setDate(1980, 4, 23);
    date.yearBegin();
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 1 && date.day() == 1);

    date.setDate(1980, 4, 23);
    date.yearEnd();
    test.assert_true(
        date.toString('-'),
        date.year() == 1980 && date.month() == 12 && date.day() == 31);

    date.setDate(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    test.assert_true(
        date.toString('-'),
        date.year() == 0xFFFFFFFF && date.month() == 0xFFFFFFFF
        && date.day() == 0xFFFFFFFF);

    date.setDate(1980, 2, 29);
    date.shift(1, 0, 0);
    test.assert_true(date.toString('-'), date.isValid());

    date.setDate(1980, 1, 31);
    date.shift(0, 1, 0);
    test.assert_true(date.toString('-'), date.isValid());

    date.setDate(1980, 3, 31);
    date -= 31;
    test.assert_true(date.toString('-'), date.isValid());

    date.setDate(1980, 1, 31);
    date += 30;
    test.assert_true(date.toString('-'), date.isValid());


    test.finish();

    std::getchar();

    return test.getFailed();
}
