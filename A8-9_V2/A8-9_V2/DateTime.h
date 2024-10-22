#pragma once
#undef _HAS_STD_BYTE
#include <string>


class DateTime {
private:
    

public:
    int day;
    int month;
    int year;
    int hour;
    int minute;

    DateTime(int _day, int _month, int _year, int _hour, int _minute);
    DateTime();
    ~DateTime();
    ///Day getter
    int getDay() const;

    DateTime operator=(const DateTime& new_date_time);
    bool operator<(const DateTime& other_date_time);
    ///Month getter
    int getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinute() const;
    ///
    /// \return std::string representation of DateTime object in format "day.month.year hour:minute "
    char* toStr() const;


};

class DateTimeException : public std::exception {
private:
    std::string message;
public:
    DateTimeException(std::string _message);
    const char* what() const noexcept override;
};

class DateTimeValidator {
public:
    static void validateDateTime(const DateTime& dt);
};

void testDateTime();


