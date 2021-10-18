using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab5
{
    class ResearchTeamsChangedEventArgs<TKey> : EventArgs
    {
        public string CollectionName { get; set; }
        public Revision EventType { get; set; }
        public string PropertyName { get; set; }
        public int LicenceNumber { get; set; }

        public ResearchTeamsChangedEventArgs(string collectionName, Revision eventType, string propertyName, int licenceNumber) 
        {
            CollectionName = collectionName;
            EventType = eventType;
            PropertyName = propertyName;
            LicenceNumber = licenceNumber;
        }
        public override string ToString() 
        {
            return $"CollectionName = { CollectionName } EventType = { EventType } PropertyName = { PropertyName } LicenceNumber = { LicenceNumber }";
        }
    }
}
