#pragma once
#include "GL/glew.h"
#include "GLFw/glfw3.h"
#include "Texture.h"
#include "Shader.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
using namespace std;
class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void init_Scene() = 0;
	virtual void render_Scene(glm::mat4 view, glm::mat4 projection, glm::mat4 model)= 0;
	virtual void LoadTexture() = 0;
	void SetsceneLoc(vector<glm::vec3>& list);
	vector<glm::vec3> GetsceneLoc();
	int texture_count = 0;
private:

protected:
	GLuint VAO;
	GLuint VBO;
	GLuint textures_index;
	GLuint shader;
	vector<Texture> textures;
	vector<glm::vec3> sceneLocList;
	void add_single_texture(string& texture_path);
	void add_shader(string & framget_path, string& vertex_path);
	vector<glm::vec3> getLocList();

	
};

