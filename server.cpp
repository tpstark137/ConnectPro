#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>

using namespace std;
#pragma comment (lib,"ws2_32.lib")

bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;

}

int main() {

	if (!Initialize()) {
		cout << "socket initialization failed" << endl;
		return 1;
	}
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		cout << "Socket connection failed !" << endl;
		return 1;
	}
	//create address structure
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(12345);

	//convert ip to binary

	if (InetNtop(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "Address structure failed" << endl;
		closesocket(listenSocket);
		return 1;
	}


	cout << "Server running" << endl;

	return 0;
}