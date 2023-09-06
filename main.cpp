#include <iostream>
#include <vector>

using namespace std;

class Graph{
public:
  Graph(int nVertex) : adj_list(nVertex) {}

  void add_edge(int u, int v, int distance){
    adj_list[u].emplace_back(v, distance);
    adj_list[v].emplace_back(u, distance);
  }
  
private:
  vector<vector<pair<int, int>>> adj_list; 
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
