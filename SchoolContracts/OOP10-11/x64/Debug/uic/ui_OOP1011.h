/********************************************************************************
** Form generated from reading UI file 'OOP1011.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OOP1011_H
#define UI_OOP1011_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OOP1011Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OOP1011Class)
    {
        if (OOP1011Class->objectName().isEmpty())
            OOP1011Class->setObjectName(QString::fromUtf8("OOP1011Class"));
        OOP1011Class->resize(600, 400);
        menuBar = new QMenuBar(OOP1011Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        OOP1011Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OOP1011Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        OOP1011Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(OOP1011Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        OOP1011Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OOP1011Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        OOP1011Class->setStatusBar(statusBar);

        retranslateUi(OOP1011Class);

        QMetaObject::connectSlotsByName(OOP1011Class);
    } // setupUi

    void retranslateUi(QMainWindow *OOP1011Class)
    {
        OOP1011Class->setWindowTitle(QCoreApplication::translate("OOP1011Class", "OOP1011", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OOP1011Class: public Ui_OOP1011Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OOP1011_H
