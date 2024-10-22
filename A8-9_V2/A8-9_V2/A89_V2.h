#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_A89_V2.h"

class A89_V2 : public QMainWindow
{
    Q_OBJECT

public:
    A89_V2(QWidget *parent = nullptr);
    ~A89_V2();

private:
    Ui::A89_V2Class ui;
};
