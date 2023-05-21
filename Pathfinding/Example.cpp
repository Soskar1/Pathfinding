#include <iostream>
#include <vector>

#include "Graph.h"
#include "Pathfinding.h"

int main()
{
	using namespace Graphs;
	using namespace Pathfinding;

	std::vector<std::pair<int, int>> coordinates;
	coordinates.push_back(std::make_pair(0, 10));
	coordinates.push_back(std::make_pair(10, 10));
	coordinates.push_back(std::make_pair(20, 5));
	coordinates.push_back(std::make_pair(0, 0));
	coordinates.push_back(std::make_pair(10, 0));

	Graph graph({
		{0, 6, 0, 1, 0},
		{6, 0, 5, 2, 2},
		{0, 5, 0, 0, 5},
		{1, 2, 0, 0, 1},
		{0, 2, 5, 1, 0} }, coordinates);

	std::vector<Node*> nodes = graph.GetNodes();
	std::vector<int> distances = Dijkstra(graph, nodes[0]);

	for (int i = 0; i < distances.size(); ++i) {
		std::cout << distances[i] << " ";
	}
	std::cout << std::endl;

	std::list<Node*> path = AStar(graph, nodes[0], nodes[2], XCoordinateComparison);

	for (auto node : path) {
		std::cout << node->GetID() << " ";
	}

	return 0;
}