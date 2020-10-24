#include "Scene_Skybox.h"

Scene_Skybox::Scene_Skybox(string& texture_path,string & framget_path, string& vertex_path)
{
	this->add_shader(framget_path, vertex_path);
	this->add_single_texture(texture_path);
}

Scene_Skybox::Scene_Skybox(vector<string>& texture_paths, string & framget_path, string& vertex_path)
{
	this->add_shader(framget_path, vertex_path);
	for (auto path : texture_paths) {
		this->add_single_texture(path);
	}	
}

Scene_Skybox::~Scene_Skybox()
{
}

void Scene_Skybox::init_Scene()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(this->skyboxVertices), this->skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glBindVertexArray(0);

	this->LoadTexture();
}

void Scene_Skybox::render_Scene(glm::mat4 view, glm::mat4 projection, glm::mat4 model)
{
	//chage the view to unable to move
	view = glm::mat4(glm::mat3(view));

	glDepthMask(GL_FALSE);
	glUseProgram(this->shader);

	glUniformMatrix4fv(glGetUniformLocation(this->shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(this->VAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(this->shader, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textures_index);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}

void Scene_Skybox::LoadTexture()
{
	glGenTextures(1, &this->textures_index);
	glBindTexture(GL_TEXTURE_2D, this->textures_index);
	glActiveTexture(GL_TEXTURE0);
	int col = this->textures.size() / 6;
	int index = rand() % (col - 1);
	int size = this->textures.size();
	int count = 0;
	for (GLuint i = index * 6; i < 6 * (index + 1) ; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + count, 0, GL_RGBA, this->textures[i].width, this->textures[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textures[i].getImage());
		count++;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}
