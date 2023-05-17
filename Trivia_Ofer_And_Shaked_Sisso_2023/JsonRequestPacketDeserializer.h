#pragma once
#include <iostream>
#include "Requests.h"
#include "Globals.h"

#define LENGTH_FIELD_BYTES 4
#define BITS_IN_BYTE 8

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static SignupRequest deserializeSignupRequest(const Buffer& buffer);
	/*
	* Function: static extractIntFromBuffer
	* ----------------------------
	*	The function gets a buffer (vector of unsigned chars), an index and the amount of bytes.
	*	The function extracts from the buffer the number in the amount of bytes given from the index.
	*
	*	const Buffer& buffer: the buffer to insert the number to
	*	const int index: the index to start the extracting from
	*	const int bytes: the amount of bytes the number will take
	*
	*	returns: int.
   */
	static int extractIntFromBuffer(const Buffer& buffer, const int index, const int bytes);
private:
	/*
	* Function: static checkForInputValidtion
	* ----------------------------
	*	The function gets a buffer (vector of unsigned chars), an index and the amount of bytes.
	*	The function extracts from the buffer the number in the amount of bytes given from the index.
	*
	*	const SignupRequest& request: the sign up request to check it's parameters
	*
	*	returns: void.
   */
	static void checkForInputValidtion(const SignupRequest& request);
};