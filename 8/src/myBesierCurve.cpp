#include "myBesierCurve.h"
using std::cout;
using std::endl;

GLfloat xpos, ypos;
bool clickRight, clickLeft;

myBesierCurve::myBesierCurve(GLFWwindow* _window, unsigned width, unsigned height, const GLchar* vertexPath, const GLchar* fragmentPath)
{
	this->window = _window;
	this->shader = new Shader(vertexPath, fragmentPath);

	nControlPoint = 0;
	nTotalPoint = 0;
	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	clickRight = clickLeft = false;

	maxFactorial = -1;         //存储的最大阶乘初始化为-1
}

myBesierCurve::~myBesierCurve()
{
	delete shader;
}


bool myBesierCurve::point2data(vector<Point>& p)
{
	nTotalPoint = p.size();

	for (int i = 0; i < nTotalPoint;i++)
	{
		data[i * 3] = (p[i].x / SCR_WIDTH) * 2 - 1;
		data[i * 3 + 1] = -((p[i].y / SCR_HEIGHT) * 2 - 1);
		data[i * 3 + 2] = 0;
	}

	return true;
}
bool myBesierCurve::delControlPoint()
{
	if (nControlPoint <= 0)
		return false;
	controlPoints.pop_back();
	nControlPoint--;
	return true;
}
bool myBesierCurve::addControlPoint()
{
	if (nControlPoint > 1024)
		return false;

	nControlPoint++;
	controlPoints.push_back(Point(xpos, ypos));
	return true;
}

void myBesierCurve::drawPoints(int size, glm::vec3 color, bool isLine)
{
	if (nControlPoint < 1)
		return;

	shader->setVec3("fgColor", color);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, nTotalPoint * 3 * sizeof(float), data, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO);
	glPointSize(size);
	glDrawArrays(GL_POINTS, 0, nTotalPoint);

	if (isLine)
		glDrawArrays(GL_LINE_STRIP, 0, nTotalPoint);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void myBesierCurve::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// render
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	shader->use();

	if (clickRight == true)
		delControlPoint();

	if (clickLeft == true)
		addControlPoint();

	clickLeft = clickRight = false;
	point2data(controlPoints);
	drawPoints(10, glm::vec3(1.0f, 1.0f, 1.0f), true);

	//采样贝塞尔曲线
	vector<Point> sample;
	if (nControlPoint > 1)
	{
		sampleBesierCurve(0.001, sample);
		point2data(sample);
		drawPoints(3, glm::vec3(0.0f, 1.0f, 1.0f));
	}

	//绘制辅助线

	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void myBesierCurve::sampleBesierCurve(float interval, vector<Point>& sample)
{
	sample.clear();

	float x = 0, y = 0;

	for (float t = 0; t <= 1; t += interval)
	{
		x = controlPoints[0].x * bernsteinItem(0, t);
		y = controlPoints[0].y * bernsteinItem(0, t);
		for (int i = 1; i < nControlPoint; i++)
		{
			x += controlPoints[i].x * bernsteinItem(i, t);
			y += controlPoints[i].y * bernsteinItem(i, t);
		}
		sample.push_back(Point(x, y));
	}
}

float myBesierCurve::bernsteinItem(int i, float t)
{
	int n = nControlPoint - 1;
	float tmp = float(getFactorial(n)) / float((getFactorial(i) * getFactorial(n - i)));
	return (tmp * pow(1 - t, n -  i) * pow(t, i));
}

long long int myBesierCurve::computeFactorial(int end)
{
	cout << "compute f " ;
	factorial[0] = 1;
	for (int i = 1; i < end+1; i++)
	{
		factorial[i] = factorial[i - 1] * i;
		cout << factorial[i] << " ";
	}
	cout << endl;
	maxFactorial = end;
	return factorial[end];
}
long long int myBesierCurve::getFactorial(int index)
{
	return ((index <= maxFactorial)? this->factorial[index]:computeFactorial(index));
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
	xpos = x;
	ypos = y;
	return;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			cout << "Mouse left button clicked at " << xpos << " " << ypos << endl;
			clickLeft = true;
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			cout << "Mouse right button clicked at" << xpos << " " << ypos << endl;
			clickRight = true;
			break;

		default:
			return;
		}
	}

	return;
}

GLFWwindow* initWindow(const char* title, int SCR_WIDTH, int SCR_HEIGHT)
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);   //在初始化glad前要有这句话否则运行时出错
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}
	return window;

}
