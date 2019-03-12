#include "Shader.h"
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	string vertexCode, fragmentCode;
	ifstream vShaderFile, fShaderFile;
	// �쳣����
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	/*
	 * ���붥����ɫ��
	 */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); //������ɫ����������Ϊ����

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);   // ��������ɫ��Դ�븽�ӵ���ɫ��������
	glCompileShader(vertexShader);

	int success;                          // �������Ƿ���ȷ�����������ӡ������Ϣ
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		//return -1;
	}

	/*
	 * ����Ƭ����ɫ��
	 */
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	char infoLog2[512]; // �������Ƿ���ȷ�����������ӡ������Ϣ
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog2);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog2 << std::endl;
		//return -1;
	}

	/*
	 * ������ɫ������
	 */
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success); // �����ɫ�����ӳɹ�
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << infoLog << std::endl;
		//return -1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
//����
void Shader::use()
{
	glUseProgram(ID);
}
//����
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
