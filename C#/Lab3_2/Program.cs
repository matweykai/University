using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab3
{
    static class Program
    {
        /*
        // Previous
        static void Main(string[] args)
        {
            
            ResearchTeamCollection<string> researchTeamCollection = new ResearchTeamCollection<string>(team => team.Name);
            researchTeamCollection.AddDefaults(10);

            var testResTeam1 = new ResearchTeam("ResName***", "CompName***", 912, "Teammy", TimeFrame.TwoYears);
            var testResTeam2 = new ResearchTeam("ResName___", "CompName___", 912, "Turner", TimeFrame.TwoYears);

            testResTeam1.AddPapers(new Paper("T", new Person(), new DateTime(2020, 1, 10)));
            testResTeam1.AddPapers(new Paper("T", new Person(), new DateTime(2019, 1, 10)));
            testResTeam1.AddPapers(new Paper("T", new Person(), new DateTime(2018, 1, 10)));

            testResTeam2.AddPapers(new Paper("A", new Person(), new DateTime(2021, 2, 6)));
            testResTeam2.AddPapers(new Paper("A", new Person(), new DateTime(2019, 2, 6)));
            testResTeam2.AddPapers(new Paper("A", new Person(), new DateTime(2018, 2, 6)));

            researchTeamCollection.AddResearchTeams(testResTeam1, testResTeam2);

            Console.WriteLine(researchTeamCollection.LatestArticleDate);
            
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
        */
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
        static void PrintTime(Team element, TestCollections testCollection)
        {
            var timeDict = testCollection.TestTime(element.Name, element);
            foreach (var key in timeDict.Keys)
                Console.WriteLine(key + $" : {timeDict[key].Key} мс ({timeDict[key].Value} тиков)");
        }

        public static void Main() 
        {
            ResearchTeamCollection<string> researchTeamCollection = new ResearchTeamCollection<string>(team => team.Name);
            researchTeamCollection.AddDefaults(10);

            var testResTeam1 = new ResearchTeam("ResName***", "CompName***", 912, "Teammy", TimeFrame.TwoYears);
            var testResTeam2 = new ResearchTeam("ResName___", "CompName___", 912, "Turner", TimeFrame.TwoYears);

            testResTeam1.AddPapers(new Paper("B", new Person("Andrew", "Garfield", new DateTime(1985,1, 21)), new DateTime(2020, 1, 10)));
            testResTeam1.AddPapers(new Paper("C", new Person( "Santa", "Claus", new DateTime(1985, 1, 21)), new DateTime(2019, 1, 10)));
            testResTeam1.AddPapers(new Paper("A", new Person("Pavel", "Morozov", new DateTime(1985, 1, 21)), new DateTime(2018, 1, 10)));

            testResTeam2.AddPapers(new Paper("A", new Person(), new DateTime(2021, 2, 6)));
            testResTeam2.AddPapers(new Paper("A", new Person(), new DateTime(2019, 2, 6)));
            testResTeam2.AddPapers(new Paper("A", new Person(), new DateTime(2018, 2, 6)));

            researchTeamCollection.AddResearchTeams(testResTeam1, testResTeam2);

            //1
            Console.WriteLine("Статьи отсортированные по дате: ");
            foreach (var item in testResTeam1.SortArticlesByDate())
                Console.WriteLine(item);

            Console.WriteLine("\nСтатьи отсортированы по названию: ");
            foreach (var item in testResTeam1.SortByArticleName())
                Console.WriteLine(item);

            Console.WriteLine("\nСтатьи отсортированы по фамилии автора: ");
            foreach (var item in testResTeam1.SortByAuthorSurname())
                Console.WriteLine(item);
            //2

            var tTeam1 = new ResearchTeam("OOO", "Comp___Name", 122, "Troover", TimeFrame.Year);
            var tTeam2 = new ResearchTeam("FFF", "Comp_-_Name", 93, "CatDog", TimeFrame.Year);

            tTeam1.AddPapers(new Paper("FirstPaper", new Person("Andrew", "Garfield", new DateTime(1985, 1, 21)), new DateTime(2020, 5, 10)));

            tTeam2.AddPapers(new Paper("SecondPaper", new Person(), new DateTime(2021, 1, 6)));

            ResearchTeamCollection<string> strTeamCollection = new ResearchTeamCollection<string>(team => team.Name);
            strTeamCollection.AddResearchTeams(tTeam1, tTeam2, testResTeam1, testResTeam2);

            Console.WriteLine("\nResTeam<string>:");
            Console.WriteLine(strTeamCollection);

            //3
            Console.WriteLine("Дата выхода последней статьи");
            Console.WriteLine(strTeamCollection.LatestArticleDate);

            Console.WriteLine("\nКоманды с продолжительностью исследования год:");
            foreach (var item in strTeamCollection.TimeFrameGroup(TimeFrame.Year))
                Console.WriteLine(item.Value.ToShortString());

            Console.WriteLine("\nГруппировка элементов по длительности исследований: ");
            foreach (var group in strTeamCollection.DurationGroups)
            {
                Console.WriteLine("\nГруппа с продолжительностью " + group.Key);
                foreach (var item in group)
                    Console.WriteLine(item.Value.ToShortString());
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

            Console.WriteLine("\nВремя для элемента которого нет: \n");
            PrintTime(new Team("GG", 123321, "321"), testCollection);
        }
    }
}
