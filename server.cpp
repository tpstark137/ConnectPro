#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>

#define PORT 12345

using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool Initialize()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void funcInteractClient(SOCKET clientSocket, vector<SOCKET> &clients)
{

	// send /receive client
	char buffer[4096];

	while (1)
	{
		// receive incoming data of client in buffer
		int byteRecv = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (byteRecv <= 0)
		{
			cout << "Client disconnected" << endl;
			break;
		}

		string message(buffer, byteRecv);
		cout << "Message from client :" << message << endl;

		// send message to all connected clients excluding itself
		for (auto client : clients)
		{
			if (client != clientSocket)
				send(client, message.c_str(), message.length(), 0);
		}
	}
	auto it = find(clients.begin(), clients.end(), clientSocket);
	if (it != clients.end())
	{
		clients.erase(it);
	}
	closesocket(clientSocket);
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
		cout << "Socket opened successfull" << endl;
	}

	// Initialize socket

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		cout << "Socket connection failed !" << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << listenSocket << endl;
	}
	// setup address structure

	srv.sin_family = AF_INET;
	srv.sin_port = htons(PORT); // convert to network byte order
	srv.sin_addr.s_addr = INADDR_ANY;
	memset(&(srv.sin_zero), 0, 8);

	// bind socket to local port

	nRet = bind(listenSocket, (sockaddr *)&srv, sizeof(sockaddr));

	if (nRet < 0)
	{
		cout << "Failed to bind to local port" << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "Success bind to local port" << endl;
	}

	// listen the request from client

	nRet = listen(listenSocket, SOMAXCONN);

	if (nRet < 0)
	{
		cout << "Failed to start listen to local port: " << PORT << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "Success to listen local port: " << PORT << endl;
	}

	vector<SOCKET> clients;

	// accept client connection

	while (1)
	{
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);

		if (clientSocket == INVALID_SOCKET)
		{
			cout << "Invalid client socket" << endl;
		}
		else
		{
			cout << "Client connected" << endl;
		}
		clients.push_back(clientSocket);

		// create new seperate thread for handling seperate client
		thread t1(funcInteractClient, clientSocket, std::ref(clients));
		t1.detach();
	}

	closesocket(listenSocket);

	WSACleanup();
	cout << "Server running" << endl;

	return 0;
}