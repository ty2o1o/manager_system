#include <iostream>
#include "employee.h"
#include "manager.h"
#include "boss.h"

using namespace std;

int main(void)
{
	worker_manager a;
	a.show_menu();
	int i = 0;


	while (true)
	{
		cout << "请输入想要执行的功能：";
		cin >> i;

		switch (i)
		{
		case 0:a.exit_system();
			break;
		case 1:a.add_worker();
			break;
		case 2:a.show_emp();
			break;
		case 3:a.delete_emp();
			break;
		case 4:a.mod_emp();
			break;
		case 5:a.find_emp();
			break;
		case 6:a.sort_emp();
			break;
		case 7:



		default:
			break;
		}
	}


}