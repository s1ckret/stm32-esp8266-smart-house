
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
    file_name, extension = file_name.split(".", 1)
    content_type = ""
    if (extension == "ico"): content_type = "image/ico"
    if (extension == "html"): content_type = "text/html"
    return content_type

def handle_get_request(file_name):
    file_name = file_name[1:]

    if (file_name == ""):
        file_name = "index.html"
    
    content_type = parse_file_extension(file_name)
    
    response = ""
    try:
        with open(fileRoot + file_name, 'r') as file:
            # TODO: Add support of a different file extensions. (text, images)
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
