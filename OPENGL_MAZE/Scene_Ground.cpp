#include "Scene_Ground.h"



Scene_Ground::Scene_Ground()
{
}

Scene_Ground::Scene_Ground(string & texture_path, string & framget_path, string & vertex_path)
{
	this->add_shader(framget_path, vertex_path);
	this->add_single_texture(texture_path);
}

Scene_Ground::Scene_Ground(std::vector<string> texture_paths, string & framget_path, string & vertex_path)
{
	this->add_shader(framget_path, vertex_path);
	for (auto path : texture_paths) {
		this->add_single_texture(path);
	}
}


Scene_Ground::~Scene_Ground()
{
}

void Scene_Ground::init_Scene()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->Cubevertices), this->Cubevertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	this->LoadTexture();
}

void Scene_Ground::render_Scene(glm::mat4 view, glm::mat4 projection, glm::mat4 model)
{
	if (sceneLocList.empty()) exit(0);

	glUseProgram(this->shader);

	glBindVertexArray(this->VAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(this->shader, "ourTexture1"), 0);
	glBindTexture(GL_TEXTURE_2D, this->textures_index);
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	for (int i = 0; i < this->sceneLocList.size(); i++) {
		glm::mat4 model;
		model = glm::translate(model, this->sceneLocList[i]);
		glUniformMatrix4fv(glGetUniformLocation(this->shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}

void Scene_Ground::LoadTexture()
{
	glGenTextures(1, &this->textures_index);
	glBindTexture(GL_TEXTURE_2D, this->textures_index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	//generate a random index of texture
	int s = this->textures.size();
	int index = rand() % (s - 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->textures[index].width, this->textures[index].height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->textures[index].getImage());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

