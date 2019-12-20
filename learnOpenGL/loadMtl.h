#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Material
{
	string name;//材料名称
	float shinness;//反光度
	glm::vec3 ka;//阴影色
	glm::vec3 kd;//固有色
	glm::vec3 ks;//高光色
	glm::vec3 ke;//放射光
	float Ni;//光密度
	float d;//透明度，或Tr
	int lightModel;//光照模型，0-10
};

class LoadMTL
{
public:
	LoadMTL(string path)
	{
		ifstream mtlFile(path.c_str());
		if (!mtlFile.is_open())
		{
			cout << "读取失败" << endl;
			return;
		}
		string temp;
		while (getline(mtlFile, temp))
		{
			if (temp.empty())
				continue;
			//去除空格
			temp = temp.substr(temp.find_first_not_of(' '), temp.find_last_not_of(' ') + 1);
			if (temp[0] == '#')
				continue;

			if (temp.substr(0, 6) == string("newmtl"))
			{

			}
		}
	}
private:
	vector<Material> materials;
};