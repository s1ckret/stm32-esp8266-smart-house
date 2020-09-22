import socket
import threading

import http

# Check your ip with "ipconfig" cmd
host='192.168.0.107'
port=30000

def handle_client(conn, address):
    print(f"Connection from {address} has been established.")

    while True:
        msg = conn.recv(2048).decode("utf-8")
        print(f"Request\n{msg}\n")
        if (msg == ''):
            break
        
        response = http.handle_http_request(msg)
        print(f"Response\n{response}\n")
        conn.send(response.encode("utf-8"))
    conn.close()
    print(f"Connection from {address} has been closed.")


def main():
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind((host, port))
    serverSocket.listen(5)
    print(f"Started socket {serverSocket}")

    while True:
        print("Waiting for new connections...")
        # accept method blocks loop until someone has connected to server
        clientsocket, address = serverSocket.accept()
        thread = threading.Thread(target=handle_client, args=(clientsocket, address))
        thread.start()
        print(f"Active threads count: {threading.activeCount() - 1}")

if __name__ == "__main__":
    main()