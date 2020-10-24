#pragma once
#include <vector>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Scene.h"
#include "Camera.h"
#include "global.h"
#include <math.h>
#include <unordered_map>
#include "MazeMap.h"
#include <algorithm>

class World
{
public:
	World();
	World(int x, int y, int z);
	~World();

	void WorldSceneInit();
	void WorldSceneRender();
	void WorldScreenSize(int width = 0, int height = 0);
	void WorldMapInit(glm::ivec2 ground, glm::ivec2 playground, glm::ivec2 maze);
	void WorldMapChangeLevel(int i);

	void WorldsetLevel(std::unordered_map<int, std::vector<glm::ivec2>>& info);

	void WorldInsertScene(Scene* single_Scene);
	void WorldInitCamera(glm::vec3 postion);
	void WorldResetCamera(glm::vec3 postion);
	void Worldkeyboard(Camera_Movement direction);
	void WorldGravity(bool havegravity);
	void WorldLockCameraPitch(bool islockpitch);
	void WorldUpdateLOC();
	void WorldUpdateTexture();
	Camera* getCamera();

private:
	glm::ivec3 worldsize;
	glm::ivec3 worldcenterLoc;
	int ScreenWidth;
	int ScreenHeight;
	int currentLevel;
	glm::vec3 init_camera_position;
	std::unordered_map<int, std::vector<glm::ivec2>> LevelInfo;
	bool*** isblock;
	bool havegravity;
	bool isfalling;
	glm::vec3 endpoint;
	Camera * camera;
	MazeMap * map;
	std::vector<Scene*> SceneList;
	std::vector<std::vector<glm::vec3>> PositionList;

	bool iscollision(glm::vec3 &nextposition, float tolerance);
	bool isfindendpoint(glm::vec3 &nextposition, float tolerance);
};

