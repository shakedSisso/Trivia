#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include "LoginRequestHandler.h"

using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES); //get the length of the json in the buffer
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength); //get the values of the json into a string

    LoginRequest request;
    json jsonData = json::parse(jsonString); //converting the string with the json data into json type variable

    request.username = jsonData["username"];
    request.password = jsonData["password"];

    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES); //get the length of the json in the buffer
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength); //get the values of the json into a string

    SignupRequest request;
    json jsonData = json::parse(jsonString); //converting the string with the json data into json type variable

    request.username = jsonData["username"];
    request.password = jsonData["password"];
    request.email = jsonData["mail"];

    return request;
}

int JsonRequestPacketDeserializer::extractIntFromBuffer(const Buffer& buffer, const int index, const int bytes)
{
    int result = 0, i = 0;
    for (i = index; i < index + bytes; i++) 
    {
        result = (result << BITS_IN_BYTE) | buffer[i];
    }
    return result;
}

