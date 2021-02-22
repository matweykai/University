#pragma once
#include "TeacherDataBase.h"

int Teacher::count = 0;
list<string>* Teacher::dep_list = nullptr;
list<string>* Teacher::status_list = nullptr;

Teacher::Teacher()
{
	department = 0;
	status = 0;
	char* name = new char[] {""};
	char* surname = new char[] {""};
	char* second_name = new char[] {""};

	fullname = new FullName(name, surname, second_name);
	//Do not increment count, because this object is just filling
}
Teacher::Teacher(char* name, char* surname, char* second_name, int department, int status)
{
	this->department = department;
	this->status = status;
	this->fullname = new FullName(name, surname, second_name);
	count++;
}
Teacher::~Teacher()
{
	delete fullname;
	count--;
}
Teacher::Teacher(const Teacher& teacher)
{
	this->department = teacher.department;
	this->status = teacher.status;
	this->fullname = new FullName(*teacher.fullname);
}
void Teacher::set_dep_list(list<string>* dep_list1)
{
	if (dep_list1 != nullptr)
		dep_list = dep_list1;
}
void Teacher::set_status_list(list<string>* status_list1)
{
	if (status_list1 != nullptr)
		status_list = status_list1;
}
list<string>* Teacher::get_dep_list() { return dep_list; }
list<string>* Teacher::get_status_list() { return status_list; }
int Teacher::get_count()
{
	return count;
}
char* Teacher::get_department()
{
	list<string>::iterator iter = dep_list->begin();

	for (int i = 0; i < department; i++)
		iter++;
	//Full copy
	char* result = new char[(*iter).length() + 1];
	for (int i = 0; i < (*iter).length(); i++)
		result[i] = (*iter)[i];
	result[(*iter).length()] = '\0';

	return result;
}
char* Teacher::get_status()
{
	list<string>::iterator iter = status_list->begin();

	for (int i = 0; i < status; i++)
		iter++;
	//Full copy
	char* result = new char[(*iter).length() + 1];
	for (int i = 0; i < (*iter).length(); i++)
		result[i] = (*iter)[i];
	result[(*iter).length()] = '\0';

	return result;
}
FullName* Teacher::get_fullname() { return new FullName(*fullname); }
int max_size(Teacher* arr, int size)
{
	if (size < 0)
		size = Teacher::get_count();
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		FullName* fullname = arr[i].get_fullname();
		int temp_len = strlen(fullname->get_name()) + strlen(fullname->get_surname()) + strlen(fullname->get_second_name());
		if (temp_len > result)
			result = temp_len;
	}
	return result;
}
void Teacher::swap(Teacher* teacher) 
{
	int t_dep = teacher->department, t_status = teacher->status;
	FullName* t_fullName = teacher->fullname;

	teacher->department = this->department;
	teacher->status = this->status;
	teacher->fullname = this->fullname;

	this->department = t_dep;
	this->status = t_status;
	this->fullname = t_fullName;
}
void Teacher::destroy(bool copy) 
{
	if (copy)
		delete this->fullname;
	else
		this->~Teacher();
}

