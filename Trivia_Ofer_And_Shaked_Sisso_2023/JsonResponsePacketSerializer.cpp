#include "JsonResponsePacketSerializer.h"

#define BYTE_MASK 0xFF
#define LENGTH_FIELD_BYTES 4
#define BITS_IN_BYTE 8

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)Error); // adding the response code to the first byte of the buffer
    responseData["message"] = response.message;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)Login); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)Signup); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)Logout); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)GetRooms); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    // insert the rooms vector in the json object
    for (const auto& roomData : response.rooms) 
    {
        json roomJson;
        roomJson["id"] = roomData.id;
        roomJson["isActive"] = roomData.isActive;
        roomJson["maxPlayers"] = roomData.maxPlayers;
        roomJson["name"] = roomData.name;
        roomJson["numOfQuestionsInGame"] = roomData.numOfQuestionsInGame;
        roomJson["timePerQuestion"] = roomData.timePerQuestion;
        
        responseData["Rooms"].push_back(roomJson);
    }

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)GetPlayersInRoom); // adding the response code to the first byte of the buffer
    responseData["PlayersInRoom"] = response.players;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}


Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)JoinRoom); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)CreateRoom); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)HighScore); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    responseData["statistics"] = response.statistics;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)Statistics); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    responseData["statistics"] = response.statistics;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const AddQuestionResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)AddQuestion); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)CloseRoom); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)StartGame); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)GetRoomState); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    responseData["hasGameBegun"] = response.hasGameBegun;
    responseData["players"] = response.players;
    responseData["questionCount"] = response.questionCount;
    responseData["answerTimeOut"] = response.answerTimeout;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)LeaveRoom); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)GetGameResult); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    for (const auto& gameResult : response.results)
    {
        json resultJson;
        resultJson["username"] = gameResult.username;
        resultJson["correctAnswerCount"] = gameResult.correctAnswerCount;
        resultJson["wrongAnswerCount"] = gameResult.wrongAnswerCount;
        resultJson["averageAnswerTime"] = gameResult.averageAnswerTime;
       

        responseData["results"].push_back(resultJson);
    }

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)SubmitAnswer); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    responseData["correctAnswerId"] = response.correctAnswerId;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;
    json mapData;

    responseBuffer.push_back((unsigned char)GetQuestion); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    responseData["question"] = response.question;
    for (const auto& pair : response.answers) 
    {
        mapData[std::to_string(pair.first)] = pair.second;
    }
    responseData["answers"].push_back(mapData);

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)LeaveGame); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;

    jsonLength = responseData.dump().length(); // getting the length of the data (the JSON) in order to put in the length field of the response
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)

    JsonResponsePacketSerializer::insertJsonToBuffer(responseBuffer, responseData);

    return responseBuffer;
}

void JsonResponsePacketSerializer::insertIntToBuffer(Buffer& buffer, const int num, const int bytes)
{
    int i = 0;
    for (int i = bytes - 1; i >= 0; i--)
    {
        unsigned char byte = (num >> (BITS_IN_BYTE * i)) & BYTE_MASK; // extract a byte from the int value
        buffer.push_back(byte); // add the byte to the vector
    }

}

void JsonResponsePacketSerializer::insertJsonToBuffer(Buffer& buffer, const json& jsonObject)
{
    std::string jsonString = jsonObject.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end()); // creating a buffer that contains the string in order to connect it to the response buffer
    buffer.insert(buffer.end(), jsonBuffer.begin(), jsonBuffer.end()); // appending the data (JSON) to the end of the response buffer (that contains the response code and the data length value)
}
