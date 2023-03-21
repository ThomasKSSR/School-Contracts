 #pragma once
#include <vector>
#include "domain.h"
#include "exceptions.h"
//#include "VectorDinamic.h"
#include <string.h>
//using std::string;
using std::vector;


class SubjectsRepo {
private:
	vector<Subject> Subjects;
	//vector<Subject> Subjects;

public:
	SubjectsRepo(const SubjectsRepo& repo) = delete;
	SubjectsRepo() = default;

	

	virtual void repo_add_sub(const Subject& sub);
	virtual void repo_delete_sub_id(int id);
	virtual void repo_modify_sub( Subject& sub);
	virtual bool repo_find_sub( Subject&);

	virtual const vector<Subject>& repo_get_all_subs() noexcept;
	virtual int repo_size() noexcept;
	virtual ~SubjectsRepo();

};


class FileSubjectsRepo : public SubjectsRepo {
private:
	std::string Filename;

	void loadfromfile();
	void writetofile();
public:
	FileSubjectsRepo(std::string Fname) : SubjectsRepo(), Filename{ Fname }{
		loadfromfile();
	}
	void repo_add_sub(const Subject& sub) override {
		SubjectsRepo::repo_add_sub(sub);
		writetofile();
	}
	void repo_delete_sub_id(int id) override {
		SubjectsRepo::repo_delete_sub_id(id);
		writetofile();
	}
	void repo_modify_sub(Subject& sub) override{
		SubjectsRepo::repo_modify_sub(sub);
		writetofile();
	}
	bool repo_find_sub(Subject& sub) override {
		//loadfromfile();
		return SubjectsRepo::repo_find_sub(sub);
	}
	
	const vector<Subject>& repo_get_all_subs() noexcept override{
		//loadfromfile();
		return SubjectsRepo::repo_get_all_subs();
	}
	int repo_size() noexcept override{
		//loadfromfile();
		return SubjectsRepo::repo_size();
	}
};
