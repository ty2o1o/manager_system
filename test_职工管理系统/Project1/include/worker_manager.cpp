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
		cout << "文件不存在" << endl;
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
		cout << "文件为空" << endl;
		this->m_number = 0;
		this->m_worker_list = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	int number = this->get_empnumber();
	cout << "职工人数：" << number << endl;
	this->m_number = number;

	this->m_worker_list = new worker*[this->m_number];

	this->init_emp();
}

void worker_manager::exit_system(void)
{
	cout << "欢迎下次使用" << endl;
	exit(0);
}

void worker_manager::show_menu(void)
{
	cout << "*************************************************************" << endl;
	cout << "******************* 欢迎使用职工管理系统 ********************" << endl;
	cout << "******************* 0.退出管理系统 ********************" << endl;
	cout << "******************* 1.增加职工信息 ********************" << endl;
	cout << "******************* 2.显示职工信息 ********************" << endl;
	cout << "******************* 3.删除职工信息 ********************" << endl;
	cout << "******************* 4.修改职工信息 ********************" << endl;
	cout << "******************* 5.查找职工信息 ********************" << endl;
	cout << "******************* 6.按照编号排序 ********************" << endl;
	cout << "******************* 7.清空所有文档 ********************" << endl;
	cout << "*************************************************************" << endl;

	cout << endl;

}

void worker_manager::add_worker()
{
	cout << "请输入添加人数：" << endl;
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

		cout << "请输入第" << i+1 << "个人职工编号：" << endl;
		cin >> id;

		cout << "请输入第" << i+1 << "个人职工姓名：" << endl;
		cin >> name;

		cout << "选择该职工的岗位：" << endl;
		cout << "1.员工" << endl;
		cout << "2.经理" << endl;
		cout << "3.老板" << endl;
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


	cout << "成功添加" << temp << "人" << endl;

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
		cout << "文件不存在或记录为空！" << endl;

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
		cout << "文件不存在" << endl;
	}
	else
	{
		cout << "请输入删除职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->isexist(id);
		if (index == -1)
		{
			cout << "员工不存在" << endl;
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
		cout << "文件不存在" << endl;
	}

	else
	{
		cout << "请输入修改员工编号：" << endl;
		int id;
		cin >> id;
		int ret = this->isexist(id);
		if (ret == -1)
		{
			delete this->m_worker_list[ret];
			int newid = 0;
			string newname = "";
			int dselect = 0;

			cout << "查到：" << id << "号职工，请输入新的职工号：" << endl;

			cin >> newid;

			cout << "请输入新的姓名：" << endl;
			cin >> newname;

			cout << "请输入新的岗位：" << endl;
			cout << "1.员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
			cout << "修改成功" << endl;


			this->save();
		}
		else
		{
			cout << "查无此人" << endl;
		}

	}
	system("pause");
	system("cls");
}


void worker_manager::find_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入查找方式" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			int id;
			cout << "请输入查找的员工的编号" << endl;
			cin >> id;
			int ret = isexist(id);
			if (ret != -1)
			{
				cout << "查找成功！职工信息如下：" << endl;
				this->m_worker_list[ret]->worker_show();

			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入查找的员工的姓名" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < m_number; i++)
			{
				if (this->m_worker_list[i]->m_name == name)
				{
					cout << "查找成功！职工信息如下：" << endl;
					this->m_worker_list[i]->worker_show();
					flag = true;
				}
			}
			
			if(flag == false)
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "输入错误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void worker_manager::sort_emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}

	else
	{
		cout << "请输入排序方式" << endl;
		cout << "1.按照编号升序排序" << endl;
		cout << "2.按照编号降序排序" << endl;
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
	cout << "排序成功" << endl;
	this->save();
	this->show_emp();

	system("pause");
	system("cls");
}

void worker_manager::clean_file()
{
	cout << "确认清空" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;


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

		cout << "清空成功" << endl;
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