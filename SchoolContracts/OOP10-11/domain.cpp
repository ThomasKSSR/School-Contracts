#include "domain.h"

Subject::Subject() {

}


bool Subject::operator==(const Subject& other) noexcept
{
	return this->id_sub == other.id_sub;
}

Subject& Subject::operator=(const Subject &other)
{
	this->id_sub = other.id_sub;
	this->name = other.name;
	this->hours = other.hours;
	this->type = other.type;
	this->teacher = other.teacher;
	return *this;
}

Subject::Subject(int _id, const string& _name, double _hours,const string& _type,const string& _teacher):
	id_sub{ _id },
	name{_name},
	hours{_hours},
	type{ _type },
	teacher{ _teacher }
{

}

const int Subject::get_id_sub() const noexcept
{
	return this->id_sub;
}

const string& Subject::get_name() const noexcept
{
	return this->name;
}

const double Subject::get_hours() const noexcept
{
	return this->hours;
}

const string& Subject::get_type() const noexcept
{
	return this->type;
}

const string& Subject::get_teacher() const noexcept
{
	return this->teacher;
}

Subject::~Subject() {

}