void TeacherDataBase::dump_obj(FILE* source, Teacher* obj)
{
	if (obj == nullptr)
		return;
	FullName* t_fullname = obj->get_fullname();
	fprintf_s(source, "%d\n%d\n%s\n%s\n%s\n",
		obj->department,
		obj->status,
		(*t_fullname).get_name(),
		(*t_fullname).get_surname(),
		(*t_fullname).get_second_name());
	delete t_fullname;
}
void TeacherDataBase::dump_db()
{
	FILE* file = fopen(file_path.c_str(), "w");
	if (file != NULL)
		for (int i = 0; i < Teacher::get_count(); i++)
			dump_obj(file, &arr[i]);
}
Teacher* TeacherDataBase::load_object(FILE* file) 
{
	if (is_end(file))
		return nullptr;

	int department = 0, status = 0;

	fscanf_s(file, "%d\n%d\n", &department, &status);

	char* name = read_str(file);
	char* surname = read_str(file);
	char* second_name = read_str(file);
	
	return new Teacher(name, surname, second_name, department, status);
}
void TeacherDataBase::download_db()	//May be memory bugs
{
	FILE* file = fopen(file_path.c_str(), "r");
	
	if (file == nullptr)
		return;
	while (true)
	{
		Teacher* t_obj = load_object(file);
		if (t_obj == nullptr)
			break;
		Teacher* t_arr = new Teacher[t_obj->get_count()];
		//Shallow copy
		for (int i = 0; i < Teacher::get_count() - 1; i++)
			t_arr[i] = arr[i];
		t_arr[Teacher::get_count() - 1] = *t_obj;

		arr = t_arr;
	}

	fclose(file);
}

TeacherDataBase::TeacherDataBase(string file_path) 
{
	this->file_path = file_path;
	download_db();
}
Teacher* TeacherDataBase::find_teacher(FullName fullname)	//Checked
{
	for (int i = 0; i < Teacher::get_count(); i++)
		if (!strcmp(arr[i].fullname->get_name(), fullname.get_name()) &&
			!strcmp(arr[i].fullname->get_surname(), fullname.get_surname()) &&
			!strcmp(arr[i].fullname->get_second_name(), fullname.get_second_name())
			)
			return new Teacher(arr[i]);
	return nullptr;
}
Teacher* TeacherDataBase::sorted_list()	//Checked
{
	Teacher* result = copy_arr();

	for (int i = 0; i < Teacher::get_count() - 1; i++)
		for (int j = 0; j < Teacher::get_count() - i - 1; j++)
		{
			string full_name1, full_name2;
			full_name1 += result[j].fullname->get_surname();
			full_name1 += " ";
			full_name1 += result[j].fullname->get_name();
			full_name1 += " ";
			full_name1 += result[j].fullname->get_second_name();

			full_name2 += result[j + 1].fullname->get_surname();
			full_name2 += " ";
			full_name2 += result[j + 1].fullname->get_name();
			full_name2 += " ";
			full_name2 += result[j + 1].fullname->get_second_name();

			if (strcmp(full_name1.c_str(), full_name2.c_str()) > 0)
				result[j].swap(&result[j + 1]);
		}

	return result;
}
Teacher* TeacherDataBase::filter_by_status(int status, int* founded)	//Checked
{
	*founded = 0;
	for (int i = 0; i < Teacher::get_count(); i++)
		if (arr[i].status == status)
			(*founded) += 1;

	if (*founded > 0)
	{
		Teacher* result = new Teacher[*founded];
		int counter = 0;

		for (int i = 0; i < Teacher::get_count(); i++)
			if (arr[i].status == status)
				result[counter++] = *(new Teacher(arr[i]));

		return result;
	}

	return nullptr;
}
Teacher* TeacherDataBase::copy_arr()	//Checked
{
	Teacher* result = new Teacher[Teacher::get_count()];
	for (int i = 0; i < Teacher::get_count(); i++)
		result[i] = *(new Teacher(arr[i]));
	return result;
}
void TeacherDataBase::add_teacher(Teacher* teacher)	//Checked
{
	if (teacher == nullptr)
		return;
	Teacher* new_arr = new Teacher[teacher->get_count()];
	for (int i = 0; i < Teacher::get_count() - 1; i++)
		new_arr[i] = arr[i];
	new_arr[Teacher::get_count() - 1] = *teacher;

	arr = new_arr;
}
Teacher* TeacherDataBase::get_arr() { return arr; }

TeacherDataBase::~TeacherDataBase() 
{
	dump_db();
	if(arr != nullptr)
		delete[] arr;
	if(Teacher::dep_list != nullptr)
		delete Teacher::dep_list;
	if (Teacher::status_list != nullptr)
		delete Teacher::status_list;
}