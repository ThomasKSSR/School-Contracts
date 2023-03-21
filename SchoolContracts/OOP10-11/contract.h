#pragma once
#include "domain.h"
#include <vector>
using std::vector;

class ContractStudiu {
private:
	vector<Subject> contract;

public:
	void empty_contract() {
		contract.clear();
	}

	void add_contract(const Subject& sub) {
		contract.push_back(sub);

	}
	int size() {
		return int(contract.size());
	}
	const vector<Subject>& get_all_contract() {
		return contract;
	}


};