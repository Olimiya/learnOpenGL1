//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
//#include <glm\glm.hpp>
//#include <glm\gtc\matrix_transform.hpp>
//#include <glm\gtc\type_ptr.hpp>
//#include "stb_image.h"
//#include "shader.h"
//#include "camera.h"
//#include <iostream>
//
//const float SCR_WIDTH = 800.0f;
//const float SCR_HEIGHT = 600.0f;
//GLuint VAO, VBO, EBO;
//GLuint program;
//GLuint texture1;
//GLuint texture2;
//glm::vec3 cubePositions[] = {
//  glm::vec3(0.0f,  0.0f,  0.0f),
//  glm::vec3(2.0f,  5.0f, -15.0f),
//  glm::vec3(-1.5f, -2.2f, -2.5f),
//  glm::vec3(-3.8f, -2.0f, -12.3f),
//  glm::vec3(2.4f, -0.4f, -3.5f),
//  glm::vec3(-1.7f,  3.0f, -7.5f),
//  glm::vec3(1.3f, -2.0f, -2.5f),
//  glm::vec3(1.5f,  2.0f, -2.5f),
//  glm::vec3(1.5f,  0.2f, -1.5f),
//  glm::vec3(-1.3f,  1.0f, -1.5f)
//};
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//
//float deltaTime = 0.0f;
//float lastTime = 0.0f;
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstCursor = true;
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//void processInput(GLFWwindow *window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//glm::mat4 look(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
//GLFWwindow *init();
//void loadData();
//void seeMat4(glm::mat4 mat)
//{
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < 4; j++)
//			std::cout << mat[j][i] << " ";
//		std::cout << std::endl;
//	}
//}
//
//int main()
//{
//	GLFWwindow *window = init();
//
//	Shader ourShader("v1shader.glsl", "f1shader.glsl");
//	program = ourShader.ID;
//	loadData();
//
//	ourShader.use();
//	//ourShader.setInt("texture1", 0);
//	ourShader.setInt("texture2", 1);
//
//	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (SCR_WIDTH) / (SCR_HEIGHT), 0.1f, 100.0f);
//	seeMat4(projection);
//	std::cout << std::endl;
//	projection = glm::perspective(glm::radians(80.0f), (SCR_WIDTH) / (SCR_HEIGHT), 0.1f, 100.0f);
//	seeMat4(projection);
//	std::cout << std::endl;
//	projection = glm::perspective(glm::radians(camera.Zoom), ((SCR_WIDTH) / (SCR_HEIGHT)), 10.0f, 100.0f);
//	seeMat4(projection);
//
//	while (!glfwWindowShouldClose(window))
//	{
//		float currTime = glfwGetTime();
//		deltaTime = currTime - lastTime;
//		lastTime = currTime;
//
//		processInput(window);
//		glEnable(GL_DEPTH_TEST);
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		//glActiveTexture(GL_TEXTURE0);
//		//glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		ourShader.use();
//
//		glm::mat4 view;
//		//view = look(camera.Position, camera.Position + camera.Front, camera.WorldUp);
//		view = camera.GetViewMatrix();
//
//		glm::mat4 projection;
//		//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
//		projection = glm::perspective(glm::radians(camera.Zoom), (SCR_WIDTH) / (SCR_HEIGHT),0.1f, 100.0f);
//		ourShader.setMat4("view", view);
//		ourShader.setMat4("projection", projection);
//
//		glBindVertexArray(VAO);
//		for (unsigned int i = 0; i < 10; i++)
//		{
//			glm::mat4 model;
//			model = glm::translate(model, cubePositions[i]);
//			float angle = 20.0f * i;
//			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//			ourShader.setMat4("model", model);
//
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//
//	glfwTerminate();
//	system("pause");
//	return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow * window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow * window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void mouse_callback(GLFWwindow * window, double xpos, double ypos)
//{
//	if (firstCursor)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstCursor = false;
//	}
//	//注意减的顺序
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//GLFWwindow *init()
//{
//	glfwInit();
//	glfwInitHint(GLFW_VERSION_MAJOR, 4);
//	glfwInitHint(GLFW_VERSION_MINOR, 6);
//	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Learn openGL", nullptr, nullptr);
//	if (window == nullptr)
//	{
//		std::cout << "Fail to create window!";
//		system("pause");
//		glfwTerminate();
//		exit(-1);
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Fail to init GLAD!";
//		system("pause");
//		glfwTerminate();
//		exit(-1);
//	}
//	return window;
//}
//
//void loadData()
//{
//	float vertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//	//float vertices[] = {
//	//	// positions          // colors           // texture coords
//	//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//	//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//	//};
//	//unsigned int indices[] = {
//	//	0, 1, 3, // first triangle
//	//	1, 2, 3  // second triangle
//	//};
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	//glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	GLuint vPositon = glGetAttribLocation(program, "vPostion");
//	glEnableVertexAttribArray(vPositon);
//	glVertexAttribPointer(vPositon, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	//GLuint vColor = glGetAttribLocation(program, "vColor");
//	//glEnableVertexAttribArray(vColor);
//	//glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
//	glEnableVertexAttribArray(vTexCoord);
//	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	//glGenTextures(1, &texture1);
//	//glBindTexture(GL_TEXTURE_2D, texture1);
//	////横轴上、纵轴上设置环绕方式（决定超出0、1范围的表现形式）
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	////设置纹理过滤方式，决定一个纹理坐标处的颜色（由邻近像素点插值得到）
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	//int weight, height, nrChannels;
//	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	//unsigned char *data = stbi_load("./container.jpg", &weight, &height, &nrChannels, 0);
//	//if (data)
//	//{
//	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, weight, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	//	glGenerateMipmap(GL_TEXTURE_2D);
//	//}
//	//else
//	//{
//	//	std::cout << "Failed to load texture" << std::endl;
//	//	system("pause");
//	//	glfwTerminate();
//	//	exit(-1);
//	//}
//	//stbi_image_free(data);
//
//	glGenTextures(1, &texture2);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	stbi_set_flip_vertically_on_load(true);
//	int weight, height, nrChannels;
//	unsigned char *data = stbi_load("./awesomeface.png", &weight, &height, &nrChannels, 0);
//	if (data)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, weight, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else
//	{
//		std::cout << "Failed to load texture" << std::endl;
//		system("pause");
//		glfwTerminate();
//		exit(-1);
//	}
//	stbi_image_free(data);
//}
//
//glm::mat4 look(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
//{
//	glm::vec3 zaxis = glm::normalize(eye - center);
//	glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));
//	glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));
//
//	glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
//	translation[3][0] = -eye.x; // Third column, first row
//	translation[3][1] = -eye.y;
//	translation[3][2] = -eye.z;
//	glm::mat4 rotation = glm::mat4(1.0f);
//	rotation[0][0] = xaxis.x; // First column, first row
//	rotation[1][0] = xaxis.y;
//	rotation[2][0] = xaxis.z;
//	rotation[0][1] = yaxis.x; // First column, second row
//	rotation[1][1] = yaxis.y;
//	rotation[2][1] = yaxis.z;
//	rotation[0][2] = zaxis.x; // First column, third row
//	rotation[1][2] = zaxis.y;
//	rotation[2][2] = zaxis.z;
//
//	return rotation * translation;
//}
