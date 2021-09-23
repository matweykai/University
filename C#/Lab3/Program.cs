using System;
using System.Collections.Generic;
using System.Linq;

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
            Console.WriteLine("\nСортировка по номеру лицензии");
            foreach (var item in teamCollection.GetSortedByLicenceList())
                Console.WriteLine(item.ToShortString());
            Console.WriteLine("\nСортировка по названию исследований");
            foreach (var item in teamCollection.GetSortedByResearchNameList())
                Console.WriteLine(item.ToShortString());
            Console.WriteLine("\nСортировка по числу публикаций");
            foreach (var item in teamCollection.GetSortedByArticlesCount())
                Console.WriteLine(item.ToShortString() + "Кол-во статей: " + item.ArticleList.Count);
            //3
            Console.WriteLine("\nМинимальная лицензия: " + teamCollection.MinLicenceNumber);
            Console.WriteLine("\nИсследования с сроком 2 года: ");
            foreach (var item in teamCollection.TwoYearResearchTeams)
                Console.WriteLine(item);
            Console.WriteLine("\nГруппировка по кол-ву объектов");
            foreach (var group in teamCollection.GetResTeamList().GroupBy(team => team.ArticleList.Count))
            {
                Console.WriteLine("\nГруппа №" + group.Key);
                foreach (var item in group)
                    Console.WriteLine(item.ToShortString() + "Кол-во статей: " + item.ArticleList.Count);
            }    
            
            //4
            int elCount = 0;// = 1000000;
            while (true)
            {
                try
                {
                    Console.Write("Введите кол-во элементов: ");
                    elCount = Int32.Parse(Console.ReadLine());

                    if (elCount <= 0)
                    {
                        Console.WriteLine("Число должно быть положительным! Повторите ввод");
                        continue;
                    }

                    break;
                }
                catch (FormatException)
                {
                    Console.WriteLine("Ошибка при вводе числа! Повторите ввод");
                }
                catch (OverflowException)
                {
                    Console.WriteLine("Число слишком большое! Повторите ввод");
                }
            }

            TestCollections testCollection = new TestCollections(elCount);
            List<Team> lst = testCollection.GetTeamList();
            Console.WriteLine("\nВремя для первого элемента: \n");
            PrintTime(lst[0], testCollection);

            Console.WriteLine("\nВремя для элемента в середине: \n");
            PrintTime(lst[lst.Count / 2], testCollection);

            Console.WriteLine("\nВремя для элемента в конце: \n");
            PrintTime(lst[lst.Count - 1], testCollection);
        }
        static void PrintTime(Team element, TestCollections testCollection) 
        {
            var timeDict = testCollection.TestTime(element.Name, element);
            foreach (var key in timeDict.Keys)
                Console.WriteLine(key + $" : {timeDict[key].Key} мс ({timeDict[key].Value} тиков)");
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
