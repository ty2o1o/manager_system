#include "manager.h"
#include "worker_manager.h"

manager::manager(int id, string name, int dep_id)
{
	this->m_woker_id = id;
	this->m_name = name;
	this->m_dep_id = dep_id;
}

void manager::worker_show()
{
	cout << "����������" << this->m_name << endl;
	cout << "����Id��" << this->m_woker_id << endl;
	cout << "������id��" << this->get_dep_name() << endl;
}

string manager::get_dep_name()
{
	return "����";
}
