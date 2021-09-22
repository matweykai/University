using System;
using System.Collections.Generic;
using System.Text;

namespace Lab1
{
    class Person
    {
        string name;
        string surname;
        DateTime birthday;

        public Person(string name, string surname, DateTime birthday)
        {
            this.name = name;
            this.surname = surname;
            this.birthday = birthday;
        }
        public Person()
        {
            name = "Name";
            surname = "Surname";
            birthday = new DateTime(2000, 10, 10);
        }
        public string Name{ 
            get { return name; } 
            set { 
                if (value != null) 
                    name = value; 
            } 
        }
        public string Surname
        {
            get { return surname; }
            set
            {
                if (value != null)
                    surname = value;
            }
        }
        public DateTime Birthday
        {
            get { return birthday; }
            set
            {
                birthday = value;
            }
        }
        public int YearOfBirth 
        {
            get { return birthday.Year; }
            set 
            {
                if (value > 0)
                    birthday = new DateTime(value, birthday.Month, birthday.Day);
            }
        }
        public override string ToString() 
        {
            return $"Имя - {name} Фамилия - {surname} Дата рождения - {birthday.ToShortDateString()}";
        }
    }
}
