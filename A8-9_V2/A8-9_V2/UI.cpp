#include "UI.h"
#undef _HAS_STD_BYTE
#include <iostream>
#undef _HAS_STD_BYTE
#include <Windows.h>
#undef _HAS_STD_BYTE
#include <shellapi.h>
#undef _HAS_STD_BYTE


UI::UI(ServiceText as, Service us):user_service{us},admin_service{as}
{
}

void UI::addDefaultEvents() {
	DateTime date_time{ 13,5,2004,20,00 };
	Event new_event{ "aaa","nice1",date_time,23,"https://aaa" };
	admin_service.add(new_event);

	DateTime date_time1{ 7,12,2104,20,00 };
	Event new_event1{ "bbb","nice2",date_time1,23,"https://bbb" };
	admin_service.add(new_event1);

	DateTime date_time2{ 1,12,2012,21,00 };
	Event new_event2{ "ccc","nice3",date_time2,56,"https://ccc" };
	admin_service.add(new_event2);

	DateTime date_time3{ 19,6,2024,20,00 };
	Event new_event3{ "ddd","nice4",date_time3,12,"https://ddd" };
	admin_service.add(new_event3);

	DateTime date_time4{ 21,6,2001,20,30 };
	Event new_event4{ "eee","nice5",date_time4,13,"https://eee" };
	admin_service.add(new_event4);

	DateTime date_time5{ 23,1,2004,5,00 };
	Event new_event5{ "fff","nice6",date_time5,66,"https://fff" };
	admin_service.add(new_event5);

	DateTime date_time6{ 1,12,2004,4,1};
	Event new_event6{ "ggg","nice7",date_time6,23,"https://ggg" };
	admin_service.add(new_event6);

	DateTime date_time7{ 1,12,2011,2,00 };
	Event new_event7{ "hhh","nice8",date_time7,25,"https://hhh" };
	admin_service.add(new_event7);

	DateTime date_time8{ 22,1,2004,11,00 };
	Event new_event8{ "iii","nice9",date_time8,23,"https://iii" };
	admin_service.add(new_event8);

	DateTime date_time9{ 25,1,2015,21,00 };
	Event new_event9{ "jjj","nice10",date_time9,23,"https://jjj" };
	admin_service.add(new_event9);


}

int getIntInput() {
	int var;
	std::cin >> var;
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Invalid input. Integer required\n>";
		std::cin >> var;
	}
	return var;
}

void UI::start()
{
	//addDefaultEvents();
	admin_service.readFromFile();
	int user_input=0;
	while (1) {
		std::cout << "Choose Mode:\n1.Administrator\n2.User\n>";
		user_input = getIntInput();
		if (user_input == 1)
			this->AdminUI();
		else if (user_input == 2)
			this->UserUI();
		else 
			std::cout << "Invalid input\n";
	}

}

void printAdminMenu() {
	std::cout << "Choose Option:\n";
	std::cout << "1.Add Event\n";
	std::cout << "2.Remove Event\n";
	std::cout << "3.Update Event\n";
	std::cout << "4.Display all events\n";
	std::cout << "0.Change Admin/User mode\n";
}

DateTime readDateTime() {
	int day, month, year, hour, minute;
	std::cout << "Input day\n>";
	day = getIntInput();
	std::cout << "Input month\n>";
	month = getIntInput();
	std::cout << "Input year\n>";
	year = getIntInput();
	std::cout << "Input hour\n>";
	hour = getIntInput();
	std::cout << "Input minute\n>";
	minute = getIntInput();
	return DateTime{ day,month,year,hour,minute };
}

Event readEvent() {
	char title[20], link[200], description[200];
	int no_of_people;
	std::cout << "Input title\n>";
	std::cin.get();
	std::cin.getline(title, 19);
	std::cout << "Input description\n>";
	std::cin.getline(description, 200);
	std::cout << "Input link\n>";
	std::cin.getline(link, 200);
	std::cout << "Input number of people\n>";
	no_of_people = getIntInput();
	return Event{title,description,readDateTime(),no_of_people,link};
}

void UI::addEvent() {
	Event new_event;
	try {
		new_event = readEvent();
		admin_service.add(new_event);
	}
	catch (EventException ex) {
		std::cout << ex.what()<<std::endl;
	}
	catch (ServiceException ex) {
		std::cout << ex.what() << std::endl;
	}
}

