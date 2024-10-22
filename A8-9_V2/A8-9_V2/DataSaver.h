#pragma once
#undef _HAS_STD_BYTE
#include <vector>
#undef _HAS_STD_BYTE
#include "Event.h"
#undef _HAS_STD_BYTE
#include <fstream>
#undef _HAS_STD_BYTE
#include <sstream>
#undef _HAS_STD_BYTE
#include <Windows.h>
#undef _HAS_STD_BYTE
#include <shellapi.h>
#undef _HAS_STD_BYTE
#undef _HAS_STD_BYTE

class DataSaver
{
public:
	virtual void saveToFile(const std::vector<Event> events) const;
	virtual void openFile() const;
};

class DataSaverCSV : public DataSaver
{
public:
	void saveToFile(const std::vector<Event> events) const override;
	virtual void openFile() const;
};

class DataSaverHTML : public DataSaver
{
public:
	void saveToFile(const std::vector<Event> events) const override;
	virtual void openFile() const;
};

