#include "World.h"

World::World()
{
}

World::World(int x, int y, int z):isfalling(false)
{
	worldsize.x = x;
	worldsize.y = y;
	worldsize.z = z;

	worldcenterLoc.x = x / 2;
	worldcenterLoc.y = y / 2;
	worldcenterLoc.z = z / 2;

	this->isblock = new bool**[worldsize.x];
	this->currentLevel = 0;
	for (int i = 0; i < worldsize.x; i++) {
		this->isblock[i] = new bool*[worldsize.y];
	}
	for (int i = 0; i < worldsize.x; i++) {
		for (int j = 0; j < worldsize.y; j++) {
			this->isblock[i][j] = new bool[worldsize.z];
		}
	}

	for (int i = 0; i < worldsize.x; i++) {
		for (int j = 0; j < worldsize.y; j++) {
			for (int m = 0; m < worldsize.z; m++) isblock[i][j][m] = false;
		}
	}
}


World::~World()
{
}

void World::WorldSceneInit()
{
	for (auto i : this->SceneList) {
		i->init_Scene();
		//make sure the i->setloclist is used
		this->PositionList.push_back(i->GetsceneLoc());
	}
	for (auto i : this->PositionList) {
		for (auto loc : i) {
			this->isblock[int(loc.x)+worldcenterLoc.x][int(loc.y)+worldcenterLoc.y][int(loc.z)+worldcenterLoc.z] = true;
		}
	}
}

void World::WorldSceneRender()
{
	if (isfalling && havegravity) {
		glm::vec3 next = this->camera->getPosition();
		//¸Ä±äº¯Êý
		next.y = next.y - 0.2f;
		
		if (next.y > 1.0f) {
			this->camera->UpdatePosition(next);
		}
		else {
			isfalling = false;
		}
	}
	glm::mat4 view = this->camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(this->camera->Zoom, (float)this->ScreenWidth / (float)this->ScreenHeight, 0.1f, 100.0f);
	glm::mat4 model;
	for (auto i : this->SceneList) {
		i->render_Scene(view, projection, model);
	}
}

void World::WorldScreenSize(int width, int height)
{
	this->ScreenWidth = width;
	this->ScreenHeight = height;
}

void World::WorldMapInit(glm::ivec2 ground, glm::ivec2 playground, glm::ivec2 maze)
{
	this->map = new MazeMap(ground,playground,maze);
}

void World::WorldMapChangeLevel(int i)
{
	if (LevelInfo.count(i)) {
		std::vector<glm::ivec2> levellist = LevelInfo[i];
		this->map->updateMaze(levellist[0], levellist[1], levellist[2]);
	}
	else {
		std::cout << "Ending......" << std::endl;
		exit(0);
	}

}

void World::WorldsetLevel(std::unordered_map<int, std::vector<glm::ivec2>>& info)
{
	this->LevelInfo = info;
}

void World::WorldInsertScene(Scene * single_Scene)
{
	this->SceneList.push_back(single_Scene);
}

void World::WorldInitCamera(glm::vec3 postion)
{
	this->init_camera_position = postion;
	this->camera = new Camera(postion);
}

void World::WorldResetCamera(glm::vec3 postion)
{
	this->camera->UpdatePosition(postion);
}

void World::Worldkeyboard(Camera_Movement direction)
{
	glm::vec3 nextposition = this->camera->NextPostion(direction);
	if (havegravity) {
		if (!isfalling) {
			if (!iscollision(nextposition, 0.57f)) {
				if (nextposition.y > 1.2f) isfalling = true;
				if (nextposition.y <= 1.0f) nextposition.y = 1.0f;
				//nextposition.y = nextposition.y > 1.0f ? nextposition.y : 1.0f;
				this->camera->UpdatePosition(nextposition);
			}
		}
	} else{
		if (!iscollision(nextposition, 0.57f)) {
			nextposition.y = nextposition.y > 1.0f ? nextposition.y : 1.0f;
			this->camera->UpdatePosition(nextposition);
		}
			
	}
	
	if (isfindendpoint(nextposition, 1.2f)) {
		WorldResetCamera(init_camera_position);
		WorldMapChangeLevel(currentLevel);
		currentLevel++;
		WorldUpdateLOC();

		WorldUpdateTexture();
	}
}

void World::WorldGravity(bool havegravity)
{
	this->havegravity = havegravity;
	this->isfalling = this->havegravity;
}

void World::WorldLockCameraPitch(bool islockpitch)
{
	if (this->camera == nullptr) exit(0);
	this->camera->LockCameraPitch(islockpitch);
}

void World::WorldUpdateLOC()
{
	//update the scene's position
	for (int i = 0; i < this->SceneList.size(); i++) {
		switch (i)
		{
		case 1:
			this->SceneList[i]->SetsceneLoc(this->map->Groundpositions);
			break;
		case 2:
			this->SceneList[i]->SetsceneLoc(this->map->OutWallpositions);
			break;
		case 3:
			this->SceneList[i]->SetsceneLoc(this->map->Wallpositions);
			break;
		default:
			break;
		}
		
	}

	//update the world scenelist
	this->PositionList.clear();

	for (int i = 0; i < this->SceneList.size() - 1; i++) {
		this->PositionList.push_back(this->SceneList[i]->GetsceneLoc());
	}

	/*for (auto i : this->SceneList) {
		
	}*/

	//update the is block
	for (int x = 0; x < worldsize.x; x++) {
		for (int y = 0; y < worldsize.y; y++) {
			for (int z = 0; z < worldsize.z; z++) {
				this->isblock[x][y][z] = false;
			}
		}
	}

	for (auto i : this->PositionList) {
		for (auto loc : i) {
			this->isblock[int(loc.x) + worldcenterLoc.x][int(loc.y) + worldcenterLoc.y][int(loc.z) + worldcenterLoc.z] = true;
		}
	}

	this->endpoint = this->map->EndpointPositions;

	std::vector<glm::vec3> endlist;
	endlist.push_back(this->endpoint);

	this->SceneList[4]->SetsceneLoc(endlist);
}

void World::WorldUpdateTexture()
{
	for (auto i : this->SceneList) {
		i->LoadTexture();
	}
}

Camera * World::getCamera()
{
	return this->camera;
}

bool World::iscollision(glm::vec3 & nextposition, float tolerance)
{
	int x[2] = { floor(nextposition.x), ceil(nextposition.x) };
	int y[2] = { floor(nextposition.y), ceil(nextposition.y) };
	int z[2] = { floor(nextposition.z),  ceil(nextposition.z) };

	for (char i = 0; i < 2; i++) {
		for (char j = 0; j < 2; j++) {
			for (char m = 0; m < 2; m++) {
				if (isblock[x[i] + worldcenterLoc.x][y[j] + worldcenterLoc.y][z[m] + worldcenterLoc.z]
					&& abs(nextposition.x - x[i]) < tolerance
					&& abs(nextposition.y - y[j]) < tolerance
					&& abs(nextposition.z - z[m]) < tolerance)
					return true;
			}
		}
	}


	return false;
}

bool World::isfindendpoint(glm::vec3 & nextposition, float tolerance)
{
	
	float distance = sqrt(pow(nextposition.x - this->endpoint.x,2)+pow(nextposition.y - this->endpoint.y,2)+pow(nextposition.z - this->endpoint.z,2));
	
	cout << "distance: " << distance << std::endl;
	if (distance < tolerance) {
		return true;
	}

	return false;
}
