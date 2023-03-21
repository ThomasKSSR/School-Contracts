#pragma once
#include <string>
using std::string;
class RepoException {
	string msg;
public:
	RepoException(string msg) :msg{ msg } {

	}
	string get_msg() {
		return msg;
	}
	
};

class ValidException {
	string msg;
public:
	ValidException(string msg) : msg{ msg } {

	}
	string get_msg() {
		return msg;
	}
};

class SrvException {
	string msg;
public:
	SrvException(string msg) : msg{ msg } {

	}
	string get_msg() {
		return msg;
	}
};