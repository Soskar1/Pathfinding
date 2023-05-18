#include "Pathfinding.h"

#include <queue>

namespace Pathfinding {
	std::vector<int> Dijkstra(const Graphs::Graph& graph, Graphs::Node* startNode) {
		using namespace Graphs;

		std::vector<Node*> graphNodes = graph.GetNodes();
		std::vector<bool> visited(graphNodes.size(), false);
		std::vector<int> distances(graphNodes.size(), INT_MAX);

		distances[startNode->GetID()] = 0;

		std::queue<Node*> queue;
		queue.push(startNode);

		int minDistance = INT_MAX;
		int minNodeIndex = 0;

		while (!queue.empty()) {
			Node* node = queue.front();
			queue.pop();

			minDistance = INT_MAX;
			minNodeIndex = 0;

			auto neighbours = node->GetAdjacentNodes();

			for (int i = 0; i < neighbours.size(); ++i) {
				Node* neighbourNode = neighbours[i].first;
				int weight = neighbours[i].second;

				if (visited[neighbourNode->GetID()])
					continue;

				if (distances[node->GetID()] + weight < distances[neighbourNode->GetID()]) {
					distances[neighbourNode->GetID()] = distances[node->GetID()] + weight;

					if (minDistance > distances[neighbourNode->GetID()]) {
						minDistance = distances[neighbourNode->GetID()];
						minNodeIndex = neighbourNode->GetID();
					}
				}
			}

			visited[node->GetID()] = true;

			if (minDistance != INT_MAX) {
				queue.push(graphNodes[minNodeIndex]);
			}
		}

		return distances;
	}

	std::vector<Graphs::Node*> AStar(const Graphs::Graph& graph, Graphs::Node* startNode, Graphs::Node* endNode, const std::function<int(Graphs::Node*, Graphs::Node*)>& heuristicFunction) {
		using namespace Graphs;

		std::vector<Node*> graphNodes = graph.GetNodes();
		std::vector<bool> visited(graphNodes.size(), false);

		std::vector<int> distances(graphNodes.size(), INT_MAX);

		std::vector<Node*> path;

		distances[startNode->GetID()] = 0;

		std::queue<Node*> queue;
		queue.push(startNode);

		int minDistance = INT_MAX;
		int minNodeIndex = 0;

		while (!queue.empty()) {
			Node* node = queue.front();
			queue.pop();

			int minDistance = INT_MAX;
			int minNodeIndex = 0;

			auto neighbours = node->GetAdjacentNodes();

			for (int i = 0; i < neighbours.size(); ++i) {
				Node* neighbourNode = neighbours[i].first;
				int weight = neighbours[i].second;

				if (visited[neighbourNode->GetID()])
					continue;

				if (distances[node->GetID()] + weight + heuristicFunction(neighbourNode, endNode) < distances[neighbourNode->GetID()]) {
					distances[neighbourNode->GetID()] = distances[node->GetID()] + weight;

					if (minDistance > distances[neighbourNode->GetID()]) {
						minDistance = distances[neighbourNode->GetID()];
						minNodeIndex = neighbourNode->GetID();
					}
				}
			}
			
			visited[node->GetID()] = true;

			if (minDistance != INT_MAX) {
				queue.push(graphNodes[minNodeIndex]);
				path.push_back(node);
			}
		}

		path.push_back(endNode);

		return path;
	}
}