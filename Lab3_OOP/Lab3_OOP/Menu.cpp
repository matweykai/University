#include "Menu.h"

Menu::Menu()
{
	types = new vector<string>();
	types->push_back("Булочка");
	types->push_back("Пирожок");
	types->push_back("Пирожное");

	this->db = new FoodDataBase("test.txt", types);
}
Menu::~Menu() 
{
	if (db != nullptr)
		delete db;
	if (types != nullptr)
		delete types;
}

void Menu::showAll() 
{
	cout << "Все записи\n" << endl;
	show_table(db->get_food_arr(), types);
}
void Menu::findByName() 
{
	string* t_name = new string();
	
	cout << "Поиск по названию\n";
	cout << "Введите название товара: ";
	cin >> *t_name;

	Food* t_food = find_by_name(db->get_food_arr(), t_name);
	if (t_food == nullptr)
		cout << "Товар не найден";
	else
		show_table(t_food, types, 1);

	if (t_food != nullptr)
		delete t_food;
	delete t_name;
}
void Menu::showSortedArr() 
{
	Food* t_arr = sort_by_price(db->get_food_arr());

	cout << "Упорядоченный по цене список: \n\n";
	show_table(t_arr, types);

	if (t_arr != nullptr)
		for (int i = 0; i < Food::get_food_count(); i++)
			t_arr[i].destroy(true);
}
void Menu::findByDate() 
{
	cout << "Поиск товаров по дате\n\n";
	Date t_date = enterDate();
	
	int found = 0;
	Food* t_arr = filter_by_date(db->get_food_arr(), t_date, &found);
	show_table(t_arr, types, found);

	if (found != 0)
		for(int i = 0; i < found; i++)
			t_arr[i].destroy();
}
Date Menu::enterDate() 
{
	int* day = nullptr, *month = nullptr, *year = nullptr;
	Date result(1,1,1);
	
	while (true)
	{
		cout << "Введите день: ";
		day = enter_num<int>();
		while(day == nullptr)
		{
			cout << "Число введено неправильно" << endl;
			day = enter_num<int>();
		}

		cout << "Введите месяц: ";
		month = enter_num<int>();
		while (month == nullptr)
		{
			cout << "Число введено неправильно" << endl;
			month = enter_num<int>();
		}

		cout << "Введите год: ";
		year = enter_num<int>();
		while (year == nullptr)
		{
			cout << "Число введено неправильно" << endl;
			year = enter_num<int>();
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
void Menu::addRecord() 
{
	string name;
	double* weight = nullptr, *price = nullptr;
	int* count = nullptr;
	Date produceDate(1,1,1);

	cout << "Добавление новой записи" << endl;
	print_line(24, 2);
	cout << endl;

	cout << "Введите название: ";
	cin >> name;

	while (true)
	{
		cout << "Введите вес: ";
		weight = enter_num<double>();
		if (weight == nullptr)
		{
			cout << "Ошибка ввода числа" << endl;
			continue;
		}

		if (*weight < 0)
		{
			cout << "Вес не может быть отрицательным" << endl;
			continue;
		}
		break;
	}

	while (true)
	{
		cout << "Введите цену: ";
		price = enter_num<double>();
		if (price == nullptr)
		{
			cout << "Ошибка ввода числа" << endl;
			continue;
		}

		if (*price < 0)
		{
			cout << "Цена не может быть отрицательной" << endl;
			continue;
		}
		break;
	}

	while (true)
	{
		cout << "Введите кол-во товара: ";
		count = enter_num<int>();
		if (count == nullptr)
		{
			cout << "Ошибка ввода числа" << endl;
			continue;
		}

		if (*count < 0)
		{
			cout << "Кол-во не может быть отрицательным" << endl;
			continue;
		}
		break;
	}

	cout << "Типы товара" << endl;
	int counter = 0, *type_n = nullptr;
	for (vector<string>::iterator iter = types->begin(); iter != types->end(); iter++)
		cout << ++counter << " - " << *iter << endl;

	while (true) 
	{
		cout << "Введите тип товара: ";
		type_n = enter_num<int>();
		if (type_n == nullptr)
		{
			cout << "Ошибка ввода числа" << endl;
			continue;
		}
		if (*type_n < 1 || *type_n > counter)
		{
			cout << "Неправильный тип товара" << endl;
			continue;
		}
		break;
	}
	cout << "Дата производства" << endl;
	produceDate = enterDate();

	db->add_record(*price, FoodType(*type_n - 1), *weight, *count, new Date(produceDate), new string(name));

	delete weight, price, count, type_n;

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
		temp = nullptr;
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	return temp;
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
		cout << "3 - Найти товар по его названию" << endl;
		cout << "4 - Найти товары по дате" << endl;
		cout << "5 - Вывести упорядоченные записи" << endl;
		cout << "6 - Выйти" << endl;

		pressed_button = _getch();
		system("cls");
		switch (pressed_button)
		{
		case '1':
			showAll();
			break;
		case '2':
			addRecord();
			break;
		case '3':
			findByName();
			break;
		case '4':
			findByDate();
			break;
		case '5':
			showSortedArr();
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
ostream& operator <<(ostream& os, const Food& right)
{
	cout << right.name << (int)right.type << right.weight << right.count << right.price << right.produceDate->get_day << right.produceDate->get_month() << right.produceDate->get_year();
	
	return os;
}
