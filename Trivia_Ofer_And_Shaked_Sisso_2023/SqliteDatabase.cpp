#include "SqliteDatabase.h"
#include <map>
#include <string>
#include <io.h>
#include <ctime>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "json.hpp"

using namespace curlpp::options;
using json = nlohmann::json;

#define FIELDS_OF_QUESTION 6
#define FIELDS_OF_USER_QUESTION (FIELDS_OF_QUESTION + 1)

SqliteDatabase::SqliteDatabase() : _db(), _dbFileName("triviaDB.sqlite")
{
}

void SqliteDatabase::addQuestionsToDatabase()
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

int SqliteDatabase::addQuestion(QuestionStruct& q)
{
	fixValue(q.question);
	fixValue(q.correct_ans);
	fixValue(q.ans2);
	fixValue(q.ans3);
	fixValue(q.ans4);
	std::string sqlStatement = "INSERT INTO t_questions (question_id, question, correct_ans, ans2, ans3, ans4) VALUES (" + std::to_string(q.id) + ", \"" + q.question + "\", \"" + q.correct_ans + "\", \"" + q.ans2 + "\", \"" + q.ans3 + "\", \"" + q.ans4 + "\"); ";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	return 0;
}

int SqliteDatabase::addQuestion(UserQuestionStruct& q)
{
	fixValue(q.question);
	fixValue(q.correct_ans);
	fixValue(q.ans2);
	fixValue(q.ans3);
	fixValue(q.ans4);
	std::string sqlStatement = "INSERT INTO t_user_questions (question_id, author, question, correct_ans, ans2, ans3, ans4) VALUES (" + std::to_string(q.id) + ", \"" + q.author+ "\", \"" + q.question + "\", \"" + q.correct_ans + "\", \"" + q.ans2 + "\", \"" + q.ans3 + "\", \"" + q.ans4 + "\"); ";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	return 0;
}

void SqliteDatabase::fixValue(std::string& value)
{
	std::string entity = "\"";
	std::string replacement = "\'";
	size_t pos = value.find(entity);
	while (pos != std::string::npos)
	{
		value.replace(pos, entity.length(), replacement);
		pos = value.find(entity, pos + replacement.length());
	}
}

bool SqliteDatabase::createTables(int& res)
{
	std::string sqlStatemant = "CREATE TABLE IF NOT EXISTS t_users ( username text primarykey NOT NULL UNIQUE, password text NOT NULL, email text NOT NULL, address TEXT NOT NULL, phone_number TEXT NOT NULL, birth_date TEXT NOT NULL);";
	char** errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	sqlStatemant = "CREATE TABLE IF NOT EXISTS t_questions (question_id integer NOT NULL UNIQUE, question text NOT NULL, correct_ans text NOT NULL, ans2 text NOT NULL, ans3 text NOT NULL, ans4 text NOT NULL, PRIMARY KEY(question_id AUTOINCREMENT));";
	errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	sqlStatemant = "CREATE TABLE IF NOT EXISTS t_user_questions (question_id integer NOT NULL UNIQUE, author text NOT NULL, question text NOT NULL, correct_ans text NOT NULL, ans2 text NOT NULL, ans3 text NOT NULL, ans4 text NOT NULL, PRIMARY KEY(question_id AUTOINCREMENT));";
	errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;
	sqlStatemant = "CREATE TABLE IF NOT EXISTS t_statistics (username	TEXT NOT NULL UNIQUE, games_count integer NOT NULL, correct_answers integer NOT NULL, total_answers integer NOT NULL, average_answer_time integer NOT NULL, PRIMARY KEY(username), FOREIGN KEY(username) REFERENCES t_users(username)); ";
	errMessage = nullptr;
	res = sqlite3_exec(this->_db, sqlStatemant.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
		return false;

	addQuestionsToDatabase();

	return true;
}

int SqliteDatabase::callbackHighScores(void* list, int argc, char** argv, char** azColName)
{
	int i = 0;
	std::string message;
	for (i = 0; i < argc/2; i++)
	{
		message = argv[i];
		message += "- ";
		message += argv[i + 1];
		((std::list<std::string>*)list)->push_back(message);
	}
	return 0;
}

int SqliteDatabase::callbackString(void* list, int argc, char** argv, char** azColName)
{
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		((std::list<std::string>*)list)->push_back(argv[i]);
	}
	return 0;
}

