#include "Pathfinding.h"

#include <queue>
#include <map>

namespace Pathfinding {
	struct NodeCompare {
		bool operator()(const std::pair<Graphs::Node*, int>& node1, const std::pair<Graphs::Node*, int>& node2) {
			return node1.second > node2.second;
		}
	};

	std::vector<int> Dijkstra(const Graphs::Graph& graph, Graphs::Node* startNode) {
		using namespace Graphs;

		std::vector<Node*> graphNodes = graph.GetNodes();
		std::vector<bool> visited(graphNodes.size(), false);
		std::vector<int> distances(graphNodes.size(), INT_MAX);

		distances[startNode->GetID()] = 0;

		std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, NodeCompare> queue;
		queue.push(std::make_pair(startNode, 0));

		while (!queue.empty()) {
			auto node = queue.top();
			queue.pop();

			auto neighbours = node.first->GetAdjacentNodes();

			for (int i = 0; i < neighbours.size(); ++i) {
				Node* neighbourNode = neighbours[i].first;
				int weight = neighbours[i].second;

				if (visited[neighbourNode->GetID()])
					continue;

				int totalCost = distances[node.first->GetID()] + weight;

				if (totalCost < distances[neighbourNode->GetID()]) {
					distances[neighbourNode->GetID()] = totalCost;

					queue.push(std::make_pair(neighbourNode, totalCost));
				}
			}

			visited[node.first->GetID()] = true;
		}

		return distances;
	}

	std::list<Graphs::Node*> ConstructPath(std::map<Graphs::Node*, Graphs::Node*>& cameFrom, Graphs::Node* endNode) {
		using namespace Graphs;

		std::list<Node*> path;

		Node* tmp = endNode;
		path.push_front(endNode);
		while (cameFrom.find(tmp) != cameFrom.end()) {
			tmp = cameFrom[tmp];
			path.push_front(tmp);
		}

		return path;
	}

	std::list<Graphs::Node*> AStar(const Graphs::Graph& graph, Graphs::Node* startNode, Graphs::Node* endNode, const std::function<int(Graphs::Node*, Graphs::Node*)>& heuristicFunction) {
		using namespace Graphs;

		std::vector<Node*> graphNodes = graph.GetNodes();
		std::vector<bool> visited(graphNodes.size(), false);
		std::vector<int> distances(graphNodes.size(), INT_MAX);
		std::map<Node*, Node*> cameFrom;

		std::priority_queue<std::pair<Node*, int>, std::vector<std::pair<Node*, int>>, NodeCompare> queue;

		distances[startNode->GetID()] = 0;

		int heuristicValue = heuristicFunction(startNode, endNode);
		queue.push(std::make_pair(startNode, heuristicValue));

		while (!queue.empty()) {
			auto node = queue.top();
			queue.pop();

			if (node.first == endNode) {
				break;
			}

			auto neighbours = node.first->GetAdjacentNodes();

			Node* nextNode;
			for (auto neighbour : neighbours) {
				Node* neighbourNode = neighbour.first;
				int weight = neighbour.second;

				if (visited[neighbourNode->GetID()])
					continue;

				heuristicValue = heuristicFunction(neighbourNode, endNode);
				int totalCost = distances[node.first->GetID()] + weight + heuristicValue;

				if (totalCost < distances[neighbourNode->GetID()]) {
					distances[neighbourNode->GetID()] = totalCost;

					cameFrom[neighbourNode] = node.first;
					queue.push(std::make_pair(neighbourNode, totalCost));
				}
			}

			visited[node.first->GetID()] = true;
		}

		return ConstructPath(cameFrom, endNode);
	}
}