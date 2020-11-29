#pragma once

#include <string>
#include<iostream>
#include "worker_manager.h"

class worker;

class employee : public worker
{
public:
	employee(int id, string name, int dep_id);

	virtual void worker_show(void) ;

	virtual string get_dep_name() ;


};