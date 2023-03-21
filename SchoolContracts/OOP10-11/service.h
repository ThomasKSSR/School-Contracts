#pragma once
#include "repository.h"
#include <functional>
#include "validare.h"
#include "contract.h"
#include <map>
#include "Observable.h"

using std::map;
using std::unique_ptr;
using std::function;
using std::make_unique;

class UndoAction {

public:

	virtual void doundo() = 0;
	~UndoAction() = default;

};

class UndoAdd : public UndoAction {

private:
	Subject sub;
	SubjectsRepo& repo;
public:
	UndoAdd(SubjectsRepo& repo,const Subject& sub) : repo{repo}, sub{sub}{};

	void doundo() override{
		repo.repo_delete_sub_id(sub.get_id_sub());
	}
};

class UndoDel :public UndoAction {
private:
	Subject sub;
	SubjectsRepo& repo;
public:
	UndoDel(SubjectsRepo& repo, const Subject& sub) : repo{ repo }, sub{ sub }{};

	void doundo() override {
		repo.repo_add_sub(sub);
	}
};

class UndoMod : public UndoAction {
private:
	Subject sub;
	SubjectsRepo& repo;
public:
	UndoMod(SubjectsRepo& repo, const Subject& sub) : repo{ repo }, sub{ sub }{};
	void doundo() override {
		repo.repo_modify_sub(sub);
	}
};

class SubjectSrv : public Observable{
private:
	SubjectsRepo& repo;
	Validator& valid;
	ContractStudiu& contract;

	vector<Subject> srv_general_sort(bool(*cmpF)(const Subject&, const Subject&));

	vector<unique_ptr<UndoAction>> UndoActions;

public:
	
	
	SubjectSrv(SubjectsRepo& repo, Validator valid, ContractStudiu& contract) noexcept :repo{ repo }, valid{ valid }, contract{ contract }{

	}
	const void srv_add_sub(int id, string name, double hours, string type, string teacher);
	const void srv_delete_sub(int id);
	const void srv_modify_sub(int id, string name, double hours, string type, string teacher);
	const bool srv_find_sub(int id);
	const vector<Subject>& srv_get_all();
	
	
	vector<Subject> srv_sort_by_name() ;
	vector<Subject> srv_sort_by_hours() ;
	vector<Subject> srv_sort_by_type_teacher();

	vector<Subject> filter(function <bool(const Subject&)> filterfunction);
	vector<Subject> filterbytype(const string& type);
	vector<Subject> filterbyteacher(const string& type);
	
	void generate_contract(int n);
	void add_contract(int id, string name, double hours, string type, string teacher);
	vector<Subject> get_all_contract();
	void empty_contract();

	map<std::string,int> raport_type();

	void Undo();

};