int SqliteDatabase::callbackQuestions(void* list, int argc, char** argv, char** azColName)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	QuestionStruct q;
	int i = 0; 
	int currentPlace = 0;
	for (i = 0; i < argc/FIELDS_OF_QUESTION; i++)
	{
		currentPlace = i * FIELDS_OF_QUESTION;

		//Accessing all the fields of each question
		q.id = std::atoi(argv[currentPlace]);
		q.question = argv[currentPlace + 1];
		q.correct_ans = argv[currentPlace + 2];
		q.ans2 = argv[currentPlace + 3];
		q.ans3 = argv[currentPlace + 4];
		q.ans4 = argv[currentPlace + 5];

		((std::list<Question>*)list)->push_back(Question(q.question, std::vector<std::string>{q.correct_ans, q.ans2, q.ans3, q.ans4}, std::rand() % ANSWER_COUNT + 1));
	}
	return 0;
}

int SqliteDatabase::callbackUserQuestions(void* list, int argc, char** argv, char** azColName)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	QuestionStruct q;
	int i = 0; 
	int currentPlace = 0;
	for (i = 0; i < argc/FIELDS_OF_USER_QUESTION; i++)
	{
		currentPlace = i * FIELDS_OF_USER_QUESTION;

		//Accessing all the fields of each question
		q.id = std::atoi(argv[currentPlace]);
		q.question = argv[currentPlace + 2];
		q.correct_ans = argv[currentPlace + 3];
		q.ans2 = argv[currentPlace + 4];
		q.ans3 = argv[currentPlace + 5];
		q.ans4 = argv[currentPlace + 6];

		((std::list<Question>*)list)->push_back(Question(q.question, std::vector<std::string>{q.correct_ans, q.ans2, q.ans3, q.ans4}, std::rand() % ANSWER_COUNT + 1));
	}
	return 0;
}

bool SqliteDatabase::open()
{
	int fileExist = _access(this->_dbFileName.c_str(), 0);
	int res = sqlite3_open(this->_dbFileName.c_str(), &this->_db);
	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (fileExist != 0)
	{
		if (!createTables(res))
			return false;
	}
	return true;
}

bool SqliteDatabase::close()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
	return true;
}

int SqliteDatabase::doesUserExist(const std::string username)
{
	std::list<std::string> list;
	std::string sqlStatement = "SELECT * FROM t_users WHERE username = '" + username + "';";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	if (list.empty())
	{
		return ERROR_RESPONSE_CODE;
	}
	return FOUND_RESPONSE_CODE;
}

int SqliteDatabase::doesPasswordMatch(const std::string username, const std::string password)
{
	if (doesUserExist(username) != ERROR_RESPONSE_CODE)
	{
		std::list<std::string> list;
		std::string sqlStatement = "SELECT password FROM t_users WHERE username = '" + username + "' AND password = '" + password + "'; ";
		int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
		if (res != SQLITE_OK)
		{
			throw std::exception("Error- sqlite3_exec functions failed");
		}
		if (!list.empty())
		{
			return FOUND_RESPONSE_CODE;
		}
	}
	return ERROR_RESPONSE_CODE;

}

int SqliteDatabase::addNewUser(const std::string username, const std::string password, const std::string mail, const std::string address, const std::string phoneNumber, const std::string birthDate)
{
	std::string sqlStatement = "INSERT INTO t_users VALUES ('" + username + "', '" + password + "', '" + mail + "', '" + address + "', '" + phoneNumber + "', '" + birthDate + "');";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	sqlStatement = "INSERT INTO t_statistics VALUES ('" + username + "', 0, 0, 0, 0);";
	res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
    return 0;
}

std::list<Question> SqliteDatabase::getQuestions(const int amountOfQuestions, const bool includeUserQuestions)
{
	std::list<std::string> list;
	std::list<Question> questions, temp;
	int regularQuestions = amountOfQuestions, res = 0;
	std::string sqlStatement;
	if (includeUserQuestions)
	{
		int questionCount = 0, userQuestions = 0;
		sqlStatement = "SELECT COUNT(*) FROM t_user_questions;";
		res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
		if (res != SQLITE_OK)
		{
			throw std::exception("Error- sqlite3_exec functions failed");
		}
		questionCount = std::atoi(list.begin()->c_str());
		if (questionCount != 0)
		{
			do
			{
				userQuestions = std::rand() % amountOfQuestions;
			} while (userQuestions >= questionCount || userQuestions == 0);
			regularQuestions -= userQuestions;
		}

		sqlStatement = "SELECT * FROM t_user_questions ORDER BY RANDOM() LIMIT " + std::to_string(userQuestions) + ";";
		res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackUserQuestions, &temp, nullptr);
		if (res != SQLITE_OK)
		{
			throw std::exception("Error- sqlite3_exec functions failed");
		}
	}
	sqlStatement = "SELECT * FROM t_questions ORDER BY RANDOM() LIMIT " + std::to_string(regularQuestions)+ ";";
	res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackQuestions ,&temp, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}

	if (temp.empty() || temp.size() < amountOfQuestions)
	{
		throw std::exception("There are not enough questions");
	}

	//mix the order of the questions for random order of user and regular questions (if chosen to include user questions)
	int index = 0;
	while (!temp.empty()) 
	{
		index = rand() % temp.size();
		auto it = temp.begin();
		std::advance(it, index);
		questions.push_back(*it);
		temp.erase(it);
	}

	return questions;
}

