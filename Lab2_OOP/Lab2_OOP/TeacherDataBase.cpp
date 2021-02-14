#include "TeacherDataBase.h"

void TeacherDataBase::dump_obj(FILE* source, Teacher* obj)
{
	//Check memory bugs
	FullName* t_full_name = obj->get_fullname();
	fprintf(source, "%d\n%d\n%s\n%s\n%s\n", 
		obj->get_department(),
		obj->get_status(),
		t_full_name->get_name(),
		t_full_name->get_surname(),
		t_full_name->get_second_name());

	delete t_full_name;
}
void TeacherDataBase::dump_db(string file_name) 
{
	FILE* file = fopen(file_name.c_str(), "w");

	for (int i = 0; i < arr->get_count(); i++)
		dump_obj(file, &arr[i]);

	fclose(file);
}
Teacher* TeacherDataBase::load_object(FILE* file) 
{
	if (feof(file))
		return nullptr;

	int department = 0, status = 0;
	char* name = nullptr, *surname = nullptr, *second_name;
	fscanf_s(file, "%d\n%d\n", &department, &status);
	name = read_str(file);
	surname = read_str(file);
	second_name = read_str(file);

	return new Teacher(name, surname, second_name, department, status);
}
void TeacherDataBase::download_db(string file_name) 
{
	FILE* file = fopen(file_name.c_str(), "r");
	
	if (file != NULL)	//Check memory bugs
	{
		while (true)
		{
			Teacher* t_obj = load_object(file);
			if (t_obj == nullptr)
				break;
			Teacher* t_arr = new Teacher[arr->get_count() + 1];
			//Shallow copy
			for (int i = 0; i < t_arr->get_count(); i++)
				t_arr[i] = arr[i];
			t_arr[t_arr->get_count() - 1] = *t_obj;

			delete[] arr;
			delete t_obj;

			arr = t_arr;
		}
		fclose(file);
	}
}
TeacherDataBase::TeacherDataBase(string file_path) 
{
	download_db(file_path);
}
TeacherDataBase::~TeacherDataBase()	//Check memory bugs
{
	delete[] arr;
}