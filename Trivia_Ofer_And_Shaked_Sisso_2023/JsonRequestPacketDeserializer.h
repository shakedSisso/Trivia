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
	static SignupReqest deserializeSignupRequest(const Buffer& buffer);
private:
	static int extractIntFromBuffer(const Buffer& buffer, const int index, const int bytes);
};