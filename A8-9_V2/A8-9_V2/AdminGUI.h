#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <string>
class AdminGUI : public QWidget
{
private:
	ServiceText& admin_service;

	QListWidget* eventsListWidget;
	QLineEdit* titleEdit;
	QLineEdit* descriptionEdit;
	QLineEdit* linkEdit;

	QLineEdit* dayEdit;
	QLineEdit* monthEdit;
	QLineEdit* yearEdit;
	QLineEdit* hourEdit;
	QLineEdit* minuteEdit;
	QLineEdit* noOfPeopleEdit;

	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;


public:
	AdminGUI(AdminGUI &ag);
	AdminGUI(ServiceText& admint_serv);

private:
	void buildGUI();
	void populateList();

	void addButtonHandler();
	void removeButtonHandler();
	void updateButtonHandler();
	Event& getEventFromGUI();

};

