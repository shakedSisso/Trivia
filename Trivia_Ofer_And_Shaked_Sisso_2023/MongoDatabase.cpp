#include "MongoDatabase.h"

constexpr char MONGO_DB_URI[] = "mongodb://localhost:27017";
constexpr char DATABASE_NAME[] = "triviaDB";
#define USERS_COLLECTION_NAME "users"
#define QUESTIONS_COLLECTION_NAME "questions"

using mongocxx::collection;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::document;

typedef bsoncxx::builder::basic::document basicDocument;
typedef bsoncxx::builder::stream::document streamDocument;

MongoDatabase::MongoDatabase()
{
}

bool MongoDatabase::open()
{
	mongocxx::instance mongoInstance{};
	this->_uri = mongocxx::uri();
	this->_client = mongocxx::client(this->_uri);


	if (!this->_client[DATABASE_NAME]) {
		this->_client.database(DATABASE_NAME).create_collection({}); // Empty options
		std::cout << "Created database: " << DATABASE_NAME << std::endl;
	}

	// Create the collection if it does not exist
	if (!this->_client[DATABASE_NAME][USERS_COLLECTION_NAME]) {
		this->_client[DATABASE_NAME].create_collection(USERS_COLLECTION_NAME);
		std::cout << "Created collection: " << USERS_COLLECTION_NAME << std::endl;
	}
	if (!this->_client[DATABASE_NAME][QUESTIONS_COLLECTION_NAME]) {
		this->_client[DATABASE_NAME].create_collection(QUESTIONS_COLLECTION_NAME);
		std::cout << "Created collection: " << QUESTIONS_COLLECTION_NAME << std::endl;
	}

	mongocxx::database db = this->_client[DATABASE_NAME];
	bsoncxx::string::view_or_value database_name{ "triviaDB" };
	this->_db = this->_client[database_name];

	addTenAutoQuestions();

	return true;
}

bool MongoDatabase::close()
{
	return true;
}

int MongoDatabase::doesUserExist(const std::string username)
{
	mongocxx::collection usersCollections = this->_db[USERS_COLLECTION_NAME];
	auto builder = streamDocument{};
	bsoncxx::document::value queryDocument =
		builder << "username" << username
		<< finalize;

	mongocxx::cursor cursor = usersCollections.find(queryDocument.view());

	if (cursor.begin() != cursor.end())
	{
		return FOUND_RESPONSE_CODE;
	}
	return ERROR_RESPONSE_CODE;
}

int MongoDatabase::doesPasswordMatch(const std::string username, const std::string password)
{
	mongocxx::collection usersCollections = this->_db[USERS_COLLECTION_NAME];
	auto builder = streamDocument{};
	bsoncxx::document::value queryDocument =
		builder << "username" << username
		<< "password" << password
		<< finalize;

	mongocxx::cursor cursor = usersCollections.find(queryDocument.view());

	if (cursor.begin() != cursor.end())
	{
		return FOUND_RESPONSE_CODE;
	}
	return ERROR_RESPONSE_CODE;
}

int MongoDatabase::addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate)
{
	mongocxx::collection usersCollections = this->_db[USERS_COLLECTION_NAME];

	basicDocument documentBuilder{};
	documentBuilder.append(kvp("username", username));
	documentBuilder.append(kvp("password", password));
	documentBuilder.append(kvp("email", mail));
	documentBuilder.append(kvp("address", address));
	documentBuilder.append(kvp("phone_number", phoneNumber));
	documentBuilder.append(kvp("birth_date", birthDate));
	bsoncxx::document::value doc = documentBuilder.extract();

	usersCollections.insert_one(doc.view());
	return 0;
}

int MongoDatabase::addTenAutoQuestions()
{
	auto questionsColl = this->_db.collection(QUESTIONS_COLLECTION_NAME);
	if (questionsColl.count_documents({}) != 0)
	{
		std::cout << "questions already in the database" << std::endl;
		return 0;
	}

	std::list<Question> questions = AutoQuestions::getQuestionsFromFile();
	if (questions.front().id == FILE_NOT_OPEN)
	{
		return ERROR_RESPONSE_CODE;
	}

	for (auto q : questions)
	{
		addQuestion(q);
	}

	return 0;
}

int MongoDatabase::addQuestion(const Question& q)
{
	mongocxx::collection questionsCollections = this->_db[QUESTIONS_COLLECTION_NAME];

	basicDocument documentBuilder{};
	documentBuilder.append(kvp("question_id", q.id));
	documentBuilder.append(kvp("question", q.question));
	documentBuilder.append(kvp("correct_ans", q.correct_ans));
	documentBuilder.append(kvp("ans2", q.ans2));
	documentBuilder.append(kvp("ans3", q.ans3));
	documentBuilder.append(kvp("ans4", q.ans4));
	bsoncxx::document::value doc = documentBuilder.extract();

	questionsCollections.insert_one(doc.view());
	return 0;
}
