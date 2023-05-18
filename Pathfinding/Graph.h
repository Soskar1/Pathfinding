#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

namespace Graphs {
	class Node {
	private:
		size_t m_ID;
		std::pair<int, int> m_Coordinates;
		std::vector<std::pair<Node*, int>> m_AdjacentNodes;
	public:
		Node(const std::pair<int, int>& initialCoordinates, const size_t& id);
		Node(const int& x, const int& y, const size_t& id);

		void AddAdjacentNode(Node* node, const int& weight);
		std::vector<std::pair<Node*, int>> GetAdjacentNodes() const;

		std::pair<int, int> GetCoordinates() const;
		size_t GetID() const;
	};

	class Graph {
	private:
		std::vector<Node*> m_Nodes;
	public:
		Graph(const std::vector<std::vector<int>>& adjacencyMatrix, const std::vector<std::pair<int, int>>& nodeCoordinates);

		std::vector<Node*> GetNodes() const;
	};

	int XCoordinateComparison(Node* first, Node* second);
	int YCoordinateComparison(Node* first, Node* second);
	int EuclideanDistance(Node* first, Node* second);
}
#endif