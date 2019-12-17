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

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<Texture> textures;
	vector<unsigned int> indices;

	Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->textures = textures;
		this->indices = indices;

		this->setupMesh();
	}
	void Draw(Shader shader)
	{
		unsigned int diffuseNumber = 1;
		unsigned int specularNumber = 1;
		unsigned int normalNumber = 1;
		unsigned int heightNumber = 1;
		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			string number;
			string name;
			if (name == "texture_diffuse")
				number = to_string(diffuseNumber++);
			else if (name == "texture_specular")
				number = to_string(specularNumber++);
			else if (name == "texture_normal")
				number = to_string(normalNumber++);
			else if (name == "texture_height")
				number = to_string(heightNumber++);

			shader.setInt(("material." + name + number).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

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