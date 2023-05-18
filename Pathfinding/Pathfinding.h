#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "Graph.h"

#include <functional>

namespace Pathfinding {
	std::vector<int> Dijkstra(const Graphs::Graph& graph, Graphs::Node* startNode);

	std::vector<Graphs::Node*> AStar(const Graphs::Graph& graph, Graphs::Node* startNode, Graphs::Node* endNode, const std::function<int(Graphs::Node*, Graphs::Node*)>& heuristicFunction);
}
#endif