using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab5
{
    class ResearchTeamComparer : IComparer<ResearchTeam>
    {
        public int Compare(ResearchTeam left, ResearchTeam right)
        {
            if (left.ArticleList.Count < right.ArticleList.Count)
                return -1;
            else if (left.ArticleList.Count == right.ArticleList.Count)
                return 0;
            else
                return 1;
        }
    }
}
