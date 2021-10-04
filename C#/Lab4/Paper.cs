using System;
using System.Collections.Generic;

enum TimeFrame { Year, TwoYears, Long }

namespace Lab4
{
    class Paper : IComparable, IComparer<Paper>
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
        public virtual object DeepCopy() 
        {
            return new Paper(ArticleName, (Person)Author.DeepCopy(), PublishDate);
        }
        public int CompareTo(object another) 
        {
            try
            {
                Paper anObj = another as Paper;
                return PublishDate.CompareTo(anObj.PublishDate);
            }
            catch (InvalidCastException)
            {
                throw new ArgumentException("Object should have class of Paper!");
            }
        }
        public int Compare(Paper left, Paper right) 
        {
            return left.ArticleName.CompareTo(right.ArticleName);
        }
    }
}
