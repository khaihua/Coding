/*
 * Khai Hua
 * Dijkstra shortest path
 * HW 2
 * CMPS109
 */
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;
//returns random decimal from 0.0 - 1.0
inline double probability() {
	return (1.0 * rand()) / RAND_MAX;
}
//infinity symbolized as any random number
const int INF = 111111;

class Graph {
	int size;
	double range;
	bool** graph;
	double** weight;

public:

	Graph(int graph_size, double graph_density, double distance_range) {
		size = graph_size;
		range = distance_range;
		//initializes a boolean matrix which will hold edges
		graph = new bool*[graph_size]();
		for (int i = 0; i < graph_size; ++i) {
			graph[i] = new bool[graph_size]();
		}

		//initializes matrix to hold weight of connected vertices
		weight = new double*[graph_size]();
		for (int i = 0; i < graph_size; ++i) {
			weight[i] = new double[graph_size]();
		}

		//creates edges randomly based on density parameter
		for (int i = 0; i < graph_size; ++i) {
			for (int j = 0; j < graph_size; ++j) {
				if (i != j && graph[j][i] != true && graph[i][j] != true) {
					if (probability() < graph_density) {
						graph[i][j] = graph[j][i] = true;
					}
				}
			}
		}
		//assigns random weights for each edge based on specified range
		for (int i = 0; i < graph_size; ++i) {
			for (int j = 0; j < graph_size; ++j) {
				if (i != j && graph[j][i] == true && graph[i][j] == true) {
					weight[i][j] = weight[j][i] = probability() * range + 1;
				}
			}
		}
	}
	// Prints 2D representation of graph matrix
	void print_graph() {
		cout << "graph size " << size << endl;

		for (int i = 0; i < size; ++i) {
			cout << endl;
			for (int j = 0; j < size; ++j) {
				cout << graph[i][j] << " ";
			}
		}
	}
	// Prints matrix holding weights of edges
	void print_weight() {
		cout << "graph size " << size << endl;

		for (int i = 0; i < size; ++i) {
			cout << endl;
			for (int j = 0; j < size; ++j) {
				cout << weight[i][j] << " ";
			}
		}
	}
	//dijkstra implementation
	double dijkstra(int source, int destination) {
		int graph_size = this->size;
		//initializes an array that stores the shortest path
		double shortpath[graph_size];
		//initializes an array that keeps track of visited vertices
		bool visited[graph_size];
		//sets all paths to infinity, and marks all vertices as unvisited
		for (int i = 0; i < graph_size; ++i) {
			shortpath[i] = INF;
			visited[i] = false;
		}

		shortpath[source] = 0; //distance between a vertex and itself is 0
		// For current node we check all its neighboors.
		for (int i = 0; i < graph_size; ++i) {
			// min will store path between two nodes with the lowest weight.
			int min = INF;
			for (int j = 0; j < graph_size; ++j) {
				if (!visited[j]
						&& ((min == INF) || (shortpath[j] < shortpath[min]))) {
					min = j;
					// If the minimum weight vertex taken is the destination vertex then return the distance
					if (min == destination) {
						return shortpath[min];
					}
				}
			}
			// taken path will make visited node true
			visited[min] = true;
			//update the distance of the short path
			for (int i = 0; i < graph_size; ++i) {
				if (weight[min][i]
						&& shortpath[min] + weight[min][i] < shortpath[i]) {
					shortpath[i] = shortpath[min] + weight[min][i];
				}
			}
		}

		return 0;
	}
}
;

int main() {
	srand(time(0));
	int numVertex = 50;
	double density1 = 0.20;
	double density2 = 0.4;
	double range = 10.0;
	double count = numVertex - 1.0; //count keeps track of number for all existing paths

	Graph firstGraph(numVertex, density1, range); //makes first graph

	/*these were used to test if graph was implemented right
	 * Graph testGraph(numVertex, 0.1, range)
	 * testgraph.print_graph();
	 * testgraph.print_weight();
	 */
	//firstGraph.print_weight();
	double average = 0.0; //holds average path length

	//calls dijkstra x times , from 0 - n, n being total number of paths
	for (int i = 1; i < numVertex; ++i) {
		double tmp = firstGraph.dijkstra(0, i);
		// if path does not exist, then decrement count else sum distance
		if (tmp == INF) {
			--count;
		} else {
			average += tmp;
		}
	}
	average = average / count; //calculates the average path length

	cout << "The average path length of a graph with 20% density is: "
			<< average << endl << endl;

	Graph secondGraph(numVertex, density2, range);
	//resets average and count for next graph
	average = 0.0;
	count = numVertex - 1.0;

	for (int i = 1; i < numVertex; ++i) {
		int tmp = secondGraph.dijkstra(0, i);
		// if path does not exist, then decrement count else sum distance
		if (tmp == INF) {
			--count;
		} else {
			average += tmp;
		}
	}
	average = average / count;
	cout << "The average path length of a graph with 40% density is: "
			<< average << endl;
	return 0;
}

