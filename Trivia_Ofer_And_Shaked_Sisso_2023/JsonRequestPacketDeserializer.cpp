#include "JsonRequestPacketDeserializer.h"
#include "json.hpp"
#include "LoginRequestHandler.h"
#include "RegexValidation.h"

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
    request.address = jsonData["address"];
    request.phoneNumber = jsonData["phone_number"];
    request.birthDate = jsonData["birth_date"];

    JsonRequestPacketDeserializer::checkForInputValidtion(request);

    return request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES); //get the length of the json in the buffer
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength); //get the values of the json into a string

    GetPlayersInRoomRequest request;
    json jsonData = json::parse(jsonString);

    request.roomId = jsonData["room_id"];

    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES); //get the length of the json in the buffer
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength); //get the values of the json into a string

    JoinRoomRequest request;
    json jsonData = json::parse(jsonString);

    request.roomId = jsonData["room_id"];

    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES); //get the length of the json in the buffer
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength); //get the values of the json into a string

    CreateRoomRequest request;
    json jsonData = json::parse(jsonString);

    request.roomName = jsonData["room_name"];
    request.maxUsers = jsonData["max_users"];
    request.questionCount = jsonData["question_count"];
    request.answerTimeout = jsonData["time_out"];

    return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const Buffer& buffer)
{
    int jsonLength = extractIntFromBuffer(buffer, 1, LENGTH_FIELD_BYTES); //get the length of the json in the buffer
    std::string jsonString(buffer.begin() + LENGTH_FIELD_BYTES + 1, buffer.begin() + LENGTH_FIELD_BYTES + 1 + jsonLength); //get the values of the json into a string

    SubmitAnswerRequest request;
    json jsonData = json::parse(jsonString);

    request.answerId = jsonData["answer_id"];
    request.answerTime = jsonData["answer_time"];

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

void JsonRequestPacketDeserializer::checkForInputValidtion(const SignupRequest& request)
{
    if (!RegexValidation::isPasswordVaild(request.password))
    {
        throw std::exception("Password is invalid");
    }
    if (!RegexValidation::isEmailVlaid(request.email))
    {
        throw std::exception("Email is invalid");
    }
    if (!RegexValidation::isAddressVaild(request.address))
    {
        throw std::exception("Address is invalid");
    }
    if (!RegexValidation::isPhoneNumberValid(request.phoneNumber))
    {
        throw std::exception("Phone number is invalid");
    }
    if (!RegexValidation::isDataOfBirthValid(request.birthDate))
    {
        throw std::exception("Birth date is invalid");
    }
}

