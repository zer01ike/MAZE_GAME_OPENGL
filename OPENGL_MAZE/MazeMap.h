#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <vector>
#include <time.h>
//���ڹ���ͬlevel��maze������
//����Ϊground��С��ǽ�Ĵ�С���Լ�maze�Ĵ�С
//���Ϊ���ߵĵ�����

class MazeMap
{
public:
	MazeMap();
	MazeMap(glm::ivec2 ground, glm::ivec2 playground, glm::ivec2 maze);
	~MazeMap();
	std::vector<glm::vec3> Groundpositions;
	std::vector<glm::vec3> Wallpositions;
	std::vector<glm::vec3> OutWallpositions;
	std::vector<glm::vec3> Waypositions;
	glm::vec3 EndpointPositions;
	void updateMaze(glm::ivec2 & ground, glm::ivec2 & playground, glm::ivec2 & maze);

private:
	glm::ivec2 groundsize;
	glm::ivec2 playgroundsize;
	glm::ivec2 mazesize;
	void mazehelper(std::vector<std::vector<bool>>& result, glm::ivec4 p);
	std::vector<std::vector<bool>> generatemazemaps(glm::ivec2 pos);
	std::vector<glm::vec3> generateGroundPosition(glm::ivec2& pos);
	std::vector<glm::vec3> generateWallPosition(glm::ivec2& pos);
	std::vector<glm::vec3> generateoutWallPosition(glm::ivec2 &pos);
	void  generateEndpointPosition();

};

