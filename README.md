# graphs-topological-sort
A topological sort can be performed only when the graph is a DAG (Directed Acyclic Graph).
This program reads an adjacency list of a graph from an input. An example of an input is presented in the file 'graph.txt'. The first line represents the number of vertices and edges. The following lines represent an edge from one vertice to another.
Then a user can choose whether to choose an adjacency matrix or a graph matrix to execute a topological sort of the vertices.
If you choose the adjacency matrix, there are 2 algorithms to sort topologically:
  1. Kahn's algorithm - sorting with removal of independent vertices
  2. Algorithm using the DFS (Depth First Search) procedure
