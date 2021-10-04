using System;
using System.Collections.Generic;
using System.Text;

namespace Lab4
{
    class Person
    {
        string name;
        string surname;
        DateTime birthday;

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
        public override string ToString() 
        {
            return $"Имя - {name} Фамилия - {surname} Дата рождения - {birthday.ToShortDateString()}";
        }
        public override bool Equals(object obj)
        {
            try
            {
                Person person = (Person)obj;
                return person.birthday == birthday && person.name == name && person.surname == surname;
            }
            catch (InvalidCastException) 
            {
                return base.Equals(obj);
            }
        }
        public override int GetHashCode()
        {
            //Берём 2 простых числа и с их помощью получаем hash
            int hash = 7;

            hash = hash * 13 + name.GetHashCode();
            hash = hash * 13 + surname.GetHashCode();
            hash = hash * 13 + birthday.GetHashCode();

            return hash;
        }
        public virtual object DeepCopy() 
        {
            return new Person(Name, Surname, Birthday);
        }

        public static bool operator ==(Person left, Person right)
        {
            return left.Equals(right);
        }
        public static bool operator !=(Person left, Person right)
        {
            return !left.Equals(right);
        }
    }
}
