using System;
using System.Collections;
using System.Collections.Generic;

namespace Lab3
{
    delegate KeyValuePair<TKey, TValue> GenerateElement<TKey, TValue>(int j);
    partial class ResearchTeam : Team, IEnumerable, IComparer<ResearchTeam>
    {
        string researchName;
        TimeFrame researchDuration;
        List<Person> teamMembers = new List<Person>();
        List<Paper> articlesList = new List<Paper>();

        public string ResearchName 
        { 
            get { return researchName; }
            set {
                if (value != null)
                    researchName = value;
            }
        }
        public TimeFrame ResearchDuration
        {
            get { return researchDuration; }
            set
            {
                researchDuration = value;
            }
        }
        public List<Paper> ArticleList 
        {
            get { return articlesList; }
            set 
            { if (value != null) articlesList = value; }
        }
        public List<Person> TeamMembers 
        {
            get { return teamMembers; }
            set { if (value != null) teamMembers = value; }
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
            ResearchTeam res_object = new ResearchTeam(ResearchName, CompanyName, LicenceNumber, Name, ResearchDuration);
            res_object.Name = Name;

            List<Paper> articles_copy = new List<Paper>();
            foreach(var article_obj in articlesList)
                articles_copy.Add((Paper)article_obj.DeepCopy());
            res_object.ArticleList = articles_copy;

            List<Person> members_copy = new List<Person>();
            foreach (var member_obj in teamMembers)
                members_copy.Add((Person)member_obj.DeepCopy());
            res_object.teamMembers = members_copy;

            return res_object;
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
