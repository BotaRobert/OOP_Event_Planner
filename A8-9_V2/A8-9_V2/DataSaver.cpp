#undef _HAS_STD_BYTE
#include "DataSaver.h"
#undef _HAS_STD_BYTE

void DataSaverCSV::saveToFile(const std::vector<Event> events) const
{
	std::ofstream fout{ "data.csv" };
	for (auto ev : events) {
		std::stringstream buffer;
		std::string b = ev.getDateTime().toStr();
		buffer << ev.getTitle() << "," << ev.getDescription() << ","
			<< b << "," << ev.getPeopleNo() << "," << ev.getLink();
		fout << buffer.str() << std::endl;
	}
}

void DataSaverCSV::openFile() const
{
	ShellExecuteA(NULL, NULL, "excel.exe", "data.csv", 
		NULL, SW_SHOWMAXIMIZED);
}

void DataSaverHTML::saveToFile(const std::vector<Event> events) const
{
	std::ofstream fout{ "data.html"};
	fout << "<!DOCTYPE html>\n";
	fout << "<html> \n";
	fout << "<head> \n";
	fout << "<title>Events List</title>\n";
	fout << "</head>\n";
	fout << "<body>\n";
	fout << "<table border=\"1\">";
	for (auto ev : events) {
		std::string dt = ev.getDateTime().toStr();
		fout << "\t<tr>\n" << std::endl;
		fout << "\t\t<td>"<<ev.getTitle()<<"</td>\n" << std::endl;
		fout << "\t\t<td>"<<ev.getDescription()<<"</td>\n" << std::endl;
		fout << "\t\t<td>"<<dt<<"\n" << std::endl;
		fout << "\t\t<td>"<<ev.getPeopleNo()<<"</td>\n" << std::endl;
		fout << "\t\t<td><a href=" << ev.getLink() << ">Link</a></td>\n" << std::endl;
		fout << "\t</tr>\n" << std::endl;
	}
	fout << "</table>\n";
	fout << "</body>\n";
	fout << "</html>\n";
}

void DataSaverHTML::openFile() const
{
	ShellExecuteA(NULL, NULL, "chrome.exe", R"("file://C:\Users\Robert\source\repos\OOP A6-7\new OOP A4-5\data.html")",
		NULL, SW_SHOWMAXIMIZED);
}

void DataSaver::saveToFile(const std::vector<Event> events) const
{
	throw std::exception("No save type selected");
}

void DataSaver::openFile() const
{
	throw std::exception("No save type selected");
}
