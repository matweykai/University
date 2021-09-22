using System;
using System.Collections.Generic;

namespace Lab3
{
    static class Program
    {
        static void Main(string[] args)
        {
            Console.WindowWidth = 170;
            //1
            ResearchTeamCollection teamCollection = new ResearchTeamCollection();
            Random random = new Random();
            for(int i = 0; i < 5; i++)
                teamCollection.AddResearchTeams(TestCollections.GenElement(random.Next(1000)));
            teamCollection.AddResearchTeams(new ResearchTeam("ResName***", "CompName***", 912, "Teammy", TimeFrame.TwoYears));
            teamCollection.AddResearchTeams(new ResearchTeam("ResName___", "CompName___", 912, "Turner", TimeFrame.TwoYears));
            Console.WriteLine(teamCollection);
            //2
            Console.WriteLine("Сортировка по номеру лицензии");
            foreach (var item in teamCollection.GetSortedByLicenceList())
                Console.WriteLine(item.ToShortString());
            Console.WriteLine("Сортировка по названию исследований");
            foreach (var item in teamCollection.GetSortedByResearchNameList())
                Console.WriteLine(item.ToShortString());
            Console.WriteLine("Сортировка по числу публикаций");
            foreach (var item in teamCollection.GetSortedByArticlesCount())
                Console.WriteLine(item.ToShortString() + "Кол-во статей: " + item.ArticleList.Count);
            //3
            Console.WriteLine("Минимальная лицензия: " + teamCollection.MinLicenceNumber);
            Console.WriteLine("Исследования с сроком 2 года: ");
            foreach (var item in teamCollection.TwoYearResearchTeams)
                Console.WriteLine(item);
            Console.WriteLine("Группировка по кол-ву объектов");
            foreach (var item in teamCollection.NGroup(912))
                Console.WriteLine(item);
            //4
            int elCount = 1000000;

            TestCollections testCollection = new TestCollections(elCount);
            List<Team> lst = testCollection.GetTeamList();
            Console.WriteLine("Время для первого элемента: ");
            PrintTime(lst[0], testCollection);

            Console.WriteLine("Время для элемента в середине: ");
            PrintTime(lst[lst.Count / 2], testCollection);

            Console.WriteLine("Время для элемента в конце: ");
            PrintTime(lst[lst.Count - 1], testCollection);
        }
        static void PrintTime(Team element, TestCollections testCollection) 
        {
            var timeDict = testCollection.TestTime(element.Name, element);
            foreach (var key in timeDict.Keys)
                Console.WriteLine(key + " : " + timeDict[key]);
        }
        public static IList<T> RandomShuffle<T>(this IEnumerable<T> list)
        {
            var random = new Random();
            var shuffle = new List<T>(list);
            for (var i = 2; i < shuffle.Count; ++i)
            {
                var temp = shuffle[i];
                var nextRandom = random.Next(i - 1);
                shuffle[i] = shuffle[nextRandom];
                shuffle[nextRandom] = temp;
            }
            return shuffle;
        }
    }
}
