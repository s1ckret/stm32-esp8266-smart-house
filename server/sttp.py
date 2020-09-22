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
    data = int.from_bytes(payload, byteorder="big")
    print(f"Got frame: sensor ID: {sensor_id}, payload size: {payload_size}, payload: {payload}\nConverted data: {data} ")
    file_name = dict_sensor_id_to_file[sensor_id]
    try:
        with open(constants.fileRoot + file_name, 'wb') as file:
            # TODO: add support for different payload size
            file.write(str(data).encode(constants.encoding))
    except OSError as e:
        print("ERROR #{} while writing into {}".format(e.errno, constants.fileRoot + file_name))
        return b"ERROR"
    return b"OK"

def handle_sttp_msg(msg):
    response = b""
    if (chr(msg[0]) == 'R'):
        response = handle_R_frame(msg)
    
    return response