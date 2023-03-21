#include "Tests.h"

#include <iostream>
#include "validare.h"
#include "contract.h"
#include <map>
using std::map;

void Tests::test_domain()
{
	//Subject s;
	constexpr int id = 1;
	const string name = "Math";
	constexpr double hours = 200.2;
	string type = "Durere";
	string teacher = "Eusepius";

	Subject sub;
	Subject s1(id, name, hours, type, teacher);
	Subject s2(s1);
	assert(s1.get_id_sub() == id);
	assert(s1.get_hours() == hours);
	assert(s1.get_type() == type);
	assert(s1.get_teacher() == teacher);

}
void Tests::test_repo() {
	SubjectsRepo subs;
	assert(subs.repo_size() == 0);
	Subject sub1(23, "Math", 23.4, "Pain", "Hasbula");
	subs.repo_add_sub(sub1);
	assert(subs.repo_size() == 1);
	
	
	Subject sub_existent(23, "das",0.1, "Das", "das");
	try {
		subs.repo_add_sub(sub1);
		assert(false);
	}
	catch(RepoException &e) {
		assert(e.get_msg() == "Subject already exists!\n");
	}

	assert(subs.repo_find_sub(sub1) == true);
	
	
	constexpr int id_ers = 25;
	Subject sub_inex(id_ers, "das", 2.3, "dsa", "asd");
	assert(subs.repo_find_sub(sub_inex) == false);
	try {
		subs.repo_modify_sub(sub_inex);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.get_msg() == "Subject doesn't exist!\n");
	}
	Subject sub_modified(23, "Biology", 666.666, "Terror", "Hasbula");
	subs.repo_modify_sub(sub_modified);

	assert(subs.repo_size() == 1);

	const vector<Subject>& get_all = subs.repo_get_all_subs();
	//const VectorDinamic<Subject> get_all = subs.repo_get_all_subs();
	/*assert(get_all.at(0).get_id_sub() == 23);
	assert(get_all.at(0).get_name() == "Biology");*/
	
	
	try {
		subs.repo_delete_sub_id(id_ers);
		assert(false);
	}
	catch (RepoException& e) {
		assert(e.get_msg() == "Subject doesn't exist!\n");
	}
	assert(subs.repo_size() == 1);
	subs.repo_delete_sub_id(23);
	assert(subs.repo_size() == 0);


}

void Tests::test_service()
{
	SubjectsRepo repo;
	Validator valid;
	ContractStudiu contract;
	SubjectSrv srv(repo,valid,contract);
	assert(repo.repo_size() == 0);
	Subject sub(23, "Biology", 666.666, "Terror", "Hasbula");
	Subject sub_modify(23, "Math", 6.6, "Pain", "Hasbula");
	
	srv.srv_add_sub(23, "Biology", 666.666, "Terror", "Hasbula"); 
	assert(srv.srv_find_sub(23) == true);
	assert(srv.srv_find_sub(26) == false);
	srv.srv_modify_sub(23, "Math", 6.6, "Pain", "Hasbula");
	srv.srv_delete_sub(23);

	const vector<Subject>& subs= srv.srv_get_all();
	//const VectorDinamic<Subject> subs = srv.srv_get_all();

}

void Tests::test_sort()
{
	SubjectsRepo repo;
	Validator valid;
	ContractStudiu contract;
	SubjectSrv srv(repo,valid,contract);
	srv.srv_add_sub(23, "A", 6.6, "A", "B");
	srv.srv_add_sub(26, "C", 2.4, "A", "A");
	srv.srv_add_sub(20, "B", 1.2, "B", "Hasbula");
	
	
	
	vector <Subject> sorted_subs = srv.srv_sort_by_name();


	assert(sorted_subs.at(0).get_id_sub() == 23);
	assert(sorted_subs.at(1).get_id_sub() == 20);
	assert(sorted_subs.at(2).get_id_sub() == 26);


	vector <Subject> sorted_subs2 = srv.srv_sort_by_hours();
	assert(sorted_subs2.at(0).get_id_sub() == 20);
	assert(sorted_subs2.at(1).get_id_sub() == 26);
	assert(sorted_subs2.at(2).get_id_sub() == 23);

	vector <Subject> sorted_subs3 = srv.srv_sort_by_type_teacher();
	assert(sorted_subs3.at(0).get_id_sub() == 26);
	assert(sorted_subs3.at(1).get_id_sub() == 23);
	assert(sorted_subs3.at(2).get_id_sub() == 20);

	

}

void Tests::test_filtrare() {
	
	{
		SubjectsRepo repotest;
		Validator validtest;
		ContractStudiu contract;
		SubjectSrv srvtest(repotest,validtest,contract);
		srvtest.srv_add_sub(23, "A", 6.6, "A", "B");
		srvtest.srv_add_sub(25, "A", 6.6, "A", "B");
		srvtest.srv_add_sub(28, "A", 6.6, "A", "B");
		srvtest.srv_add_sub(29, "A", 6.6, "C", "B");
		vector<Subject>res1 = srvtest.filterbyteacher("B");
		assert(res1.size() == 4);
		vector<Subject>res = srvtest.filterbytype("C");
		assert(res.size() == 1);
	}
}

