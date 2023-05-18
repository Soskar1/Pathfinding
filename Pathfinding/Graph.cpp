#include "Graph.h"

#include <cstdlib>
#include <cmath>

namespace Graphs {
	Node::Node(const std::pair<int, int>& initialCoordinates, const size_t& id)
	{
		m_Coordinates = initialCoordinates;
		m_ID = id;
	}

	Node::Node(const int& x, const int& y, const size_t& id)
	{
		m_Coordinates = std::make_pair(x, y);
		m_ID = id;
	}

	void Node::AddAdjacentNode(Node* node, const int& weight)
	{
		m_AdjacentNodes.push_back(std::make_pair(node, weight));
	}

	std::vector<std::pair<Node*, int>> Node::GetAdjacentNodes() const
	{
		return m_AdjacentNodes;
	}

	std::pair<int, int> Node::GetCoordinates() const
	{
		return m_Coordinates;
	}

	size_t Node::GetID() const
	{
		return m_ID;
	}

	Graph::Graph(const std::vector<std::vector<int>>& adjacencyMatrix, const std::vector<std::pair<int, int>>& nodeCoordinates)
	{
		m_Nodes = std::vector<Node*>(adjacencyMatrix.size());

		for (int i = 0; i < adjacencyMatrix.size(); ++i) {
			m_Nodes[i] = new Node(nodeCoordinates[i], i);
		}

		for (int i = 0; i < adjacencyMatrix.size(); ++i) {
			for (int j = 0; j < adjacencyMatrix[i].size(); ++j) {
				if (adjacencyMatrix[i][j] != 0) {
					m_Nodes[i]->AddAdjacentNode(m_Nodes[j], adjacencyMatrix[i][j]);
				}
			}
		}
	}

	std::vector<Node*> Graph::GetNodes() const
	{
		return m_Nodes;
	}

	int xCoordinateComparison(Node* first, Node* second)
	{
		return abs(first->GetCoordinates().first - second->GetCoordinates().first);
	}

	int yCoordinateComparison(Node* first, Node* second)
	{
		return abs(first->GetCoordinates().second - second->GetCoordinates().second);
	}

	int EuclideanDistance(Node* first, Node* second)
	{
		auto firstPoint = first->GetCoordinates();
		auto secondPoint = second->GetCoordinates();

		return sqrt(pow(secondPoint.first - firstPoint.first, 2) +
			pow(secondPoint.second - firstPoint.second, 2));
	}
}