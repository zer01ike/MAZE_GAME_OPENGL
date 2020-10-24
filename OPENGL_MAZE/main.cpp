#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include "GL/glew.h"
#include "GLFw/glfw3.h"
#include "GL/glut.h"
#include "global.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Scene_Skybox.h"
#include "Scene_Ground.h"
#include "Scene_Wall.h"
#include "World.h"

#include "main.h"
//#include "freetype/ft2build.h"
//#include <GL/freeglut.h>

#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define KEY_E 101

int screenWidth = 1024, screenHeight = 768;
glm::vec3 init_camera_position(3.0f, 10.0f, 1.0f);
int current_level = 0;
std::vector<string> sky_textures;
string sky_frag;
string sky_vertex;
Scene_Skybox* skybox;

std::vector<string> ground_textures;
string ground_frag;
string ground_vertex;
Scene_Ground* ground;

std::vector<string> wall_textures;
string wall_frag;
string wall_vertex;
Scene_Wall* wall;

std::vector<string> outwall_textures;
std::string outwall_frag ;
std::string outwall_vertex;
Scene_Wall* outwall;


std::vector<string> endpoint_textures;
std::string endpoint_frag;
std::string endpoint_vertex;
Scene_Wall* endpoint;

World GAMEWorld(1000,1000,1000);



std::unordered_map<int, std::vector<glm::ivec2>> info;


static void idle() {
	glutPostRedisplay();
}

void key_callback(unsigned char key,int x, int y) {

	switch (key) {
	case KEY_LEFT:
		GAMEWorld.Worldkeyboard(LEFT);
		std::cout << "LEFT is passed  " << glm::to_string(GAMEWorld.getCamera()->getPosition()) << std::endl;
		break;
	case KEY_RIGHT:
		GAMEWorld.Worldkeyboard(RIGHT);
		std::cout << "RIGHT is passed  " <<glm::to_string(GAMEWorld.getCamera()->getPosition())<< std::endl;
		break;
	case KEY_UP:
		GAMEWorld.Worldkeyboard(FORWARD);
		std::cout << "UP is passed  " << glm::to_string(GAMEWorld.getCamera()->getPosition()) << std::endl;
		break;
	case KEY_DOWN:
		GAMEWorld.Worldkeyboard(BACKWARD);
		std::cout << "DOWN is passed  " << glm::to_string(GAMEWorld.getCamera()->getPosition()) << std::endl;
		break;
	case KEY_E:
		std::cout << "E is passed" << std::endl;
		GAMEWorld.WorldResetCamera(init_camera_position);
		GAMEWorld.WorldMapChangeLevel(current_level);
		current_level++;
		GAMEWorld.WorldUpdateLOC();
		GAMEWorld.WorldUpdateTexture();
		break;

	}
}

bool mouse_initial = false;
int lastposX = 0;
int lastposY = 0;
GLfloat yaw;
GLfloat pitch;
static void mouse_callback(int button, int state, int x, int y) {
	//if (stat != GLUT_DOWN) return;

	if (!mouse_initial) {
		lastposX = x;
		lastposY = y;
		mouse_initial = true;
	}

	// wheel function
	if ((button == 3) || (button == 4)) {

	}
	else {
		// other function
		GLuint xoffset = x - lastposX;
		GLuint yoffset = y - lastposY;

		lastposX = x;
		lastposY = y;

		GAMEWorld.getCamera()->updateFront(GLfloat(xoffset), GLfloat(yoffset));
	}

}

//float startx = 40.0f;
//float starty = 30.0f;
//float startz = 0.0f;
static void motion_callback(int x, int y) {
	float xoffset = x - screenWidth / 2;
	float yoffset = y - screenHeight / 2;
	GAMEWorld.getCamera()->updateFront(xoffset,yoffset);

	/*starty += 0.01f;
	startz -= 0.1f;

	GAMEWorld.getCamera()->UpdatePosition(glm::vec3(startx, starty, startz));*/
	glutWarpPointer(screenWidth / 2, screenHeight / 2);


}

void render() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);

	GAMEWorld.WorldSceneRender();

	glutSwapBuffers();
}

