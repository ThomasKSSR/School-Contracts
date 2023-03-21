#pragma once

#include <string>
#include <iostream>
using std::cout;
using std::string;

class Subject {
private:
	int id_sub;
	string name;
	double hours;
	string type;
	string teacher;

public:
	Subject();

	bool operator==(const Subject& ) noexcept;
	Subject& operator=(const Subject&);
	Subject(const Subject& ot) :id_sub{ ot.id_sub }, name{ ot.name }, hours{ ot.hours }, type{ ot.type }, teacher{ ot.teacher }{
		
	};

	Subject(int id,const string& name, double hours,const string& type,const string& teacher);
	const int get_id_sub() const noexcept;
	const string& get_name() const noexcept;
	const double get_hours() const noexcept;
	const string& get_type() const noexcept;
	const string& get_teacher() const noexcept;
	~Subject();


};