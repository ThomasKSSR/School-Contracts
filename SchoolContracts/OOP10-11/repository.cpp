#include "repository.h"
#include <iostream>
#include <fstream>
using namespace std;





void SubjectsRepo::repo_add_sub(const Subject& sub)
{
	for (Subject& s : Subjects) 

		if (&s !=nullptr &&s == sub) 
			throw(RepoException("Subject already exists!\n"));		
	Subjects.push_back(sub);
	//Subjects.add(sub);
}

void SubjectsRepo::repo_delete_sub_id(int id)
{
	
	
	Subject sub(id, "dsa", 0.1, "dsa", "as");
	/*IteratorVector<Subject> it(Subjects);
	while (it.valid()) {
		if (sub == it.element()) {
			break;
		}
		it.next();
	}*/
	auto it = find(this->Subjects.begin(), this->Subjects.end(), sub);


	if (it == Subjects.end()) {
		throw(RepoException("Subject doesn't exist!\n"));
	}

	Subjects.erase(it);
	//Subjects.del(*it);

}

void SubjectsRepo::repo_modify_sub( Subject& sub)
{
	
	auto it = find(this->Subjects.begin(), this->Subjects.end(), sub);
	/*IteratorVector<Subject> it(Subjects);
	while (it.valid()) {
		if (sub == it.element()) {
			break;
		}
		it.next();
	}*/

	if (it == Subjects.end()) {
		throw(RepoException("Subject doesn't exist!\n"));
	}
	*it = sub;
}

bool SubjectsRepo::repo_find_sub( Subject& sub)
{	
	auto it = find(this->Subjects.begin(), this->Subjects.end(), sub);
	//IteratorVector<Subject> it(Subjects);
	///*while (it.valid()) {
	//	
	//	if (sub == it.element()) {
	//		break;
	//	}
	//	it.next();
	//}*/
	if (it != this->Subjects.end()) 
		return true;	
	return false;
}

const vector<Subject>& SubjectsRepo::repo_get_all_subs() noexcept
{
	return Subjects;
}
//const VectorDinamic<Subject>& SubjectsRepo::repo_get_all_subs() noexcept
//{
//	return Subjects;
//}



int SubjectsRepo::repo_size() noexcept
{
	return int(Subjects.size());
}

SubjectsRepo::~SubjectsRepo()
{
	//Subjects.~VectorDinamic();

}


//---------------------------------------------------------------------------------------------------------


void FileSubjectsRepo::loadfromfile()
{
	std::ifstream fin(Filename);

	if (!fin.is_open()) {
		throw RepoException(Filename + " didn't open!");
	}

	while (!fin.eof()) {
		int id_sub;
		fin >> id_sub;
		if (fin.eof()) {
			break;
		}
		std::string name;
		fin >> name;
		double hours;
		fin >> hours;
		std::string type;
		fin >> type;
		std::string teacher;
		fin>> teacher;
		Subject sub( id_sub,name,hours,type,teacher );
		SubjectsRepo::repo_add_sub(sub);
	}
	fin.close();
}

void FileSubjectsRepo::writetofile()
{
	std::ofstream fout(Filename);
	if (!fout.is_open()) {
		throw RepoException(Filename + " didn't open!");
	}

	for (const auto& sub : repo_get_all_subs()) {
		fout << sub.get_id_sub();
		fout << std::endl;
		fout << sub.get_name();
		fout << std::endl;
		fout << sub.get_hours();
		fout << std::endl;
		fout << sub.get_type();
		fout << std::endl;
		fout << sub.get_teacher();
		fout << std::endl;

	}
	fout.close();
}
