#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <string>

#define PORT 12345

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool Initialize()
{
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void sendMessage(SOCKET listenSocket)
{
    cout << "Enter your Chat Name: " << endl;
    string name;
    getline(cin, name);

    // now we will repeatedly take message from client
    string message;
    while (1)
    {
        cout << "Write your message below: " << endl;
        getline(cin, message);
        string msg = name + " " + message;
        int byteSent = send(listenSocket, msg.c_str(), msg.length(), 0);
        if (byteSent == SOCKET_ERROR)
        {
            cout << "Error sending message" << endl;
            break;
        }

        if (message == "quit")
        {
            cout << "Stopping the application.." << endl;
            break;
        }
    }
    closesocket(listenSocket);
    WSACleanup();
}

void receiveMessage(SOCKET listenSocket)
{
    char buffer[1098];
    int recvLen;
    string msg = "";
    while (1)
    {
        recvLen = recv(listenSocket, buffer, sizeof(buffer), 0);
        if (recvLen <= 0)
        {
            cout << "disconnected" << endl;
            break;
        }
        else
        {
            msg = string(buffer, recvLen);
            cout << msg << endl;
        }
    }
}

struct sockaddr_in srv;

int main()
{

    int nRet = 0;

    // Initialize WSA variable to support env for socket programming

    if (!Initialize())
    {
        cout << "socket initialization failed" << endl;
        return 1;
    }
    else
    {
        cout << "Socket initialized successfull" << endl;
    }

    // Initialize socket

    string serveraddr = "127.0.0.1";

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET)
    {
        cout << "Socket connection failed !" << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // setup address structure

    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT); // convert to network byte order
    inet_pton(AF_INET, serveraddr.c_str(), &(srv.sin_addr));
    memset(&(srv.sin_zero), 0, 8);

    // connect to server

    if (connect(listenSocket, (sockaddr *)&srv, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        cout << "server not able to connect" << endl;
        closesocket(listenSocket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    thread senderThread(sendMessage, listenSocket);
    thread receiverThread(receiveMessage, listenSocket);

    senderThread.join();
    receiverThread.join();

    return 0;
}