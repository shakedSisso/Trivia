#include "MongoDatabase.h"
#include "Globals.h"
#include <ctime>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace curlpp::options;

constexpr char MONGO_DB_URI[] = "mongodb://localhost:27017";
constexpr char DATABASE_NAME[] = "triviaDB";
#define USERS_COLLECTION_NAME "users"
#define QUESTIONS_COLLECTION_NAME "questions"
#define STATISTICS_COLLECTION_NAME "statistics"

#define DEFAULT_STATISTICS_VALUE 0

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
	this->_uri = mongocxx::uri();
	this->_client = mongocxx::client(this->_uri);

	if (!this->_client[DATABASE_NAME])
	{
		this->_client.database(DATABASE_NAME).create_collection({}); // Empty options
		std::cout << "Created database: " << DATABASE_NAME << std::endl;
	}

	bsoncxx::string::view_or_value database_name{ DATABASE_NAME };
	this->_db = this->_client[database_name];

	// Create the collection if it does not exist
	if (!this->_db.has_collection(USERS_COLLECTION_NAME))
	{
		this->_client[DATABASE_NAME].create_collection(USERS_COLLECTION_NAME);
		std::cout << "Created collection: " << USERS_COLLECTION_NAME << std::endl;
	}
	if (!this->_db.has_collection(QUESTIONS_COLLECTION_NAME))
	{
		this->_client[DATABASE_NAME].create_collection(QUESTIONS_COLLECTION_NAME);
		std::cout << "Created collection: " << QUESTIONS_COLLECTION_NAME << std::endl;
		addQuestionsToDatabase();
	}
	if (!this->_db.has_collection(STATISTICS_COLLECTION_NAME))
	{
		this->_client[DATABASE_NAME].create_collection(STATISTICS_COLLECTION_NAME);
		std::cout << "Created collection: " << STATISTICS_COLLECTION_NAME << std::endl;
	}

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

	mongocxx::cursor cursor = usersCollections.find( queryDocument.view());

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

	//initializing the user's statistics 
	documentBuilder.clear();
	doc.empty();

	mongocxx::collection statisticsCollections = this->_db[STATISTICS_COLLECTION_NAME];

	documentBuilder.append(kvp("username", username));
	documentBuilder.append(kvp("games_count", DEFAULT_STATISTICS_VALUE));
	documentBuilder.append(kvp("correct_answers", DEFAULT_STATISTICS_VALUE));
	documentBuilder.append(kvp("total_answers", DEFAULT_STATISTICS_VALUE));
	documentBuilder.append(kvp("average_answer_time", DEFAULT_STATISTICS_VALUE));
	doc = documentBuilder.extract();

	statisticsCollections.insert_one(doc.view());

	return 0;
}

std::list<Question> MongoDatabase::getQuestions(const int amountOfQuestions)
{
	mongocxx::collection collection = this->_db.collection(QUESTIONS_COLLECTION_NAME);
	int count = collection.count_documents({});
	if (count < amountOfQuestions || count == 0)
	{
		throw std::exception("There are not enough questions");
	}

	mongocxx::pipeline pipe;
	pipe.sample(amountOfQuestions);
	mongocxx::cursor cursor = collection.aggregate(pipe);

	std::list<Question> questions;
	std::vector<std::string> answers;
	std::string jsonString;
	json jsonData;
	for (auto& doc : cursor)
	{
		jsonString = bsoncxx::to_json(doc);
		jsonData = json::parse(jsonString);
		answers.push_back(jsonData["correct_ans"]);
		answers.push_back(jsonData["ans2"]);
		answers.push_back(jsonData["ans3"]);
		answers.push_back(jsonData["ans4"]);
		questions.push_back(Question(jsonData["question"], answers, std::rand() % ANSWER_COUNT + 1));
		answers.clear();
	}

	return questions;
}

float MongoDatabase::getPlayerAverageAnswerTime(const std::string username)
{
	return getUserStatisticsJson(username)["average_answer_time"];
}

int MongoDatabase::getNumOfCorrectAnswers(const std::string username)
{
	return getUserStatisticsJson(username)["correct_answers"];
}

int MongoDatabase::getNumOfTotalAnswers(const std::string username)
{
	return getUserStatisticsJson(username)["total_answers"];
}

int MongoDatabase::getNumOfPlayerGames(const std::string username)
{
	return getUserStatisticsJson(username)["games_count"];
}

int MongoDatabase::getPlayerScore(const std::string username)
{
	return getNumOfCorrectAnswers(username); //the players score is the amount of correct answers they have
}

