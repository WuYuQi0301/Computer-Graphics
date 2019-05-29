#include "myBesierCurve.h"
#include <string.h>
using std::cout;
using std::endl;
using std::vector;



const char* glsl_version = "#version 330 core";
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);



int main()
{

	int SCR_WIDTH = 800, SCR_HEIGHT = 600;

	GLFWwindow* window = initWindow("Hello Cube", SCR_WIDTH, SCR_HEIGHT);

	myBesierCurve* mbc = new myBesierCurve(window, SCR_WIDTH, SCR_HEIGHT, "vShaderFile.txt", "fShaderFile.txt");
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		mbc->render();

	}
	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}