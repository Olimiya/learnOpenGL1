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
//
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//	//glDepthFunc(GL_ALWAYS);
//	//glEnable(GL_POLYGON_OFFSET_FILL);
//	//glPolygonOffset(-1.0f, -1.0f);
//	//glEnable(GL_STENCIL_TEST);
//	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	//glEnable(GL_CULL_FACE);
//
//	Shader shader("v4shader.glsl", "f4shader.glsl");
//	Shader stencilShader("v4shader.glsl", "f4shader_stencil.glsl");
//	Shader screenShder("v4shader_screen.glsl", "f4shader_screen.glsl");
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
//		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
//		- 5.0f, -0.5f, -5.0f,  0.0f, 2.0f
//	};
//	float transparentVertices[] = {
//		// positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
//		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
//		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//
//		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
//		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
//		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
//	};
//	//草的位置
//	vector<glm::vec3> vegetation
//	{
//		glm::vec3(-1.5f, 0.0f, -0.48f),
//		glm::vec3(1.5f, 0.0f, 0.51f),
//		glm::vec3(0.0f, 0.0f, 0.7f),
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
//	//整个屏幕的四边形
//	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
//	// positions   // texCoords
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	-1.0f, -1.0f,  0.0f, 0.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//
//	-1.0f,  1.0f,  0.0f, 1.0f,
//	 1.0f, -1.0f,  1.0f, 0.0f,
//	 1.0f,  1.0f,  1.0f, 1.0f
//	};
//
//	// cube VAO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//	// plane VAO
//	unsigned int planeVAO, planeVBO;
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//	//vegetation
//	//unsigned int transparentVAO, transparentVBO;
//	//glGenVertexArrays(1, &transparentVAO);
//	//glGenBuffers(1, &transparentVBO);
//	//glBindVertexArray(transparentVAO);
//	//glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
//	//glEnableVertexAttribArray(0);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	//glEnableVertexAttribArray(1);
//	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	//glBindVertexArray(0);
//	
//	// screen quad VAO
//	unsigned int quadVAO, quadVBO;
//	glGenVertexArrays(1, &quadVAO);
//	glGenBuffers(1, &quadVBO);
//	glBindVertexArray(quadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//
//	// load textures
//	// -------------
//	unsigned int cubeTexture = loadTexture("./container.jpg");
//	unsigned int floorTexture = loadTexture("./metal.png");
//	unsigned int grassTexture = loadTexture("./grass.png");
//	unsigned int windowTexture = loadTexture("./blending_transparent_window.png");
//
//	// shader configuration
//	// --------------------
//	shader.use();
//	shader.setInt("texture1", 0);
//	screenShder.use();
//	screenShder.setInt("texture1", 0);
//
//	unsigned int frameBufer;
//	glGenFramebuffers(1, &frameBufer);
//	glBindFramebuffer(GL_FRAMEBUFFER, frameBufer);
//	unsigned int textureBufer;
//	glGenTextures(1, &textureBufer);
//	glBindTexture(GL_TEXTURE_2D, textureBufer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
//		SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureBufer, 0);
//
//	unsigned int renderBufer;
//	glGenRenderbuffers(1, &renderBufer);
//	glBindRenderbuffer(GL_RENDERBUFFER, renderBufer);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
//		GL_RENDERBUFFER, renderBufer);
//
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		cout << "FrameBufer not Complete!" << endl;
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
//		//自定义的frameBuf
//		glBindFramebuffer(GL_FRAMEBUFFER, frameBufer);
//		glEnable(GL_DEPTH_TEST);
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//		shader.use();
//		glm::mat4 model = glm::mat4(1.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//		//stencilShader.use();
//		//stencilShader.setMat4("view", view);
//		//stencilShader.setMat4("projection", projection);
//
//		shader.use();
//		//glStencilMask(0x00);
//		// floor
//		glBindVertexArray(planeVAO);
//		glBindTexture(GL_TEXTURE_2D, floorTexture);
//		shader.setMat4("model", glm::mat4(1.0f));
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		glBindVertexArray(0);
//		// cubes
//		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
//		//glStencilMask(0xFF);
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		model = glm::mat4(1.0f);
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		//boder:
//		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//		//glStencilMask(0x00);
//		//glDisable(GL_DEPTH_TEST);
//		//stencilShader.use();
//		//float scale = 1.1f;
//		//glBindVertexArray(cubeVAO);
//		//glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		//model = glm::mat4(1.0f);
//		//model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		//model = glm::scale(model, glm::vec3(scale, scale, scale));
//		//stencilShader.setMat4("model", model);
//		//glDrawArrays(GL_TRIANGLES, 0, 36);
//		//model = glm::mat4(1.0f);
//		//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		//model = glm::scale(model, glm::vec3(scale, scale, scale));
//		//stencilShader.setMat4("model", model);
//		//glDrawArrays(GL_TRIANGLES, 0, 36);
//		//glBindVertexArray(0);
//		//glStencilMask(0xFF);
//		//glEnable(GL_DEPTH_TEST);
//
//		//grass
//		//shader.use();
//		//glBindVertexArray(transparentVAO);
//		//glBindTexture(GL_TEXTURE_2D, grassTexture);
//		//for (GLuint i = 0; i < vegetation.size(); i++)
//		//{
//		//	model = glm::mat4(1.0f);
//		//	model = glm::translate(model, vegetation[i]);
//		//	shader.setMat4("model", model);
//		//	glDrawArrays(GL_TRIANGLES, 0, 6);
//		//}
//
//		//window:
//		//shader.use();
//		//std::map<float, glm::vec3> sorted;
//		//for (unsigned int i = 0; i < windows.size(); i++)
//		//{
//		//	float distance = glm::length(camera.Position - windows[i]);
//		//	sorted[distance] = windows[i];
//		//}
//		//glBindVertexArray(transparentVAO);
//		//glBindTexture(GL_TEXTURE_2D, windowTexture);
//		//for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
//		//{
//		//	model = glm::mat4();
//		//	model = glm::translate(model, it->second);
//		//	shader.setMat4("model", model);
//		//	glDrawArrays(GL_TRIANGLES, 0, 6);
//		//}
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		
//		
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glDisable(GL_DEPTH_TEST);
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//		screenShder.use();
//		glBindVertexArray(quadVAO);
//		glBindTexture(GL_TEXTURE_2D, textureBufer);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &planeVAO);
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &planeVBO);
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
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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