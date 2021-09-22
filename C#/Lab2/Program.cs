using System;
using System.Diagnostics;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            //1
            Team team_1 = new Team("ABC", 123);
            Team team_2 = new Team("ABC", 123);

            if (team_1 == team_2)
                Console.WriteLine("Объекты равны по значению");

            if (!ReferenceEquals(team_1, team_2))
                Console.WriteLine("Ссылки на объекты не равны");
            //2
            try
            {
                team_1.LicenceNumber = -1;
            }
            catch (ArgumentException ex) 
            {
                Console.WriteLine(ex.Message);
            }
            //3
            ResearchTeam researchTeam = new ResearchTeam();
            researchTeam.AddPapers(new Paper("Статья №1", new Person(), new DateTime(2000,1,1)), new Paper());
            researchTeam.AddMembers(new Person(), new Person("Иван", "Иванов", new DateTime(1997, 5, 12)));
            Console.WriteLine(researchTeam);
            //4
            Console.WriteLine(researchTeam.Team + "\n");
            //5
            ResearchTeam rTeamCopy = (ResearchTeam)researchTeam.DeepCopy();
            researchTeam.Name = "New Name";
            Console.WriteLine("Данные исходного объекта(изменённые): ");
            Console.WriteLine(researchTeam);
            Console.WriteLine("Данные копии: ");
            Console.WriteLine(rTeamCopy);
            //6
            Console.WriteLine("Участники без публикаций: ");
            foreach (var member in researchTeam.GetMembersWithZeroArticles())
                Console.WriteLine(member);
            //7
            researchTeam.AddPapers(new Paper("Новая статья №1", new Person(), DateTime.Now));
            researchTeam.AddPapers(new Paper("Новая статья №2", new Person(), new DateTime(2020, 10, 11)));
            researchTeam.AddPapers(new Paper("Старая статья №2", new Person(), new DateTime(2010, 10, 11)));

            Console.WriteLine("\nПубликации за последние 2 года");
            foreach (var article in researchTeam.GetLatestPapers(2))
                Console.WriteLine(article);
            //8
            Console.WriteLine("\nУчастники проекта, у которых есть публикации:");
            foreach (var member in researchTeam)
                Console.WriteLine(member);
            //9
            Console.WriteLine("\nУчастники, у которых больше одной публикации:");
            foreach (var member in researchTeam.GetMembersWithMoreThanOneArticle())
                Console.WriteLine(member);
            //10
            Console.WriteLine("\nПубликации за последний год: ");
            foreach (var article in researchTeam.GetLastYearPapers())
                Console.WriteLine(article);
        }

    }
}
