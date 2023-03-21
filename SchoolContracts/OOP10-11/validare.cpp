#include "validare.h"
#include "exceptions.h"
void Validator::valid_sub(const Subject& sub)
{
	if (sub.get_id_sub() < 0 || sub.get_hours() < 0 || sub.get_name() == "" || sub.get_teacher() == "" || sub.get_type() == "") {
		throw(ValidException("Invalid Subject!\n"));
	}

}
