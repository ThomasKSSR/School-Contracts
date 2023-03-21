#include "SubjectGUI.h"

void SubjectsGui::initializareGUIComponents()
{
	 lyMain = new QHBoxLayout;
	this->setLayout(lyMain);
	
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editID = new QLineEdit;
	editName = new QLineEdit;
	editHours = new QLineEdit;
	editType = new QLineEdit;
	editTeacher = new QLineEdit;

	lyForm->addRow(lblID, editID);
	lyForm->addRow(lblName, editName);
	lyForm->addRow(lblHours, editHours);
	lyForm->addRow(lblType, editType);
	lyForm->addRow(lblTeacher, editTeacher);
	btnAddSubject = new QPushButton("Add Subject");
	lyForm->addWidget(btnAddSubject);

	btnReloadData = new QPushButton("Reload Data");
	lyForm->addWidget(btnReloadData);

	QWidget* oriz = new QWidget;
	QHBoxLayout* lyoriz = new QHBoxLayout;
	oriz->setLayout(lyoriz);
	btnDelSubject = new QPushButton("Delete Subject");
	lyoriz->addWidget(btnDelSubject);
	btnModSubject = new QPushButton("Modify Subject");
	lyoriz->addWidget(btnModSubject);
	btnFindSubject = new QPushButton("Find Subject");
	lyoriz->addWidget(btnFindSubject);
	
	QWidget* oriz2 = new QWidget;
	QHBoxLayout* lyoriz2 = new QHBoxLayout;
	oriz2->setLayout(lyoriz2);
	btnUndo = new QPushButton("Undo");
	lyoriz2->addWidget(btnUndo);

	QWidget* oriz3 = new QWidget;
	QHBoxLayout* lyoriz3 = new QHBoxLayout;
	oriz3->setLayout(lyoriz3);
	btnnamesort = new QPushButton("Name Sort");
	btntypesort = new QPushButton("Type Sort");
	btntypefilter = new QPushButton("Type Filter");
	btnteacherfilter = new QPushButton("Teacher Filter");
	lyoriz3->addWidget(btnnamesort);
	lyoriz3->addWidget(btntypesort);
	lyoriz3->addWidget(btntypefilter);
	lyoriz3->addWidget(btnteacherfilter);

	QWidget* Contract = new QWidget;
	QHBoxLayout* lyContract = new QHBoxLayout;
	Contract->setLayout(lyContract);
	btncontr = new QPushButton("Contract");
	lyContract->addWidget(btncontr);

	lyLeft->addWidget(form);
	lyLeft->addWidget(oriz);
	lyLeft->addWidget(oriz2);
	lyLeft->addWidget(oriz3);
	lyLeft->addWidget(Contract);
	lyMain->addWidget(left);
	
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColums = 5;
	this->SubjectsTable = new QTableWidget{ noLines,noColums };

	QStringList tblHeaderList;
	tblHeaderList << "ID" << "Name" << "Hours" << "Type" << "Teacher";
	this->SubjectsTable->setHorizontalHeaderLabels(tblHeaderList);

	this->SubjectsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	lyRight->addWidget(SubjectsTable);
	lyMain->addWidget(right);

	/*QWidget* nou = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;*/
	nou->setLayout(vl);
	lyMain->addWidget(nou);
	//lyMain->addWidget(nou);
	//QWidget* nou = new QWidget;
	//QVBoxLayout* vl = new QVBoxLayout;
	/*nou->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lst);
	lyMain->addWidget(nou);*/
	
}

void SubjectsGui::connectSignalsSlots()
{
	QObject::connect(btnAddSubject, &QPushButton::clicked, this, &SubjectsGui::guiAddSubject);
	QObject::connect(btnDelSubject, &QPushButton::clicked, this, &SubjectsGui::guiDelSubject);
	QObject::connect(btnModSubject, &QPushButton::clicked, this, &SubjectsGui::guiModSubject);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &SubjectsGui::guiUndo);

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		reloadSubjectList(srv.srv_get_all());
		});
	/*int poz = 0;
	for (auto but : butoanereal) {
		QObject::connect(but, &QPushButton::clicked, [&]() {
			afistype(butoane.at(poz));
			});
		poz++;
	}*/

	QObject::connect(btnteacherfilter, &QPushButton::clicked, this, &SubjectsGui::guiTeacherFilter);
	QObject::connect(btntypefilter, &QPushButton::clicked, this, &SubjectsGui::guiTypeFilter);
	QObject::connect(btnnamesort, &QPushButton::clicked, this, &SubjectsGui::guiNameSort);
	QObject::connect(btntypesort, &QPushButton::clicked, this, &SubjectsGui::guiTypeSort);

	QObject::connect(btncontr, &QPushButton::clicked,[&](){
		ContractList* contract = new ContractList(srv);
		Imgdraw* imgdraw = new Imgdraw(srv);
		
		});

}

