import socket
import time

host='192.168.0.108'
port=30000

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSocket.connect((host, port))

msgLedOn = b"R\x01\x01\x01"
msgLedOff = b"R\x01\x01\x00"

while True:
    clientSocket.send(msgLedOn)
    response = clientSocket.recv(10)
    print(response)
    time.sleep(0.5)
    clientSocket.send(msgLedOff)
    response = clientSocket.recv(10)
    print(response)
    time.sleep(0.5)
