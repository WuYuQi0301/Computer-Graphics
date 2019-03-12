#include "Shader.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GL/gl3w.h>

#include <vector>
using std::vector;

const char* glsl_version = "#version 130";

// 窗口大小变化时视口自适应的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 输入控制
void processImput(GLFWwindow *window);

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
int main()
{	
	glfwSetErrorCallback(glfw_error_callback);
	// 初始化
	glfwInit();
	// 设置版本号和核心模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(500, 400, "Hello GLFW", NULL, NULL);
	if (window  ==  NULL) 
	{
		std::cout << "error" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);
	//使用glad管理指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize GLAD" << std::endl;
		return -1;
	}

	/***********************************************************
	* 初始化IMGUI
	*/
	gl3wInit();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();  // context
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();  // style // ImGui::StyleColorsClassic();
	ImGui_ImplGlfw_InitForOpenGL(window, true); // platform/randererbinging
	ImGui_ImplOpenGL3_Init(glsl_version);

	/***********************************************************
     * 顶点
     */
	float vertices[] = {
		// 位置              // 颜色
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 右下
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f    // 
	};
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);     // 绑定缓冲到VBO的缓冲类型上

	Shader ourShader("vShaderFile.txt", "fShaderFile.txt");


	vector<ImVec4> colors;
	ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	colors.push_back(ImVec4(0.0f, 0.0f, 1.0f, 1.00f));
	colors.push_back(ImVec4(1.0f, 0.0f, 0.0f, 1.00f));
	colors.push_back(ImVec4(0.0f, 1.0f, 0.0f, 1.00f));

	bool show_demo_window = true;
	bool if_change_whole = true;

	/*********************************************************************8
	 * 渲染循环
	 */
	while (!glfwWindowShouldClose(window))
	{
		processImput(window);
		glfwPollEvents();         //检查触发事件并调用对应的回调函数
		
		std::cout << "here" << std::endl;
		ImGui_ImplOpenGL3_NewFrame();  // Start the Dear ImGui frame
		std::cout << "here" << std::endl;
		ImGui_ImplGlfw_NewFrame();
		std::cout << "here" << std::endl;
		ImGui::NewFrame();
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		{
			std::cout << "here" << std::endl;
			ImGui::Begin("COLOR");
			ImGui::SetWindowSize(ImVec2(50, 170));
			ImGui::SetWindowPos(ImVec2(-0.5f, 0));

			ImGui::Text("Change the colors");
			ImGui::ColorEdit3("RIGHT", (float*)&colors[0]); // Edit 3 floats representing a color
			ImGui::ColorEdit3("LEFT", (float*)&colors[1]); // Edit 3 floats representing a color
			ImGui::ColorEdit3("TOP", (float*)&colors[2]); // Edit 3 floats representing a color

			//ImGui::Checkbox("IF CHANGE THE WHOLE COLOR", &if_change_whole);
			//ImGui::ColorEdit3("WHOLE COLOR", (float*)&color_whole, 1);
			//Change the color
			//if (if_change_whole)
			//{
				//for (int i = 0; i < 3; i++)
				////{
					//vertices[i * 6 + 3] = color_whole.x;
					//vertices[i * 6 + 4] = color_whole.y;
					//vertices[i * 6 + 5] = color_whole.z;
				//}
			//}
			//els/e {
			for (int i = 0; i < 3; i++) 
			{
				vertices[i * 6 + 3] = colors[i].x;
				vertices[i * 6 + 4] = colors[i].y;
				vertices[i * 6 + 5] = colors[i].z;
			}
			//}
			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();


		}


		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);  // 将定义的顶点数据复制到当前绑定的缓冲内存中
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 链接并启用顶点位置属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 连接并启用颜色属性
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形

		ImGui::Render();

		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);  //交换颜色缓冲（绘制窗口输出）
	

	 }


	 ImGui_ImplOpenGL3_Shutdown();
	 ImGui_ImplGlfw_Shutdown();
	 ImGui::DestroyContext();

	 glfwDestroyWindow(window);
	 glfwTerminate();


	return 0;
} 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processImput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
