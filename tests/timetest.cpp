#include <gtest/gtest.h>

#include "datetime/time.h"

TEST(TimeTest, testToString) {
    {
        datetime::Time time(12, 25, 20);
        EXPECT_EQ(time.toString(), "12:25:20");
    }

    {
        datetime::Time time(01, 01, 01);
        EXPECT_EQ(time.toString(), "01:01:01");
    }

    {
        datetime::Time time(80, 70, 90);
        EXPECT_EQ(time.toString(), "08:10:30");
    }
}

TEST(TimeTest, testFromString) {
    EXPECT_EQ(datetime::Time::fromString("12:25:20").toString(), "12:25:20");
    EXPECT_EQ(datetime::Time::fromString("01:01:01").toString(), "01:01:01");
    EXPECT_EQ(datetime::Time::fromString("80:70:90").toString(), "08:10:30");
}

TEST(DateTest, testSetHours) {
    datetime::Time time;
    time.setHours(12);
    EXPECT_EQ(time.hours(), 12);
    time.setHours(25);
    EXPECT_EQ(time.hours(), 1);
    time.setHours(10);
    EXPECT_EQ(time.hours(), 10);
}

TEST(DateTest, testSetMinutes) {
    datetime::Time time;
    time.setMinutes(12);
    EXPECT_EQ(time.minutes(), 12);
    time.setMinutes(01);
    EXPECT_EQ(time.minutes(), 1);
    time.setMinutes(754);
    EXPECT_EQ(time.minutes(), 34);
}

TEST(DateTest, testSetSeconds) {
    datetime::Time time;
    time.setSeconds(12);
    EXPECT_EQ(time.seconds(), 12);
    time.setSeconds(30);
    EXPECT_EQ(time.seconds(), 30);
    time.setSeconds(900);
    EXPECT_EQ(time.seconds(), 0);
}
