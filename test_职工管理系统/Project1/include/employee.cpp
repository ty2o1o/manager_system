#include <string>
#include "employee.h"
#include "worker_manager.h"


using namespace std;
employee::employee(int id, string name, int dep_id)
{
	this->m_woker_id = id;
	this->m_name = name;
	this->m_dep_id = dep_id;
}

void employee::worker_show()
{
	cout << "ְ��������" << this->m_name << endl;
	cout << "ְ��Id��" << this->m_woker_id << endl;
	cout << "����id��" << this->get_dep_name() << endl;
}

string employee::get_dep_name()
{
	return "Ա��";
}