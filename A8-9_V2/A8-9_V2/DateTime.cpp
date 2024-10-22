//
// Created by Robert on 02.04.2024.
//
#undef _HAS_STD_BYTE
#include <string.h>
#undef _HAS_STD_BYTE
#include <cstdlib>
#undef _HAS_STD_BYTE
#include <cassert>
#undef _HAS_STD_BYTE
#include "DateTime.h"
#undef _HAS_STD_BYTE
#include <exception>
#undef _HAS_STD_BYTE

using namespace std;

DateTime::DateTime(int _day, int _month, int _year, int _hour, int _minute) {
    /*if (_day < 1 || _day>31)
        throw std::exception("Invalid day");
    if(_month<1 || _month>12)
        throw std::exception("Invalid month");
    if(_hour<0 || _hour>24)
        throw std::exception("Invalid hour");
    if(_minute<0 || _minute>60)
        throw std::exception("Invalid minute");*/
    this->day = _day;
    this->month = _month;
    this->year = _year;
    this->hour = _hour;
    this->minute = _minute;
}

DateTime::DateTime() : day(0),month(0),year(0),hour(0),minute(0) {}

DateTime DateTime::operator=(const DateTime& new_date_time) {
    this->minute = new_date_time.minute;
    this->month = new_date_time.month;
    this->hour = new_date_time.hour;
    this->year = new_date_time.year;
    this->day = new_date_time.day;
    return *this;
}

bool DateTime::operator<(const DateTime& other_date_time)
{
    if (this->year < other_date_time.year)
        return true;
    else if (this->year == other_date_time.year)
        if (this->month < other_date_time.month)
            return true;
        else if (this->month == other_date_time.month)
            if (this->day < other_date_time.day)
                return true;
            else if (this->day == other_date_time.day)
                if (this->hour < other_date_time.hour)
                    return true;
                else if (this->hour == other_date_time.hour)
                    if (this->minute < other_date_time.minute)
                        return true;
    return false;
}

int DateTime::getMonth() const {
    return this->month;
}

int DateTime::getYear() const
{
    return this->year;
}

int DateTime::getHour() const
{
    return this->hour;
}

int DateTime::getMinute() const
{
    return this->minute;
}

char* DateTime::toStr() const {
    char dt_str[100] = "";
    char new_elem[10] = "";

    itoa(day, new_elem, 10);
    strcat(dt_str, new_elem);
    strcat(dt_str, ".");

    itoa(month, new_elem, 10);
    strcat(dt_str, new_elem);
    strcat(dt_str, ".");

    itoa(year, new_elem, 10);
    strcat(dt_str, new_elem);
    strcat(dt_str, " ");

    itoa(hour, new_elem, 10);
    strcat(dt_str, new_elem);
    strcat(dt_str, ":");

    itoa(minute, new_elem, 10);
    strcat(dt_str, new_elem);
    strcat(dt_str, " ");
    return dt_str;
    ///
}

int DateTime::getDay() const {
    return day;
}


DateTime::~DateTime() = default;

DateTimeException::DateTimeException(std::string _message) : message{_message}
{
}

const char* DateTimeException::what() const noexcept
{
    return message.c_str();
}

void DateTimeValidator::validateDateTime(const DateTime& dt)
{
    std::string errors;
    if (dt.getDay() < 1 or dt.getDay() > 31)
        errors += "Invalid Day\n";
    if (dt.getMonth() < 1 or dt.getMonth() > 12)
        errors += "Invalid Month\n";
    if (dt.getYear() < 0 or dt.getYear() > 9999)
        errors += "Invalid Year\n";
    if (dt.getHour() < 0 or dt.getHour() > 23)
        errors += "Invalid Hour\n";
    if (dt.getMinute() < 0 or dt.getMinute() > 59)
        errors += "Invalid Minute\n";
    if (errors.size() > 0)
        throw DateTimeException(errors);
}
