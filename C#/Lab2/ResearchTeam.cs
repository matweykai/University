using System;
using System.Collections;
using System.Collections.Generic;

namespace Lab2
{
    partial class ResearchTeam : Team, IEnumerable
    {
        string researchName;
        TimeFrame researchDuration;
        ArrayList teamMembers = new ArrayList();
        ArrayList articlesArr = new ArrayList();

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
        public ArrayList ArticleArr 
        {
            get { return articlesArr; }
            set 
            { if (value != null) articlesArr = value; }
        }
        public ArrayList TeamMembers 
        {
            get { return teamMembers; }
            set { if (value != null) teamMembers = value; }
        }
        public Paper LastArticle 
        {
            get {
                if (articlesArr.Count == 0)
                    return null;
                else
                {
                    Paper tArticle = (Paper)articlesArr[0];
                    foreach (Paper article in articlesArr)
                        if (article.PublishDate >= tArticle.PublishDate)
                            tArticle = article;

                    return tArticle;
                }
                    }
        }
        public Team Team
        {
            get { return new Team(CompanyName, LicenceNumber) { Name = Name }; }
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
            articlesArr.AddRange(newPapers);
        }
        public void AddMembers(params Person[] newMembers) 
        {
            teamMembers.AddRange(newMembers);
        }
        public override string ToString()
        {
            string resultStr = $"Имя компании - \"{ companyName }\" Название исследования - \"{ researchName }\" Регистрационный номер - {licenceNumber} " +
                $"Длительность исследования - { researchDuration } Название команды: \"{ Name }\"\nСтатьи: \n";

            foreach(var article in articlesArr)
                resultStr += article.ToString() + "\n";

            resultStr += "Участники: \n";
            foreach (var member in teamMembers)
                resultStr += member.ToString() + "\n";

            return resultStr;
        }
        public virtual string ToShortString() 
        {
            return $"Имя компании - {companyName} Название исследования - {researchName} Регистрационный номер - {licenceNumber} " +
                $"Длительность исследования - { researchDuration }";
        }
        public object DeepCopy()
        {
            ResearchTeam res_object = new ResearchTeam(ResearchName, CompanyName, LicenceNumber, Name, ResearchDuration);
            res_object.Name = Name;

            ArrayList articles_copy = new ArrayList();
            foreach(var article_obj in articlesArr)
                articles_copy.Add(((Paper)article_obj).DeepCopy());
            res_object.ArticleArr = articles_copy;

            ArrayList members_copy = new ArrayList();
            foreach (var member_obj in teamMembers)
                members_copy.Add(((Person)member_obj).DeepCopy());
            res_object.teamMembers = articles_copy;

            return res_object;
        }
        public IEnumerable<Person> GetMembersWithZeroArticles() 
        {
            ArrayList result_arr = new ArrayList();
            foreach (var member in TeamMembers)
            {
                bool has_publishes = false;
                foreach (var article in ArticleArr)
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

            foreach (var article in articlesArr)
                if (((Paper)article).PublishDate.CompareTo(new DateTime(DateTime.Now.Year - n_years, DateTime.Now.Month, DateTime.Now.Day)) > 0)
                    result_arr.Add(article);

            foreach (var article in result_arr)
                yield return (Paper)article;
        }
        public IEnumerator GetEnumerator() 
        {
            return new ResearchTeamEnumerator(ArticleArr);
        }
        public IEnumerable<Person> GetMembersWithMoreThanOneArticle() 
        {
            ArrayList resultArr = new ArrayList();

            Dictionary<Person, int> membersArticleCountPairs = new Dictionary<Person, int>();
            foreach (var member in TeamMembers)
            {
                membersArticleCountPairs.Add((Person)member, 0);
                foreach (var article in articlesArr)
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

        public bool this[TimeFrame timeFrame]
        {
            get { return timeFrame == researchDuration; }
        }
    }
}
