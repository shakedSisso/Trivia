import socket
import json
import struct

PORT = 1444
CODE_LEN = 1
JSON_LENGTH = 4
LOGIN_REQUEST = 1
SIGNUP_REQUEST = 2

def client():
    socket_to_server = socket.socket()
    try:
        socket_to_server.connect(('localhost', PORT)) # using localhost refers to 127.0.0.1 which is a local address within the same machine
    except ConnectionRefusedError:
        print("Couldn't connect to server!")
        return
    print("Connected to server on localhost:{}".format(PORT))
    selection = input("Enter s for signup and l for login: ")
    if selection == "s":
        data = {'username': "user1", 'password': "1234", "mail": "test@gmail.com"}
        request = str(chr(SIGNUP_REQUEST))
    elif selection == 'l':
        data = {'username': "user1", 'password': "1234"}
        request = str(chr(LOGIN_REQUEST))
    dataJson = json.dumps(data)

    request += struct.pack('!I', len(dataJson))
    request += dataJson
    print("Sending request:")
    print(request)
    socket_to_server.send(request.encode())
    response_code = socket_to_server.recv(CODE_LEN).decode() # using decode since the sockets returns data received in binary
    response_json_length_bytes = socket_to_server.recv(JSON_LENGTH).decode()
    response_json_length = struct.unpack('!I', response_json_length_bytes)
    response_json = socket_to_server.recv(response_json_length).decode()
    print("Received from server:", response_json)
    socket_to_server.close()

def main():
    client()
    
if __name__ == '__main__':
    main()
