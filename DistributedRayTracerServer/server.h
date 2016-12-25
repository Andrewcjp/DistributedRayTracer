#pragma once
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include "Vector3.h"
#include <sstream> 
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define WIDTH 1280
#define HEIGHT 720
#define ArrayLength WIDTH*HEIGHT
class Worker {

private:

	//multideimetional array might not be needed however currently will be passed to host for collection! and suming

public:
	int m_offsetx, m_offsety, m_width, m_height;
	Vector3 WorkerColour = Vector3(0, 0, 0);
	Worker(SOCKET sok, int offsetx, int offsety, int width, int height) {
		m_offsetx = offsetx;
		m_offsety = offsety;
		m_height = height;
		m_width = width;
		Wocker_sockect = sok;
		WorkerBuffer = new Vector3[height*width];
		//initilise the buffer
		for (int i = 0; i < height*width; i++) {
			WorkerBuffer[i] = WorkerColour;
		}
		//remove this
		m_State = STATE_UNINTILISED;
	}

	void AssignWork(int offsetx, int offsety, int width, int height) {
		m_offsetx = offsetx;
		m_offsety = offsety;
		m_height = height;
		m_width = width;
		WorkerBuffer = new Vector3[height*width];
		//initilise the buffer
		for (int i = 0; i < height*width; i++) {
			WorkerBuffer[i] = WorkerColour;
		}
		//remove this
		m_State = STATE_UNINTILISED;
	}
	int m_State = 0;
	int id = 0;
	SOCKET Wocker_sockect;
	
	bool operator== (Worker rhs) {
		return id == rhs.id;
	}
	enum WORKERSTATE
	{
		STATE_UNKNOWN = 0,
		STATE_UNINTILISED,//the worker has not been told what it should do yet
		STATE_IDLE,
		STATE_STARTING,
		STATE_WORKING,
		STATE_FINISHED,
		STATE_ERROR
	};
	Vector3 *WorkerBuffer;
};
class Server {
public:
	Server();
	int m_width = 0;
	int m_height = 0;
	bool CheckAlive(SOCKET sok);
	void StartALL();
	bool Start(Worker* w);
	int ReceiveArray(Worker* w);
	void ReinitWorker(Worker * w);
	void HandleClient(Worker* w);

	void CloseAndRemoveWorker(Worker * w);


	void UpdateUI();
	void AssignWorkers(int split);
	~Server();

	void Loop();
	int Send(SOCKET socket, std::string Message);

	void SendCSTR(SOCKET socket, char * msg, int length);
	std::vector<Worker*> workers;
	std::string WaitRECV(SOCKET Socket);
private:
	SOCKET ListenSocket = INVALID_SOCKET;

	SOCKET BuildListenSocket();

	SOCKET LISTEN(SOCKET Listensocket);

	void CloseSocket(SOCKET target);
	std::vector<std::thread> threads;
	int currentidtally = 0;
};
