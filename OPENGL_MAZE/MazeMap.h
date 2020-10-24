#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/noise.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <vector>
#include <time.h>
//用于管理不同level的maze的问题
//输入为ground大小，墙的大小，以及maze的大小
//输出为三者的点坐标

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