void Tests::test_validare() {
	Validator valid;
	SubjectsRepo repo;
	ContractStudiu contract;
	SubjectSrv srv(repo,valid,contract);
	
	Subject sub(-23, "", -20, "", "");
	try {
		srv.srv_add_sub(-23, "", -20, "", "");
	}
	catch (ValidException& e) {
		assert(e.get_msg() == "Invalid Subject!\n");
	}
}

void Tests::test_contract()
{
	SubjectsRepo repotest;
	Validator validtest;
	ContractStudiu contract;
	SubjectSrv srvtest(repotest, validtest, contract);
	srvtest.srv_add_sub(23, "A", 6.6, "A", "B");
	srvtest.srv_add_sub(25, "A", 6.6, "A", "B");
	srvtest.srv_add_sub(28, "A", 6.6, "A", "B");
	srvtest.srv_add_sub(29, "A", 6.6, "C", "B");
	
	srvtest.add_contract(23, "A", 6.6, "A", "B");
	vector<Subject> contract1 = srvtest.get_all_contract();
	assert(contract1.size() == 1);
	try {
		srvtest.add_contract(33, "A", 6.6, "A", "B");
	}
	catch (SrvException& s) {
		assert(s.get_msg() == "Subject doesn't exist in repository!\n");
	}

	try {
		srvtest.add_contract(-20, "A", 6.6, "A", "B");
	}
	catch (ValidException& v) {
		assert(v.get_msg() == "Invalid Subject!\n");
	}

	int n = 5;
	try {
		srvtest.generate_contract(n);
	}
	catch (SrvException& s) {
		assert(s.get_msg() == "There are not enough Subjects in repository\n");
	}
	int n2 = 1;
	srvtest.generate_contract(n2);
	vector<Subject> contract2 = srvtest.get_all_contract();
	assert(contract2.size() == 1);
	srvtest.empty_contract();
	vector<Subject> contract3 = srvtest.get_all_contract();
	assert(contract3.size() == 0);
}

void Tests::test_raport()
{
	SubjectsRepo repotest;
	Validator validtest;
	ContractStudiu contract;
	SubjectSrv srvtest(repotest, validtest, contract);
	srvtest.srv_add_sub(23, "A", 6.6, "A", "B");
	srvtest.srv_add_sub(25, "A", 6.6, "A", "B");
	srvtest.srv_add_sub(28, "A", 6.6, "A", "B");
	srvtest.srv_add_sub(29, "A", 6.6, "C", "B");
	map<std::string, int> raport= srvtest.raport_type();
	assert(raport["A"] == 3);
	assert(raport["C"] == 1);
}

void Tests::test_file_repo()
{
	try {
		FileSubjectsRepo filerepo("testfilerepo-1.txt");
	}
	catch (RepoException re) {
		assert(re.get_msg() == "testfilerepo-1.txt didn't open!");
	}
	FileSubjectsRepo filerepo("testfilerepo1.txt");

	Subject sub1(27, "Math", 3.4, "dsa", "ads");
	Subject sub2(29, "Math", 3.4, "dsa", "ads");
	try {
		filerepo.repo_add_sub(sub1);

	}
	catch (RepoException re) {
		assert(re.get_msg() == "Subject already exists!\n");
	}
	try {
		filerepo.repo_add_sub(sub2);

	}
	catch (RepoException re) {
		assert(re.get_msg() == "Subject already exists!\n");
	}
	assert(filerepo.repo_size() == 2);
	filerepo.repo_delete_sub_id(29);
	assert(filerepo.repo_size() == 1);
	Subject sub_modify(27, "Info", 9.2, "sda", "Hasbula");
	filerepo.repo_modify_sub(sub_modify);
	assert(filerepo.repo_find_sub(sub_modify) == true);
}

void Tests::test_undo()
{
	SubjectsRepo repo;
	Validator valid;
	ContractStudiu ct;
	SubjectSrv srv(repo, valid, ct);
	srv.srv_add_sub(23, "A", 6.6, "A", "B");
	srv.srv_add_sub(25, "A", 6.6, "A", "B");
	srv.srv_add_sub(28, "A", 6.6, "A", "B");
	srv.srv_add_sub(29, "A", 6.6, "C", "B");
	assert(srv.srv_get_all().size() == 4);
	srv.Undo();
	assert(srv.srv_get_all().size() == 3);
	srv.srv_delete_sub(28);
	assert(srv.srv_get_all().size() == 2);
	srv.Undo();
	assert(srv.srv_get_all().size() == 3);
	assert(srv.srv_get_all().front().get_name() == "A");
	srv.srv_modify_sub(23, "C", 666, "C", "C");
	assert(srv.srv_get_all().front().get_name() == "C");
	srv.Undo();
	assert(srv.srv_get_all().front().get_name() == "A");
}


void Tests::run_all_tests()
{
	cout << "Initiate tests\n";

	this->test_domain();
	this->test_validare();
	this->test_repo();
	this->test_service();
	this->test_sort();
	this->test_filtrare();
	this->test_validare();
	this->test_contract();
	this->test_raport();
	this->test_file_repo();
	this->test_undo();
	
	cout << "Finished tests\n";
}
