﻿using System;

enum TimeFrame { Year, TwoYears, Long }

namespace Lab1
{
    class Paper
    {
        public string ArticleName { get; set; }
        public Person Author { get; set; }
        public DateTime PublishDate { get; set; }

        public Paper(string articleName, Person author, DateTime publishDate) 
        {
            ArticleName = articleName;
            Author = author;
            PublishDate = publishDate;
        }
        public Paper() 
        {
            ArticleName = "Base article";
            Author = new Person("Clark", "Kent", new DateTime(1987, 10, 13));
            PublishDate = new DateTime(2000, 1, 1);
        }
        public override string ToString()
        {
            return $"{PublishDate.ToShortDateString()} - \"{ArticleName}\" Автор: {Author.ToString()}";
        }
    }
}
