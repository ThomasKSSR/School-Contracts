#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include "service.h"
#include "Observer.h"
#include "GuiRDONLY.h"
#include "MyListModel.h"
using std::vector;
using std::string;

class SubjectsGui : public QWidget {
private:
	SubjectSrv& srv;
	QLabel* lblID = new QLabel{ "Id Subject:" };
	QLabel* lblName = new QLabel{ "Name Subject:" };
	QLabel* lblHours = new QLabel{ "Hours Subject:" };
	QLabel* lblType = new QLabel{ "Type Subject" };
	QLabel* lblTeacher = new QLabel{ "Teacher Subject" };

	QHBoxLayout* lyMain;
	QWidget* left;
	QVBoxLayout* lyLeft;
	QLineEdit* editID;
	QLineEdit* editName;
	QLineEdit* editHours;
	QLineEdit* editType;
	QLineEdit* editTeacher;

	QPushButton* btnAddSubject;
	QPushButton* btnDelSubject;
	QPushButton* btnModSubject;
	QPushButton* btnFindSubject;

	QPushButton* btnReloadData;
	QPushButton* btnUndo;

	QPushButton* btntypesort;
	QPushButton* btnnamesort;
	QPushButton* btntypefilter;
	QPushButton* btnteacherfilter;

	QPushButton* btncontr;

	/*QListWidget* contrlist;
	QPushButton* btncontr;
	QPushButton* btnclearcontr;
	QPushButton* btngeneratecontr;
	QPushButton* btnaddcontr;*/

	/*QLabel* addcontrlabel;
	QLineEdit* addlinecontr;

	QLabel* generatenmlabel;
	QLineEdit* generatenmline;

	QListWidget* lst;*/

	QTableWidget* SubjectsTable;

	vector<std::string> butoane;
	map<QPushButton*,int> butoanereal;

	/*QWidget* nou;
	QVBoxLayout* vl;*/
	QWidget* nou = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	

	void initializareGUIComponents();
	//void connectSignalsSlots();
	void reloadSubjectList(vector<Subject> subs);
	void afistype(string type);
	void connectSignalsSlots();
public:
	SubjectsGui(SubjectSrv& srv) : srv{ srv } {
		initializareGUIComponents();
		//connectSignalsSlots();
		reloadSubjectList(srv.srv_get_all());
		addbtns();
		connectSignalsSlots();
		//addlbtns();
	};

	~SubjectsGui() = default;
	void guiAddSubject();
	void guiDelSubject();
	void guiModSubject();
	void guiUndo();
	void addbtns();
	void addlbtns();
	void guiNameSort();
	void guiTypeSort();
	void guiTypeFilter();
	void guiTeacherFilter();

	//void guiContractCreate();

	/*void guiContractCreate();
	void guiConnectSingalsContract();
	void guiaddContract();
	void generateContract();
	void clearContract();
	void refreshContract(vector<Subject> subs);*/
};


class ContractList : public SubjectsGui,public Observer{

private:
	SubjectSrv& srv;

	//QListWidget* contrlist;
	MyListModel* contrlist;
	QListView* contrlistview = new QListView;
	QPushButton* btncontr;
	QPushButton* btnclearcontr;
	QPushButton* btngeneratecontr;
	QPushButton* btnaddcontr;

	QLabel* addcontrlabel;
	QLineEdit* addlinecontr;

	QLabel* generatenmlabel;
	QLineEdit* generatenmline;

	QListWidget* lst;

	void guiContractCreate();
	void guiConnectSingalsContract();
	void guiaddContract();
	void generateContract();
	void clearContract();
	void refreshContract(vector<Subject> subs);

	void update() override {
		refreshContract(srv.get_all_contract());

	};
public:
	
	ContractList(SubjectSrv& srv) :SubjectsGui{ srv }, srv { srv } {
		guiContractCreate();
		contrlist = new MyListModel(srv.get_all_contract());
		contrlistview->setModel(contrlist);
		guiConnectSingalsContract();

		refreshContract(srv.get_all_contract());
		srv.addObserver(this);
	};



};