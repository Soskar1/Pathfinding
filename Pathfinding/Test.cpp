#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Graph.h"
#include "Pathfinding.h"
#include "Experimentator.h"

#define GRAPH_SIZE 1000
#define MAX_COST 100
#define MAX_NODE_DISTANCE 1000

std::vector<std::pair<int, int>> GenerateCoordinates() {
	std::vector<std::pair<int, int>> coordinates;

	for (int i = 0; i < GRAPH_SIZE; ++i) {
		std::pair<int, int> tmp = std::make_pair(rand() % MAX_NODE_DISTANCE, rand() % MAX_NODE_DISTANCE);
		coordinates.push_back(tmp);
	}

	return coordinates;
}

std::vector<std::vector<int>> GenerateAdjacencyMatrix(const std::vector<std::pair<int, int>>& coordinates) {
	std::vector<std::vector<int>> adjacencyMatrix(GRAPH_SIZE, std::vector<int>(GRAPH_SIZE, 0));

	for (int i = 0; i < GRAPH_SIZE; ++i) {
		int randomNodeIndex = 0;
		
		do {
			randomNodeIndex = rand() % GRAPH_SIZE;
		} while (randomNodeIndex == i || adjacencyMatrix[i][randomNodeIndex] != 0);

		int randomCost = 1 + rand() % MAX_COST;

		adjacencyMatrix[i][randomNodeIndex] = randomCost;
		adjacencyMatrix[randomNodeIndex][i] = randomCost;
	}

	return adjacencyMatrix;
}

Graphs::Graph CreateGraph() {
	auto coordinates = GenerateCoordinates();
	auto adjacencyMatrix = GenerateAdjacencyMatrix(coordinates);

	return Graphs::Graph(adjacencyMatrix, coordinates);
}

void PrintGraph(const Graphs::Graph& graph) {
	auto nodes = graph.GetNodes();

	for (auto node : nodes) {
		int id = node->GetID();
		auto coordinates = node->GetCoordinates();
		auto neighbours = node->GetAdjacentNodes();

		std::cout << id << ": " << "(" << coordinates.first << ", " << coordinates.second << ")\n";
		for (auto neighbour : neighbours) {
			std::cout << "\t" << id << " -> " << neighbour.first->GetID() << ": " << neighbour.second << std::endl;
		}
	}
}

int main() {
	using namespace Graphs;
	using namespace Pathfinding;

	srand((unsigned)time(NULL));

	Graph graph = CreateGraph();

	//std::cout << "Generated graph: \n";
	//PrintGraph(graph);

	float time = 0;
	Node* startNode = graph.GetNodes()[0];
	Node* endNode = graph.GetNodes()[0];

	time = GetAverageExecutionTime(
		[&graph, &startNode]() {
		Dijkstra(graph, startNode);
		},
	[&graph, &startNode]() {
			startNode = graph.GetNodes()[rand() % GRAPH_SIZE];
		});

	std::cout << "Dijkstra average time: " << time << " microseconds\n";

	time = GetAverageExecutionTime(
		[&graph, &startNode, &endNode]() {
			AStar(graph, startNode, endNode, XCoordinateComparison);
		}, 
		[&graph, &startNode, &endNode]() {
			auto nodes = graph.GetNodes();
			startNode = nodes[rand() % GRAPH_SIZE];

			do {
				endNode = nodes[rand() % GRAPH_SIZE];
			} while (endNode == startNode);
		}
	);

	std::cout << "A*|XCoordinateComparison average time: " << time << " microseconds\n";

	time = GetAverageExecutionTime(
		[&graph, &startNode, &endNode]() {
			AStar(graph, startNode, endNode, YCoordinateComparison);
		},
		[&graph, &startNode, &endNode]() {
			auto nodes = graph.GetNodes();
			startNode = nodes[rand() % GRAPH_SIZE];

			do {
				endNode = nodes[rand() % GRAPH_SIZE];
			} while (endNode == startNode);
		}
		);

	std::cout << "A*|YCoordinateComparison average time: " << time << " microseconds\n";

	time = GetAverageExecutionTime(
		[&graph, &startNode, &endNode]() {
			AStar(graph, startNode, endNode, EuclideanDistance);
		},
		[&graph, &startNode, &endNode]() {
			auto nodes = graph.GetNodes();
			startNode = nodes[rand() % GRAPH_SIZE];

			do {
				endNode = nodes[rand() % GRAPH_SIZE];
			} while (endNode == startNode);
		}
		);

	std::cout << "A*|EuclideanDistance average time: " << time << " microseconds\n";

	return 0;
}