std::vector<std::string> MongoDatabase::getHighScores()
{
	mongocxx::collection statisticsColl = this->_db[STATISTICS_COLLECTION_NAME];
	mongocxx::options::find options;
	options.sort(streamDocument{} << "correct_answers" << -1 << bsoncxx::builder::stream::finalize);  // Sort in descending order of "score" field
	options.limit(HIGH_SCORES_COUNT);

	mongocxx::cursor cursor = statisticsColl.find({}, options);  // Retrieve all documents from the collection with the specified sort order
	json jsonData;
	std::vector<std::string> highScores;
	std::string message;

	for (const auto& doc : cursor) {
		// Access the fields of the document and perform the desired operations
		jsonData = json::parse(bsoncxx::to_json(doc));
		message = jsonData["username"];
		message += "- ";
		message += std::to_string((int)jsonData["correct_answers"]);
		highScores.push_back(message);
	}
	return highScores;
}

int MongoDatabase::submitGameStatistics(const std::string username, const int correctAnswerCount, const int wrongAnswerCount, const float averageAnswerTime)
{
	basicDocument documentBuilder;
	json userData = getUserStatisticsJson(username);
	int totalAnswers = userData["total_answers"] + correctAnswerCount + wrongAnswerCount;
	float avg = ((float)userData["average_answer_time"] * (int)userData["total_answers"] + averageAnswerTime) / totalAnswers;
	int correctAnswers = userData["correct_answers"] + correctAnswerCount;

	documentBuilder.append(kvp("username", username));
	documentBuilder.append(kvp("games_count", userData["games_count"] + 1));
	documentBuilder.append(kvp("correct_answers", correctAnswers));
	documentBuilder.append(kvp("total_answers", totalAnswers));
	documentBuilder.append(kvp("average_answer_time", avg));
	bsoncxx::document::value doc = documentBuilder.extract();

	mongocxx::collection statisticsCollections = this->_db[STATISTICS_COLLECTION_NAME];
	auto builder = streamDocument{};
	bsoncxx::document::value filter = builder << "username" << username << finalize;
	mongocxx::options::find_one_and_update options{};
	statisticsCollections.find_one_and_update(filter.view(), doc.view(), options);

	return 0;
}

void MongoDatabase::addQuestionsToDatabase()
{
	curlpp::Cleanup cleaner;
	curlpp::Easy request;
	request.setOpt(Url(API_URL));

	std::string response;
	request.setOpt(WriteFunction([&response](char* ptr, size_t size, size_t nmemb) {
		response.append(ptr, size * nmemb);
		return size * nmemb;
		}));

	// Perform the request
	request.perform();

	// Parse the JSON response
	QuestionStruct q;
	json jsonData = json::parse(response);
	if (jsonData.contains("results") && jsonData["results"].is_array()) {
		const auto& results = jsonData["results"];
		for (size_t i = 0; i < results.size(); i++) {
			const auto& questionObj = results[i];

			// Extract question details
			q.id = i + 1;
			q.question = questionObj["question"].get<std::string>();
			ApiEntity::checkForHtmlEntity(q.question);
			q.correct_ans = questionObj["correct_answer"].get<std::string>();
			ApiEntity::checkForHtmlEntity(q.correct_ans);
			q.ans2 = questionObj["incorrect_answers"].get<std::vector<std::string>>()[0];
			ApiEntity::checkForHtmlEntity(q.ans2);
			q.ans3 = questionObj["incorrect_answers"].get<std::vector<std::string>>()[1];
			ApiEntity::checkForHtmlEntity(q.ans3);
			q.ans4 = questionObj["incorrect_answers"].get<std::vector<std::string>>()[2];
			ApiEntity::checkForHtmlEntity(q.ans4);

			addQuestion(q);
		}
	}
}

int MongoDatabase::addQuestion(const QuestionStruct& q)
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

json MongoDatabase::getUserStatisticsJson(const std::string& username)
{
	if (!doesUserExist(username))
	{
		throw std::exception("user doesn't exist");
	}
	int sum = 0, count = 0;
	mongocxx::collection statisticsCollections = this->_db[STATISTICS_COLLECTION_NAME];
	auto builder = streamDocument{};
	bsoncxx::document::value queryDocument = builder << "username" << username << finalize;

	mongocxx::cursor cursor = statisticsCollections.find(queryDocument.view());
	auto& doc =*cursor.begin(); //only needs to access the beginning of the cursor because there is only one user with each username 
	
	std::string jsonString = bsoncxx::to_json(doc);
	return json::parse(jsonString);
}
