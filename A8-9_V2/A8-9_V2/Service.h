#pragma once
#undef _HAS_STD_BYTE
#include "Repo.h"
#undef _HAS_STD_BYTE
#include "Event.h"
#undef _HAS_STD_BYTE
class Service
{
protected:
	Repo repo{};
public:
	Service();
	//ADMIN FUNCTIONS

	/// add element to repo if it isn't already in there, throw std::exception otherwise
	void add(Event new_event);
	///remove event with event_title if it is in repo throw std::exception otherwise
	Event remove(const char* event_title);
	//update event with event_title if it is in repo throw std::exception otherwise
	void update(const char* event_title,Event new_event_data);
	//getter
	const std::vector<Event>& getAll();
	//getter
	int getRepoSize();

	//USER FUNCTIONS
	//get all events in a given month or get them all sorted chronologically if month=0
	 void getAllByMonth(std::vector<Event>& events_this_month, int month);
	 void increaseEventPeople(Event event);
	 void decreaseEventPeople(Event event);
};

class ServiceText : public Service {
private:
	std::string save_file;
public:
	ServiceText(std::string sf);
	void saveToFile();
	void readFromFile();
	void add(Event new_event);
	Event remove(const char* event_title);
	void update(const char* event_title, Event new_event_data);
	void increaseEventPeople(Event event);
	void decreaseEventPeople(Event event);
};

class ServiceException : public std::exception {
private:
	std::string message;
public:
	ServiceException(std::string _message);
	const char* what() const noexcept override;
};
