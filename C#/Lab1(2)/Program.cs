using System;
using System.Diagnostics;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            ResearchTeam team = new ResearchTeam();
            Console.WriteLine(team.ToShortString());

            Console.WriteLine($"Индексатор для Year = : Year = {team[TimeFrame.Year]} TwoYears = {team[TimeFrame.TwoYears]} Long = {team[TimeFrame.Long]}\n");
            
            team.ResearchName = "Поиск Немо";
            team.ResearchDuration = TimeFrame.TwoYears;
            team.LicenceNumber = 18999;
            team.CompanyName = "ООО \"Рыболов\"";
            team.ArticleArr = new Paper[] { new Paper(), new Paper("Первая попытка", new Person(), new DateTime(2002, 8, 13)), 
                new Paper("Вторая попытка", new Person("Фёдр", "Макгрегор", new DateTime(2009, 2, 9)), new DateTime(2010, 10, 12))};
            Console.WriteLine(team.ToString() + "\n");

            team.AddPapers(new Paper("Новое исследование", new Person("Иван", "Иванов", new DateTime(1998, 10, 7)), new DateTime(2021, 9, 10)));
            Console.WriteLine(team.ToString() + "\n");
            Console.WriteLine("Последнее исследование: \n" + team.LastArticle.ToString());

            //Сравнение скорости работы для одномерного, прямоугольного и ступенчатого массива

            string[] strArr = null;
            int strNum = 0, colNum = 0;

            while (true)
            {
                Console.WriteLine("Введите ncol, nrow, через запятую");
                string line = Console.ReadLine();

                strArr = line.Split(',');
                try
                {
                    strNum = Int32.Parse(strArr[0]);
                    colNum = Int32.Parse(strArr[1]);
                    break;
                }
                catch (FormatException)
                {
                    Console.WriteLine("Вы допустили ошибку при вводе!");
                }
                catch (ArgumentNullException)
                {
                    Console.WriteLine("Вы допустили ошибку при вводе!");
                }
            }
            int resSize = strNum * colNum;

            Paper[] paperLinearArr = new Paper[resSize];
            for (int i = 0; i < resSize; i++)
                paperLinearArr[i] = new Paper();

            
            Random random = new Random();
            Paper[][] paperStairsArr = new Paper[strNum][];
            for (int i = 0; i < strNum - 1; i++)
            {
                int t_size = random.Next(1, colNum);
                paperStairsArr[i] = new Paper[t_size];
                resSize -= t_size;
            }
            paperStairsArr[strNum - 1] = new Paper[resSize];

            for (int i = 0; i < paperStairsArr.Length; i++)
                for (int j = 0; j < paperStairsArr[i].Length; j++)
                    paperStairsArr[i][j] = new Paper();

            Paper[,] paperRectangleArr = new Paper[strNum, colNum];
            for (int i = 0; i < strNum; i++)
                for (int j = 0; j < colNum; j++)
                    paperRectangleArr[i, j] = new Paper();
            
        
            Stopwatch sw = new Stopwatch();

            sw.Start();
            foreach (Paper[] arr in paperStairsArr)
                foreach (Paper item in arr)
                    item.ArticleName = "NewName";
            sw.Stop();
            Console.WriteLine("Результат для зубчатого массива: " + sw.ElapsedMilliseconds.ToString());

            sw.Restart();
            foreach (Paper item in paperRectangleArr)
                item.ArticleName = "NewName";
            sw.Stop();
            Console.WriteLine("Результат для прямоугольного массива: " + sw.ElapsedMilliseconds.ToString());

            sw.Restart();
            foreach (Paper item in paperLinearArr)
                item.ArticleName = "NewName";
            sw.Stop();
            Console.WriteLine("Результат для линейного массива: " + sw.ElapsedMilliseconds.ToString());
        }
    }
}
