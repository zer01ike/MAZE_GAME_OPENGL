#include "Scene.h"



Scene::Scene()
{
	/*this->init_Scene();*/
}


Scene::~Scene()
{
}

void Scene::init_Scene()
{
}

void Scene::render_Scene(glm::mat4 view, glm::mat4 projection, glm::mat4 model)
{

}

void Scene::SetsceneLoc(vector<glm::vec3>& list)
{
	this->sceneLocList = list;
}

vector<glm::vec3> Scene::GetsceneLoc()
{
	return this->sceneLocList;
}


void Scene::add_single_texture(string & texture_path)
{
	Texture p_texture(texture_path);
	this->textures.push_back(p_texture);
}

void Scene::add_shader(string & framget_path, string & vertex_path)
{
	const char * vertex = vertex_path.c_str();
	const char * fragment = framget_path.c_str();
	this->shader = Shader::create_program(const_cast<char*>(vertex), const_cast<char*>(fragment));
}

vector<glm::vec3> Scene::getLocList()
{
	return sceneLocList;
}

