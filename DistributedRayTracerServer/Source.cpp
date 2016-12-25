#include "include\GLFW\glfw3.h"
#include <iostream>
#include "server.h"
#include "Framebuffer.h"
int width = 1280;
int height = 720;
bool refresh = true;
Framebuffer* buffer;
Server* m_server;
std::thread m_Serverthread;
void RunServerThread(Server* serv) {
	serv->Loop();
}
bool ShouldRender = true;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_F1:
			ShouldRender = true;
			break;
		case GLFW_KEY_F2:
			m_server->StartALL();
			ShouldRender = true;
			break;
		case GLFW_KEY_F3:
			m_server->UpdateUI();
			ShouldRender = true;
			break;
		
		default:
			break;
		}
	}

}
void init() {
	m_server = new Server();
	m_server->m_height = height;
	m_server->m_width = width;
	m_Serverthread = std::thread(&RunServerThread, m_server);
	buffer = new Framebuffer(width, height);
}
void Render() {
	ShouldRender = true;
}
int main(void)
{
	init();
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "RayTracer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	std::cout << "F1: Refresh Buffer" << std::endl;
	std::cout << "F2: Start Render on Clients" << std::endl;
	std::cout << "F3: List and Assign Clients" << std::endl;
	while (!glfwWindowShouldClose(window))
	{
		if (ShouldRender == true) {
			glClear(GL_COLOR_BUFFER_BIT);
			if (m_server->workers.size() > 0) {
				for (int wi = 0; wi < m_server->workers.size(); wi++) {
					Worker* work = m_server->workers[wi];
					int y = work->m_offsety;
					int size = work->m_width * (work->m_height);
					int x = work->m_offsetx;
					for (int i = 0; i < size; i++) {
						//	work->WorkerBuffer[i]	
						Colour debugvar = work->WorkerBuffer[i];

						if (x >= work->m_offsetx + work->m_width) {
							y++;
							x = work->m_offsetx;
						}
						x++;
						if (x >= work->m_offsetx + work->m_width) {
							//	printf("Restricting x\n");
							x = work->m_offsetx + work->m_width;
						}
						if (y >= work->m_offsety + work->m_height) {
							//printf("Restricting y\n");
							y = work->m_offsety + work->m_height - 1;
						}
						if (x == work->m_offsetx) {
							//debugvar = Colour(0, 1,0);
						}
						buffer->WriteRGBToFramebuffer(debugvar, x, y);
					}
				}
			}
			Colour *pBuffer = buffer->GetBuffer();
			glDrawPixels(width, height, GL_RGB, GL_FLOAT, pBuffer);

			glFlush();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			ShouldRender = false;
		}
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}