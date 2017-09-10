#pragma once

#include <vector>
struct GraphNode {
	GraphNode(int _x, int _y) : x(_x), y(_y) {};
	int x, y;
	std::vector<GraphNode*> nextNodes;
};

class Map {
	std::vector<std::vector<int>> m_mapData;
	GraphNode *m_mapGraph;

	int m_entryPointX;
	int m_entryPointY;
	int m_exitPointX;
	int m_exitPointY;

public:
	Map();
	~Map();

	bool loadMapFromFile(const std::string& _name);

	void setMapData(std::vector<std::vector<int>> _mapData);
	int getMapData(int _x, int _y);

	GraphNode *getMapGraph();

	int getMapWidth() { return m_mapData[0].size(); };
	int getMapHeight() { return m_mapData.size(); };

	static const int HIGH_TERRAIN = 0;
	static const int LOW_TERRAIN = 1;
	static const int ENTRY_POINT = 2;
	static const int EXIT_POINT = 3;

	static const char DIR_LEFT = 'L';
	static const char DIR_RIGHT = 'R';
	static const char DIR_UP = 'U';
	static const char DIR_DOWN = 'D';
	static const char DIR_BRANCH = 'x';

private:
	GraphNode *initGraph(const int& _x, const int& _y, std::vector<std::vector<char>>& _directions, std::vector<std::vector<bool>>& _visited);
	GraphNode *createGraph(std::vector<std::vector<bool>>& _visited, const int& _x, const int& _y);
	int findNeighbours(const std::vector<std::vector<bool>>& _visited, const std::vector<std::vector<char>>& _directions, const int& _x, const int& _y, std::vector<int> &neighboursX, std::vector<int> &neighboursY);
};

