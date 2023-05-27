import socket
import json
import struct
import time

PORT = 1444
CODE_LEN = 1
JSON_LENGTH = 4
LOGIN_REQUEST = 1
SIGNUP_REQUEST = 2
GET_PLAYERS_IN_ROOM_REQUEST = 3
JOIN_ROOM_REQUEST = 4
CREATE_ROOM_REQUEST = 5
HIGH_SCORE_REQUEST = 6
LOGOUT_REQUEST = 7
GET_ROOMS_REQUEST = 8
GET_STATISTICS = 9

def client():
    socket_to_server = socket.socket()
    try:
        socket_to_server.connect(('localhost', PORT)) # using localhost refers to 127.0.0.1 which is a local address within the same machine
    except ConnectionRefusedError:
        print("Couldn't connect to server!")
        return
    print("Connected to server on localhost:{}".format(PORT))
    selection = input("Enter your selection(u, l, e, p, j, c, h, o, r, s, f): ")
    while selection != "f":
        if selection == "u": #signup
            data = {'username': "user1", 'password': "Pass123#", "mail": "test@gmail.com", "address": "(Sesame, 10, Tel Aviv)", "phone_number": "0519876532", "birth_date": "01.01.2023"}
            request = bytes([SIGNUP_REQUEST])
        elif selection == 'l': #login
            data = {'username': "user1", 'password': "Pass123#"}
            request = bytes([LOGIN_REQUEST])
        elif selection == 'e': #error
            # sending login message with a sign up code
            data = {'username': "user1", 'password': "1234"}
            request = bytes([SIGNUP_REQUEST])
        elif selection == "p": #players in room
            data = {'room_id': 1};
            request = bytes([GET_PLAYERS_IN_ROOM_REQUEST]);
        elif selection == "j": #join room
            data = {'room_id': 1};
            request = bytes([HIGH_SCORE_REQUEST]);
        elif selection == "c": #create room
            data = {'room_name': "room1", 'max_users': 6, 'question_count': 15, 'time_out': 60};
            request = bytes([CREATE_ROOM_REQUEST]);
        elif selection == "h": #high score
            data = {};
            request = bytes([HIGH_SCORE_REQUEST]);
        elif selection == "o": #logout
            data = {};
            request = bytes([LOGOUT_REQUEST]);
        elif selection == "r": #get rooms
            data = {};
            request = bytes([GET_ROOMS_REQUEST]);
        elif selection == "s": #statistics
            data = {};
            request = bytes([GET_STATISTICS]);
        elif selection == "f": #finish
            break
        dataJson = json.dumps(data)
        dataJson = dataJson.encode('utf-8')
        request += struct.pack('!I', len(dataJson))
        request += dataJson
        print("Sending request:")
        print(request)
        socket_to_server.send(request)
        response_code = socket_to_server.recv(CODE_LEN)
        response_json_length_bytes = socket_to_server.recv(JSON_LENGTH)
        response_json_length = struct.unpack('!I', response_json_length_bytes)[0]
        response_json = socket_to_server.recv(response_json_length).decode()
        print("Received from server:", response_json)
        selection = input("Enter s for signup and l for login: ")
    socket_to_server.close()

def main():
    client()
    
if __name__ == '__main__':
    main()
