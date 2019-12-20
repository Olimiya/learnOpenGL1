#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
GLFWwindow* init();
void drawPointLight(Shader shader);
void setDefaultLight(Shader shader);
void setDesertLight(Shader shader);
void setFactoryLight(Shader shader);
void setHorrorLight(Shader shader);
void setBiochemicalLight(Shader shader);
bool overlap(glm::vec3 a, glm::vec3 b);

#define NR_POINT_LIGHTS 4
#define INIT_DISTANCE 5.0f

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
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f,  -1.0f, -1.0f),
	glm::vec3(2.0f,  2.0f, 2.0f)
};
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
unsigned int lightVAO;
bool gameStart = false;

int main()
{
	GLFWwindow *window = init();

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("vshader_model.glsl", "fshader_model.glsl");

	Shader lampShader("vshader_light.glsl", "fshader_light.glsl");
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Model ourModel("./obj/Space Station Scene.obj");
	Model ourModel1("./nanosuit/nanosuit.obj");
	glm::vec3 robotPos = glm::vec3(0, 0, 0);

	SceneName scene = Olimi;

	bool finish = false;
	while (!glfwWindowShouldClose(window))
	{
		if (finish)
			break;
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (scene)
		{
		case Olimi:
		{
			//画空间站
			ourShader.use();
			//设置光源
			setBiochemicalLight(ourShader);
			ourShader.setVec3("viewPos", camera.Position);
			glm::mat4 projection = glm::perspective(
				glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			ourShader.setMat4("projection", projection);
			ourShader.setMat4("view", view);
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			ourShader.setMat4("model", model);
			ourModel.Draw(ourShader);

			//画追逐者：
			if(gameStart)
			{
				float speed = 1.0f;
				model = glm::mat4(1.0f);
				glm::vec3 dir = glm::normalize(camera.Position - robotPos);
				robotPos = robotPos + dir * speed * deltaTime;
				model = glm::translate(model, robotPos);
				model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
				auto i = std::atan2(camera.Position.x - robotPos.x, camera.Position.z - robotPos.z);
				model = glm::rotate(model, i, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
				ourShader.setMat4("model", model);
				ourModel1.Draw(ourShader);
			}
			else  
				ourModel1.Draw(ourShader);

			//画光源
			drawPointLight(lampShader);

			//判断结束：
			if (gameStart)
			{
				if(overlap(robotPos, camera.Position))
				{
					std::cout << "Game Over!" << std::endl;
					finish = true;
				}
			}
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
	system("pause");
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
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		gameStart = true;
}

GLFWwindow * init()
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
		exit(-1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
	return window;
}

void drawPointLight(Shader shader)
{
	shader.use();
	glm::mat4 projection = glm::perspective(
		glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	shader.setMat4("model", model);
	glBindVertexArray(lightVAO);
	for (unsigned int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}

void setDefaultLight(Shader shader)
{
	shader.use();
	//定向光
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, 0.0f);
	//点光源
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		std::string name = "pointLights[";
		std::string temp;
		std::stringstream ss;
		ss << i;
		ss >> temp;
		name = name + temp + ("].");
		if (i == 0)
			pointLightPositions[i] =
			glm::vec3(camera.Position.x, camera.Position.y + 1.0f, camera.Position.z);
		shader.setVec3(name + "pos", pointLightPositions[i]);
		shader.setVec3(name + "ambient", 0.05f, 0.05f, 0.05f);
		shader.setVec3(name + "diffuse", 0.8f, 0.8f, 0.8f);
		shader.setVec3(name + "specular", 1.0f, 1.0f, 1.0f);
		shader.setFloat(name + "constant", 1.0f);
		shader.setFloat(name + "linear", 0.09f);
		shader.setFloat(name + "quadratic", 0.032f);
	}
	//聚光灯
	shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09f);
	shader.setFloat("spotLight.quadratic", 0.032f);
	shader.setVec3("spotLight.pos", camera.Position);
	shader.setVec3("spotLight.direction", camera.Front);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

void setDesertLight(Shader shader)
{
	glm::vec3 pointLightColors[] = {
	glm::vec3(1.0f, 0.6f, 0.0f),
	glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(1.0f, 1.0, 0.0),
	glm::vec3(0.2f, 0.2f, 1.0f)
	};

	shader.use();
	// Directional light
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.ambient"), 0.3f, 0.24f, 0.14f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.diffuse"), 0.7f, 0.42f, 0.26f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
	// Point light 1
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].pos"), camera.Position.x, camera.Position.y + 1.0f, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].quadratic"), 0.032f);
	// Point light 2
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].pos"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].quadratic"), 0.032f);
	// Point light 3
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].pos"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].quadratic"), 0.032f);
	// Point light 4
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].pos"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].quadratic"), 0.032f);
	// SpotLight
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.pos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.diffuse"), 0.8f, 0.8f, 0.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.specular"), 0.8f, 0.8f, 0.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(13.0f)));
}

