#pragma once
#include "service.h"
#include "validare.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
class Ui {
private:
	SubjectSrv& srv;
	const void menu();
	const void ui_add_sub();
	const void ui_delete_sub();
	const void ui_modify_sub();
	const void ui_print_subs();

	const void ui_add_contract();
	const void ui_generate_contract();
	const void ui_empty_contract();
	
public:
	Ui(Ui& ui) noexcept = delete;
	Ui(SubjectSrv& srv)noexcept : srv{ srv } {

	}
	const void run();

};