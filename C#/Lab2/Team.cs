﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Team : INameAndCopy
    {
        protected string companyName;
        protected int licenceNumber;

        public string Name { get; set; }
        public string CompanyName
        {
            get { return companyName; }
            set { if (value != null) companyName = value; }
        }
        public int LicenceNumber
        {
            get { return licenceNumber; }
            set
            {
                if (value <= 0)
                    throw new ArgumentException("LicenceNumber can be only positive integer");
                else
                    licenceNumber = value;
            }
        }

        public Team(string companyName, int licenceNumber) 
        {
            this.companyName = companyName;
            LicenceNumber = licenceNumber;
        }
        public Team() 
        {
            companyName = "NoNameCompany";
            licenceNumber = new Random().Next();
        }
        public object DeepCopy() 
        {
            return new Team() { Name = Name };
        }
        public override bool Equals(object obj)
        {
            try
            {
                Team team = (Team)obj;
                return team.companyName == companyName && team.licenceNumber == licenceNumber;
            }
            catch (InvalidCastException)
            {
                return base.Equals(obj);
            }
            
        }
        public override string ToString()
        {
            return "Имя компании: " + companyName + " Регистрационный номер: " + licenceNumber.ToString();
        }
        public override int GetHashCode()
        {
            //Берём 2 простых числа и с их помощью получаем hash
            int hash = 7;

            hash = hash * 13 + companyName.GetHashCode();
            hash = hash * 13 + licenceNumber.GetHashCode();

            return hash;
        }

        public static bool operator ==(Team left, Team right)
        {
            return left.Equals(right);
        }
        public static bool operator !=(Team left, Team right)
        {
            return !left.Equals(right);
        }
    }
}
