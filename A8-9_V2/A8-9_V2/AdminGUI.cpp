#include "AdminGUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include <exception>
#include <QMessageBox>
AdminGUI::AdminGUI(AdminGUI& ag) : admin_service{ ag.admin_service }
{
	this->buildGUI();
	this->populateList();

	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::removeButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateButtonHandler);

}

AdminGUI::AdminGUI(ServiceText& admint_serv) : admin_service{ admint_serv }
{
	this->admin_service.readFromFile();
	this->buildGUI();
	this->populateList();

	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addButtonHandler);
}


void AdminGUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	this->eventsListWidget = new QListWidget{};
	mainLayout->addWidget(eventsListWidget);
	

	QGridLayout* rightLayout = new QGridLayout{};

	QLabel* titleLabel = new QLabel{ "Title" };
	this->titleEdit = new QLineEdit{};
	QLabel* discriptionLabel = new QLabel{ "Description" };
	this->descriptionEdit = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "Link" };
	this->linkEdit = new QLineEdit{};

	QLabel* dayLabel = new QLabel{ "Day" };
	this->dayEdit = new QLineEdit{};
	QLabel* yearLabel = new QLabel{ "Year" };
	this->yearEdit = new QLineEdit{};
	QLabel* monthLabel = new QLabel{ "Month" };
	this->monthEdit = new QLineEdit{};
	QLabel* hourLabel = new QLabel{ "Hour" };
	this->hourEdit = new QLineEdit{};
	QLabel* minuteLabel = new QLabel{ "Minute" };
	this->minuteEdit = new QLineEdit{};
	QLabel* noOfPeopleLabel = new QLabel{ "Number of People" };
	this->noOfPeopleEdit = new QLineEdit{};

	rightLayout->addWidget(titleLabel, 0, 0);
	rightLayout->addWidget(this->titleEdit, 0, 1);
	rightLayout->addWidget(discriptionLabel, 1, 0);
	rightLayout->addWidget(this->descriptionEdit, 1, 1);
	rightLayout->addWidget(linkLabel, 2, 0);
	rightLayout->addWidget(this->linkEdit, 2, 1);

	rightLayout->addWidget(dayLabel, 3, 0);
	rightLayout->addWidget(this->dayEdit, 3, 1);
	rightLayout->addWidget(monthLabel, 4, 0);
	rightLayout->addWidget(this->monthEdit, 4, 1);
	rightLayout->addWidget(yearLabel, 5, 0);
	rightLayout->addWidget(this->yearEdit, 5, 1);
	rightLayout->addWidget(hourLabel, 6, 0);
	rightLayout->addWidget(this->hourEdit, 6, 1);
	rightLayout->addWidget(minuteLabel, 7, 0);
	rightLayout->addWidget(this->minuteEdit, 7, 1);
	rightLayout->addWidget(noOfPeopleLabel, 8, 0);
	rightLayout->addWidget(this->noOfPeopleEdit, 8, 1);



	this->addButton = new QPushButton{ "Add" };
	this->deleteButton = new QPushButton{ "Delete" };
	this->updateButton = new QPushButton{ "Update" };


	rightLayout->addWidget(this->addButton, 9, 0);
	rightLayout->addWidget(this->deleteButton, 9, 1);
	rightLayout->addWidget(this->updateButton, 9, 2);

	mainLayout->addLayout(rightLayout);
}

void AdminGUI::populateList()
{
	this->eventsListWidget->clear();

	for (auto s : this->admin_service.getAll())
	{
		char buffer[200]="";
		s.toStr(buffer);

		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(buffer) };
		QFont font{ "Verdana", 12, 10 };
		item->setFont(font);
		this->eventsListWidget->addItem(item);
	}
}

void AdminGUI::addButtonHandler()
{
	try{
		this->admin_service.add(getEventFromGUI());
	}
	catch (std::exception& ex) {
		QMessageBox error_window{ this };
		error_window.setText(ex.what());
		error_window.exec();
	}
	this->populateList();
}

void AdminGUI::removeButtonHandler()
{
	auto event_item = this->eventsListWidget->currentItem();
	if (event_item==nullptr) {
		QMessageBox error_window{ this };
		error_window.setText("Please select an item\n");
		error_window.exec();
		return;
	}
	auto event_str = event_item->text().toStdString();
	int endl_pos = event_str.find("\n");
	std::string event_name = event_str.substr(0,endl_pos);
	admin_service.remove(event_name.c_str());
	this->populateList();
}

void AdminGUI::updateButtonHandler()
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
	try {
		admin_service.update(event_name.c_str(),this->getEventFromGUI());
	}
	catch (std::exception& ex) {
		QMessageBox error_window{ this };
		error_window.setText(ex.what());
		error_window.exec();
	}
	this->populateList();
}

Event& AdminGUI::getEventFromGUI()
{
	QString title = this->titleEdit->text();
	QString description = this->descriptionEdit->text();
	QString link = this->linkEdit->text();
	QString day = this->dayEdit->text();
	QString month = this->monthEdit->text();
	QString year = this->yearEdit->text();
	QString hour = this->hourEdit->text();
	QString minute = this->minuteEdit->text();
	QString noOfPeople = this->noOfPeopleEdit->text();
	
	Event new_ev{
		title.toStdString().c_str(),
		description.toStdString().c_str(),
		DateTime(
			atoi(day.toStdString().c_str()),
			atoi(month.toStdString().c_str()),
			atoi(year.toStdString().c_str()),
			atoi(hour.toStdString().c_str()),
			atoi(minute.toStdString().c_str())),
			atoi(noOfPeople.toStdString().c_str()
		),
		link.toStdString().c_str(),
	};

	return new_ev;
	
}
