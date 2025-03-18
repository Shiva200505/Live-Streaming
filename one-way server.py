# Server side: live_stream_server.py
import socket
import cv2
import pickle
import struct

# Socket configuration
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_ip = '192.168.0.103'  # Server will listen on all IP addresses
port = 65432
socket_address = (host_ip, port)

# Bind the socket to the address and port
server_socket.bind(socket_address)
server_socket.listen(5)
print(f"Listening on {host_ip}:{port}")

# Capture video from webcam
video = cv2.VideoCapture(0)

# Accept a client connection
client_socket, addr = server_socket.accept()
print(f'Connection from: {addr}')

while video.isOpened():
    ret, frame = video.read()
    if not ret:
        break
    
    # Serialize the frame
    frame_data = pickle.dumps(frame)
    
    # Send the size of the frame first, then the frame data
    message_size = struct.pack("Q", len(frame_data))  # "Q" for unsigned long long
    
    # Send the data to the client
    client_socket.sendall(message_size + frame_data)
    
    # Display the frame on the server
    cv2.imshow('Server Video Stream', frame)
    
    if cv2.waitKey(1) == 13:  # Press 'Enter' to exit
        break

client_socket.close()
video.release()
cv2.destroyAllWindows()