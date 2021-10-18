using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace Lab5
{
    delegate KeyValuePair<TKey, TValue> GenerateElement<TKey, TValue>(int j);
    [Serializable]
    partial class ResearchTeam : Team, IEnumerable, IComparer<ResearchTeam>, INotifyPropertyChanged
    {
        string researchName;
        TimeFrame researchDuration;
        List<Person> teamMembers = new List<Person>();
        List<Paper> articlesList = new List<Paper>();
        public event PropertyChangedEventHandler PropertyChanged;

        public string ResearchName
        {
            get { return researchName; }
            set {
                if (value != null)
                {
                    researchName = value;
                    if (PropertyChanged != null)
                        PropertyChanged.Invoke(this, new PropertyChangedEventArgs("ResearchName"));
                }
            }
        }
        public TimeFrame ResearchDuration
        {
            get { return researchDuration; }
            set
            {
                researchDuration = value;
                if (PropertyChanged != null)
                    PropertyChanged.Invoke(this, new PropertyChangedEventArgs("ResearchDuration"));
            }
        }
        public List<Paper> ArticleList
        {
            get { return articlesList; }
            set
            {
                if (value != null)
                    if (PropertyChanged != null)
                    {
                        articlesList = value;
                        PropertyChanged.Invoke(this, new PropertyChangedEventArgs("ArticleList"));
                    }
            }
        }
        public List<Person> TeamMembers
        {
            get { return teamMembers; }
            set {
                if (value != null)
                    if (PropertyChanged != null)
                    {
                        teamMembers = value;
                        PropertyChanged.Invoke(this, new PropertyChangedEventArgs("TeamMembers"));
                    }
            }
        }
        public Paper LastArticle
        {
            get {
                if (articlesList.Count == 0)
                    return null;
                else
                {
                    Paper tArticle = (Paper)articlesList[0];
                    foreach (Paper article in articlesList)
                        if (article.PublishDate >= tArticle.PublishDate)
                            tArticle = article;

                    return tArticle;
                }
            }
        }
        public Team Team
        {
            get { return new Team(CompanyName, LicenceNumber, Name); }
            set
            {
                if (value != null)
                {
                    CompanyName = value.CompanyName;
                    LicenceNumber = value.LicenceNumber;
                    Name = value.Name;
                }
            }
        }

        public ResearchTeam(string researchName, string companyName, int licenceNumber, string teamName, TimeFrame researchDuration)
        {
            this.researchName = researchName;
            this.companyName = companyName;
            this.licenceNumber = licenceNumber;
            this.researchDuration = researchDuration;
            Name = teamName;
        }
        public ResearchTeam()
        {
            researchName = "Base Research";
            companyName = "Simple Company";
            Name = "Common team";
            licenceNumber = 1;
            researchDuration = TimeFrame.Year;
        }
        public void AddPapers(params Paper[] newPapers) 
        {
            articlesList.AddRange(newPapers);
        }
        public void AddMembers(params Person[] newMembers) 
        {
            teamMembers.AddRange(newMembers);
        }
        public bool AddFromConsole() 
        {
            try
            {
                Console.WriteLine("Введите данные статьи: Название статьи, Дату публикации\nДанные можно вводить через , или :");
                string usersEnter = Console.ReadLine();

                string[] rawPaperData = usersEnter.Split(',', ':');

                if (rawPaperData.Length < 2)
                {
                    Console.WriteLine("Слишком мало объектов, вы либо ввели неправильный разделитель или ввели мало слов! Объект не добавлен!");
                    return false;
                }
                string articleName = rawPaperData[0];
                DateTime publishDate = DateTime.Parse(rawPaperData[1]);

                Console.WriteLine("Введите данные автора: Имя Фамилия Дата рождения\nДанные можно вводить через , или :");
                usersEnter = Console.ReadLine();

                string[] rawAuthorData = usersEnter.Split(',', ':');

                if (rawAuthorData.Length < 3)
                {
                    Console.WriteLine("Слишком мало объектов, вы либо ввели неправильный разделитель или ввели мало слов! Объект не добавлен!");
                    return false;
                }
                string name = rawAuthorData[0];
                string surname = rawAuthorData[1];
                DateTime birthDate = DateTime.Parse(rawAuthorData[2]);

                articlesList.Add(new Paper(articleName, new Person(name, surname, birthDate), publishDate));
            }
            catch (FormatException) 
            {
                Console.WriteLine("Данные введены неверно! Объект не добавлен!");
                return false;
            }
            return true;
        }

        public override string ToString()
        {
            string resultStr = $"Имя компании - \"{ companyName }\" Название исследования - \"{ researchName }\" Регистрационный номер - {licenceNumber} " +
                $"Длительность исследования - { researchDuration } Название команды: \"{ Name }\"\nСтатьи: \n";

            foreach(var article in articlesList)
                resultStr += article.ToString() + "\n";

            resultStr += "Участники: \n";
            foreach (var member in teamMembers)
                resultStr += member.ToString() + "\n";

            return resultStr;
        }
        public virtual string ToShortString() 
        {
            return $"Имя компании - {companyName} Название исследования - {researchName} Регистрационный номер - {licenceNumber} " +
                $"Длительность исследования - { researchDuration }\n";
        }
        public object DeepCopy()
        {
            MemoryStream memoryStream = null;
            try
            {
                memoryStream = new MemoryStream();
                BinaryFormatter binaryFormatter = new BinaryFormatter();

                binaryFormatter.Serialize(memoryStream, this);
                memoryStream.Seek(0, SeekOrigin.Begin);
                return binaryFormatter.Deserialize(memoryStream);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                throw new Exception("Copy error!");
            }
            finally 
            {
                if (memoryStream != null)
                    memoryStream.Close();
            }
        }
        public bool Save(string fileName) 
        {
            return Save(fileName, this);
        }
        public bool Load(string fileName) 
        {
            FileStream fileStream = null;
            try
            {
                fileStream = new FileStream(fileName, FileMode.Open);
                BinaryFormatter formatter = new BinaryFormatter();

                ResearchTeam desObj = formatter.Deserialize(fileStream) as ResearchTeam;

                if (desObj.ArticleList == null || desObj.CompanyName == null || desObj.Name == null
                    || desObj.Team == null || desObj.TeamMembers == null)
                    return false;

                researchName = desObj.ResearchName;
                researchDuration = desObj.researchDuration;
                teamMembers = desObj.teamMembers;
                articlesList = desObj.articlesList;

                return true;
            }
            catch (Exception)
            {
                return false;
            }
            finally
            {
                if (fileStream != null)
                    fileStream.Close();
            }
        }
        public static bool Save(string fileName, ResearchTeam obj) 
        {
            FileStream fileStream = null;
            try
            {
                fileStream = new FileStream(fileName, FileMode.Create);
                BinaryFormatter formatter = new BinaryFormatter();

                formatter.Serialize(fileStream, obj);

                return true;
            }
            catch (Exception)
            {
                return false;
            }
            finally
            {
                if (fileStream != null)
                    fileStream.Close();
            }
        }
        public static bool Load(string fileName, ref ResearchTeam obj) 
        {
            if (obj != null)
                return obj.Load(fileName);
            else
                throw new ArgumentNullException();
        }

        public IEnumerable<Person> GetMembersWithZeroArticles() 
        {
            ArrayList result_arr = new ArrayList();
            foreach (var member in TeamMembers)
            {
                bool has_publishes = false;
                foreach (var article in ArticleList)
                    if (((Paper)article).Author.Equals(member))
                    {
                        has_publishes = true;
                        break;
                    }
                if (!has_publishes)
                    result_arr.Add(member);
            }

            foreach (var member in result_arr)
                yield return (Person)member;
        }
        public IEnumerable<Paper> GetLatestPapers(int n_years) 
        {
            ArrayList result_arr = new ArrayList();

            foreach (var article in articlesList)
                if (((Paper)article).PublishDate.CompareTo(new DateTime(DateTime.Now.Year - n_years, DateTime.Now.Month, DateTime.Now.Day)) > 0)
                    result_arr.Add(article);

            foreach (var article in result_arr)
                yield return (Paper)article;
        }
        public IEnumerator GetEnumerator() 
        {
            return new ResearchTeamEnumerator(ArticleList);
        }
        public IEnumerable<Person> GetMembersWithMoreThanOneArticle() 
        {
            ArrayList resultArr = new ArrayList();

            Dictionary<Person, int> membersArticleCountPairs = new Dictionary<Person, int>();
            foreach (var member in TeamMembers)
            {
                membersArticleCountPairs.Add((Person)member, 0);
                foreach (var article in articlesList)
                    if (((Paper)article).Author == (Person)member)
                        membersArticleCountPairs[(Person)member] += 1;
            }

            foreach (var pair in membersArticleCountPairs)
                if (pair.Value > 1)
                    resultArr.Add(pair.Key);

            foreach (var item in resultArr)
                yield return (Person)item;
        }
        public IEnumerable<Paper> GetLastYearPapers() 
        {
            foreach (var article in GetLatestPapers(1))
                yield return article;
        }
        public int Compare(ResearchTeam left, ResearchTeam right)
        {
            return string.Compare(left.researchName, right.researchName);
        }
        public List<Paper> SortArticlesByDate() 
        {
            List<Paper> result = new List<Paper>();
            foreach (var item in ArticleList)
                result.Add(item.DeepCopy() as Paper);

            result.Sort();
            return result;
        }
        public List<Paper> SortByArticleName() 
        {
            List<Paper> result = new List<Paper>();
            foreach (var item in ArticleList)
                result.Add(item.DeepCopy() as Paper);

            result.Sort(new Paper());
            return result;
        }
        public List<Paper> SortByAuthorSurname() 
        {
            List<Paper> result = new List<Paper>();
            foreach (var item in ArticleList)
                result.Add(item.DeepCopy() as Paper);

            result.Sort(new PaperComparer());

            return result;
        }

        public bool this[TimeFrame timeFrame]
        {
            get { return timeFrame == researchDuration; }
        }
    }
}
