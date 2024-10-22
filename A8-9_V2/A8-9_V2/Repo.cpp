#undef _HAS_STD_BYTE
#include "Repo.h"
#undef _HAS_STD_BYTE
#include <cassert>
#undef _HAS_STD_BYTE
#include <algorithm>
#undef _HAS_STD_BYTE

#undef _HAS_STD_BYTE


Repo::Repo()
{
    data = std::vector<Event>{};
}

void Repo::add(Event new_event)
{
	this->data.push_back(new_event);
}

void Repo::remove(int index)
{
	this->data.erase(data.begin()+index);
}

int Repo::getSize()
{
	return this->data.size();
}

Event& Repo::operator[](int index)
{
    return data[index];
}

bool Repo::alreadyHas(Event the_event)
{
    if(find(data.begin(),data.end(),the_event)!=data.end())
            return true;
    return false;
}

const std::vector<Event>& Repo::getData()
{
    return this->data;
}

bool comp(Event ev1,Event ev2){
    return ev1.getDateTime() < ev2.getDateTime();
}

void Repo::sort() {
    std::sort(data.begin(),data.end(),comp);
}

void Repo::increaseEventPeople(Event event) {
    auto ev = find(data.begin(), data.end(), event);
    if (ev == data.end())
        return;
    int i = ev - data.begin();
    data[i].setNoOfPeople(ev->getPeopleNo() + 1);
}

void Repo::decreaseEventPeople(Event event) {
    auto ev = find(data.begin(), data.end(), event);
    if (ev == data.end())
        return;
    int i = ev - data.begin();
    data[i].setNoOfPeople(ev->getPeopleNo() - 1);
}

void testRepo()
{
    Repo v1{};

    DateTime test_dt1(10, 2, 2004, 20, 12);
    Event test_ev1("Rwack", "qt", test_dt1, 20, "http://yey");

    DateTime test_dt2(4, 12, 2014, 20, 12);
    Event test_ev2("Jazz", "not qt", test_dt2, 10, "http://art");

    DateTime test_dt3(4, 12, 2003, 10, 12);
    Event test_ev3("Manele", "wow", test_dt2, 120, "http://barf");

    v1.add(test_ev1);
    assert(!v1.alreadyHas(test_ev2));
    v1.add(test_ev2);
    assert(v1.alreadyHas(test_ev2));
    assert(v1.getSize() == 2);
    assert(v1[1] == test_ev2);
    v1[1] = test_ev3;
    assert(v1[1] ==test_ev3);
    v1.add(test_ev2);
    assert(v1.getSize() == 3);

    v1.remove(1);
    assert(v1.getSize() == 2);
    assert(v1[0] == test_ev1);
    assert(v1[1] == test_ev2);
}
