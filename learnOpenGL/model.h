#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "stb_image.h"

unsigned int TextureFromFile(const char* path, const char* directory, bool gamma = false);

class Model
{
public:
	Model(string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}
	void Draw(Shader shader)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
			meshes[i].Draw(shader);
	}

private:
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	unsigned int whiteTexture;

	void loadModel(string const &path)
	{
		Assimp::Importer im;
		const aiScene *scene = im.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP:: " << im.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0, path.find_last_of("/"));

		whiteTexture = TextureFromFile("white.bmp", "./");
		processNode(scene->mRootNode, scene);
	}
	void processNode(aiNode* node, const aiScene* scene)
	{
		for (int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			Mesh ourMesh = processMesh(mesh, scene);
			this->meshes.push_back(ourMesh);
		}
		for (int i = 0; i < node->mNumChildren; i++)
			processNode(node->mChildren[i], scene);
	}
	Mesh processMesh(aiMesh* mesh, const aiScene* scene)
	{
		vector<Vertex> vertices;
		vector<Texture> textures;
		//默认都至少会有一张白色的贴图
		Texture texture;
		texture.id = whiteTexture;
		texture.name = "white";
		texture.path = "./white.bmp";
		textures.push_back(texture);
		vector<unsigned int> indices;
		Material matAttr;
		matAttr.ka = glm::vec3(1.0f, 0.5f, 0.31f);
		matAttr.kd = glm::vec3(1.0f, 0.5f, 0.31f);
		matAttr.ks = glm::vec3(0.5f, 0.5f, 0.5f);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 position;
			glm::vec3 normal;
			glm::vec2 texCoord;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;

			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;
			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;
			
			if (mesh->mTextureCoords[0])
			{
				texCoord.x = mesh->mTextureCoords[0][i].x;
				texCoord.y = mesh->mTextureCoords[0][i].y;
			}
			else
				texCoord = glm::vec2(0.0f, 0.0f);

			// tangent
			//Tangent.x = mesh->mTangents[i].x;
			//Tangent.y = mesh->mTangents[i].y;
			//Tangent.z = mesh->mTangents[i].z;
			//// bitangent
			//Bitangent.x = mesh->mBitangents[i].x;
			//Bitangent.y = mesh->mBitangents[i].y;
			//Bitangent.z = mesh->mBitangents[i].z;

			vertex.position = position;
			vertex.normal = normal;
			vertex.texCoord = texCoord;
			vertex.Tangent = Tangent;
			vertex.Bitangent = Bitangent;

			vertices.push_back(vertex);
		}
	
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		if (mesh->mMaterialIndex > 0)
		{
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			//1. diffuse maps
			vector<Texture> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// 2. specular maps
			vector<Texture> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// 3. normal maps
			std::vector<Texture> normalMaps = loadMaterialTextures(material,
				aiTextureType_HEIGHT, "texture_normal");
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// 4. height maps
			std::vector<Texture> heightMaps = loadMaterialTextures(material,
				aiTextureType_AMBIENT, "texture_height");
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

			aiColor3D color;
			glm::vec3 temp;
			material->Get(AI_MATKEY_COLOR_AMBIENT, color);
			temp.r = color.r;
			temp.g = color.g;
			temp.b = color.b;
			matAttr.ka = temp;
			material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			temp.r = color.r;
			temp.g = color.g;
			temp.b = color.b;
			matAttr.kd = temp;
			material->Get(AI_MATKEY_COLOR_SPECULAR, color);
			temp.r = color.r;
			temp.g = color.g;
			temp.b = color.b;
			matAttr.ks = temp;
			float shinness;
			material->Get(AI_MATKEY_SHININESS, shinness);
			matAttr.shiness = shinness / 4;
			//auto i = aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shinness);

			//material->Get(AI_MATKEY_SHININESS_STRENGTH, shinness);
		}
		return Mesh(vertices, textures, indices, matAttr);
	}
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0; j < this->textures_loaded.size(); j++)
				if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					skip = true;
					break;
				}

			if(!skip)
			{
				Texture texture;
				unsigned int id = TextureFromFile(str.C_Str(), directory.c_str());
				texture.id = id;
				texture.path = str.C_Str();
				texture.name = typeName;
				textures.push_back(texture);
				textures_loaded.push_back(texture);
			}
		}
		return textures;
	}

};

unsigned int TextureFromFile(const char * path, const char * directory, bool gamma)
{
	string fileName = string(directory) + "/" + string(path);
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
