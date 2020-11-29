#pragma once


#include <iostream>
#include "worker_manager.h"

using namespace std;

class worker;

class boss :public worker
{
public:
	boss(int id, string name, int dep_id);

	~boss();

	virtual void worker_show();

	virtual string get_dep_name();

};
