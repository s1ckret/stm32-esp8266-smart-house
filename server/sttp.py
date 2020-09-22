# S1ckret Team Transfer Protocol

def handle_R_frame(msg):
    pass

def handle_sttp_msg(msg):
    response = b""
    if (chr(msg[0]) == 'R'):
        response = handle_R_frame(msg)
    
    return response