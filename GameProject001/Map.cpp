#include "stdafx.h"
#include "Map.h"
#include "Util.h"
#include <fstream>
#include <iostream>

Map::Map() {
}


Map::~Map() {
	// TODO graph deletion
}

bool Map::loadMapFromFile(const std::string& _name) {
	std::ifstream mapFile;
	std::ifstream dataFile;

	std::string mapPath = _name;
	mapPath.append(".map");
	
	std::string dataPath = _name;
	dataPath.append(".data");

	if (!mapFile || !dataFile) {
		std::string msg = "Error loading map ";
		msg.append(_name);
		Util::printMessage(msg);
		return false;
	}

	m_mapData.clear();

	std::string line;

	// Read map data
	mapFile.open(mapPath);
	std::vector<std::vector<bool>> visited;
	int y = 0;
	while (std::getline(mapFile, line)) {
		std::vector<int> mapRow;
		std::vector<bool> visitedRow;
		for (int x = 0; x < line.size(); ++x) {
			int tile = Util::charToInt(line[x]);
			mapRow.push_back(tile);

			if (tile == HIGH_TERRAIN) {
				visitedRow.push_back(true);
			}
			else {
				visitedRow.push_back(false);
			}

			if (tile == ENTRY_POINT) {
				m_entryPointX = x;
				m_entryPointY = y;
			}

			if (tile == EXIT_POINT) {
				m_exitPointX = x;
				m_exitPointY = y;
			}
		}
		y++;

		m_mapData.push_back(mapRow);
		visited.push_back(visitedRow);
	}
	
	mapFile.close();

	// Read map directions
	dataFile.open(dataPath);
	std::vector<std::vector<char>> mapDirections;
	while (std::getline(dataFile, line)) {
		std::vector<char> dataRow;
		for (int x = 0; x < line.size(); ++x) {
			char tile = line[x];
			dataRow.push_back(tile);
		}
		mapDirections.push_back(dataRow);
	}

	mapFile.close();

	// Initialize graph
	m_mapGraph = initGraph(m_entryPointX, m_entryPointY, mapDirections, visited);

	return true;
}

void Map::setMapData(std::vector<std::vector<int>> _mapData) {
	m_mapData = _mapData;
}

int Map::getMapData(int _x, int _y) {
	return m_mapData[_y][_x];
}

GraphNode * Map::getMapGraph() {
	return m_mapGraph;
}


GraphNode * Map::initGraph(const int & _x, const int & _y, std::vector<std::vector<char>>& _directions, std::vector<std::vector<bool>>& _visited) {
	int currentX = _x;
	int currentY = _y;

	char lastDirection = _directions[_y][_x];

	GraphNode *newNode = new GraphNode(_x, _y);
	GraphNode *currentNode = newNode;
	while (_directions[currentY][currentX] != DIR_BRANCH) {
		// Curve
		if (_directions[currentY][currentX] != lastDirection) {
			GraphNode *node = new GraphNode(currentX, currentY);
			currentNode->nextNodes.push_back(node);
			currentNode = node;

			lastDirection = _directions[currentY][currentX];
		}

		// Move to next node
		switch (_directions[currentY][currentX]) {
		case (DIR_UP):
			currentY--;
			break;
		case (DIR_DOWN):
			currentY++;
			break;
		case (DIR_LEFT):
			currentX--;
			break;
		case (DIR_RIGHT):
			currentX++;
			break;
		}
	}

	// Check if final node
	if (getMapData(currentX, currentY) == EXIT_POINT) {
		GraphNode *node = new GraphNode(currentX, currentY);
		currentNode->nextNodes.push_back(node);
		return newNode;
	}

	// Branch node
	GraphNode *node = new GraphNode(currentX, currentY);
	currentNode->nextNodes.push_back(node);
	currentNode = node;

	std::vector<int> neighboursX;
	std::vector<int> neighboursY;

	int neighbourCount = findNeighbours(_visited, _directions, currentX, currentY, neighboursX, neighboursY);
	for (int i = 0; i < neighbourCount; ++i) {
		GraphNode *neighbourNode = initGraph(neighboursX[i], neighboursY[i], _directions, _visited);
		currentNode->nextNodes.push_back(neighbourNode);
	}

	return newNode;
}

GraphNode * Map::createGraph(std::vector<std::vector<bool>>& _visited, const int& _x, const int& _y) {
	std::cout << " ### graph " << _x << " " << _y << std::endl;

	std::vector<int> neighboursX;
	std::vector<int> neighboursY;

	int currentX = _x;
	int currentY = _y;

	std::vector<int> pathX;
	std::vector<int> pathY;

	// Find next branching
	/*
	while (findNeighbours(_visited, currentX, currentY, neighboursX, neighboursY) == 1) {
		_visited[currentY][currentX] = true;
		pathX.push_back(currentX);
		pathY.push_back(currentY);

		currentX = neighboursX[0];
		currentY = neighboursY[0];

		neighboursX.clear();
		neighboursY.clear();
	}
	*/

	// Check if no neighbours
	if (neighboursX.empty() || neighboursY.empty()) {
		// Check if end node
		if (getMapData(currentX, currentY) == EXIT_POINT) {
			Util::printMessage("END");
			return new GraphNode(currentX, currentY);
		}

		// Looping path - check path as not visited
		for (int i = 0; i < pathX.size(); i++) {
			_visited[pathY[i]][pathX[i]] = false;
		}
		Util::printMessage("DEADEND");
		return nullptr;
	}

	_visited[currentY][currentX] = true;
	
	std::cout << "size " << neighboursX.size() << std::endl;
	std::cout << "branching " << currentX << " " << currentY << std::endl;

	GraphNode *node = new GraphNode(currentX, currentY);
	
	// Iterate trough neighbours
	for (int i = 0; i < neighboursX.size(); i++) {
		GraphNode *newNode = createGraph(_visited, neighboursX[i], neighboursY[i]);
		if (newNode) {
			node->nextNodes.push_back(newNode);
		}
	}

	return node;
}

int Map::findNeighbours(const std::vector<std::vector<bool>>& _visited, const std::vector<std::vector<char>>& _directions, const int& _x, const int& _y, std::vector<int> &neighboursX, std::vector<int> &neighboursY) {
	int neighbourCount = 0;

	if (_x > 0) {
		if (!_visited[_y][_x - 1] && _directions[_y][_x - 1] != DIR_RIGHT) {
			neighboursX.push_back(_x - 1);
			neighboursY.push_back(_y);
			neighbourCount++;
		}
	}
	
	if (_x < getMapWidth() - 1) {
		if (!_visited[_y][_x + 1] && _directions[_y][_x + 1] != DIR_LEFT) {
			neighboursX.push_back(_x + 1);
			neighboursY.push_back(_y);
			neighbourCount++;
		}
	}

	if (_y > 0) {
		if (!_visited[_y - 1][_x] && _directions[_y - 1][_x] != DIR_DOWN) {
			neighboursX.push_back(_x);
			neighboursY.push_back(_y - 1);
			neighbourCount++;
		}
	}

	if (_y < getMapHeight() - 1) {
		if (!_visited[_y + 1][_x] && _directions[_y + 1][_x] != DIR_UP) {
			neighboursX.push_back(_x);
			neighboursY.push_back(_y + 1);
			neighbourCount++;
		}
	}

	return neighbourCount;
}



