#include "ui.h"



const void Ui::menu() {
	cout << "1->add\n";
	cout << "2->delete\n";
	cout << "3->modify\n";
	cout << "4->print subjects\n";
	cout << "5->add_contract\n";
	cout << "6->generate_contract\n";

	cout << "0->exit\n";

}




const void Ui::ui_add_sub()
{
	int id;
	double hours;
	string name, type, teacher;
	cout << "Insert id: \n";
	cin >> id;
	cout << "Insert name: \n";
	cin >> name;
	cout << "Insert hours: \n";
	cin >> hours;
	cout << "Insert type: \n";
	cin >> type;
	cout << "Insert teacher: \n";
	cin >> teacher;
	try {
		srv.srv_add_sub(id, name, hours, type, teacher);
	}
	catch (RepoException& e) {
		cout << e.get_msg();

	}
	cout << "Subject added succesfully!\n";

}

const void Ui::ui_delete_sub()
{
	int id_del;
	cout << "Insert id: \n";
	cin >> id_del;
	try {
		srv.srv_delete_sub(id_del);
	}
	catch (RepoException& e) {
		cout << e.get_msg();
	}
	cout << "Subject deleted succesfully!\n";

}

const void Ui::ui_modify_sub()
{
	int id_mod;
	double hours;
	string name, type, teacher;
	cout << "Insert id: \n";
	cin >> id_mod;
	cout << "Insert name: \n";
	cin >> name;
	cout << "Insert hours: \n";
	cin >> hours;
	cout << "Insert type: \n";
	cin >> type;
	cout << "Insert teacher: \n";
	cin >> teacher;
	srv.srv_modify_sub(id_mod, name, hours, type, teacher);
	try {
		srv.srv_modify_sub(id_mod, name, hours, type, teacher);
	}
	catch (RepoException& e) {
		cout << e.get_msg();

	}
	

}

const void Ui::ui_print_subs()
{
	vector <Subject> subs = srv.srv_get_all();
	//VectorDinamic<Subject> subs = srv.srv_get_all();
	//IteratorVector<Subject> it(subs);
	for (auto sub : subs) {
		
		cout << sub.get_id_sub() << " " << sub.get_name() << " " << sub.get_hours() << " " << sub.get_type() << " " << sub.get_teacher() << " \n";
	}
	/*while(it.valid()) {
		Subject sub = it.element();
		cout << sub.get_id_sub() << " " << sub.get_name() << " " << sub.get_hours() << " " << sub.get_type() << " " << sub.get_teacher() << " \n";
		it.next();
	}*/
}
const void Ui::ui_add_contract() {
	int id;
	string name,type, teacher;
	double hours;

	cout << "Insert id: \n";
	cin >> id;
	cout << "Insert name: \n";
	cin >> name;
	cout << "Insert hours: \n";
	cin >> hours;
	cout << "Insert type: \n";
	cin >> type;
	cout << "Insert teacher: \n";
	cin >> teacher;
	try {
		srv.add_contract(id, name, hours, type, teacher);
	}
	catch (SrvException& s) {
		cout << s.get_msg();
	}
	catch (ValidException& v) {
		cout << v.get_msg();
	}
	vector<Subject> contract_list = srv.get_all_contract();
	for (auto sub : contract_list) {
		
		cout << sub.get_id_sub() << " " << sub.get_name() << " " << sub.get_hours() << " " << sub.get_type() << " " << sub.get_teacher() << " \n";
	}
}

const void Ui::ui_generate_contract()
{
	int n;
	cout << "Insert how many subjects: \n";
	cin >> n;
	try {
		srv.generate_contract(n);
	}
	catch (SrvException& s) {
		cout << s.get_msg();
	}

	vector<Subject> contract_list = srv.get_all_contract();
	for (auto sub : contract_list) {

		cout << sub.get_id_sub() << " " << sub.get_name() << " " << sub.get_hours() << " " << sub.get_type() << " " << sub.get_teacher() << " \n";
	}
}

const void Ui::ui_empty_contract()
{
	srv.empty_contract();
	cout << "Contract golit";
}



const void Ui::run()
{
	menu();
	int cmd;
	while (1) {
		cin >> cmd;
		if (cmd == 1) {
			ui_add_sub();
		}
		else if (cmd == 2) {
			ui_delete_sub();
		}
		else if (cmd == 3) {
			ui_modify_sub();
		}
		else if (cmd == 4) {
			ui_print_subs();
		}
		else if (cmd == 5) {
			ui_add_contract();
		}
		else if (cmd == 6) {
			ui_generate_contract();
		}
		else if (cmd == 7) {
			ui_empty_contract();
		}
		else if (cmd == 0) {
			return;
		}
	}

}
