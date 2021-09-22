using System.Collections.Generic;
using System.Diagnostics;
using System;
using System.Linq;

namespace Lab3
{
    class TestCollections
    {
        List<Team> teamList = new List<Team>();
        List<string> strList = new List<string>();
        Dictionary<Team, ResearchTeam> resTeamDict = new Dictionary<Team, ResearchTeam>();
        Dictionary<string, ResearchTeam> resTeamDict2 = new Dictionary<string, ResearchTeam>();

        public TestCollections(int elementsCount) 
        {
            foreach (var num in Enumerable.Range(1, elementsCount).RandomShuffle())
            {
                ResearchTeam newObject = GenElement(num);
                teamList.Add(newObject.Team);
                strList.Add(newObject.Name);
                resTeamDict.Add(newObject.Team, newObject);
                resTeamDict2.Add(newObject.Name, newObject);
            }
        }
        public static ResearchTeam GenElement(int num) 
        {
            var result = new ResearchTeam("ResName" + num, "CompName" + num, num, "TeamName" + num, TimeFrame.Long);
            
            int artNum = new Random().Next(10);
            for (int i = 0; i < artNum; i++)
                result.AddPapers(new Paper("ArtName" + num, new Person("Author" + num, "Surname" + num, new DateTime(2000, 1, 1)), new DateTime(2020, 10, 10)));
            
            return result;
        }
        public Dictionary<string, long> TestTime(string keyStr, Team keyTeam) 
        {
            var result = new Dictionary<string, long>();

            Stopwatch sw = new Stopwatch();
            sw.Start();
            strList.Contains(keyStr);
            sw.Stop();
            result.Add("Поиск строки в списке", sw.ElapsedMilliseconds);

            sw.Restart();
            teamList.Contains(keyTeam);
            sw.Stop();
            result.Add("Поиск команды в списке", sw.ElapsedMilliseconds);

            sw.Restart();
            resTeamDict.ContainsKey(keyTeam);
            sw.Stop();
            result.Add("Поиск команды в словаре", sw.ElapsedMilliseconds);

            sw.Restart();
            resTeamDict2.ContainsKey(keyStr);
            sw.Stop();
            result.Add("Поиск команды в словаре по строке", sw.ElapsedMilliseconds);

            return result;
        }
        public List<Team> GetTeamList() 
        {
            return teamList;
        }
    }
}
