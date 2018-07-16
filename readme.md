SimpleDate for C++
==================

SimpleDate is a small C++ library that gives you an implementation of Date type
in readable format - YYYYMMDD.

It's important when you need to see dates in a debugger without extra
converting, logging, printing, etc.

It uses unsigned long to store a date. For example, date 26 January 1980 be
stored in a number 19800126.

Relational and arithmetic operators have been overloaded and you can compare and
assign values using standard operators (= == != >= <= ++ -- += -=).

There are some extra methods for date manipulating, like begin or end of a
month, begin or end of a quarter,  begin or end of a year.

Examples of usage
-----------------

Get current date

```c++
#include "date.h"
...
Date now = Date::now();
```

Initialize

```c++
Date date(1980, 12, 31);
```

Set date

```c++
date.setDate(1980, 11, 30);
```

Get year, month, day from date

```c++
int year = date.year();
int month = date.month();
int day = date.day();
```

Get size of a month

```c++
int monthSize = Date::monthSize(2018, 2);
```

Check date

```c++
if (date.isValid())
    ...
```

Shift date

```c++
date++;                 // next day
date += 7;              // over week
date.shift(0, 1, 0);    // shift for 1 month
date.shift(1, 0, 0);    // shift for 1 year
date--;                 // prior day
date.shift(-1,0,0);     // shift for -1 year
```

Begin of a month

```c++
date.setDate(1980, 12, 31);
date.monthBegin();      // 31.12.1980 -> 01.12.1980
```

End of a month

```c++
date.setDate(1980, 12, 15);
date.monthEnd();        // 15.12.1980 -> 31.12.1980
```

Some extra functions

```c++
Date date(2010, 8, 25);
date.quarterBegin();    // 01.07.2010
date.quarterEnd();      // 30.09.2010
date.yearBegin();       // 01.01.2010
date.yearEnd();         // 31.12.2010
```

Interval between 2 dates

```c++
Date begin(1980, 1, 1);
Date end(1981, 2, 2);
Date interval = begin.diff(end); // 010101 = 1 year 1 month 1 day
```

Convert date to string

```c++
Date date(2010, 8, 25);
date.toString('-');     // "2010-08-25"
```
