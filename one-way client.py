# Client side: live_stream_client.py
import socket
import cv2
import pickle
import struct

# Socket configuration
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_ip = '192.168.0.103'  # Replace with the server IP address
port = 65432

# Connect to the server
client_socket.connect((host_ip, port))

data = b""
payload_size = struct.calcsize("Q")

while True:
    # Retrieve message size
    while len(data) < payload_size:
        packet = client_socket.recv(4 * 1024)  # 4KB
        if not packet:
            break
        data += packet

    packed_msg_size = data[:payload_size]
    data = data[payload_size:]
    msg_size = struct.unpack("Q", packed_msg_size)[0]

    # Retrieve all the frame data based on the size of the frame
    while len(data) < msg_size:
        data += client_socket.recv(4 * 1024)
    
    frame_data = data[:msg_size]
    data = data[msg_size:]

    # Deserialize the frame
    frame = pickle.loads(frame_data)

    # Display the frame
    cv2.imshow('Client Video Stream', frame)

    if cv2.waitKey(1) == 13:  # Press 'Enter' to exit
        break

client_socket.close()
cv2.destroyAllWindows()