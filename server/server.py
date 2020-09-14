import socket

# Check your ip with "ipconfig" cmd
host='192.168.0.107'
port=30000

def main():
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind((host, port))
    serverSocket.listen(5)
    print(f"Started socket {serverSocket}")

    while True:
        print("Waiting for new connections...")
        # accept method blocks loop until someone has connected to server
        clientsocket, address = serverSocket.accept()
        print(f"Connection from {address} has been established.\n Created client socket: {clientsocket}")
        print("Waiting for new message...")
        # 1500 - max ETHERNET packet
        msg = clientsocket.recv(1500)
        msg = msg.decode("utf-8")
        print(f">== Message: {msg}")
        print("Sending message...")
        clientsocket.send("Hello from server".encode("utf-8"))
        print("Message sent")
        clientsocket.close()
        print("Connection closed")

if __name__ == "__main__":
    main()