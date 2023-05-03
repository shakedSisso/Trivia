#include "JsonResponsePacketSerializer.h"
#include "json.hpp"

using json = nlohmann::json;

#define ERROR_RESPONSE_CODE 1
#define LOGIN_RESPONSE_CODE 2
#define SIGNUP_RESPONSE_CODE 3


Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse response)
{
    Buffer responseBuffer;
    int jsonLength = 0;

    responseBuffer.push_back((unsigned char)ERROR_RESPONSE_CODE);
    json responseData;
    responseData["message"] = response.message;
    std::string jsonString = responseData.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end());
    jsonLength = jsonString.length();

    // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)
    responseBuffer.push_back((jsonLength >> 24) & 0xFF);
    responseBuffer.push_back((jsonLength >> 16) & 0xFF);
    responseBuffer.push_back((jsonLength >> 8) & 0xFF);
    responseBuffer.push_back(jsonLength & 0xFF);

    responseBuffer.insert(responseBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());


    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse response)
{
    Buffer responseBuffer;
    int jsonLength = 0;

    responseBuffer.push_back((unsigned char)LOGIN_RESPONSE_CODE);
    json responseData;
    responseData["status"] = response.status;
    std::string jsonString = responseData.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end());
    jsonLength = jsonString.length();

    // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)
    responseBuffer.push_back((jsonLength >> 24) & 0xFF);
    responseBuffer.push_back((jsonLength >> 16) & 0xFF);
    responseBuffer.push_back((jsonLength >> 8) & 0xFF);
    responseBuffer.push_back(jsonLength & 0xFF);

    responseBuffer.insert(responseBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());



    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse response)
{
    Buffer responseBuffer;
    int jsonLength = 0;

    responseBuffer.push_back((unsigned char)SIGNUP_RESPONSE_CODE);
    json responseData;
    responseData["status"] = response.status;
    std::string jsonString = responseData.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end());
    jsonLength = jsonString.length();

    // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)
    responseBuffer.push_back((jsonLength >> 24) & 0xFF);
    responseBuffer.push_back((jsonLength >> 16) & 0xFF);
    responseBuffer.push_back((jsonLength >> 8) & 0xFF);
    responseBuffer.push_back(jsonLength & 0xFF);

    responseBuffer.insert(responseBuffer.end(), jsonBuffer.begin(), jsonBuffer.end());

    return responseBuffer;
}
