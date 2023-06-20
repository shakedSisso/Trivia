using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MongoDB.Driver;

namespace Trivia
{
    class MongoDB
    {
        private dynamic client;
        private dynamic database;
        private string keysCollectionName;
        private string databaseName;

        public MongoDB()
        {
            string connectionString = "mongodb://localhost:27017";
            this.databaseName = "triviaDB";
            this.keysCollectionName = "keys";

            this.client = new MongoClient(connectionString);
            this.database = client.GetDatabase(databaseName);
        }
        public int[] RetrieveKeyFromMongoDB()
        {
            
            var collection = database.GetCollection<KeyDocument>(this.keysCollectionName);

            var filter = Builders<KeyDocument>.Filter.Empty;
            var options = new FindOptions<KeyDocument>()
            {
                Limit = 1
            };

            var keyDocument = collection.Find(filter, options).FirstOrDefault();

            if (keyDocument != null)
            {
                return keyDocument.Key;
            }
            else
            {
                // Handle case when key is not found in MongoDB
                // You may choose to throw an exception or return a default key
                return "defaultKey";
            }
        }
    }
}
