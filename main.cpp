#include <iostream>
#include <vector>

using namespace std;

class Graph{
public:
  Graph(int nVertex) : adj_list(nVertex) {}

  void add_edge(int u, int v){
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
  }
  
private:
  vector<vector<int>> adj_list; 
};

int main(){

  int nVertex = 5; 
  Graph myGraph(nVertex);
  
}
