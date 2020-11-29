#pragma once

#include <iostream>
#include "worker_manager.h"

using namespace std;

class worker;

class manager :public worker
{
public:
	manager(int id, string name, int dep_id);
	
	~manager();

	virtual void worker_show();

	virtual string get_dep_name();

};
