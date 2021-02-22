#include "menu.h"

void start_menu(TeacherDataBase* db) 
{
	char pressed_button = NULL;
	while (true)
	{
		system("cls");
		cout << "����" << endl;
		print_line(49, 1);
		cout << endl;
		cout << "1 - ������� ������ ���� ��������������" << endl;
		cout << "2 - �������� �������������" << endl;
		cout << "3 - ����� ������������� �� ���" << endl;
		cout << "4 - ����� �������������� �� ���������" << endl;
		cout << "5 - ������� ��������������� ������ ��������������" << endl;
		cout << "6 - �����" << endl;

		pressed_button = _getch();
		system("cls");
		switch (pressed_button)
		{
		case '1':
			show_table(db->get_arr());
			break;
		case '2':
			add_record(db);
			break;
		case '3':
			find_teacher(db);
			break;
		case '4':
			find_by_status(db);
			break;
		case '5':
			sort_by_fio(db);
			break;
		case '6':
			return;
			break;
		}
		cout << endl;
		cout << "������� ����� ������� ��� ������ � ����" << endl;
		_getch();
		system("cls");
	}

}
void show_table(Teacher* arr, int size) 
{
	if (size < 0)
		size = arr->get_count();

	int fio_size = max_size(arr, size) + 5, status_size = 15, dep_size = 9;
	
	cout.setf(ios::left);
	cout.width(dep_size);
	cout << "�������\t";
	cout.width(fio_size);
	cout << "���";
	cout.width(status_size);
	cout << "������ ������" << endl;

	print_line(dep_size + fio_size + status_size, 2);
	cout << endl;

	for (int i = 0; i < size; i++)
	{
		FullName* fullName = arr[i].get_fullname();
		char* dep_temp = arr[i].get_department(), * status = arr[i].get_status();

		cout.width(dep_size);
		for (int j = 0; j < strlen(dep_temp); j++)
			dep_temp[j] = to_upper(dep_temp[j]);
		cout << dep_temp;
		cout.width(fio_size);
		
		cout << string(fullName->get_surname()) + " " + string(fullName->get_name()) + " " + string(fullName->get_second_name());
		cout.width(status_size);
		cout << status << endl;

		delete fullName;
		delete[] dep_temp;
		delete[] status;
	}

	print_line(dep_size + fio_size + status_size, 2);
}
void add_record(TeacherDataBase* db)
{
	cout << " ���������� ����� ������" << endl;
	print_line(23, 2);
	cout << endl;

	int status = 0, department = 0;

	cout << "������ ������: ";
	while (true)
	{
		int status = get_word_from_list(Teacher::get_status_list());

		if (status >= 0)
			break;

		cout << "������ ������� ������ ���! ��������� ����: ";
	}

	cout << "�������: ";
	while (true)
	{
		department = get_word_from_list(Teacher::get_dep_list());

		if (department >= 0)
			break;

		cout << "����� ������� �� ����������! ��������� ����: " << endl;
	}

	cout << "�������: ";

	char* surname = read_str(stdin);
	cout << "���: ";
	char* name = read_str(stdin);
	cout << "��������: ";
	char* second_name = read_str(stdin);

	db->add_teacher(new Teacher(name, surname, second_name, department, status));
}
void find_teacher(TeacherDataBase* db) 
{
	cout << "����� ������������� �� ���" << endl;
	print_line(26, 2);
	cout << endl;

	cout << "������� ������ ������������� " << endl;
	cout << "�������: ";
	char* t_surname = read_str(stdin);
	cout << "���: ";
	char* t_name = read_str(stdin);
	cout << "��������: ";
	char* t_second_name = read_str(stdin);

	FullName t_fullName(t_name, t_surname, t_second_name);	//Will be deleted
	Teacher* found = db->find_teacher(t_fullName);

	if (found == nullptr)
		cout << "������ ������������� ��� � ���� ������!";
	else
	{
		show_table(found, 1);
		found->destroy(true);
	}
}
void find_by_status(TeacherDataBase* db) 
{
	cout << "����� �������������� �� �� ������" << endl;
	print_line(33, 2);
	cout << endl;
	cout << "������� ��������� �������������: ";

	int found = 0;
	Teacher* t_res = nullptr;

	while (true)
	{
		int status_num = get_word_from_list(Teacher::get_status_list());
		if (status_num >= 0)
		{
			t_res = db->filter_by_status(status_num, &found);
			show_table(t_res, found);
			break;
		}
		cout << "����� ��������� �� ����������! ��������� ����: ";
	}
	if (t_res != nullptr)
		for(int i = 0; i < found; i++)
			t_res[i].destroy(true);

}
void sort_by_fio(TeacherDataBase* db) 
{
	cout << "��������������� �������\n\n" << endl;

	Teacher* sorted = db->sorted_list();
	show_table(sorted);
	
	for (int i = 0; i < Teacher::get_count(); i++)
		sorted[i].destroy(true);
}
