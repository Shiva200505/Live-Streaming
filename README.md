# **Live Streaming System 📡🎥**

This project implements a **real-time video streaming system** using **Python**, **OpenCV**, and **Sockets**. It allows both **one-way** and **two-way** communication between a server and a client.

## **Features 🚀**
✅ **One-Way Streaming:**  
- The **server** captures video from a webcam and transmits it to the **client**.  
- The **client** receives and displays the video in real time.  

✅ **Two-Way Streaming:**  
- Both the **client and server** can **send and receive video** simultaneously, enabling real-time **bi-directional** communication.  

✅ **Uses Sockets & OpenCV:**  
- **Sockets**: Used for network communication between server and client.  
- **OpenCV**: Used for capturing, processing, and displaying video frames.  

✅ **Supports C & Python Implementations:**  
- Two versions:  
  - **Python-based streaming** (Sockets + OpenCV).  
  - **C-based implementation** (for low-level control).  

✅ **Efficient Data Transmission:**  
- Video frames are serialized using **Pickle** before being sent over the network.  
- Frames are packed with a **struct header** to ensure smooth transmission.  

---

## **Technologies Used 🛠️**
- **Python** (for scripting and real-time processing)
- **OpenCV** (for video capture and display)
- **Sockets (TCP)** (for network communication)
- **Pickle & Struct** (for efficient serialization of frames)
- **C Language** (for an alternative low-level implementation)

---
