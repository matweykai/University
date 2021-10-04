using System;
using System.Collections;
using System.Collections.Generic;

namespace Lab4
{
    partial class ResearchTeam
    {
        public class ResearchTeamEnumerator : IEnumerator<Person>
        {
            List<Person> personList = new List<Person>();
            int curIndex = -1;
            public ResearchTeamEnumerator(List<Paper> articles)
            {
                foreach (var article in articles)
                    if (!personList.Contains(article.Author))
                        personList.Add(article.Author);
            }
            bool IEnumerator.MoveNext()
            {
                curIndex++;
                return curIndex < personList.Count;
            }
            public Person Current 
            {
                get {
                    return Current;
                }
            }
            object IEnumerator.Current
            {
                get {
                    try
                    {
                        return personList[curIndex];
                    }
                    catch (IndexOutOfRangeException)
                    {
                        throw new InvalidOperationException();
                    }
                }
            }
            void IEnumerator.Reset()
            {
                curIndex = -1;
            }
            void IDisposable.Dispose() 
            {
                return;
            }
        };
    }
}
