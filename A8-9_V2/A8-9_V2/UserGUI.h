#pragma once
#include <qwidget.h>
#include "Service.h"
#include "DataSaver.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QMessageBox>

class UserGUI : public QWidget
{
private:

	Service& user_service;
	ServiceText& admin_service;
	DataSaver* data_saver;
	std::vector<Event>::const_iterator admint_list_iterator;

	QListWidget* eventsListWidget;


	QPushButton* CSVButton;
	QPushButton* HTMLButton;
	QPushButton* addButton;
	QPushButton* nextButton;
	QPushButton* removeButton;
	QPushButton* seeUserListButton;
	QPushButton* seeAdminListButton;
	QPushButton* openFileButton;
	QLineEdit* filterMonth;
	std::vector<Event> filtered_events;
public:
	UserGUI(ServiceText& admin_serv, Service& user_serv);
	UserGUI(UserGUI& ug);
private:
	
	void buildGUI();
	void addButtonHandler();
	void removeButtonHandler();
	void HTMLButtonHandler();
	void CSVButtonHandler();
	void seeAdminListButtonHandler();
	void seeUserListButtonHandler();
	void nextButtonHandler();
	void initFilterIterator();
	void openFileButtonHandler();
};

