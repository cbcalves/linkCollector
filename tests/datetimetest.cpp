#include <gtest/gtest.h>

#include "datetime/datetime.h"

TEST(DateTimeTest, testToString) {
    {
        datetime::DateTime dt(2024, 01, 31, 12, 25, 20);
        EXPECT_EQ(dt.toString(), "2024-01-31 12:25:20");
    }

    {
        datetime::DateTime dt(1975, 12, 24, 01, 01, 01);
        EXPECT_EQ(dt.toString(), "1975-12-24 01:01:01");
    }

    {
        datetime::DateTime dt(2005, 07, 12, 80, 70, 90);
        EXPECT_EQ(dt.toString(), "2005-07-12 08:10:30");
    }
}

TEST(DateTimeTest, testFromString) {
    EXPECT_EQ(datetime::DateTime::fromString("2024-01-31 12:25:20").toString(), "2024-01-31 12:25:20");
    EXPECT_EQ(datetime::DateTime::fromString("1975-12-24 01:01:01").toString(), "1975-12-24 01:01:01");
    EXPECT_EQ(datetime::DateTime::fromString("2005-07-12 08:10:30").toString(), "2005-07-12 08:10:30");
}

TEST(DateTimeTest, testDateTime) {
    {
        datetime::DateTime dt(2024, 01, 31, 12, 25, 20);
        datetime::Date date(2024, 01, 31);
        datetime::Time time(12, 25, 20);
        EXPECT_EQ(dt.date(), date);
        EXPECT_EQ(dt.time(), time);
    }

    {
        datetime::DateTime dt(1975, 12, 24, 01, 01, 01);
        datetime::Date date(1975, 12, 24);
        datetime::Time time(01, 01, 01);
        EXPECT_EQ(dt.date(), date);
        EXPECT_EQ(dt.time(), time);
    }

    {
        datetime::DateTime dt(2005, 07, 12, 80, 70, 90);
        datetime::Date date(2005, 07, 12);
        datetime::Time time(8, 10, 30);
        EXPECT_EQ(dt.date(), date);
        EXPECT_EQ(dt.time(), time);
    }
}