void setFactoryLight(Shader shader)
{
	glm::vec3 pointLightColors[] = {
	glm::vec3(0.2f, 0.2f, 0.6f),
	glm::vec3(0.3f, 0.3f, 0.7f),
	glm::vec3(0.0f, 0.0f, 0.3f),
	glm::vec3(0.4f, 0.4f, 0.4f)
	};

	shader.use();
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.ambient"), 0.05f, 0.05f, 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.diffuse"), 0.2f, 0.2f, 0.7f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.specular"), 0.7f, 0.7f, 0.7f);
	// Point light 1
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].pos"), camera.Position.x, camera.Position.y + 1.0f, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].quadratic"), 0.032f);
	// Point light 2
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].pos"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].quadratic"), 0.032f);
	// Point light 3
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].pos"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].quadratic"), 0.032f);
	// Point light 4
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].pos"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].quadratic"), 0.032f);
	// SpotLight
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.pos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.linear"), 0.009f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.quadratic"), 0.0032f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(12.5f)));
}

void setHorrorLight(Shader shader)
{
	glm::vec3 pointLightColors[] = {
	glm::vec3(0.1f, 0.1f, 0.1f),
	glm::vec3(0.1f, 0.1f, 0.1f),
	glm::vec3(0.1f, 0.1f, 0.1f),
	glm::vec3(0.3f, 0.1f, 0.1f)
	};

	shader.use();
	// Directional light
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.diffuse"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
	// Point light 1
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].position"), camera.Position.x, camera.Position.y + 1.0f, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].linear"), 0.14f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].quadratic"), 0.07f);
	// Point light 2
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].linear"), 0.14f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].quadratic"), 0.07f);
	// Point light 3
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].linear"), 0.22f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].quadratic"), 0.20f);
	// Point light 4
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].linear"), 0.14f);
	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].quadratic"), 0.07f);
	// SpotLight
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.quadratic"), 0.032f);
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.cutOff"), glm::cos(glm::radians(10.0f)));
	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
}

void setBiochemicalLight(Shader shader)
{
	glm::vec3 pointLightColors[] = {
	glm::vec3(0.4f, 0.7f, 0.1f),
	glm::vec3(0.4f, 0.7f, 0.1f),
	glm::vec3(0.4f, 0.7f, 0.1f),
	glm::vec3(0.4f, 0.7f, 0.1f)
	};

	shader.use();
	// Directional light

	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);

	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);

	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.diffuse"), 1.0f, 1.0f, 1.0f);

	glUniform3f(glGetUniformLocation(shader.ID, "dirLight.specular"), 1.0f, 1.0f, 1.0f);
	// Point light 1

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].position"), camera.Position.x, camera.Position.y + 1.0f, camera.Position.z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1f, pointLightColors[0].y * 0.1f, pointLightColors[0].z * 0.1f);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].diffuse"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[0].specular"), pointLightColors[0].x, pointLightColors[0].y, pointLightColors[0].z);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].linear"), 0.07f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[0].quadratic"), 0.017f);
	// Point light 2

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1f, pointLightColors[1].y * 0.1f, pointLightColors[1].z * 0.1f);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].diffuse"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[1].specular"), pointLightColors[1].x, pointLightColors[1].y, pointLightColors[1].z);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].linear"), 0.07f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[1].quadratic"), 0.017f);
	// Point light 3

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1f, pointLightColors[2].y * 0.1f, pointLightColors[2].z * 0.1f);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].diffuse"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[2].specular"), pointLightColors[2].x, pointLightColors[2].y, pointLightColors[2].z);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].linear"), 0.07f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[2].quadratic"), 0.017f);
	// Point light 4

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1f, pointLightColors[3].y * 0.1f, pointLightColors[3].z * 0.1f);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].diffuse"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);

	glUniform3f(glGetUniformLocation(shader.ID, "pointLights[3].specular"), pointLightColors[3].x, pointLightColors[3].y, pointLightColors[3].z);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].linear"), 0.07f);

	glUniform1f(glGetUniformLocation(shader.ID, "pointLights[3].quadratic"), 0.017f);
	// SpotLight

	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);

	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);

	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);

	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.diffuse"), 0.0f, 1.0f, 0.0f);

	glUniform3f(glGetUniformLocation(shader.ID, "spotLight.specular"), 0.0f, 1.0f, 0.0f);

	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.linear"), 0.07f);

	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.quadratic"), 0.017f);

	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.cutOff"), glm::cos(glm::radians(7.0f)));

	glUniform1f(glGetUniformLocation(shader.ID, "spotLight.outerCutOff"), glm::cos(glm::radians(10.0f)));
}

bool overlap(glm::vec3 a, glm::vec3 b)
{
	if (abs(a.x - b.x) < pow(0.1, 1) && abs(a.y - b.y) < pow(0.1, 1) && abs(a.z - b.z) < pow(0.1, 1))
		return true;
	else
		return false;
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
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}