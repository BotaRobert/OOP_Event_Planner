//
// Created by Robert on 02.04.2024.
//
#pragma once
#undef _HAS_STD_BYTE
#include "DateTime.h"
#undef _HAS_STD_BYTE
#include <iostream>
#undef _HAS_STD_BYTE
class Event {
private:
    char title[20] = "";
    char description[50] = "";
    int no_of_people;
    char link[30] = "";
    DateTime date_time = DateTime(1, 1, 1, 1, 1);

public:
    Event(const char* _title, const char* _description, const DateTime& _date_time, int _no_of_people, const char* _link);
    Event();
    void toStr(char* ev_str) const;
    //getter
    const char* getTitle() const;

    const char* getName() const;
    //getter
    const char* getDescription() const {
        return this->description;
    }
    //getter
    const char* getLink() const {
        return this->link;
    }
    //getter
    const int getPeopleNo() const {
        return this->no_of_people;
    }
    //two events are considered the same if they have the same title
    bool operator==(Event other_event);
    //getter
    DateTime getDateTime() const;
    //setter
    void setNoOfPeople(int new_no);
    friend std::istream& operator>>(std::istream& stream, Event& a);
    friend std::ostream& operator<<(std::ostream& stream, const Event& a);
};

class EventException : public std::exception {
private:
    std::string message;
public:
    EventException(std::string _message);
    const char* what() const noexcept override;
};

class EventValidator {
public:
    static void validateEvent(const Event& e);
};

void testEvent();