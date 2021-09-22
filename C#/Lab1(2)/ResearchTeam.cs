using System;

namespace Lab1
{
    class ResearchTeam
    {
        string researchName;
        string companyName;
        int licenceNumber;
        TimeFrame researchDuration;
        Paper[] articlesArr;
        string[] researchDurationString = { "Год", "Два года", "Долго" };
        public ResearchTeam(string researchName, string companyName, int licenceNumber, TimeFrame researchDuration) 
        {
            this.researchName = researchName;
            this.companyName = companyName;
            this.licenceNumber = licenceNumber;
            this.researchDuration = researchDuration;
            articlesArr = new Paper[0];
        }
        public ResearchTeam() 
        {
            researchName = "Base Research";
            companyName = "Simple Company";
            licenceNumber = 0;
            researchDuration = TimeFrame.Year;
            articlesArr = new Paper[0];
        }
        public string ResearchName 
        { get { return researchName; }
            set {
                if (value != null)
                    researchName = value;
            }
        }
        public string CompanyName
        {
            get { return companyName; }
            set
            {
                if (value != null)
                    companyName = value;
            }
        }
        public int LicenceNumber
        {
            get { return licenceNumber; }
            set
            {
                if (value >= 0)
                    licenceNumber = value;
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
        public Paper[] ArticleArr 
        {
            get { return articlesArr; }
            set 
            {
                if (value != null)
                    articlesArr = value;
            }
        }
        public Paper LastArticle 
        {
            get {
                if (articlesArr.Length == 0)
                    return null;
                else
                {
                    Paper tArticle = articlesArr[0];
                    foreach (Paper article in articlesArr)
                        if (article.PublishDate >= tArticle.PublishDate)
                            tArticle = article;

                    return tArticle;
                }
                    }
        }
        public bool this[TimeFrame timeFrame] 
        { 
            get { return timeFrame == researchDuration; } 
        }
        public void AddPapers(params Paper[] newPapers) 
        {
            Paper[] t_arr = new Paper[articlesArr.Length + newPapers.Length];
            articlesArr.CopyTo(t_arr, 0);
            newPapers.CopyTo(t_arr, articlesArr.Length);
            articlesArr = t_arr;
            /*Paper[] t_arr = new Paper[articlesArr.Length + newPapers.Length];

            for(int i = 0; i < articlesArr.Length; i++)
                t_arr[i] = articlesArr[i];
            for (int i = 0; i < newPapers.Length; i++)
                t_arr[i + articlesArr.Length] = newPapers[i];

            articlesArr = t_arr;*/
        }
        public override string ToString()
        {
            string resultStr = $"Имя компании - \"{companyName}\" Название исследования - \"{researchName}\" Регистрационный номер - {licenceNumber} " +
                $"Длительность исследования - {researchDurationString[(int)researchDuration]} Статьи: \n";

            for (int i = 0; i < articlesArr.Length; i++)
                resultStr += articlesArr[i].ToString() + "\n";

            return resultStr;
        }
        public virtual string ToShortString() 
        {
            return $"Имя компании - {companyName} Название исследования - {researchName} Регистрационный номер - {licenceNumber} " +
                $"Длительность исследования - { researchDurationString[(int)researchDuration]}";
        }
    }
}