void SubjectsGui::reloadSubjectList(vector<Subject> subs)
{
	SubjectsTable->clearContents();
	SubjectsTable->setRowCount(subs.size());

	int linenumber = 0;
	for (auto& sub : subs) {
		this->SubjectsTable->setItem(linenumber, 0, new QTableWidgetItem(QString::number(sub.get_id_sub())));
		this->SubjectsTable->setItem(linenumber, 1, new QTableWidgetItem(QString::fromStdString(sub.get_name())));
		this->SubjectsTable->setItem(linenumber, 2, new QTableWidgetItem(QString::number(sub.get_hours())));
		this->SubjectsTable->setItem(linenumber, 3, new QTableWidgetItem(QString::fromStdString(sub.get_type())));
		this->SubjectsTable->setItem(linenumber, 4, new QTableWidgetItem(QString::fromStdString(sub.get_teacher())));
		linenumber++;

	}
	addbtns();
}

void SubjectsGui::afistype(std::string type)
{
	map<std::string, int> raport = srv.raport_type();
	QMessageBox::information(this, "Info", QString::number(raport[type]));
}

void SubjectsGui::guiAddSubject()
{
	try {
		int Id = editID->text().toInt();
		string Name = editName->text().toStdString();
		double Hours = editHours->text().toDouble();
		string type = editType->text().toStdString();
		string teacher = editTeacher->text().toStdString();

		editID->clear();
		editName->clear();
		editHours->clear();
		editType->clear();
		editTeacher->clear();

		this->srv.srv_add_sub(Id, Name, Hours, type, teacher);
		
		QMessageBox::information(this, "Info", QString::fromStdString("Subject added succesfully!"));
		this->reloadSubjectList(srv.srv_get_all());
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_msg()));
	}
	catch (ValidException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_msg()));
	}
	
}

void SubjectsGui::guiDelSubject()
{
	try {
		int id = editID->text().toInt();

		editID->clear();
		editName->clear();
		editHours->clear();
		editType->clear();
		editTeacher->clear();

		Subject fake_sub(id, "dsa", 213, "dsada", "ads");
		std::string type;
		for (auto sub : srv.srv_get_all()) {
			if (fake_sub == sub) {
				type = sub.get_type();
			}
		}

		this->srv.srv_delete_sub(id);
		QMessageBox::information(this, "Info", QString::fromStdString("Subject deleted succesfully!"));
		

		QPushButton* btn = new QPushButton(QString::fromStdString(type));

		butoanereal[btn]--;
		for (auto& sub : butoanereal) {
			if (sub.second == 0) {
				butoanereal.erase(sub.first);
				//delete sub.first;
			}
		}
		this->reloadSubjectList(srv.srv_get_all());

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_msg()));
	}
	catch (ValidException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_msg()));
	}
	catch (SrvException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_msg()));
	}
}

void SubjectsGui::guiModSubject()
{
	try {
		int Id = editID->text().toInt();
		string Name = editName->text().toStdString();
		double Hours = editHours->text().toDouble();
		string type = editType->text().toStdString();
		string teacher = editTeacher->text().toStdString();

		editID->clear();
		editName->clear();
		editHours->clear();
		editType->clear();
		editTeacher->clear();

		srv.srv_modify_sub(Id, Name, Hours, type, teacher);
		QMessageBox::information(this, "Info", QString::fromStdString("Subject modified succesfully!"));
		this->reloadSubjectList(srv.srv_get_all());
		
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.get_msg()));
	}
	catch (ValidException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_msg()));
	}
	catch (SrvException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_msg()));
	}
}

void SubjectsGui::guiUndo()
{
	try {
		srv.Undo();
		this->reloadSubjectList(srv.srv_get_all());
	}
	catch (SrvException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_msg()));
	}
}

void SubjectsGui::addbtns()
{
	

	map<std::string, int> raport = srv.raport_type();

	for (auto it : butoanereal) {
		QPushButton* btn = it.first;
		if (raport.find((it.first)->text().toStdString()) == raport.end()) {
			butoanereal.erase(it.first);
			QObject::disconnect(btn);
			btn->hide();
			break;
		}
	}

	//map<std::string, int>::iterator it;
	butoanereal.clear();
	for (auto sub : raport) {
		auto it = std::find(butoane.begin(), butoane.end(), sub.first);
		if (it == butoane.end()) {
			butoane.push_back(sub.first);

			QPushButton* btn= new QPushButton(QString::fromStdString(sub.first));
			vl->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [sub]() {
				QMessageBox::information(nullptr, "Info", QString::number(sub.second));
				});
			
			butoanereal[btn] = 1;
			
		}
		else {
			QPushButton* btn = new QPushButton(QString::fromStdString(sub.first));
			butoanereal[btn]++;
		}
	}
	
}

