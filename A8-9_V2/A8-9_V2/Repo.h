#pragma once
#undef _HAS_STD_BYTE
#include "Event.h"
#undef _HAS_STD_BYTE
#include <vector>
#undef _HAS_STD_BYTE
class Repo{
private:
	std::vector<Event> data{};

public:
	Repo();
	//add new event to repo
	void add(Event new_event);
	//remove event at index
	void remove(int index);
	//getter
	int getSize();
	//get event at index
	Event& operator[](int index);
	//true if repo has element, false otherwise
	bool alreadyHas(Event the_event);
	//getter
	const std::vector<Event>& getData();
	//sort events chronologically
	void sort();
	void increaseEventPeople(Event event);
	void decreaseEventPeople(Event event);
};

void testRepo();

