﻿//#include <glad/glad.h>
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
//
//	Shader shader("v6shader.glsl", "f6shader.glsl");
//	unsigned int diffuseMap = loadTexture("brickwall.jpg");
//	unsigned int normalMap = loadTexture("brickwall_normal.jpg");
//	shader.use();
//	shader.setInt("diffuseMap", 0);
//	shader.setInt("normalMap", 1);
//
//	// 平面的数据
//	// 根据顶点坐标以及纹理坐标，手动计算切线向量和副切线向量
//	// positions
//	glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
//	glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
//	glm::vec3 pos3(1.0f, -1.0f, 0.0f);
//	glm::vec3 pos4(1.0f, 1.0f, 0.0f);
//	// texture coordinates
//	glm::vec2 uv1(0.0f, 1.0f);
//	glm::vec2 uv2(0.0f, 0.0f);
//	glm::vec2 uv3(1.0f, 0.0f);
//	glm::vec2 uv4(1.0f, 1.0f);
//	// normal vector
//	glm::vec3 nm(0.0f, 0.0f, 1.0f);
//
//	// calculate tangent/bitangent vectors of both triangles
//	glm::vec3 tangent1, bitangent1;
//	glm::vec3 tangent2, bitangent2;
//	// triangle 1
//	// ----------
//	glm::vec3 edge1 = pos2 - pos1;
//	glm::vec3 edge2 = pos3 - pos1;
//	glm::vec2 deltaUV1 = uv2 - uv1;
//	glm::vec2 deltaUV2 = uv3 - uv1;
//
//	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
//
//	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
//	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
//	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
//	tangent1 = glm::normalize(tangent1);
//
//	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
//	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
//	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
//	bitangent1 = glm::normalize(bitangent1);
//
//	// triangle 2
//	// ----------
//	edge1 = pos3 - pos1;
//	edge2 = pos4 - pos1;
//	deltaUV1 = uv3 - uv1;
//	deltaUV2 = uv4 - uv1;
//
//	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
//
//	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
//	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
//	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
//	tangent2 = glm::normalize(tangent2);
//
//
//	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
//	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
//	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
//	bitangent2 = glm::normalize(bitangent2);
//
//
//	float quadVertices[] = {
//		// positions            // normal         // texcoords  // tangent                          // bitangent
//		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
//
//		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
//		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
//	};
//
//	unsigned int cubeVAO;
//	unsigned int cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
//	glBindVertexArray(0);
//
//	glm::vec3 lightPos = glm::vec3(0.5f, 1.0f, 0.3f);
//	glEnable(GL_DEPTH_TEST);
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
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// configure view/projection matrices
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		shader.use();
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", view);
//		// render normal-mapped quad
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
//		shader.setMat4("model", model);
//		shader.setVec3("viewPos", camera.Position);
//		shader.setVec3("lightPos", lightPos);
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, normalMap);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		//model = glm::mat4(1.0f);
//		//model = glm::translate(model, glm::vec3(lightPos.x, lightPos.y, lightPos.z - 0.2));
//		//model = glm::scale(model, glm::vec3(0.1f));
//		//shader.setMat4("model", model);
//		//glDrawArrays(GL_TRIANGLES, 0, 6);
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
//	//stbi_set_flip_vertically_on_load(true);
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
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
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