#pragma once
#undef _HAS_STD_BYTE
#include "Service.h"
#undef _HAS_STD_BYTE
#include "DataSaver.h"
#undef _HAS_STD_BYTE
class UI
{
private:
	ServiceText admin_service;
	Service user_service;
	DataSaver* data_saver;
public:
	UI(ServiceText as,Service us);
	void addDefaultEvents();
	void start();
	void addEvent();
	void removeAdminEvent();
	void updateEvent();
	void displayAdminEvents();
	void AdminUI();
	void cycleEvents(int month);
	void displayUserEvents();
	void removeUserEvent();
	void getSaveType();
	void UserUI();
};

