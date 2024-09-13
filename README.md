# ConnectPro: Real-Time Chat Application

## Overview

**ConnectPro** is a multi-client chatroom application developed in C++ using socket programming and multi-threading. This application allows multiple users to connect and communicate with each other in real-time.

## Features

- **Multi-client support**: Multiple users can connect to the chatroom simultaneously.
- **Real-time communication**: Messages sent by any user are broadcasted to all connected users.
- **Socket programming**: Utilizes TCP/IP sockets for network communication.
- **Multi-threading**: Ensures that the server can handle multiple clients at the same time by assigning a dedicated thread to each connected client.

## Tech Stack

- **C++**
- **Socket Programming**
- **Multi-threading**

## Installation and Setup

### Prerequisites

- A C++ compiler (e.g., g++)
- Basic knowledge of socket programming
- Linux or Windows environment (Linux preferred for socket programming)

### Steps to Setup:

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/connectpro.git
   ```
2. Navigate to the project directory:
   ```bash
   cd connectpro
   ```
3. Compile the server and client files:
   ```bash
   g++ server.cpp -o server -lpthread
   g++ client.cpp -o client
   ```
4. Run the server:
   ```bash
   ./server
   ```
5. In a new terminal window, run the client:
   ```bash
   ./client
   ```

## Usage

- Start the server first.
- Run the client on different terminals (or machines) to simulate multiple users.
- Once connected, users can start sending messages, and the server will broadcast these messages to all connected users.

## Future Enhancements

- Adding user authentication.
- Introducing private messaging between clients.
- Implementing a graphical user interface (GUI).
- Enhancing security with encryption.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to contribute to this project by creating a pull request or raising an issue.

## Contact

For any queries or issues, reach out at:

- **GitHub**: [tpstark137](https://github.com/tpstark137)
