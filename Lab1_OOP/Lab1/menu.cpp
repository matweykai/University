#include "menu.h"

#define BUFFERSIZE 20

Teacher* start_menu(Teacher* arr, int* size, list<string>* dep_list, list<string>* status_list) 
{
	char pressed_button;
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
			show_table(arr, *size, dep_list, status_list);
			break;
		case '2':
			arr = add_record(arr, size, dep_list, status_list);
			break;
		case '3':
			find_teacher(arr, *size, dep_list, status_list);
			break;
		case '4':
			find_by_status(arr, *size, dep_list, status_list);
			break;
		case '5':
			sort_by_fio(arr, *size, dep_list, status_list);
			break;
		case '6':
			return arr;
			break;
		}
		cout << endl;
		cout << "������� ����� ������� ��� ������ � ����" << endl;
		_getch();
		system("cls");
	}
}
void show_table(Teacher* arr, int size, list<string>* dep_list, list<string>* status_list)
{	
	int fio_size = max_size(arr, size) + 2, status_size = 15, dep_size = 9;

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
		cout.width(dep_size);
		string dep_temp = get_element(dep_list, arr[i].department);
		for (int i = 0; i < dep_temp.length(); i++)
			dep_temp[i] = to_upper(dep_temp[i]);
		cout << dep_temp;
		cout.width(fio_size);
		cout << arr[i].fio;
		cout.width(status_size);
		cout << get_element(status_list, arr[i].status) << endl;
	}

	print_line(dep_size + fio_size + status_size, 2);
}
int max_size(Teacher* arr, int size) 
{
	int result = 0;
	for (int i = 0; i < size; i++)
		if (strlen(arr[i].fio) > result)
			result = strlen(arr[i].fio);
	return result;
}
void print_line(int size, int adding_count = 0)
{
	for (int i = 0; i < size + adding_count; i++)
		cout << "-";
}
string get_element(list<string>* lst, int pos) 
{
	int counter = 1;
	for (list<string>::iterator iter = lst->begin(); iter != lst->end(); iter++)
	{
		if (counter == pos)
			return *iter;
		counter++;
	}
	return string("");
}
Teacher* add_record(Teacher* arr, int* size, list<string>* dep_list, list<string>* status_list)
{
	Teacher* result = new Teacher[*size + 1];
	Teacher new_obj;
	// Shallow copy
	for (int i = 0; i < *size; i++)
		result[i] = arr[i];

	cout << " ���������� ����� ������" << endl;
	print_line(23, 2);
	cout << endl;


	cout << "������ ������: ";
	while (true) 
	{
		int status = get_word_from_list(status_list);
		if (status > 0)
		{
			new_obj.status = status;
			break;
		}
		cout << "������ ������� ������ ���! ��������� ����: ";
	}

	cout << "�������: ";
	while (true)
	{
		int department = get_word_from_list(dep_list);
		if (department > 0)
		{
			new_obj.department = department;
			break;
		}
		cout << "����� ������� �� ����������! ��������� ����: " << endl;
	}
	
	cout << "���: ";

	new_obj.fio = read_str(stdin);

	result[*size] = new_obj;
	*size += 1;

	delete arr;

	return result;
}
int get_word_from_list(list<string>* lst) 
{
	char* str = read_str(stdin);

	string entered_word;

	entered_word += str;

	int counter = 1;
	for (int i = 0; i < entered_word.length(); i++)
		entered_word[i] = to_lower(entered_word[i]);
	
	for (list<string>::iterator iter = lst->begin(); iter != lst->end(); iter++, counter++)
		if (*iter == entered_word)
			return counter;

	return -1;
}
char to_lower(char sym) 
{
	if ((int)sym >= '�' && (int)sym <= '�')
		return (char)(sym + 32);
	else
		return tolower(sym);
}
char to_upper(char sym) 
{
	if ((int)sym >= '�' && (int)sym <= '�')
		return (char)(sym - 32);
	else
		return tolower(sym);
}
void find_teacher(Teacher* arr, int size, list<string>* dep_list, list<string>* status_list)
{
	cout << "����� ������������� �� ���" << endl;
	print_line(26, 2);
	cout << endl;

	cout << "������� ��� �������������: ";
	char* temp_fio = read_str(stdin);
	Teacher* found = find_by_fio(arr, size, temp_fio);

	if (found == nullptr)
		cout << "������ ������������� ��� � ���� ������!";
	else
		show_table(found, 1, dep_list, status_list);

	delete temp_fio;
}
void find_by_status(Teacher* arr, int size, list<string>* dep_list, list<string>* status_list)
{
	cout << "����� �������������� �� �� ������" << endl;
	print_line(33, 2);
	cout << endl;
	cout << "������� ��������� �������������: ";
	
	int found = 0;

	while (true) 
	{
		int status_num = get_word_from_list(status_list);
		if (status_num > 0)
		{
			arr = filter_by_status(arr, size, status_num, &found);
			show_table(arr, found, dep_list, status_list);
			break;
		}
		cout << "����� ��������� �� ����������! ��������� ����: ";
	}
	if(found != 0)
		delete arr;
}
void sort_by_fio(Teacher* arr, int size, list<string>* dep_list, list<string>* status_list)
{
	cout << "��������������� �������\n\n" << endl;

	Teacher* sorted = sort(arr, size);
	show_table(sorted, size, dep_list, status_list);
	delete sorted;
}