#pragma once
#include <vector>
#include "Responses.h"
#include "Globals.h"

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
};