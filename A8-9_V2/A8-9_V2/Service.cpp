#undef _HAS_STD_BYTE
#include "Service.h"
#undef _HAS_STD_BYTE
#include <exception>
#undef _HAS_STD_BYTE
#include <string.h>
#undef _HAS_STD_BYTE
#include <iostream>
#undef _HAS_STD_BYTE
#include <algorithm>
#undef _HAS_STD_BYTE
#include <fstream>
#undef _HAS_STD_BYTE


Service::Service()
{
	repo = Repo{};
}

void Service::add(Event new_event)
{
	if (repo.alreadyHas(new_event))
		throw ServiceException("Event already registered in Repository");
	repo.add(new_event);
}

Event Service::remove(const char* event_title)
{
	int i = 0;
	for (auto ev : repo.getData()) {
		if (!strcmp(repo[i].getTitle(), event_title)) {
			Event removed = repo[i];
			repo.remove(i);
			return removed;
		}
		i++;
	}
	throw ServiceException("Event title not found in Repository");
}

void Service::update(const char* event_title,Event new_event_data)
{
	bool found= false;
	int i = 0;
	for (auto ev : repo.getData()) {
		if (!strcmp(ev.getTitle(), event_title)) {
			repo[i] = new_event_data;
			found = true;
		}
		i++;
	}
	if(!found)
		throw ServiceException("Event title not found in Repository");
}

const std::vector<Event>& Service::getAll()
{
	return repo.getData();
}



int Service::getRepoSize()
{
	return repo.getSize();
}


void Service::getAllByMonth(std::vector<Event>& events_this_month, int month)
{
	if (month == 0) {
		repo.sort();
		events_this_month = repo.getData();
		return;
	}
	std::vector<Event> empty{};
	events_this_month = empty;
	std::vector<Event> all_events = repo.getData();
	
	for (auto ev : all_events)
		if (ev.getDateTime().getMonth() == month) {
			events_this_month.push_back(ev);
		}


}

 void Service::increaseEventPeople(Event event) {
	 repo.increaseEventPeople(event);
 }

 void Service::decreaseEventPeople(Event event) {
	 repo.decreaseEventPeople(event);
 }

 void ServiceText::saveToFile()
 {
	 std::ofstream fout{ save_file };
	 for (auto ev : this->getAll()) {
		 fout << "\n";
		 fout << ev;
	 }
	 fout.close();
 }

 void ServiceText::readFromFile()
 {
	 std::ifstream fin{ save_file };
	 fin.get();
	 while (!fin.eof()) {
		 Event e{};
		 fin >> e;
		 repo.add(e);
	 }
	 fin.close();
 }

 void ServiceText::add(Event new_event)
 {
	 Service::add(new_event);
	 saveToFile();
 }

 Event ServiceText::remove(const char* event_title)
 {
	 Event ev = Service::remove(event_title);
	 saveToFile();
	 return ev;
 }

 void ServiceText::update(const char* event_title, Event new_event_data)
 {
	 Service::update(event_title, new_event_data);
	 saveToFile();
 }

 void ServiceText::increaseEventPeople(Event event)
 {
	 Service::increaseEventPeople(event);
	 saveToFile();
 }

 void ServiceText::decreaseEventPeople(Event event)
 {
	 Service::decreaseEventPeople(event);
	 saveToFile();
 }

 ServiceText::ServiceText(std::string sf) : save_file{ sf }, Service{}
 {
 }

 ServiceException::ServiceException(std::string _message) : message{_message}
 {
 }

 const char* ServiceException::what() const noexcept
 {
	 return message.c_str();
 }
