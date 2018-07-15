SimpleDate
==========

SimpleDate is a small C++ library that gives you a simple implementation of Date
type in readable format - YYYYMMDD.

It's important when you need to see dates in a debugger without extra logging,
printing, etc.

It uses unsigned long to store a date. For example, date 26 January 1980 be
stored in a number 19800126.

There are some functions in a library which manipulates with a date type.

Examples of usage
-----------------

Get current date

```c++
#include "date.h"
...
Date date = DateNow(); // YYYYMMDD
```

Set date

```c++
Date date = DatePack(1980, 11, 30); // 19801130
```

Get year, month, day from date

```c++
uint year = Year(date);
uint month = Month(date);
uint day = Day(date);
```

Get size of a month

```c++
uint monthSize = MonthSize(2018, 2);
```

Get year, month, day from date in one invoke

```c++
uint year, month, day;
DateUnpack(date, &year, &month, &day);
```

Check date

```c++
if (IsDateValid(date))
    ...
```

Shift date

```c++
Date shiftedDate = DateAdd(date, years, months, days);
Date nextDay = DateAdd(date, 0, 0, 1);
Date previousDay = DateAdd(date, 0, 0, -1);
```

Begin of a month

```c++
Date monthBegin = MonthBegin(date); // 31.12.1980 -> 01.12.1980
```

End of a month

```c++
Date monthEnd = MonthEnd(date); // 20.12.1980 -> 31.12.1980
```

Some extra functions

```c++
Date date = DatePack(2010, 8, 25);
Date quarterBegin = QuarterBegin(date); // 25.08.2010 -> 01.07.2010
Date quarterEnd = QuarterEnd(date);     // 25.08.2010 -> 30.09.2010
Date yearBegin = YearBegin(date);       // 25.08.2010 -> 01.01.2010
Date yearEnd = YearEnd(date);           // 25.08.2010 -> 31.12.2010
```

Interval between 2 dates

```c++
Date begin = DatePack(1980, 1, 1);
Date end = DatePack(1981, 2, 2);
Date interval = DateInterval(begin, end); // 010101 = 1 year 1 month 1 day
```

Convert date to string

```c++
Date date = DatePack(2010, 8, 25);
std::string str = DateToStr(date, '-'); // "2010-08-25"
```
