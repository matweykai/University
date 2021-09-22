using System;
using System.Collections;
using System.Collections.Generic;

namespace Lab2
{
    partial class ResearchTeam
    {
        public class ResearchTeamEnumerator : IEnumerator<Person>
        {
            ArrayList personList = new ArrayList();
            int curIndex = -1;
            public ResearchTeamEnumerator(ArrayList articles)
            {
                foreach (var article in articles)
                    if (!personList.Contains(((Paper)article).Author))
                        personList.Add(((Paper)article).Author);
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
