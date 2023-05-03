#pragma once
#include <vector>
#include "Responses.h"
#include "Globals.h"

class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse response);
	static Buffer serializeResponse(LoginResponse response);
	static Buffer serializeResponse(SignupResponse response);

};