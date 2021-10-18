using System;
using System.Collections.Generic;
using System.IO;

namespace Lab5
{
    static class Program
    {
        private static void PrintLine(int n) 
        {
            Console.WriteLine();
            for(int i = 0; i < n; i++)
                Console.Write("-");
            Console.WriteLine();
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
        public static void Main() 
        {

            int lineLen = 60;

            ResearchTeam tTeam = new ResearchTeam("First", "OAO", 1, "TSquad1", TimeFrame.Long);

            for (int i = 0; i < 3; i++)
                tTeam.ArticleList.Add(new Paper(
                    "Article №" + i,
                    new Person("Author №" + i, "Surname №" + i, new DateTime(2000, 10, (i % 25) + 1)),
                    new DateTime(2020, 11, (i % 25) + 1)));

            PrintLine(lineLen);
            //1
            ResearchTeam tTeamCopy = tTeam.DeepCopy() as ResearchTeam;

            Console.WriteLine("Основной объект:");
            Console.WriteLine(tTeam);

            Console.WriteLine("Копия: ");
            Console.WriteLine(tTeamCopy);
            
            PrintLine(lineLen);
            //2
            Console.Write("Введите имя файла для сохранения файла: ");
            string filePath = Console.ReadLine();
            Console.WriteLine();

            ResearchTeam tTeam2 = new ResearchTeam();

            if (File.Exists(filePath))
            {
                Console.WriteLine("Попытка загрузить объект из файла...");
                if (tTeam2.Load(filePath))
                    Console.WriteLine("Успех!");
                else
                    Console.WriteLine("Ошибка загрузки файла, состояние установлено по умолчанию");
            }
            else
            {
                Console.WriteLine("Файла с таким именем не обнаружено, состояние установлено по умолчанию");
            }
            Console.WriteLine("Данный файл будет использован для хранения данных");

            PrintLine(lineLen);
            //3
            Console.WriteLine(tTeam2);

            PrintLine(lineLen);
            //4
            do
            {
                Console.WriteLine("\n\nДобавление статьи: \n");
            } while (!tTeam2.AddFromConsole());

            tTeam2.Save(filePath);

            PrintLine(lineLen);
            Console.WriteLine("Вывод объекта после добавления статьи: \n");
            Console.WriteLine(tTeam2);

            PrintLine(lineLen);
            //5
            if (ResearchTeam.Load(filePath, ref tTeam2))
                Console.WriteLine("\n\nЧтениe объекта из файла успешно\n");
            Console.WriteLine(tTeam2);

            PrintLine(lineLen);
            do
            {
                Console.WriteLine("\n\nДобавление статьи: \n");
            } while (!tTeam2.AddFromConsole());
            ResearchTeam.Save(filePath, tTeam2);
            Console.WriteLine(tTeam2);
        }
    }
}
