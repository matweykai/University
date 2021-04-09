#include "Menu.h"

Menu::Menu(string fileName) 
{
	db = new FoodDataBase(fileName);
}
void Menu::showAll()
{
	cout << "Все записи\n" << endl;

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
				cout << "Введите день: ";
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
				cout << "Введите месяц: ";
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
				cout << "Введите год: ";
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
			cout << "Повторите ввод" << endl;
		}
	}

	delete day, month, year;

	return result;
}
void Menu::showSortedArr() 
{
	deque<Food> sorted = sort_by_price(db->get_food_arr());
	cout << "Отсортированный список продуктов: \n" << endl;
	show_table(sorted);
}
void Menu::findByDate()
{
	cout << "Поиск товаров по дате\n\n";
	Date t_date = enterDate();

	deque<Food> found = find_by_date(db->get_food_arr(), t_date);
	show_table(found);
}
void Menu::addRecord(istream& str)
{
	string name;
	double* price = nullptr;
	Date produceDate(1, 1, 1);

	cout << "Добавление новой записи" << endl;
	print_line(24, 2);
	cout << endl;

	cout << "Введите название: ";
	getline(str, name);


	while (true)
	{
		try
		{
			cout << "Введите цену: ";
			price = enter_num<double>();

			if (*price < 0)
			{
				cout << "Цена не может быть отрицательной" << endl;
				continue;
			}
			break;
		}
		catch (EnterException ex)
		{
			cout << ex.get_msg() << endl;
		}
	}

	cout << "Дата производства" << endl;
	produceDate = enterDate();

	cout << "Добавить запись в начало? (Y)" << endl;
	bool before = false;
	char pr_but = _getch();
	if (pr_but == 'Y' || pr_but == 'y' || pr_but == 'н' || pr_but == 'Н')
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
		cout << "Меню" << endl;
		print_line(49, 1);
		cout << endl;
		cout << "1 - Показать все записи" << endl;
		cout << "2 - Добавить запись" << endl;
		cout << "3 - Найти товары по дате" << endl;
		cout << "4 - Вывести упорядоченные записи" << endl;
		cout << "5 - Удалить первую запись" << endl;
		cout << "6 - Выход" << endl;

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
		cout << "Нажмите любую клавишу, чтобы вернуться в главное меню" << endl;
		_getch();
		system("cls");
	}
}
void Menu::deleteRecord()
{
	cout << "Удалить запись?(Y)" << endl;
	char pr_but = _getch();
	if (pr_but == 'Y' || pr_but == 'y' || pr_but == 'н' || pr_but == 'Н')
		try
		{
			db->delete_record();
			cout << "Запись удалена" << endl;
		}
		catch (invalid_argument ex)
		{
			cout << "Нечего удалять!";
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
		throw EnterException("Неправильный ввод числа!!");
	}

	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return temp;
}