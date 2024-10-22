#include "MainGUI.h"
#include <qlayout.h>
#include <qlabel.h>

MainGUI::MainGUI(AdminGUI _admin_gui, UserGUI _user_gui):admin_gui{_admin_gui}, user_gui{_user_gui}
{
	this->buildGUI();
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &MainGUI::adminButtonHandler);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &MainGUI::userButtonHandler);

}

void MainGUI::buildGUI()
{
	QGridLayout* mainLayout = new QGridLayout{ this };
	QLabel* Choose = new QLabel{ "CHOOSE" };
	QLabel* Mode = new QLabel{ "MODE" };
	this->adminButton = new QPushButton{ "Admin" };
	this->userButton = new QPushButton{ "User" };

	mainLayout->addWidget(Choose, 0,0,Qt::AlignRight);
	mainLayout->addWidget(Mode, 0, 1, Qt::AlignLeft);

	mainLayout->addWidget(adminButton, 1, 0);
	mainLayout->addWidget(userButton, 1, 1);


}

void MainGUI::userButtonHandler()
{
	admin_gui.hide();
	user_gui.show();
}

void MainGUI::adminButtonHandler()
{
	user_gui.hide();
	admin_gui.show();
}
