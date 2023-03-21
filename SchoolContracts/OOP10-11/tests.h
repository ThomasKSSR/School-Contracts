#pragma once
#include "domain.h"
#include "repository.h"
#include "service.h"
#include <iostream>
#include <assert.h>

using std::cin;
using std::cout;

class Tests {

private:
	void test_domain();
	void test_repo();
	void test_service();
	void test_sort();
	void test_filtrare();
	void test_validare();
	void test_contract();
	void test_raport();
	void test_file_repo();
	void test_undo();
public:
	void run_all_tests();

};