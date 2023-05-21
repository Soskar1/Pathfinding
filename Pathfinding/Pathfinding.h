#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "Graph.h"

#include <vector>
#include <list>
#include <functional>

namespace Pathfinding {
	std::vector<int> Dijkstra(const Graphs::Graph& graph, Graphs::Node* startNode);

	std::list<Graphs::Node*> AStar(const Graphs::Graph& graph, Graphs::Node* startNode, Graphs::Node* endNode, const std::function<int(Graphs::Node*, Graphs::Node*)>& heuristicFunction);
}
#endif