void LOADPARAMATER() {
	//skybox 1
	sky_textures.push_back("Texture/right1.png");
	sky_textures.push_back("Texture/left1.png");
	sky_textures.push_back("Texture/up1.png");
	sky_textures.push_back("Texture/down1.png");
	sky_textures.push_back("Texture/back1.png");
	sky_textures.push_back("Texture/front1.png");
	//skybox 2
	sky_textures.push_back("Texture/right2.jpg");
	sky_textures.push_back("Texture/left2.jpg");
	sky_textures.push_back("Texture/up2.jpg");
	sky_textures.push_back("Texture/down2.jpg");
	sky_textures.push_back("Texture/back2.jpg");
	sky_textures.push_back("Texture/front2.jpg");
	//skybox 3
	sky_textures.push_back("Texture/right3.jpg");
	sky_textures.push_back("Texture/left3.jpg");
	sky_textures.push_back("Texture/up3.jpg");
	sky_textures.push_back("Texture/down3.jpg");
	sky_textures.push_back("Texture/back3.jpg");
	sky_textures.push_back("Texture/front3.jpg");
	//skybox 4
	sky_textures.push_back("Texture/right4.jpg");
	sky_textures.push_back("Texture/left4.jpg");
	sky_textures.push_back("Texture/up4.jpg");
	sky_textures.push_back("Texture/down4.jpg");
	sky_textures.push_back("Texture/back4.jpg");
	sky_textures.push_back("Texture/front4.jpg");
	sky_frag = "Shader/SkyBox.fragment";
	sky_vertex = "Shader/SkyBox.vertex";

	//ground paramater
	ground_textures.push_back("Texture/ground1.jpg");
	ground_textures.push_back("Texture/ground2.jpg");
	ground_textures.push_back("Texture/ground3.jpg");
	ground_textures.push_back("Texture/ground4.jpg");
	ground_textures.push_back("Texture/ground5.jpg");
	ground_frag = "Shader/cube.fragment";
	ground_vertex = "Shader/cube.vertex";

	//outWall paramater

	outwall_textures.push_back("Texture/outwall1.jpg");
	outwall_textures.push_back("Texture/outwall2.jpg");
	outwall_textures.push_back("Texture/outwall3.jpg");
	outwall_textures.push_back("Texture/outwall4.jpg");
	outwall_textures.push_back("Texture/outwall5.jpg");
	outwall_textures.push_back("Texture/outwall6.jpg");
	outwall_frag = ground_frag;
	outwall_vertex = ground_vertex;

	//wall paramater
	wall_textures.push_back("Texture/wall1.jpg");
	wall_textures.push_back("Texture/wall2.jpg");
	wall_textures.push_back("Texture/wall3.jpg");
	wall_textures.push_back("Texture/wall4.jpg");
	wall_textures.push_back("Texture/wall5.jpg");
	wall_textures.push_back("Texture/wall6.jpg");
	wall_frag = ground_frag;
	wall_vertex = ground_vertex;

	//endpoint paramater
	endpoint_textures.push_back("Texture/endpoint1.jpg");
	endpoint_textures.push_back("Texture/endpoint2.jpg");
	endpoint_textures.push_back("Texture/endpoint3.jpg");
	endpoint_textures.push_back("Texture/endpoint4.jpg");
	endpoint_textures.push_back("Texture/endpoint5.jpg");
	endpoint_textures.push_back("Texture/endpoint6.jpg");
	endpoint_frag = ground_frag;
	endpoint_vertex = ground_vertex;

	//ground playground mazeground
	info[0] = std::vector<glm::ivec2>{ glm::ivec2(30, 30), glm::ivec2(10,10),glm::ivec2(7,7) };
	info[1] = std::vector<glm::ivec2>{ glm::ivec2(40, 40), glm::ivec2(15,15),glm::ivec2(13,13) };
	info[2] = std::vector<glm::ivec2>{ glm::ivec2(40, 40), glm::ivec2(20,20),glm::ivec2(17,17) };
	info[3] = std::vector<glm::ivec2>{ glm::ivec2(60, 60), glm::ivec2(24,24),glm::ivec2(23,23) };
	info[4] = std::vector<glm::ivec2>{ glm::ivec2(80, 80), glm::ivec2(30,30),glm::ivec2(29,29) };
	info[5] = std::vector<glm::ivec2>{ glm::ivec2(80, 80), glm::ivec2(38,38),glm::ivec2(37,37) };
	info[6] = std::vector<glm::ivec2>{ glm::ivec2(90, 90), glm::ivec2(42,42),glm::ivec2(41,41) };
	info[7] = std::vector<glm::ivec2>{ glm::ivec2(100, 100), glm::ivec2(50,50),glm::ivec2(49,49) };
}

void Init() {

	GAMEWorld.WorldMapInit(info[0][0], info[0][1], info[0][2]);
	GAMEWorld.WorldsetLevel(info);
	skybox = new Scene_Skybox(sky_textures, sky_frag, sky_vertex);
	ground = new Scene_Ground(ground_textures, ground_frag, ground_vertex);
	//ground->SetsceneLoc();
	outwall = new Scene_Wall(outwall_textures, outwall_frag, outwall_vertex);
	//outwall->SetsceneLoc(OutWallpositions);
	wall = new Scene_Wall(wall_textures, wall_frag, wall_vertex);
	//wall->SetsceneLoc(Wallpositions);

	endpoint = new Scene_Wall(endpoint_textures, endpoint_frag, endpoint_vertex);

	//init world
	GAMEWorld.WorldInsertScene(skybox);
	GAMEWorld.WorldInsertScene(ground);
	GAMEWorld.WorldInsertScene(wall);
	GAMEWorld.WorldInsertScene(outwall);
	GAMEWorld.WorldInsertScene(endpoint);
	GAMEWorld.WorldUpdateLOC();
	GAMEWorld.WorldScreenSize(screenWidth, screenHeight);
	GAMEWorld.WorldInitCamera(init_camera_position);
	//GAMEWorld.WorldInitCamera(glm::vec3(startx, starty, startz));
	GAMEWorld.WorldGravity(true);
	GAMEWorld.WorldLockCameraPitch(true);
	/*GAMEWorld.WorldGravity(true);
	GAMEWorld.WorldLockCameraPitch(true);*/
	GAMEWorld.WorldSceneInit();
	
}

int new_test(int argc, char* argv[]) {

	LOADPARAMATER();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("MAZE");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(glew_status) << std::endl;
		return 1;
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	
	Init();

	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutKeyboardFunc(key_callback);
	glutIdleFunc(idle);
	/*glutMouseFunc(mouse_callback);*/
	glutMotionFunc(motion_callback);
	glutMainLoop();
}

int main(int argc, char* argv[]) {
	//test_loop(argc,argv);
	

	
	new_test(argc, argv);

	/*unsigned char key = 96;
	cout << key << endl;
	key |= 4;
	cout << key << endl;
	key &= ~4;
	cout << key << endl;
	cin >> key;*/
	return 0;
}