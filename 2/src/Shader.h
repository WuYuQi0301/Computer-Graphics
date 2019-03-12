#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using std::string;
using std::ifstream;
using std::stringstream;

class Shader
{
public:
	// program id
	unsigned int ID;

	//constructor
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	//¼¤»î
	void use();
	//¹¤¾ß
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
};

#endif // !SHADER_H
