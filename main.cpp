#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

#define INF std::numeric_limits<double>::infinity()

class Graph{
public:
  Graph(int nVertices) : adj_list(nVertices), nVertices(nVertices), visited(nVertices, false) {}

  struct Edge {
    int first;
    double second;
    Edge(int _target, double _dist) : first(_target), second(_dist) {}
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
    //    nVertices = graph_.get_nVertices();

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
	int v = edge.first;
	double distance = edge.second;

	if (distFromSrcVertex[u] + distance < distFromSrcVertex[v]) {
	  distFromSrcVertex[v] = distFromSrcVertex[u] + distance;
	  minHeap.push({v, distFromSrcVertex[v]});
	}
      }
    }
  }
  
private:
  Graph& graph_;
  //  int nVertices;
  int srcVertex;
};

int main(){
  int nVertices = 5; 
  Graph g(nVertices);

  g.add_edge(0, 1, 2);
  g.add_edge(0, 2, 4);
  g.add_edge(1, 2, 1);
  g.add_edge(2, 3, 1);
  g.add_edge(3, 4, 3);

  Dijkstra dijkstra(g, 0);

  dijkstra.search();
  
  for (int i = 0; i < dijkstra.distFromSrcVertex.size(); ++i)
    cout << "Distance from vertex 0 to vertex " << i << ": " << dijkstra.distFromSrcVertex[i] << endl;
}
