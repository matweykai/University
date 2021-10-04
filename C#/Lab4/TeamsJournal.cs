using System.Collections.Generic;

namespace Lab4
{
    class TeamsJournal<TKey>
    {
        List<TeamsJournalEntry> changesList = new List<TeamsJournalEntry>();

        public void ChangesEventController(object sender, ResearchTeamsChangedEventArgs<TKey> args)
        {
            changesList.Add(new TeamsJournalEntry(args.CollectionName, args.EventType, args.PropertyName, args.LicenceNumber));
        }
        public override string ToString()
        {
            string result = "События: \n";
            foreach (var item in changesList)
                result += item + "\n";

            return result;
        }
    }
}
