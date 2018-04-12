#pragma once
#include<glad\glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include<string>
#include<vector>
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;  // ������
	glm::vec2 texCoords; // ��������
	

};

class Mesh
{
public:
	std::vector<unsigned int>indices;
	std::vector<glm::vec3> positionv;//miaomaipmia
	Mesh(std::string path) {
		std::vector<glm::vec3> temp_position;
		std::vector<glm::vec2> temp_texCoords;
		std::vector<glm::vec3> temp_normal;
		
		std::ifstream file(path);
		std::string line;
		while (std::getline(file, line))
		{
			if (line.substr(0, 2) == "vt") // ����������������
			{
				std::istringstream s(line.substr(2));
				glm::vec2 v;
				s >> v.x;
				s >> v.y;
				v.y = -v.y; 
				temp_texCoords.push_back(v);

				// ����������������
			}
			else if (line.substr(0, 2) == "vn") // ���㷨��������
			{
				std::istringstream s(line.substr(2));
				glm::vec3 n;
				s >> n.x;
				s >> n.y;
				s >> n.z;
				temp_normal.push_back(n);
				// ��������������
			}
			else if (line.substr(0, 1) == "v") // ����λ������
			{
				std::istringstream s(line.substr(1));
				glm::vec3 v;
				s >> v.x;
				s >> v.y;
				s >> v.z;
				temp_position.push_back(v);
				// ��������λ������
			}
			else if (line.substr(0, 1) == "f") // ������
			{
				std::istringstream s(line.substr(1));
				unsigned int f;
				s >> f;
				indices.push_back(f);
				s >> f;
				indices.push_back(f);
				s >> f;
				indices.push_back(f);
				// ����������
			}
			else if (line[0] == '#') // ע�ͺ���
			{
			}
			else
			{
				// �������� ��ʱ������
			}//199798,xy
		}
		for (int i = 0; i < temp_position.size(); i++) {
			
			Vertex a;
			vertData.push_back(a);
			vertData[i].position = temp_position[i];
		}
		for (int i = 0; i < temp_normal.size(); i++) {
			vertData[i].normal = temp_normal[i];
		}
		for (int i = 0; i < temp_texCoords.size(); i++) {
			vertData[i].texCoords = temp_texCoords[i];
		}
		for (unsigned int i = 0; i < indices.size(); i++) {
			glm::vec3 vertexlll = temp_position[indices[i] - 1];
			positionv.push_back(vertexlll);
		}
		setupMesh();
	};

	void draw(Shader& shader) {

		glBindVertexArray(VAOId);
		
		glDrawArrays(GL_TRIANGLES, 0, positionv.size());
		
		glBindVertexArray(0);
	};// ����Mesh
		
private:

	std::vector<Vertex> vertData;// ��������
	GLuint VAOId, VBOId; // �������
	
	void setupMesh() {
		glGenVertexArrays(1, &this->VAOId);
		glGenBuffers(1, &this->VBOId);

		glBindVertexArray(this->VAOId);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBOId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)* this->positionv.size(),
			&this->positionv[0], GL_STATIC_DRAW);
		// ����λ������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			sizeof(glm::vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);

	/*	// ���㷨��������
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (GLvoid*)(3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);
		// ������������
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (GLvoid*)(5 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);*/

	};  // ����VAO,VBO�Ȼ�����
};
