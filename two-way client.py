import socket
import cv2
import pickle
import struct
import threading

# Socket setup
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host_ip = '192.168.0.103'  # Change this to your server IP
port = 65432
client_socket.connect((host_ip, port))

video_capture = cv2.VideoCapture(0)  # Capture video from client's webcam

def send_video():
    while video_capture.isOpened():
        ret, frame = video_capture.read()
        if not ret:
            break
        frame_data = pickle.dumps(frame)
        message_size = struct.pack("Q", len(frame_data))
        client_socket.sendall(message_size + frame_data)
        cv2.imshow('Client Video Stream', frame)
        if cv2.waitKey(1) == 13:  # Press 'Enter' to exit
            break

def receive_video():
    data = b""
    payload_size = struct.calcsize("Q")
    while True:
        while len(data) < payload_size:
            packet = client_socket.recv(4 * 1024)
            if not packet:
                return
            data += packet
        
        packed_msg_size = data[:payload_size]
        data = data[payload_size:]
        msg_size = struct.unpack("Q", packed_msg_size)[0]

        while len(data) < msg_size:
            data += client_socket.recv(4 * 1024)
        
        frame_data = data[:msg_size]
        data = data[msg_size:]
        frame = pickle.loads(frame_data)

        cv2.imshow('Server Video Stream', frame)
        if cv2.waitKey(1) == 13:  # Press 'Enter' to exit
            break

send_thread = threading.Thread(target=send_video)
receive_thread = threading.Thread(target=receive_video)

send_thread.start()
receive_thread.start()

send_thread.join()
receive_thread.join()

client_socket.close()
video_capture.release()
cv2.destroyAllWindows()
