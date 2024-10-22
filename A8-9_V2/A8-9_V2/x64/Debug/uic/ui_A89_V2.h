/********************************************************************************
** Form generated from reading UI file 'A89_V2.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A89_V2_H
#define UI_A89_V2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_A89_V2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *A89_V2Class)
    {
        if (A89_V2Class->objectName().isEmpty())
            A89_V2Class->setObjectName("A89_V2Class");
        A89_V2Class->resize(600, 400);
        menuBar = new QMenuBar(A89_V2Class);
        menuBar->setObjectName("menuBar");
        A89_V2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(A89_V2Class);
        mainToolBar->setObjectName("mainToolBar");
        A89_V2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(A89_V2Class);
        centralWidget->setObjectName("centralWidget");
        A89_V2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(A89_V2Class);
        statusBar->setObjectName("statusBar");
        A89_V2Class->setStatusBar(statusBar);

        retranslateUi(A89_V2Class);

        QMetaObject::connectSlotsByName(A89_V2Class);
    } // setupUi

    void retranslateUi(QMainWindow *A89_V2Class)
    {
        A89_V2Class->setWindowTitle(QCoreApplication::translate("A89_V2Class", "A89_V2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class A89_V2Class: public Ui_A89_V2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A89_V2_H