void UI::removeAdminEvent() {
	char title[20];
	std::cout << "Input title\n>";
	std::cin.get();
	std::cin.getline(title, 20);
	try {
		admin_service.remove(title);
	}
	catch (EventException ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (ServiceException ex) {
		std::cout << ex.what() << std::endl;
	}
}

void UI::updateEvent() {
	char title[20];
	std::cout << "Input title\n>";
	std::cin.get();
	std::cin.getline(title, 20);
	try {
		admin_service.update(title,readEvent());
	}
	catch (EventException ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (ServiceException ex) {
		std::cout << ex.what() << std::endl;
	}
}

void UI::displayAdminEvents() {
	std::vector<Event> events = admin_service.getAll();
	char current_event[100];
	for (int i = 0; i < admin_service.getRepoSize(); i++) {
		events[i].toStr(current_event);
		std::cout << "Event no." << i << std::endl << current_event << std::endl;
	}
}

void UI::AdminUI()
{
	int user_input=0;
	std::cout << "Welcome to admin mode!\n";
	while (1) {
		printAdminMenu();
		user_input = getIntInput();
		switch (user_input)
		{
		case 1:
			addEvent();
			break;
		case 2:
			removeAdminEvent();
			break;
		case 3:
			updateEvent();
			break;
		case 4:
			displayAdminEvents();
			break;
		case 0:
			return;
		default:
			std::cout << "Invalid input!\n";
			break;
		}
	}

}

void printCycleOptions() {
	std::cout << "1.Next\n";
	std::cout << "2.Add to your list\n";
	std::cout << "3.Return to main menu\n>";
}

void UI::cycleEvents(int month) {
	int user_input=0;
	std::vector<Event> events;
	admin_service.getAllByMonth(events, month);
	if (events.size() == 0) {
		std::cout << "No events that month! :(\n";
		return;
	}
	char current_event[200];
	int i = 0;
	while (1) {
		events[i].toStr(current_event);
		//ShellExecuteA(NULL, NULL, "chrome.exe", events[i].getLink(), NULL, SW_SHOWMAXIMIZED);
		std::cout << "<--------------------------------------------->\n";
		std::cout << current_event<<std::endl;
		std::cout << "<--------------------------------------------->\n";

		printCycleOptions();

		user_input = getIntInput();
		while (user_input < 1 && user_input>3) {
			std::cout << "Invalid input!\n>";
			user_input = getIntInput();
		}

		if (user_input == 3)
			break;
		else if (user_input == 2) {
			try {
				user_service.add(events[i]);
				user_service.increaseEventPeople(events[i]);
				admin_service.increaseEventPeople(events[i]);
				this->data_saver->saveToFile(user_service.getAll());
			}
			catch (EventException ex) {
				std::cout << ex.what() << std::endl;
			}
			catch (ServiceException ex) {
				std::cout << ex.what() << std::endl;
			}
		}
		else if (user_input == 1);
		i++;
		if (i == events.size())
			i = 0;
	}
}

void printUserOptions() {
	std::cout << "1.See events by month\n";
	std::cout << "2.Display your list of events\n";
	std::cout << "3.Remove an event from your list\n";
	std::cout << "4.Open file with the events list\n";
	std::cout << "0.Change Admin/User mode\n>";
}


void UI::displayUserEvents() {
	std::vector<Event> events = user_service.getAll();
	char current_event[100];
	int i = 0;
	for (auto ev : events) {
		ev.toStr(current_event);
		std::cout << "<--------------------------------------------->\n";
		std::cout << "Event no." << i << std::endl << current_event << std::endl;
		std::cout << "<--------------------------------------------->\n\n";
		i++;
	}
}

void UI::removeUserEvent() {
	char title[20];
	std::cout << "Input title\n>";
	std::cin.get();
	std::cin.getline(title, 20);
	try {
		Event removed_event = user_service.remove(title);
		user_service.decreaseEventPeople(removed_event);
		admin_service.decreaseEventPeople(removed_event);
	}
	catch (std::exception ex) {
		std::cout << ex.what() << std::endl;
	}
}

void UI::getSaveType()
{
	std::cout << "In what type of file should the events list be saved ?\n";
	std::cout << "1.CSV\n";
	std::cout << "2.HTML\n";
	while (1) {
		auto user_input = getIntInput();
		if (user_input == 1) {
			this->data_saver = new DataSaverCSV{};
			break;
		}
		else if (user_input == 2) {
			this->data_saver = new DataSaverHTML{};
			break;
		}
		else
			std::cout << "Invalid Input\n";
	}
}

void UI::UserUI()
{
	int user_input=0;
	std::cout << "Welcome to user mode!\n";
	int month = 0;
	char month_s[3];

	getSaveType();

	while (1) {
		printUserOptions();
		user_input = getIntInput();
		switch (user_input)
		{
		case 1:
			std::cout << "Input month or 0 to see all events\n>";
			month = getIntInput();
			cycleEvents(month);
			break;
		case 2:
			displayUserEvents();
			break;
		case 3:
			removeUserEvent();
			break;
		case 4:
			data_saver->openFile();
			break;
		case 0:
			return;
		default:
			std::cout << "Invalid input!\n";
			break;
		}
	}
}

