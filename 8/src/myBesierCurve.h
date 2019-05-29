#pragma once
#include "utility.h"
#include "Shader.h"
using std::vector;



class Point
{
public:
	float x, y;
	Point(float _x = 0, float _y = 0)
	{
		x = _x;
		y = _y;
	}

	bool operator==(const Point& other)
	{
		return (x == other.x && y == other.y);
	}
};

class myBesierCurve
{
public:
	myBesierCurve(GLFWwindow* _window, unsigned width, unsigned height, const GLchar* vertexPath, const GLchar* fragmentPat);
	~myBesierCurve();


	bool addControlPoint();
	bool delControlPoint();

	bool point2data(vector<Point>& p);
	void drawPoints(int size, glm::vec3 color, bool isLline = false);
	void render();

	void sampleBesierCurve(float interval, vector<Point>& sample);

	float bernsteinItem(int i, float t);

	long long int computeFactorial(int end);
	long long int getFactorial(int index);



private:

	vector<Point> controlPoints; //控制点的屏幕坐标
	int nControlPoint;

	Shader* shader;

	GLFWwindow* window;

	float data[3072];
	int nTotalPoint;

	long long int factorial[21];
	int maxFactorial;

	// settings
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void cursor_position_callback(GLFWwindow* window, double x, double y);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

GLFWwindow* initWindow(const char* title, int SCR_WIDTH, int SCR_HEIGHT);