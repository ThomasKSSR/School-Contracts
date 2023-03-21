#include "service.h"
#include "VectorDinamic.h"
#include <random>
#include <algorithm>


const void SubjectSrv::srv_add_sub(int id, string name, double hours, string type, string teacher)
{
	Subject sub(id, name, hours, type, teacher);
	valid.valid_sub(sub);
	repo.repo_add_sub(sub);
	UndoActions.push_back(make_unique<UndoAdd>(repo, sub));
}

const void SubjectSrv::srv_delete_sub(int id)
{
	if (id < 0) {
		throw(SrvException("Invalid ID"));
	}

	vector<Subject> subs = repo.repo_get_all_subs();
	Subject fake_sub(id, "das", 2.3, "dsa", "ads");
	for (auto sub : subs) {
		if (sub == fake_sub)
			UndoActions.push_back(make_unique<UndoDel>(repo, sub));
	}
	repo.repo_delete_sub_id(id);
	
	notifyAll();
	

	

}

const void SubjectSrv::srv_modify_sub(int id, string name, double hours, string type, string teacher)
{
	Subject sub_validate(id, name, hours, type, teacher);
	valid.valid_sub(sub_validate);
	vector<Subject> subs = repo.repo_get_all_subs();
	Subject fake_sub(id, "das", 2.3, "dsa", "ads");

	for (auto sub : subs) {
		if (sub == fake_sub)
			UndoActions.push_back(make_unique<UndoMod>(repo, sub));
	}

	Subject sub_modify(id, name, hours, type, teacher);
	repo.repo_modify_sub(sub_modify);

	
}

const bool SubjectSrv::srv_find_sub(int id)
{
	if (id < 0) {
		throw SrvException("Id invalid!");
	}
	Subject sub_fake(id, "das", 12.2, "da", "ads");

	return repo.repo_find_sub(sub_fake);
}

const vector<Subject>& SubjectSrv::srv_get_all()
{
	return repo.repo_get_all_subs();
}
//const VectorDinamic<Subject>& SubjectSrv::srv_get_all()
//{
//	return repo.repo_get_all_subs();
//}

vector<Subject> SubjectSrv::srv_general_sort(bool(*cmpF)(const Subject&, const Subject&))
{
	vector<Subject> sort_subs = repo.repo_get_all_subs();
	//vector<Subject> sort_subs;

	//VectorDinamic<Subject> sort_subs_init = repo.repo_get_all_subs();
	/*IteratorVector<Subject> it(sort_subs_init);
	
	for (int i = 0; i < sort_subs_init.size(); i++) {
		sort_subs.push_back(it.element());
		it.next();
	}*/

	/*for (int i = 0; i < sort_subs.size()-1; i++) {
		for (int j = i + 1; j < sort_subs.size(); j++) {
			if (!cmpF(sort_subs.at(i), sort_subs.at(j))) {
				Subject aux = sort_subs.at(i);
				sort_subs.at(i) = sort_subs.at(j);
				sort_subs.at(j) = aux;

			}
		}
	}*/
	sort(sort_subs.begin(), sort_subs.end(), cmpF);
	return sort_subs;
}

vector<Subject> SubjectSrv::srv_sort_by_name()
{
	return srv_general_sort([](const Subject& s1, const Subject& s2) {
		return s1.get_name() <= s2.get_name();
		});
}

vector<Subject> SubjectSrv::srv_sort_by_hours()
{
	return srv_general_sort([](const Subject& s1, const Subject& s2)noexcept {
		return s1.get_hours() <= s2.get_hours();
		});
}

vector<Subject> SubjectSrv::srv_sort_by_type_teacher()
{
	return srv_general_sort([](const Subject& s1, const Subject& s2)noexcept {
		if (s1.get_type() == s2.get_type()) 

			return s1.get_teacher() <= s2.get_teacher();
		else {
			return s1.get_type() <= s2.get_type();
		}
		});
}

vector<Subject> SubjectSrv::filter(function<bool(const Subject&)> filterfunction)
{
	vector<Subject>res;
	vector<Subject> subs = repo.repo_get_all_subs();
	/*for (auto sub : subs)
		if (filterfunction(sub))
			res.push_back(sub);*/
	copy_if(subs.begin(), subs.end(), back_inserter(res), filterfunction);
	return res;
}

vector<Subject> SubjectSrv::filterbytype(const string& type)
{
	return this->filter([&](const Subject& ev)noexcept {return ev.get_type() == type; });
}

vector<Subject> SubjectSrv::filterbyteacher(const string& teacher)
{
	return this->filter([&](const Subject& ev)noexcept {return ev.get_teacher() == teacher; });
}

void SubjectSrv::generate_contract(int n)
{
	vector<Subject>repolist = this->srv_get_all();
	std::random_device rd;
	std::mt19937 generator(rd());
	if (n + contract.size() > repolist.size())
		throw SrvException("There are not enough Subjects in repository\n");
	contract.empty_contract();
	while (n)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, int(repolist.size()) - 1);
		int rndNr = dist(mt);// numar aleator intre [0,size-1]
		contract.add_contract(repolist.at(rndNr));
		n--;
	}
	notifyAll();
}

void SubjectSrv::add_contract(int id,string name,double hours,string type,string teacher)
{
	Subject sub(id, name, hours, type, teacher);
	valid.valid_sub(sub);
	if (repo.repo_find_sub(sub) == false) {
		throw SrvException("Subject doesn't exist in repository!\n");
	}
	contract.add_contract(sub);
	this->notifyAll();
}

vector<Subject> SubjectSrv::get_all_contract()
{
	return contract.get_all_contract();
	//this->notifyAll();
}

void SubjectSrv::empty_contract()
{
	contract.empty_contract();
	this->notifyAll();
}

map<std::string,int> SubjectSrv::raport_type()
{
	map<std::string,int> raport;
	map<std::string, int>::iterator it;
	vector<Subject> repo_list = repo.repo_get_all_subs();
	for (auto i : repo_list) {
		it = raport.find(i.get_type());
		if (it == raport.end()) {
			raport.insert({i.get_type(),1});
		}
		else {
			raport[i.get_type()]++;
		}
		
	}
	return raport;

}

void SubjectSrv::Undo()
{
	if (UndoActions.empty()) {
		throw(SrvException("Undo can't be done!"));
	}

	UndoActions.back()->doundo();
	UndoActions.pop_back();

}
