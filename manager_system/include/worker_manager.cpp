#include <iostream>
#include "worker_manager.h"
#include"employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;



worker_manager::worker_manager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->m_number = 0;
		this->m_worker_list = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}


	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->m_number = 0;
		this->m_worker_list = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int number = this->get_empnumber();
	cout << "ְ��������" << number << endl;
	this->m_number = number;

	this->m_worker_list = new worker*[this->m_number];

	this->init_emp();
}

void worker_manager::exit_system(void)
{
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}

void worker_manager::show_menu(void)
{
	cout << "*************************************************************" << endl;
	cout << "******************* ��ӭʹ��ְ������ϵͳ ********************" << endl;
	cout << "******************* 0.�˳�����ϵͳ ********************" << endl;
	cout << "******************* 1.����ְ����Ϣ ********************" << endl;
	cout << "******************* 2.��ʾְ����Ϣ ********************" << endl;
	cout << "******************* 3.ɾ��ְ����Ϣ ********************" << endl;
	cout << "******************* 4.�޸�ְ����Ϣ ********************" << endl;
	cout << "******************* 5.����ְ����Ϣ ********************" << endl;
	cout << "******************* 6.���ձ������ ********************" << endl;
	cout << "******************* 7.��������ĵ� ********************" << endl;
	cout << "*************************************************************" << endl;

	cout << endl;

}

void worker_manager::add_worker()
{
	cout << "���������������" << endl;
	int temp;
	cin >> temp;
	int newsize;
	newsize = this->m_number + temp;


	worker **newspace = new worker*[newsize];

	if (this->m_worker_list != NULL)
	{
		for (int i = 0; i < this->m_number; i++)
		{
			newspace[i] = this->m_worker_list[i];
		}
	}

	for (int i = 0; i <temp; i++)
	{
		int id;
		string name;
		int dselect;

		cout << "�������" << i+1 << "����ְ����ţ�" << endl;
		cin >> id;

		cout << "�������" << i+1 << "����ְ��������" << endl;
		cin >> name;

		cout << "ѡ���ְ���ĸ�λ��" << endl;
		cout << "1.Ա��" << endl;
		cout << "2.����" << endl;
		cout << "3.�ϰ�" << endl;
		cin >> dselect;

		worker *temp_worker = NULL;
		switch (dselect)
		{
		case 1:temp_worker = new employee(id, name, 1);
			break;
		case 2:temp_worker = new manager(id, name, 2);
			break;
		case 3:temp_worker = new boss(id, name, 3);
			break;
		default:
			break;
		}
		newspace[this->m_number + i] = temp_worker;

	}


	delete this->m_worker_list;

	this->m_worker_list = newspace;

	this->m_number = newsize;

	this->m_FileIsEmpty = false;


	cout << "�ɹ����" << temp << "��" << endl;

	this->save();

}

void worker_manager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_number; i++)
	{
		ofs << this->m_worker_list[i]->m_woker_id << " "
			<< this->m_worker_list[i]->m_name << " "
			<< this->m_worker_list[i]->m_dep_id << endl;
	}

	ofs.close();
}

int worker_manager::get_empnumber()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;

	int number = 0;
	while (ifs >> id && ifs >> name && ifs >> did )
	{
		number++;
	}

	return number;

}

void worker_manager::init_emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		worker *worker_temp = NULL;
		if (did == 1)
		{
			worker_temp = new employee(id, name, did);
		}

		if (did == 2)
		{
			worker_temp = new manager(id, name, did);
		}

		if (did == 3)
		{
			worker_temp = new boss(id, name, did);
		}

		this->m_worker_list[index] = worker_temp;

	}
}


void worker_manager:: show_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;

	}
	else
	{
		for (int i = 0; i < m_number; i++)
		{
			this->m_worker_list[i]->worker_show();
		}

	}
}

int worker_manager::isexist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_number; i++)
	{
		if (this->m_number == id)
		{
			index = i;
			break;
		}
	}
	return true;
}

void worker_manager::delete_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{
		cout << "������ɾ��ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->isexist(id);
		if (index == -1)
		{
			cout << "Ա��������" << endl;
		}
		else
		{
			for (int i = index; i < this->m_number - 1; i++)
			{
				this->m_worker_list[i] = this->m_worker_list[i + 1];
			}
			this->m_number--;
			this->save();
		}
	}
	system("pause");
	system("cls");

}

void worker_manager::mod_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ�������" << endl;
	}

	else
	{
		cout << "�������޸�Ա����ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->isexist(id);
		if (ret == -1)
		{
			delete this->m_worker_list[ret];
			int newid = 0;
			string newname = "";
			int dselect = 0;

			cout << "�鵽��" << id << "��ְ�����������µ�ְ���ţ�" << endl;

			cin >> newid;

			cout << "�������µ�������" << endl;
			cin >> newname;

			cout << "�������µĸ�λ��" << endl;
			cout << "1.Ա��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dselect;

			worker *newworker = NULL;
			switch(dselect)
			{
			case 1:newworker = new employee(newid, newname, 1);
				break;
			case 2:newworker = new manager(newid, newname, 2);
				break;
			case 3:newworker = new boss(newid, newname, 3);
				break;
			default:
				break;
			}
			this->m_worker_list[ret] = newworker;
			cout << "�޸ĳɹ�" << endl;


			this->save();
		}
		else
		{
			cout << "���޴���" << endl;
		}

	}
	system("pause");
	system("cls");
}


void worker_manager::find_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ" << endl;
		cout << "1.����ְ����Ų���" << endl;
		cout << "2.����ְ����������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "��������ҵ�Ա���ı��" << endl;
			cin >> id;
			int ret = isexist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ���ְ����Ϣ���£�" << endl;
				this->m_worker_list[ret]->worker_show();

			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "��������ҵ�Ա��������" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_number; i++)
			{
				if (this->m_worker_list[i]->m_name == name)
				{
					cout << "���ҳɹ���ְ����Ϣ���£�" << endl;
					this->m_worker_list[i]->worker_show();
					flag = true;
				}
			}
			
			if(flag == false)
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "�������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void worker_manager::sort_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}

	else
	{
		cout << "����������ʽ" << endl;
		cout << "1.���ձ����������" << endl;
		cout << "2.���ձ�Ž�������" << endl;
	}

	int select = 0;
	cin >> select; 
	for (int i = 0; i < m_number; i++)
	{
		int minindex = i;
		for (int j = i + 1; j < this->m_number; j++)
		{
			if (select == 1)
			{
				if (this->m_worker_list[i]->m_woker_id > this->m_worker_list[j]->m_woker_id)
				{
					minindex = j;
				}
			}
			else
			{
				if (this->m_worker_list[i]->m_woker_id < this->m_worker_list[j]->m_woker_id)
				{
					minindex = j;
				}
			}
		}
		if (minindex != i)
		{
			worker *temp = this->m_worker_list[i];
			this->m_worker_list[i] = this->m_worker_list[minindex];
			this->m_worker_list[minindex] = temp;
		}
	}
	cout << "����ɹ�" << endl;
	this->save();
	this->show_emp();

	system("pause");
	system("cls");
}

void worker_manager::clean_file()
{
	cout << "ȷ�����" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;


	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_worker_list != NULL)
		{
			for (int i = 0; i < this->m_number; i++)
			{
				delete this->m_worker_list[i];
				this->m_worker_list[i];
			}
			delete[] this->m_worker_list;
			this->m_worker_list = NULL;
			this->m_number = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

worker_manager::~worker_manager()
{
	if (this->m_worker_list != NULL)
	{
		delete[] this->m_worker_list;
		this->m_worker_list = NULL;
	}
	

}