# TCP Echo Server and Client in C
This project demonstrates a simple TCP client-server chat application written in C. The **server** listens for incoming connections and **echoes back** any messages received from the client. This project was made to demonstrate basic network programming in C.

## Features

- TCP socket communication
- Basic echo server functionality
- Two-way terminal-based chat
- Built for simplicity and clarity

## Requirements

- GCC compiler (`gcc`)
- Linux environment (e.g., **WSL with Ubuntu**)
- Two terminal windows

## Files

- `server.c` – The echo server that listens for client connections.
- `client.c` – The client that connects to the server and sends messages.

## How to Compile

Open a terminal window and navigate to the project directory:

```bash
gcc server.c -o server  
gcc client.c -o client
```  
In one terminal window, first run:
```
./server
```
In a second terminal window, run:
```
./client
```

## How It Works

1. **Type a message** in the **client terminal** and press **Enter**.
2. The **server terminal** will **display the received message**.
3. The **server echoes** the message back to the **client**, and it is **displayed in the client terminal**.

## Key Concepts Used

- **Socket functions**: `socket()`, `bind()`, `listen()`, `accept()`, `connect()`
- **Networking protocol**: TCP/IP with IPv4
- **Data transmission**: `read()`, `write()`, `send()`
- **Address structures**: `struct sockaddr_in`, `htons()`, `inet_addr()`
- **Buffer management**: `memset()`, `fgets()`

