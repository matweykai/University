#include "filesystem.h"

void dump_obj(FILE* source, Teacher* obj)
{
	fprintf(source, "%d\n%s\n%d\n", obj->department, obj->fio, obj->status);
}
void dump_db(string file_path, Teacher* arr, int size) 
{
	FILE* file = fopen(file_path.c_str(), "w");
	if (file == NULL)
	{
		cout << "Ошибка сохранения базы данных" << endl;
		return;
	}
	
	for (int i = 0; i < size; i++)
		dump_obj(file, &arr[i]);
	
	fclose(file);
}
Teacher* load_object(FILE* file) 
{
	if (feof(file))
		return nullptr;

	Teacher* result = new Teacher();
	fscanf_s(file, "%d\n", &result->department);
	result->fio = read_str(file);
	fscanf_s(file, "%d\n", &result->status);

	return result;
}
Teacher* download_db(string file_name, int* size) 
{
	FILE* file = fopen(file_name.c_str(), "r");
	*size = 0;

	Teacher* result = nullptr;
	if (file == NULL)
	{
		cout << "База данных пуста. Нажмите любую клавишу для продолжения" << endl;
		_getch();
		system("cls");
	}
	else 
	{
		while (true)
		{
			Teacher* t_obj = load_object(file);
			if (t_obj == nullptr)
				break;
			Teacher* t_arr = new Teacher[*size + 1];
			//Shallow copy
			for (int i = 0; i < *size; i++)
				t_arr[i] = result[i];
			t_arr[*size] = *t_obj;

			delete[] result;
			delete t_obj;

			result = t_arr;
			*size += 1;
		}
		fclose(file);
	}

	return result;
}