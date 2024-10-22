#undef _HAS_STD_BYTE
#include <string.h>
#undef _HAS_STD_BYTE
#include <cstdlib>
#undef _HAS_STD_BYTE
#include <cassert>
#undef _HAS_STD_BYTE
#include "Event.h"
#undef _HAS_STD_BYTE
using namespace std;
#undef _HAS_STD_BYTE

Event::Event(const char* _title, const char* _description, const DateTime& _date_time, int _no_of_people, const char* _link) {
    this->date_time = _date_time;
    strcpy(title, _title);
    strcpy(description, _description);
    this->no_of_people = _no_of_people;
    strcpy(link, _link);
    EventValidator::validateEvent(*this);
}

Event::Event() : title(""), description(""), link(""), no_of_people(0) {
    DateTime dt;
    date_time = dt;
}


void Event::toStr(char* ev_str) const {
    strcpy(ev_str, "");
    char char_buffer[10] = "";
    strcat(ev_str, title);
    strcat(ev_str, "\n");

    strcat(ev_str, description);
    strcat(ev_str, "\n");

    strcat(ev_str, date_time.toStr());
    strcat(ev_str, "\n");

    itoa(no_of_people, char_buffer, 10);
    strcat(ev_str, char_buffer);
    strcat(ev_str, "\n");

    strcat(ev_str, link);
    strcat(ev_str, "\n");

}

bool Event::operator==(Event other_event)
{
    return !strcmp(this->title, other_event.title);
}

DateTime Event::getDateTime() const {
    return date_time;
}

void Event::setNoOfPeople(int new_no)
{
    this->no_of_people = new_no;
}

const char* Event::getTitle() const{
    return this->title;
}

const char* Event::getName() const
{
    return this->title;
}

std::istream& operator>>(std::istream& stream, Event& a)
{
    stream.getline(a.title, 20);
    stream.getline(a.description, 50);
   
    stream >> a.date_time.day;
    stream.get();
    stream >> a.date_time.month;
    stream.get();
    stream >> a.date_time.year;
    stream.get();
    stream >> a.date_time.hour;
    stream.get();
    stream >> a.date_time.minute;
    stream.get();

    stream >> a.no_of_people;
    stream.get();
    stream.getline(a.link, 30);
    stream.get();

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Event& a)
{
    char a_str[200];
    a.toStr(a_str);
    stream << a_str;
    return stream;
}

void testEvent() {
    DateTime test_dt(10, 2, 2004, 20, 12);
    Event test_ev("Rwack", "qt", test_dt, 20, "http://yey");
    Event test_ev2("Rwack", "qt", test_dt, 30, "http://ney");
    assert(test_ev == test_ev2);
    assert(!strcmp("10.2.2004 20:12 ", test_ev.getDateTime().toStr()));
    char buffer[50];
    test_ev.toStr(buffer);
    assert(!strcmp("Rwack\nqt\n10.2.2004 20:12 \n20\nhttp://yey\n", buffer));
    assert(!strcmp(test_ev.getTitle(), "Rwack"));

    test_ev.setNoOfPeople(2);

    assert(test_ev.getPeopleNo() == 2);

}

EventException::EventException(std::string _message) : message{_message}
{
}

const char* EventException::what() const noexcept
{
    return message.c_str();
}

void EventValidator::validateEvent(const Event& e)
{
    std::string errors;
    int i;
    char e_link[30];
    char link_format[9] = "https://";
    bool bad_link = false;
    try {
        DateTimeValidator::validateDateTime(e.getDateTime());
    }
    catch (DateTimeException ex) {
        errors += ex.what();
    }
    
    strcpy(e_link, e.getLink());
    if (strcmp(e_link, "") == 0)
        bad_link = true;
    for (i = 0; i < 8 and i<strlen(e_link); i++) {
        if (e_link[i] != link_format[i]) {
            bad_link = true;
            break;
        }
    }
    if (bad_link)
        errors += "Invalid Link\n";
    if (e.getPeopleNo() < 0)
        errors += "Invalid Number of People\n";
    if (errors.size() > 0)
        throw EventException(errors);
}
