
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#include "Scene.h"
#include "RayTracer.h"
Scene* m_scene;
RayTracer* tracer;
int pixelcount = 1280 * 720;
int arraylength = pixelcount * 3;
long* ary;
void Initilise(int width, int height, int offsetx, int offsety) {
	//width = 1280;
	//height = 720;
	if (tracer != NULL) {
		delete tracer;
	}
	if (m_scene != NULL) {
		delete m_scene;
	}
	printf("INIt : %d width %d height %d offsetx %d offsety", width, height, offsetx, offsety);
	tracer = new RayTracer(width, height, offsetx, offsety);
	m_scene = new Scene();
	m_scene->InitDefaultScene();
	///total width
	m_scene->SetSceneWidth((float)width / (float)height);
	pixelcount = width*height;
	arraylength = pixelcount * 3;
	ary = new long[arraylength];
}
SOCKET ConnectToServer(char* address) {
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char *sendbuf = "this is a test\n";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;


	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(address, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	return ConnectSocket;
}
void CloseSocket(SOCKET target) {
	int iResult = 0;
	// shutdown the connection since we're done
	iResult = shutdown(target, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(target);
		WSACleanup();
		return;
	}
}
void SendCSTR(SOCKET socket, char* msg, int length) {
	int iResult;
	iResult = send(socket, msg, length, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		WSACleanup();
		return;
	}
	printf("Bytes sent: %d\n", iResult);
}
std::string WaitRECV(SOCKET Socket) {
	int iResult = 0;
	int iSendResult = 0;
	char recvbuf[DEFAULT_BUFLEN];
	int length = DEFAULT_BUFLEN;
	do {

		iResult = recv(Socket, recvbuf, length, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			char* pos = strchr(recvbuf, '\n');
			if (pos != 0) {
				//end of message.
				break;
			}
		}
		else if (iResult == 0) {
			printf("Connection closing...\n");
			return std::string("End of Stream");
		}
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(Socket);
			WSACleanup();
			return std::string("Close");
		}

	} while (iResult > 0);
	//every message will terminate with \n
	char* pos = strchr(recvbuf, '\n');
	std::string data(recvbuf, pos - recvbuf + 1);
	printf("got %s", data.c_str());

	return data;
}
void Send(SOCKET socket, std::string Message) {
	int iResult;
	iResult = send(socket, Message.c_str(), Message.length(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		WSACleanup();
		return;
	}
	printf("Bytes sent: %d\n", iResult);
}

void EncodeVectorToLong(Colour col, long* a, long* b, long* c) {
	float factor = pow(10, 7);
	*a = long(col[0] * factor);
	*b = long(col[1] * factor);
	*c = long(col[2] * factor);
}
void StartTrace() {
	//trace!

	tracer->DoRayTrace(m_scene);
	//trace finished
	Colour *pBuffer = tracer->GetFramebuffer()->GetBuffer();
	int x = 0;
	int y = 0;

	for (int i = 0; i < arraylength; i += 3) {
		//	Colour col = pBuffer[i / 3];
		Colour col = pBuffer[i / 3];
		//	printf("%f ", col[0]);
		EncodeVectorToLong(col, &ary[i], &ary[i + 1], &ary[i + 2]);
	}
}

void init() {
	ary = new long[arraylength];

}
void SendARRAy(SOCKET sok) {
	printf("Sending data\n");

	int unitsize = 32;
	char* data = new char[arraylength * unitsize];
	for (int i = 0; i < arraylength * unitsize; i += unitsize) {
		long input = ary[i / unitsize];
		for (int j = 0; j < unitsize; j++) {
			if (j == 0) {
				data[i] = (unsigned char)(input & 0xFF);
			}
			else {
				data[i + j] = (unsigned char)(input >> 8 * j);
			}
		}
		//long accum = 0;
		//for (int j = 0; j < unitsize; j += 2) {
		//	accum = accum | ((unsigned char)(data[j + i + 1]) << 8 * (j + 1) | (unsigned char)(data[i + j]) << 8 * j);
		//}
		//printf("%d ", accum);
	}


	SendCSTR(sok, data, arraylength * unitsize);
}
#include <sstream>
int __cdecl main(int argc, char **argv)
{

	WSADATA wsaData;
	SOCKET ConnectSocket;
	for (unsigned int i = 0; i < 10; i++) {
		ConnectSocket = ConnectToServer("192.168.0.100");
		if (ConnectSocket != 1) {
			printf("Connect Sucesful\n");
			break;
		}
		printf("Connect failed Waiting 1 second to retry\n");
		Sleep(1000);
	}
	
	char *sendbuf = "this is a test\n";
	char recvbuf[DEFAULT_BUFLEN];

	int recvbuflen = DEFAULT_BUFLEN;
	init();
	//SendCSTR(ConnectSocket, sendbuf,15);
	//CloseSocket(ConnectSocket);
	while (1) {
		std::string data = WaitRECV(ConnectSocket);
		if (data == "CheckAlive\n") {
			Send(ConnectSocket, "Alive\n");
		}
		else if (data == "Start\n") {
			Send(ConnectSocket, "StartConfirmed\n");
			StartTrace();
			//Send(ConnectSocket, "BufferSend\n");//append more data like size etc.
			SendARRAy(ConnectSocket);
			std::ostringstream strs;
			strs << tracer->TimeinMS<<"\n";
			std::string str = strs.str();
			Send(ConnectSocket, str);

		}
		else if (data.find("INIT") == 0) {
			//we have been given init.
			data.erase(0, 4);
			char* string = new char[data.length()];
			strcpy(string, data.c_str());

			//char* splitb = strtok(NULL, "x");
		//	printf("x = %s\n", string);
			std::string str = string;

			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == ':')
					str[i] = ' ';
			}

			std::vector<int> array;
			std::stringstream ss(str);
			int temp;
			while (ss >> temp)
				array.push_back(temp); // done! now array={102,330,3133,76531,451,000,12,44412}
	/*		for (int i = 0; i < array.size(); i++) {
				std::cout << array[i] << std::endl;
			}*/
			//	int xpos = splitb[0];
				//split = strtok(string, "y");
				//splitb = strtok(NULL, "y");
			//	printf("%s", split);
			//	printf("y is %s\n", splitb);


			Initilise(array[3], array[2], array[0], array[1]);
			Send(ConnectSocket, "Ready\n");
		}
		else
		{
			break;
		}
	}
	// cleanup
	CloseSocket(ConnectSocket);
	closesocket(ConnectSocket);
	WSACleanup();
//	getchar();
	return 0;
}

