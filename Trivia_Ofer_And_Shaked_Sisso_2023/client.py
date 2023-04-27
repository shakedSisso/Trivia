import socket

PORT = 1444
LEN = 6

def client():
    socket_to_server = socket.socket()
    try:
        socket_to_server.connect(('localhost', PORT)) # using localhost refers to 127.0.0.1 which is a local address within the same machine
    except ConnectionRefusedError:
        print("Couldn't connect to server!")
        return
    print("Connected to server. sending hello")
    socket_to_server.send("hello".encode()) # using encode since the sockets need to receive data in binary
    msg = socket_to_server.recv(LEN).decode() # using decode since the sockets returns data received in binary
    print("Recieved from server:", msg)
    socket_to_server.close()

def main():
    client()
    
if __name__ == '__main__':
    main()