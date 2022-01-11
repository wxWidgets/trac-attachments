import socket

HOST = 'localhost'
PORT = 12345
for i in range(0, 1000):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    s.send(b'Hello, World')
    s.close()

