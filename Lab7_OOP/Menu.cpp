#include "Menu.h"

Menu::Menu(string fileName) 
{
	db = new FoodDataBase(fileName);
}
void Menu::showAll()
{
	cout << "��� ������\n" << endl;

	show_table(db->get_food_arr());
}
Date Menu::enterDate()
{
	int* day = nullptr, * month = nullptr, * year = nullptr;
	Date result(1, 1, 1);

	while (true)
	{
		try
		{
			while (true)
			{
				cout << "������� ����: ";
				day = enter_num<int>();
				break;
			}
		}
		catch (EnterException ex)
		{
			cout << ex.get_msg() << endl;
		}
		try
		{
			while (true)
			{
				cout << "������� �����: ";
				month = enter_num<int>();
				break;
			}
		}
		catch (EnterException ex)
		{
			cout << ex.get_msg() << endl;
		}
		try
		{
			while (true)
			{
				cout << "������� ���: ";
				year = enter_num<int>();
				break;
			}
		}
		catch (EnterException ex)
		{
			cout << ex.get_msg() << endl;
		}

		try
		{
			result = Date(*day, *month, *year);
			break;
		}
		catch (DateException ex)
		{
			cout << ex.get_str() << endl;
			cout << "��������� ����" << endl;
		}
	}

	delete day, month, year;

	return result;
}
void Menu::showSortedArr() 
{
	deque<Food> sorted = sort_by_price(db->get_food_arr());
	cout << "��������������� ������ ���������: \n" << endl;
	show_table(sorted);
}
void Menu::findByDate()
{
	cout << "����� ������� �� ����\n\n";
	Date t_date = enterDate();

	deque<Food> found = find_by_date(db->get_food_arr(), t_date);
	show_table(found);
}
void Menu::addRecord(istream& str)
{
	string name;
	double* price = nullptr;
	Date produceDate(1, 1, 1);

	cout << "���������� ����� ������" << endl;
	print_line(24, 2);
	cout << endl;

	cout << "������� ��������: ";
	getline(str, name);


	while (true)
	{
		try
		{
			cout << "������� ����: ";
			price = enter_num<double>();

			if (*price < 0)
			{
				cout << "���� �� ����� ���� �������������" << endl;
				continue;
			}
			break;
		}
		catch (EnterException ex)
		{
			cout << ex.get_msg() << endl;
		}
	}

	cout << "���� ������������" << endl;
	produceDate = enterDate();

	cout << "�������� ������ � ������? (Y)" << endl;
	bool before = false;
	char pr_but = _getch();
	if (pr_but == 'Y' || pr_but == 'y' || pr_but == '�' || pr_but == '�')
		before = true;

	db->add_record(*price, new Date(produceDate), new string(name), before);

	delete price;
}
void Menu::startMenu()
{
	char pressed_button = NULL;
	while (true)
	{
		system("cls");
		cout << "����" << endl;
		print_line(49, 1);
		cout << endl;
		cout << "1 - �������� ��� ������" << endl;
		cout << "2 - �������� ������" << endl;
		cout << "3 - ����� ������ �� ����" << endl;
		cout << "4 - ������� ������������� ������" << endl;
		cout << "5 - ������� ������ ������" << endl;
		cout << "6 - �����" << endl;

		pressed_button = _getch();
		system("cls");
		switch (pressed_button)
		{
		case '1':
			showAll();
			break;
		case '2':
			addRecord(cin);
			break;
		case '3':
			findByDate();
			break;
		case '4':
			showSortedArr();
			break;
		case '5':
			deleteRecord();
			break;
		case '6':
			return;
			break;
		}
		cout << endl;
		cout << "������� ����� �������, ����� ��������� � ������� ����" << endl;
		_getch();
		system("cls");
	}
}
void Menu::deleteRecord()
{
	cout << "������� ������?(Y)" << endl;
	char pr_but = _getch();
	if (pr_but == 'Y' || pr_but == 'y' || pr_but == '�' || pr_but == '�')
		try
		{
			db->delete_record();
			cout << "������ �������" << endl;
		}
		catch (invalid_argument ex)
		{
			cout << "������ �������!";
		}
}
Menu::~Menu() 
{
	if (db != nullptr)
		delete db;
}
template<class T>
T* enter_num()
{
	T* temp = new T();
	*temp = 0;

	cin >> *temp;

	if (cin.fail())
	{
		cin.clear();
		delete temp;
		throw EnterException("������������ ���� �����!!");
	}

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return temp;
}