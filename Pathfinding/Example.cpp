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
		{0, 6, 0, 3, 0},
		{6, 0, 5, 2, 2},
		{0, 5, 0, 0, 5},
		{3, 2, 0, 0, 3},
		{0, 2, 5, 3, 0} }, coordinates);

	std::vector<Node*> nodes = graph.GetNodes();
	std::vector<int> distances = Dijkstra(graph, nodes[0]);

	for (int i = 0; i < distances.size(); ++i) {
		std::cout << distances[i] << " ";
	}
	std::cout << std::endl;

	std::vector<Node*> path = AStar(graph, nodes[0], nodes[2], EuclideanDistance);

	for (int i = 0; i < path.size() - 1; ++i) {
		std::cout << path[i]->GetID() << " -> ";
	}
	std::cout << path.back()->GetID() << std::endl;

	return 0;
}