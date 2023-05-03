#include "JsonResponsePacketSerializer.h"
#include "json.hpp"

using json = nlohmann::json;

#define ERROR_RESPONSE_CODE 1
#define LOGIN_RESPONSE_CODE 2
#define SIGNUP_RESPONSE_CODE 3

#define BYTE_MASK 0xFF
#define LENGTH_FIELD_BYTES 4
#define BITS_IN_BYTE 8

Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;

    responseBuffer.push_back((unsigned char)ERROR_RESPONSE_CODE); // adding the response code to the first byte of the buffer
    json responseData;
    responseData["message"] = response.message;
    std::string jsonString = responseData.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end()); // creating a buffer that contains the string in order to connect it to the response buffer
    jsonLength = jsonString.length(); // getting the length of the data (the JSON) in order to put in the length field of the response

    // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES);

    responseBuffer.insert(responseBuffer.end(), jsonBuffer.begin(), jsonBuffer.end()); // appending the data (JSON) to the end of the response buffer (that contains the response code and the data length value 


    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;

    responseBuffer.push_back((unsigned char)LOGIN_RESPONSE_CODE); // adding the response code to the first byte of the buffer
    json responseData;
    responseData["status"] = response.status;
    std::string jsonString = responseData.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end()); // creating a buffer that contains the string in order to connect it to the response buffer
    jsonLength = jsonString.length(); // getting the length of the data (the JSON) in order to put in the length field of the response

    // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES);

    responseBuffer.insert(responseBuffer.end(), jsonBuffer.begin(), jsonBuffer.end()); // appending the data (JSON) to the end of the response buffer (that contains the response code and the data length value 



    return responseBuffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& response)
{
    Buffer responseBuffer;
    int jsonLength = 0;

    responseBuffer.push_back((unsigned char)SIGNUP_RESPONSE_CODE); // adding the response code to the first byte of the buffer
    json responseData;
    responseData["status"] = response.status;
    std::string jsonString = responseData.dump();
    Buffer jsonBuffer(jsonString.begin(), jsonString.end()); // creating a buffer that contains the string in order to connect it to the response buffer
    jsonLength = jsonString.length(); // getting the length of the data (the JSON) in order to put in the length field of the response

    // inserting the value of the length of the json in bytes (and filling the 4 bytes of the length field)
    JsonResponsePacketSerializer::insertIntToBuffer(responseBuffer, jsonLength, LENGTH_FIELD_BYTES); 

    responseBuffer.insert(responseBuffer.end(), jsonBuffer.begin(), jsonBuffer.end()); // appending the data (JSON) to the end of the response buffer (that contains the response code and the data length value 

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
