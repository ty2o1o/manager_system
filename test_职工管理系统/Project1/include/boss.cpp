#include <iostream>
#include "boss.h"
#include "worker_manager.h"

boss::boss(int id, string name, int dep_id)
{
	this->m_woker_id = id;
	this->m_name = name;
	this->m_dep_id = dep_id;
}

void boss::worker_show()
{
	cout << "�ϰ�������" << this->m_name << endl;
	cout << "�ϰ�Id��" << this->m_woker_id << endl;
	cout << "�ϰ岿��id��" << this->get_dep_name() << endl;
}

string boss::get_dep_name()
{
	return "�ϰ�";
}