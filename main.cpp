#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

#define INF std::numeric_limits<double>::infinity()

class Graph{
public:
  Graph(int nVertices) : adj_list(nVertices), nVertices(nVertices), visited(nVertices, false) {}

  struct Edge {
    int target;
    double dist;
    Edge(int _target, double _dist) : target(_target), dist(_dist) {}
  };
  
  void add_edge(int u, int v, double distance){
    adj_list[u].emplace_back(v, distance);
    adj_list[v].emplace_back(u, distance);
  }

  int get_nVertices(){
    return nVertices;
  }

  vector<bool> visited;
  vector<vector<Edge>> adj_list;

private:
  int nVertices;
};

class Dijkstra{
public:
  Dijkstra(Graph& graph, int srcVertex) : graph_(graph), srcVertex(srcVertex){
    distFromSrcVertex.assign(graph.get_nVertices(), INF);
    distFromSrcVertex[srcVertex] = 0.0;
    graph_.visited[srcVertex] = true;

    minHeap.push({srcVertex, 0.0});
  }

  vector<double> distFromSrcVertex;

  struct CompareVertices {
    bool operator()(const pair<int, double>& a, const pair<int, double>& b) {
      return a.second > b.second;
    }
  };

  priority_queue<pair<int, double>, vector<pair<int, double>>, CompareVertices> minHeap;
  
  void search(){
    while(!minHeap.empty()){
      int u         = minHeap.top().first;
      double dist_u = minHeap.top().second;
      minHeap.pop();

      if (dist_u > distFromSrcVertex[u])
	continue;

      for (const Graph::Edge edge : graph_.adj_list[u]) {
	int v = edge.target;
	double distance = edge.dist;

	if (distFromSrcVertex[u] + distance < distFromSrcVertex[v]) {
	  distFromSrcVertex[v] = distFromSrcVertex[u] + distance;
	  minHeap.push({v, distFromSrcVertex[v]});
	}
      }
    }
  }
  
private:
  Graph& graph_;
  int srcVertex;
};

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    return 1;
  }
  
  ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    cerr << "Error: Could not open input file." << endl;
    return 1;
  }

  int nVertices, srcVertex;
  inputFile >> nVertices >> srcVertex;
  
  Graph g(nVertices);

  int from, to;
  double weight;

  while (inputFile >> from >> to >> weight) {
    g.add_edge(from, to, weight);
  }

  inputFile.close();
  
  Dijkstra dijkstra(g, srcVertex);
  dijkstra.search();
  
  for (int i = 0; i < dijkstra.distFromSrcVertex.size(); ++i)
    cout << "Distance from vertex " << srcVertex << " to vertex " << i << ": " << dijkstra.distFromSrcVertex[i] << endl;
}
