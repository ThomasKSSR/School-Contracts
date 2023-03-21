#include "OOP1011.h"
#include <QtWidgets/QApplication>

#include "tests.h"
#include <iostream>

//#include "repository.h"
#include "service.h"
#include "validare.h"
//#include "contract.h"
#include "SubjectGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tests t;
    t.run_all_tests();

    FileSubjectsRepo filerepo("Subjects.txt");
    Validator valid;
    ContractStudiu contract;

    SubjectSrv srv(filerepo, valid, contract);

    SubjectsGui gui(srv);

    
    //OOP1011 w;
    
    gui.show();
   
    //w.show();
    return a.exec();
}
