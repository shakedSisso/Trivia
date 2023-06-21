using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MongoDB.Driver;
using MongoDB.Bson;
using System.Numerics;

namespace Trivia
{
    class MongoDB
    {
        private MongoClient client;
        private IMongoDatabase database;
        private string keysCollectionName;
        private string databaseName;

        public MongoDB()
        {
            MongoClientSettings settings = MongoClientSettings.FromUrl(new MongoUrl("mongodb://localhost:27017"));
            
            string connectionString = "mongodb://localhost:27017";
            this.databaseName = "triviaDB";
            this.keysCollectionName = "keys";
            this.client = new MongoClient(settings);
            //this.client = new MongoClient(connectionString);
            this.database = client.GetDatabase(databaseName);
        }
        public ObjectId insertKeys(BigInteger publicKey, BigInteger modulus)
        {
            
            var collection = database.GetCollection<BsonDocument>("keys");

            var document = new BsonDocument
        {
            { "public_key", publicKey.ToString() },
            { "modulus", modulus.ToString() },
            { "isServer", 0 }
        };

            collection.InsertOne(document);

            return document["_id"].AsObjectId;
        }

        public BsonDocument getServerKeys()
        {
            IMongoCollection<BsonDocument> collection = database.GetCollection<BsonDocument>("keys");
            //database.GetCollection<BsonDocument>("keys");
            //database.GetCollection<BsonDocument>("keys")
            

            var findOptions = new FindOptions
            {
                BatchSize = 1
            };

            var filter = Builders<BsonDocument>.Filter.Eq("isServer", 1);
            IFindFluent<BsonDocument, BsonDocument> document = collection.Find(filter);
            //collection.Find(filter);
            //using (var cursor = collection.Find(filter, findOptions).ToCursor())
            //{
            //    cursor.MoveNext();
            //    return cursor;
            //    //Console.WriteLine($"Number of documents in cursor: {cursor.Current.Count()}");
            //}
            return document.ToCursor().MoveNext().ToBsonDocument();
        }

        public void deleteDocument(ObjectId documentId)
        { 
            var collection = database.GetCollection<BsonDocument>("keys");

            var filter = Builders<BsonDocument>.Filter.Eq("_id", documentId);
            collection.DeleteOne(filter);
        }
    }
    public class KeyDocument
    {
        public ObjectId Id { get; set; }
        public int PublicKey { get; set; }
        public int Modulus { get; set; }
        public bool isServer { get; set; }
    }
}
