#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "AdminGUI.h"
#include "UserGUI.h"

class MainGUI : public QWidget
{
private:
	AdminGUI admin_gui;
	UserGUI user_gui;

	QPushButton* adminButton;
	QPushButton* userButton;

public:
	MainGUI(AdminGUI _admin_gui,UserGUI _user_gui);

private:
	void buildGUI();
	void userButtonHandler();
	void adminButtonHandler();

};