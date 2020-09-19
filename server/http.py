
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

def parse_file_extension(file_name):
    return "text/html"

def handle_get_request(file_name):
    # TODO: Add file type parsing
    # Example: if .html then content_type = text/html
    # Example: is .css then content_type = text/css

    file_name = file_name[1:]

    if (file_name == ""):
        file_name = "index.html"
    
    content_type = parse_file_extension(file_name)
    
    response = ""
    try:
        with open(fileRoot + file_name, 'r') as file:
            file_str = file.read()
            file_len = len(file_str)

            response += response_header(200)
            response += response_content_type(content_type)
            response += response_content_length(file_len)
            response += file_str
            return response
    except OSError as e:
        print("ERROR {}: There is no file {}".format(e.errno, fileRoot + file_name))


def handle_http_request(request):
    args = request.split(" ", 2)

    response = ""
    if (args[0] == "GET"):
        response = handle_get_request(args[1])
    return response