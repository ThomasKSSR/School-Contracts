#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOP1011.h"

class OOP1011 : public QMainWindow
{
    Q_OBJECT

public:
    OOP1011(QWidget *parent = Q_NULLPTR);

private:
    Ui::OOP1011Class ui;
};
