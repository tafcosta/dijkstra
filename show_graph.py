import networkx as nx
import matplotlib.pyplot as plt

def read_graph_data(filename):
    edges = []
    with open(filename, "r") as file:
        nVertices = int(file.readline().strip())
        srcVertex = int(file.readline().strip())
        for line in file:
            from_vertex, to_vertex, weight = map(int, line.strip().split())
            edges.append((from_vertex, to_vertex, weight))
    
    return nVertices, srcVertex, edges

def visualize_graph(nVertices, srcVertex, edges):
    G = nx.Graph()
    for from_vertex, to_vertex, weight in edges:
        G.add_edge(from_vertex, to_vertex, weight=weight)

    pos = nx.spring_layout(G)
    labels = {i: i for i in range(nVertices)}

    nx.draw(G, pos, with_labels=True, labels=labels, node_size=500)
    labels = nx.get_edge_attributes(G, 'weight')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=labels)
    plt.show()

if __name__ == "__main__":
    nVertices, srcVertex, edges = read_graph_data("graph.txt")
    visualize_graph(nVertices, srcVertex, edges)
