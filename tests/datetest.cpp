#include <gtest/gtest.h>

#include "datetime/date.h"

TEST(DateTest, testToString) {
    {
        datetime::Date date(2024, 01, 31);
        EXPECT_EQ(date.toString(), "2024-01-31");
    }

    {
        datetime::Date date(2024, 02, 28);
        EXPECT_EQ(date.toString(), "2024-02-28");
    }

    {
        datetime::Date date(1980, 12, 24);
        EXPECT_EQ(date.toString(), "1980-12-24");
    }
}

TEST(DateTest, testFromString) {
    EXPECT_EQ(datetime::Date::fromString("1980-12-24").toString(), "1980-12-24");
    EXPECT_EQ(datetime::Date::fromString("2024-02-28").toString(), "2024-02-28");
    EXPECT_EQ(datetime::Date::fromString("1980-12-24").toString(), "1980-12-24");
}

TEST(DateTest, testSetYear) {
    datetime::Date date;
    date.setYear(2024);
    EXPECT_EQ(date.year(), 2024);
    date.setYear(2025);
    EXPECT_EQ(date.year(), 2025);
    date.setYear(2023);
    EXPECT_EQ(date.year(), 2023);
}

TEST(DateTest, testSetMonth) {
    datetime::Date date;
    date.setMonth(1);
    EXPECT_EQ(date.month(), 1);
    date.setMonth(12);
    EXPECT_EQ(date.month(), 12);
    date.setMonth(13);
    EXPECT_EQ(date.month(), 13);
}

TEST(DateTest, testSetDay) {
    datetime::Date date;
    date.setDay(1);
    EXPECT_EQ(date.day(), 1);
    date.setDay(31);
    EXPECT_EQ(date.day(), 31);
    date.setDay(15);
    EXPECT_EQ(date.day(), 15);
}

TEST(DateTest, testIsValid) {
    datetime::Date date(2024, 01, 31);
    EXPECT_EQ(date.isValid(), true);
    date.setMonth(02);
    EXPECT_EQ(date.isValid(), false);
    date.setDay(29);
    EXPECT_EQ(date.isValid(), true);
    date.setYear(2023);
    EXPECT_EQ(date.isValid(), false);
    date.setMonth(15);
    EXPECT_EQ(date.isValid(), false);
}

TEST(DateTest, testAddDays) {
    datetime::Date date(2024, 01, 31);
    date.addDays(1);
    EXPECT_EQ(date.toString(), "2024-02-01");
    date.addDays(-5);
    EXPECT_EQ(date.toString(), "2024-01-27");
    date.addDays(-30);
    EXPECT_EQ(date.toString(), "2023-12-28");
    date.addDays(20);
    EXPECT_EQ(date.toString(), "2024-01-17");
}

TEST(DateTest, testAddMonths) {
    datetime::Date date(2024, 01, 31);
    date.addMonths(5);
    EXPECT_EQ(date.toString(), "2024-06-30");
    date.addMonths(-10);
    EXPECT_EQ(date.toString(), "2023-08-30");
    date.addMonths(30);
    EXPECT_EQ(date.toString(), "2026-02-28");
}

TEST(DateTest, testAddYears) {
    datetime::Date date(2024, 02, 29);
    date.addYears(5);
    EXPECT_EQ(date.toString(), "2029-02-28");
    date.addYears(-6);
    EXPECT_EQ(date.toString(), "2023-02-28");
    date.addYears(2);
    EXPECT_EQ(date.toString(), "2025-02-28");
}

TEST(DateTest, testWeekDay) {
    datetime::Date date(2024, 01, 31);
    date.addMonths(2);
    EXPECT_EQ(date.weekDay(), 1);
    date.addDays(-6);
    EXPECT_EQ(date.weekDay(), 2);
    date.addDays(200);
    EXPECT_EQ(date.weekDay(), 6);
}
