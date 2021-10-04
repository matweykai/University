using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab4
{
    static class Program
    {
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
            ResearchTeamCollection<string> firstCollection = new ResearchTeamCollection<string>(team => team.Name) { CollectionName = "FirstCollection" };
            ResearchTeamCollection<string> secondCollection = new ResearchTeamCollection<string>(team => team.Name) { CollectionName = "SecondCollection" };

            TeamsJournal<string> journal = new TeamsJournal<string>();
            firstCollection.ResearchTeamsChanged += journal.ChangesEventController;
            secondCollection.ResearchTeamsChanged += journal.ChangesEventController;

            ResearchTeam tTeam1 = new ResearchTeam("First", "OAO", 1, "TSquad1", TimeFrame.Long);
            ResearchTeam tTeam2 = new ResearchTeam("Second", "OAO", 2, "TSquad2", TimeFrame.TwoYears);

            ResearchTeam tTeam3 = new ResearchTeam("Third", "PAR", 3, "Ppp1", TimeFrame.TwoYears);
            ResearchTeam tTeam4 = new ResearchTeam("Fourth", "PAR", 4, "Ppp2", TimeFrame.Long);

            firstCollection.AddResearchTeams(tTeam1, tTeam2);
            secondCollection.AddResearchTeams(tTeam3, tTeam4);

            tTeam1.ResearchName = "New name";
            tTeam2.ResearchDuration = TimeFrame.Long;
            tTeam3.ResearchName = "Reser Name123";
            tTeam4.ResearchDuration = TimeFrame.Year;

            firstCollection.Remove(tTeam2);
            secondCollection.Remove(tTeam4);

            tTeam2.ResearchDuration = TimeFrame.TwoYears;
            tTeam4.ResearchName = "Old Research Name";

            firstCollection.Replace(tTeam1, tTeam3);
            tTeam1.ResearchName = "TTeam11 new ResName";

            Console.WriteLine(journal);
        }
    }
}
