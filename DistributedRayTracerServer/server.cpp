
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "Source.h"
SOCKET Server::BuildListenSocket() {
	WSADATA wsaData;
	int iResult;
	struct addrinfo *result = NULL;
	struct addrinfo hints;
	SOCKET ListenSocket = INVALID_SOCKET;


	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);
	return ListenSocket;
}
int Server::Send(SOCKET socket, std::string Message) {
	int iResult;
	iResult = send(socket, Message.c_str(), Message.length(), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		socket = NULL;
		//		WSACleanup();
		return -1;
	}
	printf("Bytes sent: %d\n", iResult);
	return 1;
}
void Server::SendCSTR(SOCKET socket, char* msg, int length) {
	int iResult;
	iResult = send(socket, msg, length, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(socket);
		socket = NULL;
		//	WSACleanup();
		return;
	}
	printf("Bytes sent: %d\n", iResult);
}
std::string Server::WaitRECV(SOCKET Socket) {
	int iResult = 0;
	int iSendResult = 0;
	char recvbuf[DEFAULT_BUFLEN];
	int length = DEFAULT_BUFLEN;
	do {

		iResult = recv(Socket, recvbuf, length, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			if (strchr(recvbuf, '\n') != nullptr) {
				//end of message.
				break;
			}
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(Socket);
			Socket = NULL;
			//	WSACleanup();
			return std::string("invalid");
		}

	} while (iResult > 0);
	//every message will terminate with \n
	char* pos = strchr(recvbuf, '\n');
	std::string data(recvbuf, pos - recvbuf + 1);
	return data;
}
SOCKET Server::LISTEN(SOCKET Listensocket) {
	int iResult = 0;
	SOCKET ClientSocket = INVALID_SOCKET;
	
	iResult = listen(Listensocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(Listensocket);
		//	WSACleanup();
	}
	// Accept a client socket
	ClientSocket = accept(Listensocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(Listensocket);
		//WSACleanup();
		return INVALID_SOCKET;
	}
	return ClientSocket;
}
void Server::CloseSocket(SOCKET target) {
	int iResult = 0;
	// shutdown the connection since we're done
	iResult = shutdown(target, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(target);
		//	WSACleanup();
		return;
	}
}
//todo:: lock comincations
Server::Server() {
	std::cout << "Starting Server" << std::endl;
	
	ListenSocket = BuildListenSocket();
}
bool Server::CheckAlive(SOCKET sok) {
	//checks that a client is still alive.
	Send(sok, "CheckAlive\n");
	printf("Sending alive\n");
	std::string out = WaitRECV(sok);
	//	printf("out == %s", out);
	if (out == "Alive\n") {
		printf("Cleint alive\n");
		return true;
	}
	return false;
}
clock_t tstart = clock();
void Server::StartALL() {
	if (workers.size() > 0) {
		fprintf(stdout, "Trace start.\n");
		tstart = clock();
		for (int i = 0; i < workers.size(); i++)
		{
			Start(workers[i]);
		}
	}
	else
	{
		printf("Failed to Start Trace, No workers Connected\n");
	}
}
bool Server::Start(Worker* w) {
	if (w->m_State == Worker::STATE_UNINTILISED) {
		printf("Start Called on Uninitalised worker\n");
		return false;
	}
	if (w->m_State == Worker::STATE_ERROR) {
		printf("worker Error\n");
		return false;
	}
	w->m_State = Worker::STATE_STARTING;
	if (Send(w->Wocker_sockect, "Start\n") == 1) {
		std::string out = WaitRECV(w->Wocker_sockect);
		//	printf("out == %s", out);
		if (out == "StartConfirmed\n") {
			w->m_State = Worker::STATE_WORKING;
			return true;
		}
	}
	w->m_State = Worker::STATE_ERROR;
	printf("Failed to Start Worker %d\n", w->id);

	return false;
}
int Server::ReceiveArray(Worker* w) {
	printf("REciving array\n");
	SOCKET arraysok = w->Wocker_sockect;
	int pixelcount = w->m_width * w->m_height;
	int unitsize = 32;
	int length = pixelcount * unitsize * 3;//int size is 4
	int iResult = 0;
	int iSendResult = 0;
	char* recvbuf = new char[length];
	int datacount = 0;
	do {
		
		iResult = recv(arraysok, recvbuf, length, 0);
		if (iResult > 0) {
			printf("Array Bytes received: %d\n", iResult);
			datacount += iResult;
			if (datacount == length) {
				break;
			}
			if (strchr(recvbuf, '\r') != nullptr) {
				//end of message.
				break;
			}
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(arraysok);
			return -1;
		}

	} while (iResult > 0);
	for (int px = 0; px < pixelcount; px++) {
		float tris[3];
		for (int i = 0; i < 96; i += unitsize) {
			long accum = 0;
			for (int j = 0; j < unitsize; j += 2) {
				accum = accum | ((unsigned char)(recvbuf[(96 * px) + j + i + 1]) << 8 * (j + 1) | (unsigned char)(recvbuf[(96 * px) + i + j]) << 8 * j);
			}
			float factor = pow(10, 7);
			tris[i / unitsize] = accum / factor;
		}
		w->WorkerBuffer[px] = Vector3(tris[0], tris[1], tris[2]);
	}
	printf("finnished array\n");
	return 1;
}
void Server::ReinitWorker(Worker* w) {
	std::stringstream stringStream;
	stringStream << "INIT :" << w->m_offsetx << ":" << w->m_offsety << ":" << w->m_height << ":" << w->m_width << std::endl;
	std::string data = stringStream.str();
	if (Send(w->Wocker_sockect, data) == -1) {
		w->m_State = Worker::STATE_ERROR;
		return;
	}
	if (WaitRECV(w->Wocker_sockect) != "Ready\n") {
		printf("Worker init failed\n");
	}
	else
	{
		printf("Worker Ready\n");
		w->m_State = Worker::STATE_IDLE;
	}
}
void Server::HandleClient(Worker* w) {

	std::stringstream stringStream;
	stringStream << "INIT :" << w->m_offsetx << ":" << w->m_offsety << ":" << w->m_height << ":" << w->m_width << std::endl;
	std::string data = stringStream.str();
	Send(w->Wocker_sockect, data);
	if (WaitRECV(w->Wocker_sockect) != "Ready\n") {
		printf("Worker init failed\n");
	}
	else
	{
		printf("Worker Ready\n");
		w->m_State = Worker::STATE_IDLE;
	}

	while (true)
	{
		if (w->m_State == Worker::STATE_ERROR) {
			break;
		}
		if (w->m_State == Worker::STATE_WORKING) {
			//the worker is tracing wait for data 
			Sleep(1000);
			if (ReceiveArray(w) == 1) {
				printf("w %d finished in Time taken: %s ms\n", w->id, WaitRECV(w->Wocker_sockect));
				Render();
				//	printf("w %d finished in Time taken: %.00fms\n",w->id, (double)(clock() - tstart) * 1000 / CLOCKS_PER_SEC);
				//	fprintf(stdout, "Done!!!\n");
				w->m_State = Worker::STATE_FINISHED;
			}
			else
			{
				w->m_State = Worker::STATE_ERROR;
				break;
			}
		}
		else if (w->m_State == Worker::STATE_UNKNOWN)
		{

			if (CheckAlive(w->Wocker_sockect) == false)
			{
				w->m_State = 0;
				break;
			}
			w->m_State = Worker::STATE_IDLE;
			Sleep(2500);
			//	UpdateUI();
		}
	}
	CloseAndRemoveWorker(w);
}
void Server::CloseAndRemoveWorker(Worker* w) {
	printf("Worker %d Disconected\n", w->id);
	CloseSocket(w->Wocker_sockect);
	closesocket(w->Wocker_sockect);
	w->Wocker_sockect = NULL;
	workers.erase(std::remove(workers.begin(), workers.end(), w), workers.end());
	UpdateUI();//cause a Refresh
}
void Server::UpdateUI() {
	printf("------%d Workers Connected------\n", workers.size());
	for (int i = 0; i < workers.size(); i++)
	{
		//	system("cls");
		std::cout << "Worker " << i << " state = " << workers[i]->m_State << std::endl;
	}
	AssignWorkers(0);
}
void Server::AssignWorkers(int split) {
	if (workers.size() > 0) {
		split = workers.size();
	}
	for (int i = 0; i < workers.size(); i++) {
		if (i == 0) {
			workers[i]->AssignWork(0, 0, m_width / split, m_height );
		}
		else
		{
			workers[i]->AssignWork(i*m_width / split,0 , m_width / split, m_height);
		}
		if (i == 1) {
			workers[i]->WorkerColour = Vector3(1, 0, 0);
		}else if (i == 2) {
			workers[i]->WorkerColour = Vector3(0, 1, 0);
		}else if (i == 3) {
			workers[i]->WorkerColour = Vector3(0, 0, 1);
		}
		ReinitWorker(workers[i]);//relay new config to client
	}
}
void Server::Loop() {

	SOCKET ClientSocket = NULL;
	while (1) {
		ClientSocket = LISTEN(ListenSocket);
		//client socket is for some reason 18446744073709551615
		//might be fixed
		if (ClientSocket != NULL && ClientSocket < 1500) {
			Worker* w;// = new Worker(ClientSocket, 0, 0, 1280 / 2, 720 / 2);
			w = new Worker(ClientSocket, 0, 0, 1280, 720);
			w->id = currentidtally;
			currentidtally++;
			threads.push_back(std::thread(&Server::HandleClient, this, w));
			workers.push_back(w);
			UpdateUI();
		}
		ClientSocket = NULL;
		Sleep(1000);
	}
}

Server::~Server() {
	CloseSocket(ListenSocket);
	// cleanup
	closesocket(ListenSocket);
	WSACleanup();
}

