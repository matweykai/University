using System.Collections.Generic;

namespace Lab5
{
    class PaperComparer : IComparer<Paper>
    {
        public int Compare(Paper left, Paper right) 
        {
            return left.Author.Surname.CompareTo(right.Author.Surname);
        }
    }
}
