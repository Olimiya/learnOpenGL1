#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shader.h"

using namespace std;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
	// tangent切线
	glm::vec3 Tangent;
	// bitangent双切线
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string name;
	string path;
};

struct Material
{
	float shiness;
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;
	Material material;

	Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<unsigned int> indices, Material material)
	{
		this->vertices = vertices;
		this->textures = textures;
		this->indices = indices;
		this->material = material;

		this->setupMesh();
	}
	void Draw(Shader shader)
	{
		shader.setBool("hasAmbient", false);
		shader.setBool("hasSpecular", false);
		shader.setBool("hasDiffuse", false);

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			string name = textures[i].name;
			if (name == "texture_ambient")
				shader.setBool("hasAmbient", true);
			else if (name == "texture_diffuse")
				shader.setBool("hasDiffuse", true);
			else if (name == "texture_specular")
				shader.setBool("hasSpecular", true);
			//else if (name == "texture_normal")
			//	number = to_string(normalNumber++);
			//else if (name == "texture_height")
			//	number = to_string(heightNumber++);

			glActiveTexture(GL_TEXTURE0 + i);
			shader.setInt(("material." + name).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		//传入材质
		shader.setVec3("material.ka", material.ka);
		shader.setVec3("material.kd", material.kd);
		shader.setVec3("material.ks", material.ks);
		shader.setFloat("material.shininess", material.shiness);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
	}

private:
	GLuint VAO, VBO, VEO;
	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VEO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(),
			&indices[0], GL_STATIC_DRAW);

		//顶点 v
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//法向量 vn
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		//纹理坐标 f
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		//切线
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		//双切线
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
	}
};