void SubjectsGui::addlbtns()
{
	lyMain->addWidget(nou);
}

void SubjectsGui::guiNameSort()
{
	
	this->reloadSubjectList(srv.srv_sort_by_name());
}

void SubjectsGui::guiTypeSort()
{
	//srv.srv_sort_by_type_teacher();
	this->reloadSubjectList(srv.srv_sort_by_type_teacher());
}

void SubjectsGui::guiTypeFilter()
{
	string type = editType->text().toStdString();
	
	this->reloadSubjectList(srv.filterbytype(type));
}

void SubjectsGui::guiTeacherFilter()
{
	
	string teacher = editTeacher->text().toStdString();
	this->reloadSubjectList(srv.filterbyteacher(teacher));

}


void ContractList::guiContractCreate()
{
	QWidget* window = new QWidget;
	QHBoxLayout* Contractlayout = new QHBoxLayout;
	window->setLayout(Contractlayout);

	QWidget* ListWidget = new QWidget;
	QHBoxLayout* listlayout = new QHBoxLayout;
	ListWidget->setLayout(listlayout);
	//contrlist = new QListWidget;
	listlayout->addWidget(contrlistview);

	Contractlayout->addWidget(ListWidget);

	QWidget* EditContract = new QWidget;
	QVBoxLayout* lyEditContract = new QVBoxLayout;
	EditContract->setLayout(lyEditContract);

	QWidget* addContractWidget = new QWidget;
	QHBoxLayout* lyaddContractWidget = new QHBoxLayout;
	addContractWidget->setLayout(lyaddContractWidget);
	addcontrlabel = new QLabel("ID:");
	lyaddContractWidget->addWidget(addcontrlabel);

	addlinecontr = new QLineEdit;
	lyaddContractWidget->addWidget(addlinecontr);
	lyEditContract->addWidget(addContractWidget);

	btnaddcontr = new QPushButton("Add Subject");
	lyEditContract->addWidget(btnaddcontr);
	btnclearcontr = new QPushButton("Clear Contract");
	lyEditContract->addWidget(btnclearcontr);

	QWidget* generatenumber = new QWidget;
	QHBoxLayout* lygeneratenumber = new QHBoxLayout;
	generatenumber->setLayout(lygeneratenumber);

	generatenmlabel = new QLabel("Number of Subjects:");
	generatenmline = new QLineEdit;
	lygeneratenumber->addWidget(generatenmlabel);
	lygeneratenumber->addWidget(generatenmline);
	lyEditContract->addWidget(generatenumber);


	btngeneratecontr = new QPushButton("Generate Contract");
	lyEditContract->addWidget(btngeneratecontr);


	Contractlayout->addWidget(EditContract);

	window->show();
	/*guiConnectSingalsContract();
	refreshContract(srv.get_all_contract());*/
}

void ContractList::guiConnectSingalsContract()
{
	QObject::connect(btnaddcontr, &QPushButton::clicked, this, &ContractList::guiaddContract);
	QObject::connect(btnclearcontr, &QPushButton::clicked, this, &ContractList::clearContract);
	QObject::connect(btngeneratecontr, &QPushButton::clicked, this, &ContractList::generateContract);

}

void ContractList::guiaddContract()
{

	
	int id = addlinecontr->text().toInt();
	addlinecontr->clear();
	Subject sub_found;
	//if (srv.srv_find_sub(id) == true) {
		Subject subid(id, "sa", 12, "dsa", "das");
		vector<Subject> subs = srv.srv_get_all();
		for (auto sub : subs) {
			if (subid == sub) {
				sub_found = sub;
			}
		}
		try {
			srv.add_contract(id, sub_found.get_name(), sub_found.get_hours(), sub_found.get_type(), sub_found.get_teacher());
			refreshContract(srv.get_all_contract());
			//}
		}	
	catch(SrvException se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_msg()));
	}
	/*catch (ValidException ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.get_msg()));
	}*/
	

}

void ContractList::generateContract()
{
	int nr = generatenmline->text().toInt();
	try {
		srv.generate_contract(nr);

	}
	catch (SrvException se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.get_msg()));

	}
	refreshContract(srv.get_all_contract());
}
void ContractList::clearContract()
{
	srv.empty_contract();
	refreshContract(srv.get_all_contract());
}

void ContractList::refreshContract(vector<Subject> subs)
{
	/*contrlist->clear();
	for (const auto& sub : subs) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(sub.get_name()));
		contrlist->addItem(item);
	}*/
	contrlist->setSubs(subs);
}
