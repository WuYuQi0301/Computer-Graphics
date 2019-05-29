#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "utility.h"

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
	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void setVec3(const std::string &name, const glm::vec3 &vec) const
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vec[0]);
	}
};

#endif // !SHADER_H
