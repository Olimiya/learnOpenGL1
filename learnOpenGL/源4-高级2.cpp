//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "shader.h"
//#include "camera.h"
//#include "stb_image.h"
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <map>
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//GLFWwindow *init();
//GLuint loadTexture(char const *path);
//
//#define NR_POINT_LIGHTS 4
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//	GLFWwindow* window = init();
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//	glEnable(GL_POLYGON_OFFSET_FILL);
//	glPolygonOffset(0.1f, 0.1f);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_CULL_FACE);
//	
//	Shader shader("v4shader.glsl", "f4shader.glsl");
//	Shader screenShader("v4shader.glsl", "f4shader_screen.glsl");
//	unsigned int cubeTexture = loadTexture("./marble.jpg");
//	glBindTexture(GL_TEXTURE_2D, cubeTexture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	unsigned int floorTexture = loadTexture("./metal.png");
//	glBindTexture(GL_TEXTURE_2D, floorTexture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	unsigned int grassTexture = loadTexture("./grass.png");
//	glBindTexture(GL_TEXTURE_2D, grassTexture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	unsigned int windowTexture = loadTexture("./blending_transparent_window.png");
//	glBindTexture(GL_TEXTURE_2D, windowTexture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	shader.use();
//	shader.setInt("texture1", 0);
//	screenShader.use();
//	screenShader.setInt("texture1", 0);
//
//	float cubeVertices[] = {
//		// Back face
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//		// Front face
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//		// Left face
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//		// Right face
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
//		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
//		// Bottom face
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//		// Top face
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
//		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
//	};
//	float planeVertices[] = {
//		// positions
//		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f
//	};
//	float transparentVertices[] = {
//		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
//		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
//		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
//		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
//	};
//
//	//草的位置
//	vector<glm::vec3> vegetation
//	{
//		glm::vec3(-1.5f, 0.0f, -0.48f),
//		glm::vec3(1.5f, 0.0f, 0.51f),
//		glm::vec3(0.0f, 0.0f, 0.55f),
//		glm::vec3(-0.3f, 0.0f, -2.3f),
//		glm::vec3(0.5f, 0.0f, -0.6f)
//	};
//	//玻璃窗户的位置
//	vector<glm::vec3> windows
//	{
//		glm::vec3(-1.5f, 0.0f, -0.48f),
//		glm::vec3(1.5f, 0.0f, 0.51f),
//		glm::vec3(0.0f, 0.0f, 0.7f),
//		glm::vec3(-0.3f, 0.0f, -2.3f),
//		glm::vec3(0.5f, 0.0f, -0.6f)
//	};
//	//立方体
//	unsigned int cubeVAO;
//	unsigned int cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glBindVertexArray(cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
//	glBindVertexArray(0);
//	//地板
//	unsigned int floorVAO;
//	unsigned int floorVBO;
//	glGenVertexArrays(1, &floorVAO);
//	glBindVertexArray(floorVAO);
//	glGenBuffers(1, &floorVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
//	glBindVertexArray(0);
//	//grass, 渲染不规则图形
//	unsigned int grassVAO;
//	unsigned int grassVBO;
//	glGenVertexArrays(1, &grassVAO);
//	glBindVertexArray(grassVAO);
//	glGenBuffers(1, &grassVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
//	glBindVertexArray(0);
//	//window, 渲染透明物体
//	unsigned int windowVAO;
//	unsigned int windowVBO;
//	glGenVertexArrays(1, &windowVAO);
//	glBindVertexArray(windowVAO);
//	glGenBuffers(1, &windowVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, windowVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
//	glBindVertexArray(0);
//	//screen, 承载离屏渲染的结果
//	unsigned int screenVAO;
//	unsigned int screenVBO;
//	glGenVertexArrays(1, &screenVAO);
//	glBindVertexArray(screenVAO);
//	glGenBuffers(1, &screenVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
//	glBindVertexArray(0);
//
//	unsigned int frameBuffer;
//	glGenFramebuffers(1, &frameBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
//	unsigned int textureBuffer;
//	glGenTextures(1, &textureBuffer);
//	glBindTexture(GL_TEXTURE_2D, textureBuffer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT,
//		0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	unsigned int renderBuffer;
//	glGenRenderbuffers(1, &renderBuffer);
//	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureBuffer, 0);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
//		GL_RENDERBUFFER, renderBuffer);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		cout << "Frame buffer not Complete!" << endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		processInput(window);
//
//		// render
//		// ------
//		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
//		glEnable(GL_DEPTH_TEST);
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
//			(float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//		//cube
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		glm::mat4 model(1.0f);
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		//floor
//		glBindVertexArray(floorVAO);
//		glBindTexture(GL_TEXTURE_2D, floorTexture);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(0.0f, -0.1f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		//grass
//		glBindVertexArray(grassVAO);
//		glBindTexture(GL_TEXTURE_2D, grassTexture);
//		for(GLuint i = 0; i < vegetation.size(); i++)
//		{
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, vegetation[i]);
//			shader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//		//window
//		glBindVertexArray(windowVAO);
//		glBindTexture(GL_TEXTURE_2D, windowTexture);
//		map<float, glm::vec3> sorted;
//		for (GLuint i = 0; i < windows.size(); i++)
//		{
//			float distance = glm::length(camera.Position - windows[i]);
//			sorted[distance] = windows[i];
//		}
//		for (auto i = sorted.rbegin(); i != sorted.rend(); i++)
//		{
//			model = glm::mat4(1.0f);
//			model = glm::translate(model, i->second);
//			shader.setMat4("model", model);
//			glDrawArrays(GL_TRIANGLES, 0, 6);
//		}
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		glBindVertexArray(screenVAO);
//		screenShader.use();
//		glm::mat4 unit(1.0f);
//		screenShader.setMat4("view", unit);
//		screenShader.setMat4("projection", unit);
//		model = glm::mat4(1.0f);
//		model = glm::scale(model, glm::vec3(2.0f));
//		screenShader.setMat4("model", model);
//		glBindTexture(GL_TEXTURE_2D, textureBuffer);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
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
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = (float)xpos;
//		lastY = (float)ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = (float)xpos - lastX;
//	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = (float)xpos;
//	lastY = (float)ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll((float)yoffset);
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
//GLuint loadTexture(char const *path)
//{
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}