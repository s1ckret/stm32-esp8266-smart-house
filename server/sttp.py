# S1ckret Team Transfer Protocol

import constants

dict_sensor_id_to_file = {
 1 : "ledStatus.txt",
 2 : "temperature.txt"
}

def handle_R_frame(msg):
    sensor_id = msg[1]
    payload_size = msg[2]
    payload = msg[3:]
    # TODO: Write into the file
    return b"OK"

def handle_sttp_msg(msg):
    response = b""
    if (chr(msg[0]) == 'R'):
        response = handle_R_frame(msg)
    
    return response