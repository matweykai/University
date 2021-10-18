using System;
using System.Collections.Generic;
using System.Linq;
using System.ComponentModel;

namespace Lab5
{
    delegate TKey KeySelector<TKey>(ResearchTeam rt);
    delegate void ResearchTeamsChangedHandler<TKey>(object source, ResearchTeamsChangedEventArgs<TKey> args);
    enum Revision { Remove, Replace, Property, Add }
    class ResearchTeamCollection<Tkey>
    {
        Dictionary<Tkey, ResearchTeam> resTeamDict = new Dictionary<Tkey, ResearchTeam>();
        KeySelector<Tkey> keySelector;
        public string CollectionName { get; set; }
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
        public event ResearchTeamsChangedHandler<Tkey> ResearchTeamsChanged;

        public ResearchTeamCollection(KeySelector<Tkey> keySelector)
        {
            this.keySelector = keySelector;
        }

        void ControlPropertyChanging(object source, PropertyChangedEventArgs args) 
        {
            ResearchTeamsChanged.Invoke(this, new ResearchTeamsChangedEventArgs<Tkey>(CollectionName, Revision.Property, args.PropertyName, (source as ResearchTeam).LicenceNumber));
        }
        public void AddDefaults(int n)
        {
            for (int i = 0; i < n; i++)
            {
                ResearchTeam tTeam = new ResearchTeam("A" + i, "C" + i, i, "T" + i, TimeFrame.Long);
                AddResearchTeams(tTeam);
            }
        }
        public void AddResearchTeams(params ResearchTeam[] newTeams)
        {
            foreach (var team in newTeams)
            {
                team.PropertyChanged += ControlPropertyChanging;
                resTeamDict.Add(keySelector.Invoke(team), team);
                // Do not add right, added only last object

                ResearchTeamsChanged.Invoke(this, new ResearchTeamsChangedEventArgs<Tkey>(CollectionName, Revision.Add, "AddResearchTeams", team.LicenceNumber));
            }
        }
        /*public void AddResearchTeams(ref ResearchTeam newTeam)
        {

            foreach (var team in newTeams)
            {
                
                // Do not add right, added only last object
                team.PropertyChanged += ControlPropertyChanging;

                ResearchTeamsChanged.Invoke(this, new ResearchTeamsChangedEventArgs<Tkey>(CollectionName, Revision.Add, "AddResearchTeams", team.LicenceNumber));
            }
        }*/
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
        public bool Remove(ResearchTeam rt) 
        {
            if (!resTeamDict.Values.Contains(rt))
                return false;
            
            foreach (var pair in resTeamDict)
                if (pair.Value == rt)
                {
                    pair.Value.PropertyChanged -= ControlPropertyChanging;
                    resTeamDict.Remove(pair.Key);
                    ResearchTeamsChanged.Invoke(this, new ResearchTeamsChangedEventArgs<Tkey>(CollectionName, Revision.Remove, "", rt.LicenceNumber));
                    break;
                }

            return true;
        }
        public bool Replace(ResearchTeam rold, ResearchTeam rnew) 
        {
            if (!resTeamDict.Values.Contains(rold))
                return false;

            Tkey tempKey = default(Tkey);
            foreach (var pair in resTeamDict)
                if (pair.Value == rold)
                {
                    pair.Value.PropertyChanged -= ControlPropertyChanging;
                    tempKey = pair.Key;
                    rnew.PropertyChanged += ControlPropertyChanging;
                }

            resTeamDict[tempKey] = rnew;
            ResearchTeamsChanged.Invoke(this, new ResearchTeamsChangedEventArgs<Tkey>(CollectionName, Revision.Replace, "", rold.LicenceNumber));

            return true;
        }
    }
}
