import socket

PORT = 1444
LEN = 6

def client():
    socket_to_server = socket.socket()
    try:
        socket_to_server.connect(('localhost', PORT))
    except ConnectionRefusedError:
        print("Couldn't connect to server!")
        return
    print("Connected to server. sending hello")
    socket_to_server.send("hello".encode())
    msg = socket_to_server.recv(LEN).decode()
    print("Recieved from server:", msg)

def main():
    client()
    
if __name__ == '__main__':
    main()