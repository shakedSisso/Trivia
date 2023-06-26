#pragma once
#include <vector>

using std::vector;

typedef int RequestId;
typedef unsigned char Byte;
typedef vector<Byte> Buffer;
typedef unsigned int RoomID;
typedef unsigned int GameID;

<<<<<<< Trivia_Ofer_And_Shaked_Sisso_2023/Globals.h
enum codes { Error, Login, Signup, GetPlayersInRoom, JoinRoom, CreateRoom, HighScore, Logout, GetRooms, Statistics, CloseRoom, StartGame, GetRoomState, LeaveRoom, LeaveGame, GetQuestion, GetQuestionFailed, SubmitAnswer, GetGameResult , GetGameResultFailed, AddQuestion, HeadToHead };
