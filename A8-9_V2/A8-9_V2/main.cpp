#include <QtWidgets/QApplication>
#include "AdminGUI.h"
#include "UserGUI.h"
#include "MainGUI.h"

void addDefaultEvents(ServiceText admin_service) {
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

	DateTime date_time6{ 1,12,2004,4,1 };
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repo repo{};
    ServiceText admin_serv{"repo.in"};
	//addDefaultEvents(admin_serv);
    Service user_serv{};
    AdminGUI admin_gui{ admin_serv};
    UserGUI user_gui{ admin_serv,user_serv };
    //gui.show();
    //user_gui.show();
    //gui.hide();
    MainGUI main_gui{admin_gui,user_gui};
    main_gui.show();
    return a.exec();
}
