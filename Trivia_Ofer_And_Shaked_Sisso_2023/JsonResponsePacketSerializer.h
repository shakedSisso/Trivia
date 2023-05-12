#pragma once
#include <vector>
#include "Responses.h"
#include "Globals.h"
#include "json.hpp"

using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(const ErrorResponse& response);
	static Buffer serializeResponse(const LoginResponse& response);
	static Buffer serializeResponse(const SignupResponse& response);

private:
    /*
    * Function: static insertIntToBuffer
    * ----------------------------
    *   The function gets a buffer (vector of unsigned chars), a number and the amount of bytes to fit in. The function inserts to the buffer the number in a binary form in the amount of bytes given.
    *
    *   Buffer& buffer: the buffer to insert the number to
    *   const int num: the number to insert to the buffer
    *   const int bytes: the amount of bytes the number will take
    *
    *   returns: void.
    */
	static void insertIntToBuffer(Buffer& buffer, const int num, const int bytes);
    /*
    * Function: static insertJsonToBuffer
    * ----------------------------
    *   The function gets a buffer (vector of unsigned chars) and a json object, the function serializes the json into a string and inserts the string to the buffer
    *
    *   Buffer& buffer: The buffer to json the number to
    *   const json& jsonObject: The json object to insert to the buffer
    *
    *   returns: void.
    */
    static void insertJsonToBuffer(Buffer& buffer, const json& jsonObject);
};