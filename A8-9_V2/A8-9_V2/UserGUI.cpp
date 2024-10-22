#include "UserGUI.h"
#include <qlayout.h>
#include <qlabel.h>

UserGUI::UserGUI(ServiceText& admint_serv, Service& user_serv) : admin_service{ admint_serv }, user_service{ user_serv }
{
	this->buildGUI();
}

UserGUI::UserGUI(UserGUI& ug): user_service{ug.user_service}, admin_service{ug.admin_service}
{
	this->buildGUI();
}

void UserGUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	this->eventsListWidget = new QListWidget{};
	mainLayout->addWidget(eventsListWidget);

	QGridLayout* rightLayout = new QGridLayout{};


	this->addButton = new QPushButton{ "Add" };
	this->seeUserListButton = new QPushButton{ "Show Your List" };
	this->seeAdminListButton = new QPushButton{ "Show Admin List" };
	this->nextButton = new QPushButton{ "Next" };

	this->HTMLButton = new QPushButton{ "HTML" };
	this->CSVButton = new QPushButton{ "CSV" };

	this->removeButton = new QPushButton{ "Remove" };
	this->openFileButton = new QPushButton{ "Open File" };

	QLabel* chooseFile = new QLabel{ "Choose File Type" };

	QLabel* filter = new QLabel{ "Filter Month:" };
	this->filterMonth = new QLineEdit{};
	rightLayout->addWidget(filter, 2, 0);
	rightLayout->addWidget(this->filterMonth, 2, 1);
	rightLayout->addWidget(chooseFile, 1, 0);
	rightLayout->addWidget(this->HTMLButton, 2, 0);
	rightLayout->addWidget(this->CSVButton, 2, 1);
	rightLayout->addWidget(this->nextButton, 0, 0);
	rightLayout->addWidget(this->addButton, 0, 1);
	rightLayout->addWidget(this->seeUserListButton, 1, 1);
	rightLayout->addWidget(this->seeAdminListButton, 1, 0);
	rightLayout->addWidget(this->removeButton, 0, 0);
	rightLayout->addWidget(this->openFileButton, 0, 1);
	this->removeButton->hide();
	this->openFileButton->hide();
	this->nextButton->hide();
	this->addButton->hide();
	this->seeAdminListButton->hide();
	this->seeUserListButton->hide();
	
	

	mainLayout->addLayout(rightLayout);

	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addButtonHandler);
	QObject::connect(this->CSVButton, &QPushButton::clicked, this, &UserGUI::CSVButtonHandler);
	QObject::connect(this->HTMLButton, &QPushButton::clicked, this, &UserGUI::HTMLButtonHandler);
	QObject::connect(this->seeAdminListButton, &QPushButton::clicked, this, &UserGUI::seeAdminListButtonHandler);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::nextButtonHandler);
	QObject::connect(this->removeButton, &QPushButton::clicked, this, &UserGUI::removeButtonHandler);
	QObject::connect(this->seeUserListButton, &QPushButton::clicked, this, &UserGUI::seeUserListButtonHandler);
	QObject::connect(this->openFileButton, &QPushButton::clicked, this, &UserGUI::openFileButtonHandler);

}

void UserGUI::addButtonHandler()
{
	try {
		this->user_service.add(*(this->admint_list_iterator));
		this->eventsListWidget->addItem(QString::fromStdString("Event added!"));
		user_service.increaseEventPeople(*(this->admint_list_iterator));
		admin_service.increaseEventPeople(*(this->admint_list_iterator));
		data_saver->saveToFile(user_service.getAll());
	}
	catch (std::exception& ex) {
		QMessageBox error_window{ this };
		error_window.setText(ex.what());
		error_window.exec();
	}
}

void UserGUI::removeButtonHandler()
{
	auto event_item = this->eventsListWidget->currentItem();
	if (event_item == nullptr) {
		QMessageBox error_window{ this };
		error_window.setText("Please select an item\n");
		error_window.exec();
		return;
	}
	auto event_str = event_item->text().toStdString();
	int endl_pos = event_str.find("\n");
	std::string event_name = event_str.substr(0, endl_pos);
	auto removed_event = user_service.remove(event_name.c_str());
	user_service.decreaseEventPeople(removed_event);
	admin_service.decreaseEventPeople(removed_event);
	data_saver->saveToFile(user_service.getAll());
	this->seeUserListButtonHandler();
}

void UserGUI::HTMLButtonHandler()
{
	this->data_saver = new DataSaverHTML{};
	this->HTMLButton->hide();
	this->CSVButton->hide();
	this->seeAdminListButton->show();
	this->seeUserListButton->show();

}

void UserGUI::CSVButtonHandler()
{
	this->data_saver = new DataSaverCSV{};
	this->HTMLButton->hide();
	this->CSVButton->hide();
	this->seeAdminListButton->show();
	this->seeUserListButton->show();
}

void UserGUI::seeAdminListButtonHandler()
{
	this->removeButton->hide();
	this->openFileButton->hide();
	this->nextButton->show();
	this->addButton->show();
	this->initFilterIterator();
	this->eventsListWidget->clear();
	Event event=*(this->admint_list_iterator);
	char buffer[200];
	event.toStr(buffer);

	QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(buffer) };
	QFont font{ "Verdana", 15, 10 };
	item->setFont(font);
	this->eventsListWidget->addItem(item);
}

void UserGUI::seeUserListButtonHandler()
{
	this->eventsListWidget->clear();
	this->removeButton->show();
	this->openFileButton->show();
	this->nextButton->hide();
	this->addButton->hide();
	for (auto s : this->user_service.getAll())
	{
		char buffer[200] = "";
		s.toStr(buffer);
		this->eventsListWidget->addItem(QString::fromStdString(buffer));
	}
}

void UserGUI::nextButtonHandler()
{
	this->admint_list_iterator++;
	if (this->admint_list_iterator == this->filtered_events.end()) {
		this->initFilterIterator();
	}
	Event event = *(this->admint_list_iterator);
	char buffer[200];
	event.toStr(buffer);
	this->eventsListWidget->clear();

	QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(buffer) };
	QFont font{ "Verdana", 15, 10 };
	item->setFont(font);
	this->eventsListWidget->addItem(item);
}

void UserGUI::initFilterIterator()
{
	int month = atoi(this->filterMonth->text().toStdString().c_str());
	if (month <= 0 or month > 12)
		month = 0;

	this->admin_service.getAllByMonth(filtered_events, month);
	this->admint_list_iterator = filtered_events.begin();
}

void UserGUI::openFileButtonHandler()
{
	this->data_saver->openFile();
}
