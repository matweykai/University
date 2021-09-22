using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab3
{
    class ResearchTeamCollection
    {
        List<ResearchTeam> resTeamList = new List<ResearchTeam>();

        public int MinLicenceNumber 
        {
            get {
                return resTeamList.Min(team => team.LicenceNumber);
            }
        }
        public IEnumerable<ResearchTeam> TwoYearResearchTeams 
        {
            get 
            {
                foreach (var item in resTeamList.Where(team => team.ResearchDuration == TimeFrame.TwoYears))
                    yield return item;
            }
        }

        public void AddDefaults(int n) 
        {
            for (int i = 0; i < n; i++)
                resTeamList.Add(new ResearchTeam());
        }
        public void AddResearchTeams(params ResearchTeam[] newTeams) 
        {
            resTeamList.AddRange(newTeams);
        }
        public override string ToString()
        {
            string resultStr = "";
            for (int i = 0; i < resTeamList.Count; i++)
                resultStr += "Элемент №" + (i + 1).ToString() + "\n" + resTeamList[i].ToString();

            return resultStr;
        }
        public string ToShortString() 
        {
            string resultStr = "";
            for (int i = 0; i < resTeamList.Count; i++)
                resultStr += "Элемент №" + (i + 1).ToString() + "\n" + resTeamList[i].ToShortString() + 
                    $"Кол-во статей: {resTeamList[i].ArticleList.Count} Кол-во участников: {resTeamList[i].TeamMembers.Count}\n";

            return resultStr;
        }
        public List<ResearchTeam> NGroup(int memNum) 
        {
            List<ResearchTeam> result = new List<ResearchTeam>();

            var tCollection = result.GroupBy(item => item.TeamMembers.Count).Where(group => group.Key == memNum);
            foreach (var group in tCollection)
                foreach (var item in group)
                    result.Add(item);

            return result;
        }
        public List<ResearchTeam> GetSortedByLicenceList() 
        {
            List<ResearchTeam> listCopy = new List<ResearchTeam>();
            foreach (var item in resTeamList)
                listCopy.Add(item.DeepCopy() as ResearchTeam);

            listCopy.Sort();

            return listCopy;
        }
        public List<ResearchTeam> GetSortedByResearchNameList() 
        {
            List<ResearchTeam> listCopy = new List<ResearchTeam>();
            foreach (var item in resTeamList)
                listCopy.Add(item.DeepCopy() as ResearchTeam);

            listCopy.Sort(new ResearchTeam());

            return listCopy;
        }
        public List<ResearchTeam> GetSortedByArticlesCount() 
        {
            List<ResearchTeam> listCopy = new List<ResearchTeam>();
            foreach (var item in resTeamList)
                listCopy.Add(item.DeepCopy() as ResearchTeam);

            listCopy.Sort(new ResearchTeamComparer());

            return listCopy;
        }
    }
}
