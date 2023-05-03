#pragma once
#include <vector>
#include "Responses.h"

using std::vector;

class JsonResponsePacketSerializer
{
public:
	static vector<unsigned char> serializeResponse(ErrorResponse response);
	static vector<unsigned char> serializeResponse(LoginResponse response);
	static vector<unsigned char> serializeResponse(SignupResponse response);

};