float SqliteDatabase::getPlayerAverageAnswerTime(const std::string username)
{
	if (!doesUserExist(username))
	{ 
		throw std::exception("user doesn't exist");
	}
	float avg;
	std::list<std::string> list;
	std::string sqlStatement = "SELECT average_answer_time FROM t_statistics WHERE username = '" + username + "';";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	avg = std::atoi(list.front().c_str());
	return avg;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string username)
{
	if (!doesUserExist(username))
	{
		throw std::exception("user doesn't exist");
	}
	std::list<std::string> list;
	std::string sqlStatement = "SELECT correct_answers FROM t_statistics WHERE username = '" + username + "';";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	return std::atoi(list.front().c_str());
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string username)
{
	if (!doesUserExist(username))
	{
		throw std::exception("user doesn't exist");
	}
	std::list<std::string> list;
	std::string sqlStatement = "SELECT total_answers FROM t_statistics WHERE username = '" + username + "';";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	return std::atoi(list.front().c_str());
}

int SqliteDatabase::getNumOfPlayerGames(const std::string username)
{
	if (!doesUserExist(username))
	{
		throw std::exception("user doesn't exist");
	}
	std::list<std::string> list;
	std::string sqlStatement = "SELECT games_count FROM t_statistics WHERE username = '" + username + "';";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	return std::atoi(list.front().c_str());
}

int SqliteDatabase::getPlayerScore(const std::string username)
{
	return getNumOfCorrectAnswers(username); //the players score is the amount of correct answers they have
}

std::vector<std::string> SqliteDatabase::getHighScores()
{
	std::vector<std::string> highScores;
	std::list<std::string> list;
	std::string sqlStatement = "select username, correct_answers from t_statistics ORDER by correct_answers DESC LIMIT " + std::to_string(HIGH_SCORES_COUNT) + "; ";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackHighScores, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	for (auto& user : list)
	{
		highScores.push_back(user);
	}
	return highScores;
}

int SqliteDatabase::submitGameStatistics(const std::string username, const int correctAnswerCount, const int wrongAnswerCount, const float averageAnswerTime)
{
	int totalAnswers = getNumOfTotalAnswers(username) + correctAnswerCount + wrongAnswerCount;
	float averageTime = (getPlayerAverageAnswerTime(username)*getNumOfTotalAnswers(username) + averageAnswerTime) / totalAnswers;
	int correctAnswers = getNumOfCorrectAnswers(username) + correctAnswerCount;
	int gameCount = getNumOfPlayerGames(username) + 1;

	std::string sqlStatement = "UPDATE t_statistics SET games_count =  "+std::to_string(gameCount) + ", correct_answers = " + std::to_string(correctAnswers) + ", total_answers = " + std::to_string(totalAnswers) + ", average_answer_time = " + std::to_string(averageTime) + " WHERE username = '" + username + "'; ";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), nullptr, nullptr, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}

	return 0;
}

int SqliteDatabase::addUserQuestion(const std::string author, const std::string question, const std::string correctAnswer, const std::string ans2, const std::string ans3, const std::string ans4)
{
	int questionCount = 0;
	std::list<std::string> list;
	std::string sqlStatement = "SELECT COUNT(*) FROM t_user_questions;";
	int res = sqlite3_exec(this->_db, sqlStatement.c_str(), callbackString, &list, nullptr);
	if (res != SQLITE_OK)
	{
		throw std::exception("Error- sqlite3_exec functions failed");
	}
	questionCount = std::atoi(list.begin()->c_str());
	UserQuestionStruct q;
	q.id = questionCount + 1;
	q.author = author;
	q.question = question;
	q.correct_ans = correctAnswer;
	q.ans2 = ans2;
	q.ans3 = ans3;
	q.ans4 = ans4;
	addQuestion(q);
	return 0;
}
