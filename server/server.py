import socket
import threading
import os

# Check your ip with "ipconfig" cmd
host='192.168.0.107'
port=30000
fileRoot = "../webpage/"
# @status - int
def response_header(status):
    return "HTTP/1.1 {} OK\n".format(status)

# @type - str
def response_content_type(type):
    return "Content-Type: {}\n".format(type)

# @len - int
def response_content_length(len):
    return "Content-Length: {}\n\n".format(len)

def handle_get_request(args):
    file_name = args[1]
    # TODO: Add file type parsing
    # Example: if .html then content_type = text/html
    # Example: is .css then content_type = text/css
    if (file_name == "/"): 
        file_name = "index.html"

    response = ""
    if (os.path.isfile(fileRoot + file_name)):
        file = open(fileRoot + file_name)
        file_str = file.read()
        file_len = len(file_str)

        response += response_header(200)
        response += response_content_type("text/html")
        response += response_content_length(file_len)
        response += file_str
    else:
        response += "ERROR: There is no file {}".format(fileRoot + file_name)
    return response

def handle_http_request(request, args):
    response = ""
    if (request == "GET"):
        response = handle_get_request(args)
    return response

def handle_client(conn, address):
    print(f"Connection from {address} has been established.")

    while True:
        msg = conn.recv(2048).decode("utf-8")
        print(f"Request\n{msg}\n")
        args = msg.split(" ", 2)
        # TODO: pass better args
        response = handle_http_request(args[0], args)
        print(f"Response\n{response}\n")
        conn.send(response.encode("utf-8"))
        break
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