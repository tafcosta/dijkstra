#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define INF std::numeric_limits<double>::infinity()

class Graph{
public:
  Graph(int nVertex) : adj_list(nVertex), dist_toOtherVertices(nVertex, vector<double>(nVertex, INF)), nVertex(nVertex) {}

  void add_edge(int u, int v, double distance){
    adj_list[u].emplace_back(v, distance);
    adj_list[v].emplace_back(u, distance);
  }

  vector<vector<double>> dist_toOtherVertices;

  int get_nVertex(){
    return nVertex;
  }
  
private:
  vector<vector<pair<int, double>>> adj_list;
  int nVertex;
};

class Dijkstra{
public:
  Dijkstra(Graph& graph, int SrcVertex) : graph_(graph), SrcVertex(SrcVertex){
    graph_.dist_toOtherVertices[SrcVertex][SrcVertex] = 0.0;
    nVertex = graph_.get_nVertex();
  }

private:
  Graph& graph_;
  int nVertex;
  int SrcVertex;
};

int main(){
  int nVertex = 5; 
  Graph g(nVertex);

  // Adding edges to the graph
  g.add_edge(0, 1, 2);
  g.add_edge(0, 2, 4);
  g.add_edge(1, 2, 1);
  g.add_edge(2, 3, 1);
  g.add_edge(3, 4, 3);
  
}
