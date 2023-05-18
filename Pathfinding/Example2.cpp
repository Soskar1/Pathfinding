#include <iostream>
#include <vector>

#include "Graph.h"
#include "Pathfinding.h"

int main()
{
	using namespace Graphs;
	using namespace Pathfinding;

	std::vector<std::pair<int, int>> coordinates;
	coordinates.push_back(std::make_pair(0, 0));
	coordinates.push_back(std::make_pair(30, 50));
	coordinates.push_back(std::make_pair(45, 0));
	coordinates.push_back(std::make_pair(75, 50));

	Graph graph({
		{0, 10, 7, 0},
		{10, 0, 0, 5},
		{7, 0, 0, 8},
		{0, 5, 8, 0} }, coordinates);

	std::vector<Node*> nodes = graph.GetNodes();
	std::vector<Node*> path = AStar(graph, nodes[0], nodes[3], XCoordinateComparison);

	for (int i = 0; i < path.size() - 1; ++i) {
		std::cout << path[i]->GetID() << " -> ";
	}
	std::cout << path.back()->GetID() << std::endl;

	return 0;
}