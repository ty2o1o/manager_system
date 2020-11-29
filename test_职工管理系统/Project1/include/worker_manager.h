#pragma once
#include <iostream>
#include <string>
#include <fstream>

#define FILENAME "export.txt"

using namespace std;

class worker;

class worker_manager
{
public:
	worker_manager();

	void show_menu(void);

	void exit_system(void);
	
	void add_worker(void);

	void save();
	
	int get_empnumber();

	void init_emp();

	void show_emp();

	void delete_emp();

	int isexist(int id);

	void mod_emp();

	void find_emp();

	void sort_emp();

	void clean_file();

	~worker_manager();

private:
	int m_number;
	worker **m_worker_list;
	bool m_FileIsEmpty;
};


class worker
{
public:

	virtual void worker_show() = 0;

	virtual string get_dep_name() = 0;

	int m_woker_id;

	string m_name;

	int m_dep_id;

};