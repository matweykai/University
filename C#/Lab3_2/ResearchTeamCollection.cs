using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab3
{
    delegate TKey KeySelector<TKey>(ResearchTeam rt);
    class ResearchTeamCollection<Tkey>
    {
        Dictionary<Tkey, ResearchTeam> resTeamDict = new Dictionary<Tkey, ResearchTeam>();
        KeySelector<Tkey> KeySelector;

        public DateTime LatestArticleDate
        {
            get {
                if (resTeamDict.Count == 0)
                    return new DateTime();

                return resTeamDict.Select(pair => pair.Value.ArticleList).Where(list => list.Count > 0).SelectMany(list => list).Max(article => article.PublishDate);
            }
        }
        public IEnumerable<IGrouping<TimeFrame, KeyValuePair<Tkey, ResearchTeam>>> DurationGroups 
        {
            get{
                return resTeamDict.GroupBy(pair => pair.Value.ResearchDuration);
            }
        }

        public ResearchTeamCollection(KeySelector<Tkey> keySelector)
        {
            KeySelector = keySelector;
        }

        public void AddDefaults(int n)
        {
            for (int i = 0; i < n; i++)
            {
                ResearchTeam tTeam = new ResearchTeam("A" + i, "C" + i, i, "T" + i, TimeFrame.Long);
                resTeamDict.Add(KeySelector.Invoke(tTeam), tTeam);
            }
        }
        public void AddResearchTeams(params ResearchTeam[] newTeams)
        {
            foreach (var team in newTeams)
                resTeamDict.Add(KeySelector.Invoke(team), team);
        }
        public override string ToString()
        {
            string resultStr = "";
            int counter = 0;
            foreach (var item in resTeamDict)
                resultStr += "Элемент №" + (++counter).ToString() + "\n" + item.Value.ToString() + "\n";

            return resultStr;
        }
        public string ToShortString()
        {
            string resultStr = "";
            int counter = 0;
            foreach (var item in resTeamDict)
                resultStr += "Элемент №" + (++counter).ToString() + "\n" + item.Value.ToShortString() +
                    $"Кол-во статей: {item.Value.ArticleList.Count} Кол-во участников: {item.Value.TeamMembers.Count}\n";

            return resultStr;
        }
        public IEnumerable<KeyValuePair<Tkey, ResearchTeam>> TimeFrameGroup(TimeFrame value)
        {
            foreach (var item in resTeamDict.Where(pair => pair.Value.ResearchDuration == value))
                yield return item;
              
        }
        
        /*public int MinLicenceNumber 
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

        
        
        
        
        public List<ResearchTeam> NGroup(int memNum)
        {
            var result = new List<ResearchTeam>();

            foreach (var group in resTeamList.GroupBy(team => team.TeamMembers.Count).Where(group => group.Key == memNum).ToList())
                foreach(var item in group)
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
        public List<ResearchTeam> GetResTeamList() 
        {
            return resTeamList;
        }*/
    }
}
