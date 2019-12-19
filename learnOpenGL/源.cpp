#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

#define NR_POINT_LIGHTS 4

enum SceneName
{
	Olimi, SICONG, HUANG, OU
};

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("vshader_model.glsl", "fshader_model.glsl");

	// load models
	// -----------
	Model ourModel("./obj/Space Station Scene.obj");
	//Model ourModel("./nanosuit/nanosuit.obj");

	SceneName scene = Olimi;

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (scene)
		{
		case Olimi:
		{
			ourShader.use();
			//设置光源
			//定向光
			ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
			ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
			ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
			ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
			//点光源
			for (int i = 0; i < NR_POINT_LIGHTS; i++)
			{
				std::string name = "pointLights[";
				std::string temp;
				std::stringstream ss;
				ss << i;
				ss >> temp;
				name = name + temp + ("].");
				ourShader.setVec3(name + "pos", pointLightPositions[i]);
				ourShader.setVec3(name + "ambient", 0.05f, 0.05f, 0.05f);
				ourShader.setVec3(name + "diffuse", 0.8f, 0.8f, 0.8f);
				ourShader.setVec3(name + "specular", 1.0f, 1.0f, 1.0f);
				ourShader.setFloat(name + "constant", 1.0f);
				ourShader.setFloat(name + "linear", 0.09);
				ourShader.setFloat(name + "quadratic", 0.032);
			}
			//聚光灯
			ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
			ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
			ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
			ourShader.setFloat("spotLight.constant", 1.0f);
			ourShader.setFloat("spotLight.linear", 0.09);
			ourShader.setFloat("spotLight.quadratic", 0.032);
			ourShader.setVec3("spotLight.pos", camera.Position);
			ourShader.setVec3("spotLight.direction", camera.Front);
			ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
			ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

			ourShader.setVec3("viewPos", camera.Position);

			// view/projection transformations
			glm::mat4 projection = glm::perspective(
				glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			ourShader.setMat4("projection", projection);
			ourShader.setMat4("view", view);

			// render the loaded model
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			ourShader.setMat4("model", model);
			ourModel.Draw(ourShader);
		}
			break;
		case SICONG:
			break;
		case HUANG:
			break;
		case OU:
			break;
		default:
			break;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}