#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include "LoginRequestHandler.h"

using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES);
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength);

    LoginRequest request;
    json jsonData = json::parse(jsonString);

    request.username = jsonData["username"];
    request.password = jsonData["password"];

    return request;
}

SignupReqest JsonRequestPacketDeserializer::deserializeSignupRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES);
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength);

    SignupReqest request;
    json jsonData = json::parse(jsonString);

    request.username = jsonData["username"];
    request.password = jsonData["password"];
    request.email = jsonData["email"];

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

