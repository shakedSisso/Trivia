#include "JsonResponsePacketSerializer.h"

#define ERROR_RESPONSE_CODE 1
#define LOGIN_RESPONSE_CODE 2
#define SIGNUP_RESPONSE_CODE 3

#define LOGOUT_RESPONSE_CODE 4
#define GET_ROOMS_RESPONSE_CODE 5
#define GET_PLAYERS_IN_ROOM_RESPONSE_CODE 6
#define JOIN_ROOM_RESPONSE_CODE 7
#define CREATE_ROOM_RESPONSE_CODE 8
#define GET_HIGH_SCORE_RESPONSE_CODE 9
#define GET_PERSONAL_STATS_RESPONSE_CODE 10

#define BYTE_MASK 0xFF
#define LENGTH_FIELD_BYTES 4
#define BITS_IN_BYTE 8

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;
    json responseData;

    responseBuffer.push_back((unsigned char)ERROR_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)LOGIN_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)SIGNUP_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)LOGOUT_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)GET_ROOMS_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)GET_PLAYERS_IN_ROOM_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)JOIN_ROOM_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)CREATE_ROOM_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)GET_HIGH_SCORE_RESPONSE_CODE); // adding the response code to the first byte of the buffer
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

    responseBuffer.push_back((unsigned char)GET_PERSONAL_STATS_RESPONSE_CODE); // adding the response code to the first byte of the buffer
    responseData["status"] = response.status;
    responseData["statistics"] = response.statistics;

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
