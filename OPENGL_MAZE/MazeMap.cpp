#include "MazeMap.h"

MazeMap::MazeMap() {

}

MazeMap::MazeMap(glm::ivec2 ground,glm::ivec2 playground,glm::ivec2 maze):groundsize(ground),playgroundsize(playground),mazesize(maze)
{
	this->updateMaze(ground, playground, maze);
}


MazeMap::~MazeMap()
{
}

void MazeMap::updateMaze(glm::ivec2 & ground, glm::ivec2 & playground, glm::ivec2 & maze)
{	
	this->Waypositions.clear();
	this->Groundpositions.clear();
	this->Wallpositions.clear();
	this->OutWallpositions.clear();

	this->Groundpositions = this->generateGroundPosition(ground);
	this->Wallpositions = generateWallPosition(maze);
	this->OutWallpositions = generateoutWallPosition(playground);
	generateEndpointPosition();
}

void MazeMap::mazehelper(std::vector<std::vector<bool>>& result, glm::ivec4 p)
{
	int height = p.z - p.x + 1;
	int width = p.w - p.y + 1;
	if (height <= 0) return;
	if (width <= 0) return;
	if (height < 2 || width < 2) return;

	/*for (auto i : result) {
		for (auto j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}*/
	/*std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;*/

	if (width < height) {
		int index = rand() % (height - 1) + p.x;
		index = 2 * index + 1;

		for (int i = 2 * p.y; i <= 2 * p.w; i++) {
			result[index][i] = false;
		}

		int destory = rand() % (width - 1) + p.y;
		destory = 2 * destory;
		result[index][destory] = true;


		////left up
		//mazehelper(result, glm::ivec4(p.x,p.y, index - 1, destory - 1));
		//
		////left down
		//mazehelper(result, glm::ivec4(index + 1, p.y, p.z, destory - 1));

		////right up
		//mazehelper(result, glm::ivec4(p.x, destory + 1, index - 1, p.w));

		////right down
		//mazehelper(result, glm::ivec4(index + 1, destory + 1, p.z, p.w));

		//up
		mazehelper(result, glm::ivec4(p.x, p.y, (index - 1) / 2, p.w));

		//down
		mazehelper(result, glm::ivec4((index + 1) / 2, p.y, p.z, p.w));

	}
	else {
		int index = rand() % (width - 1) + p.y;
		index = 2 * index + 1;

		for (int i = 2 * p.x; i <= 2 * p.z; i++) {
			result[i][index] = false;
		}

		int destory = rand() % (height - 1) + p.x;
		destory = 2 * destory;
		result[destory][index] = true;


		////left up
		//mazehelper(result, glm::ivec4(p.x, p.y, destory - 1, index - 1));

		////left down
		//mazehelper(result, glm::ivec4(destory + 1, p.y, p.z, index - 1));

		////right up
		//mazehelper(result, glm::ivec4(p.x, index + 1, destory - 1, p.w));

		////right down
		//mazehelper(result, glm::ivec4(destory + 1, index + 1, p.z, p.w));

		//left
		mazehelper(result, glm::ivec4(p.x, p.y, p.z, (index - 1) / 2));
		//right
		mazehelper(result, glm::ivec4(p.x, (index + 1) / 2, p.z, p.w));
	}
	return;
}

std::vector<std::vector<bool>> MazeMap::generatemazemaps(glm::ivec2 pos)
{
	std::vector<std::vector<bool>> result(pos.y, std::vector<bool>(pos.x, true));

	int col = (pos.y + 1) / 2;
	int row = (pos.x + 1) / 2;

	glm::ivec4 position(0, 0, col - 1, row - 1);

	srand((unsigned)time(NULL));
	mazehelper(result, position);

	return result;
}

std::vector<glm::vec3> MazeMap::generateGroundPosition(glm::ivec2 & pos)
{
	std::vector<glm::vec3> result;

	int block_count = 0;
	for (int i = 0; i < pos.x; i++) {
		for (int j = 0; j < pos.y; j++) {
			result.push_back(glm::vec3(0.0f + i, 0.0f, 0.0f + j));
		}
	}
	return result;
}

std::vector<glm::vec3> MazeMap::generateWallPosition(glm::ivec2 & pos)
{
	std::vector<glm::vec3> result;
	glm::vec3 offset = glm::vec3((groundsize.x - playgroundsize.x) / 2 + 1, 0.0f, (groundsize.y - playgroundsize.y) / 2 + 1);
	std::vector<std::vector<bool>> mazemap = generatemazemaps(pos);
	//std::vector<std::vector<bool>> mazemap = generatemazemaps(playgroundsize.x - 2, playgroundsize.y - 2);
	for (auto i : mazemap) {
		for (auto j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	int prev_i = 0;
	int prev_j = 0;
	for (int i = 0; i < pos.x; i++) {
		for (int j = 0; j < pos.y; j++) {
			if (i < pos.x && j < pos.y && mazemap[i][j] == false)
				result.push_back(glm::vec3(0.0f + i, 1.0f, 0.0f + j) + offset);
			else {
				if (i > prev_i && j > prev_j) {
					this->Waypositions.push_back(glm::vec3(0.0f + i, 1.0f, 0.0f + j) + offset);
					prev_i = i;
					prev_j = j;
				}
				
			}
				
		}
	}

	return result;
}

std::vector<glm::vec3> MazeMap::generateoutWallPosition(glm::ivec2 & pos)
{
	std::vector<glm::vec3> result;
	glm::vec3 offset = glm::vec3((groundsize.x - playgroundsize.x) / 2, 0.0f, (groundsize.y - playgroundsize.y) / 2);
	for (int i = 1; i < pos.x - 1; i++) {
		if (i != pos.x / 2 && i != pos.x / 2 - 1)
			result.push_back(glm::vec3(i, 1.0f, 0.0f) + offset);
		else {
			result.push_back(glm::vec3(i, 3.0f, 0.0f) + offset);
			result.push_back(glm::vec3(i, 4.0f, 0.0f) + offset);
		}
		result.push_back(glm::vec3(i, 1.0f, pos.y - 1) + offset);
		result.push_back(glm::vec3(i, 2.0f, 0.0f) + offset);
		result.push_back(glm::vec3(i, 2.0f, pos.y - 1) + offset);
	}

	for (int i = 0; i < pos.y; i++) {
		result.push_back(glm::vec3(0.0f, 1.0f, i) + offset);
		result.push_back(glm::vec3(pos.x - 1, 1.0f, i) + offset);
		result.push_back(glm::vec3(0.0f, 2.0f, i) + offset);
		result.push_back(glm::vec3(pos.x - 1, 2.0f, i) + offset);
	}


	return result;
}

void MazeMap::generateEndpointPosition()
{

	/*this->EndpointPositions =  glm::vec3(1.0f, 0.0f, 2.0f);
	return;*/
	int len = this->Waypositions.size();
	//int rand_index = rand() % (len - 1);

	/*for (int i = mazesize.x - 1; i > mazesize.x / 2; i--) {
		for (int j = mazesize.y - 1; j > mazesize.y / 2; j--) {

		}
	}*/

	if (len > 0 && len <= 3) {
		this->EndpointPositions = this->Waypositions[len-1];
		return;
	}

	int rand_index = rand() % (len / 2 - 1) + len / 2 - 1;
	/*if (len - 5 >= 0) {
		this->EndpointPositions = this->Waypositions[len - 5];
	}
	else {
		
	}*/

	this->EndpointPositions = this->Waypositions[rand_index];
	
}
