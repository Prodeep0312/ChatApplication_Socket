# Multi-Client Chat Application (C++ Winsock)

A simple real-time chat application built using C++ and Winsock API. The project demonstrates TCP socket programming, multi-client handling, and multithreading.
![Image](https://github.com/user-attachments/assets/11964bdc-21c3-4b58-aeff-4a7dc1dfc652)

---

## Features

- TCP-based client-server communication
- Multiple client support using threads
- Real-time message broadcasting
- Full-duplex communication (send and receive simultaneously)
- Console-based chat interface

---

## Architecture

### Server
- Creates a listening socket on port 54321
- Accepts multiple client connections
- Spawns a new thread for each client
- Broadcasts messages to all connected clients except sender

### Client
- Connects to server using IP (127.0.0.1)
- Uses two threads:
  - Sender thread for sending messages
  - Receiver thread for receiving messages
- Supports exit using "quit"

---

## Tech Stack

- C++
- Winsock2 API
- Multithreading (std::thread)
- TCP/IP Sockets

---

## Build Instructions

### Compilation
```bash
g++ server.cpp -o server -lws2_32
g++ client.cpp -o server -lws2_32
```

### Start server
```bash
server.exe
```

### Start client
```bash
client.exe
```

