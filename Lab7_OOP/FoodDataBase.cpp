#include "FoodDataBase.h"

FoodDataBase::FoodDataBase(string path)
{
	this->path = path;
	download_db();
}

deque<Food> FoodDataBase::get_food_arr() { return arr; }
void FoodDataBase::add_record(double price, Date* produce_date, string* name, bool before)
{
	if (produce_date != nullptr && name != nullptr)
		if(!before)
			arr.push_back(Food(price, produce_date, name));
		else
			arr.push_front(Food(price, produce_date, name));
}

void FoodDataBase::download_db()
{
	/*ifstream stream;
	stream.open(path);

	if (stream.is_open())
	{
		while (true)
		{
			Food* t_obj = get_obj(&stream);

			if (t_obj == nullptr)
				break;

			int size = Food::get_food_count();
			Food** result = new Food * [size];
			for (int i = 0; i < size - 1; i++)
				result[i] = arr[i];
			result[size - 1] = t_obj;

			if (arr != nullptr)
				delete[] arr;

			arr = result;
		}
		stream.close();
	}*/
}
Food* FoodDataBase::get_obj(ifstream* stream)
{
	if (stream != nullptr)
		if (!is_end(stream))
		{
			double price = 0;
			int day = 0, month = 0, year = 0;
			string text;

			Food* result = nullptr;

			*stream >> price;
			*stream >> day;
			*stream >> month;
			*stream >> year;
			stream->ignore();
			getline(*stream, text);
			result = new Food(price, new Date(day, month, year), new string(text));

			return result;
		}
		else
			return nullptr;

	return nullptr;
}
void FoodDataBase::dump_db()
{
	ofstream str;
	str.open(path);

	if (str.is_open())
	{
		for (int i = 0; i < Food::get_food_count(); i++)
			arr[i].dump_obj(&str);
		str.close();
	}
}
bool FoodDataBase::is_end(ifstream* stream)
{
	streampos base = stream->tellg();
	stream->seekg(0, ios::end);
	streampos end_pos = stream->tellg();
	bool result = base == end_pos;
	stream->clear();
	stream->seekg(base);

	return result;
}

FoodDataBase::~FoodDataBase()
{
	dump_db();

	int size = Food::get_food_count();
	for (int i = 0; i < size; i++)
	{
		arr[0].destroy();
		arr.pop_front();
	}
}

void FoodDataBase::delete_record(int index) 
{
	if (index > arr.size() - 1 || index < 0)
		throw invalid_argument("Такого индекса не существует");
	
	deque<Food>::iterator iter = arr.begin();
	for (int i = 0; i < index; i++)
		iter++;

	arr[index].destroy();
	arr.erase(iter);
}