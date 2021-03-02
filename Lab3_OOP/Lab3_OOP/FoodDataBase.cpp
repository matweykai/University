#include "FoodDataBase.h"

vector<string>* FoodDataBase::types = nullptr;

FoodDataBase::FoodDataBase(string path, vector<string>* types)
{
	arr = nullptr;
	FoodDataBase::types = types;
	this->path = path;
	download_db();
}

vector<string>* FoodDataBase::get_types() { return FoodDataBase::types; }
Food* FoodDataBase::get_food_arr() { return arr; }
void FoodDataBase::add_record(double price, FoodType type, double weight, int count, Date* produce_date, string* name)
{
	if (produce_date != nullptr && name != nullptr)
	{
		Food* result = new Food[Food::foodCount + 1];
		
		for (int i = 0; i < Food::foodCount; i++)
			result[i] = arr[i];

		result[Food::foodCount - 1] = Food(price, type, weight, count, produce_date, name);
		if(arr != nullptr)
			delete[] arr;

		arr = result;
	}
}

void FoodDataBase::download_db() 
{
	ifstream stream;
	stream.open(path);

	if (stream.is_open())
	{
		while (true) 
		{
			Food* t_obj = get_obj(&stream);
			
			if (t_obj == nullptr)
				break;

			int size = Food::foodCount;
			Food* result = new Food[size];
			for (int i = 0; i < size - 1; i++)
				result[i] = arr[i];
			result[size - 1] = *t_obj;
			
			if (arr != nullptr)
				delete[] arr;
			delete t_obj;

			arr = result;
		}
		stream.close();
	}
}
Food* FoodDataBase::get_obj(ifstream* stream)
{
	if (stream != nullptr)
		if (!is_end(stream))
		{
			double price = 0, weight = 0;
			int  type = 0, count = 0, day = 0, month = 0, year = 0;
			string name;

			*stream >> price;
			*stream >> weight;
			*stream >> type;
			*stream >> count;
			*stream >> day;
			*stream >> month;
			*stream >> year;
			stream->ignore();
			getline(*stream, name);

			return new Food(price, FoodType(type), weight, count, new Date(day, month, year), new string(name));
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
		for (int i = 0; i < Food::foodCount; i++)
			dump_obj(arr[i], &str);
		str.close();
	}
}
void FoodDataBase::dump_obj(Food obj, ofstream* stream)
{
	if (stream != nullptr)
	{
		*stream << obj.price << endl;
		*stream << obj.weight << endl;
		*stream << (int)obj.type << endl;
		*stream << obj.count << endl;
		*stream << obj.produceDate->get_day() << endl;
		*stream << obj.produceDate->get_month() << endl;
		*stream << obj.produceDate->get_year() << endl;
		*stream << *obj.name << endl;
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

	int size = Food::foodCount;
	for (int i = 0; i < size; i++)
		arr[i].destroy();
}