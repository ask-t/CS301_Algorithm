#include <bits/stdc++.h>
using namespace std;

struct Edge;
struct Node
{
  string label;
  vector<Edge *> edges;
  bool visited = false;
  Node(string l) : label(l) {}
};

struct Edge
{
  int weight;
  Node *n1;
  Node *n2;
  Edge(Node *node1, Node *node2, int w) : n1(node1), n2(node2), weight(w) {}
};

vector<Edge *> bucket;
vector<Edge *> MST_EDGES;
int TOTAL_WEIGHT = 0;
map<string, Node *> nodes;

/**
 * Adds edges to the bucket.
 *
 * This function iterates over the edges of a given node and adds them to the bucket
 * if either of the nodes connected by the edge has not been visited.
 *
 * @param node A pointer to the node whose edges are to be added to the bucket.
 */
void AddEdgesToBucket(Node *node)
{
  for (auto &edge : node->edges)
  {
    if (!edge->n1->visited || !edge->n2->visited)
    {
      bucket.push_back(edge);
    }
  }
}

/**
 * Represents an edge between two nodes.
 * @return Edge*
 */
Edge *GET_BEST_EDGE()
{
  Edge *bestEdge = nullptr;
  int minWeight = INT_MAX; // initialize with big value;
  auto it = bucket.begin();
  while (it != bucket.end())
  {
    Edge *edge = *it;
    if ((edge->n1->visited && !edge->n2->visited) || (!edge->n1->visited && edge->n2->visited))
    {
      if (edge->weight < minWeight)
      {
        bestEdge = edge;
        minWeight = edge->weight;
      }
      ++it;
    }
    else
    {
      it = bucket.erase(it); // Remove edge if both nodes are visited
    }
  }
  return bestEdge;
}

/**
 * Finds the minimum spanning tree (MST) using Prim's algorithm.
 *
 * @param START The starting node for the MST.
 */
void MST_PRIM(Node *START)
{
  START->visited = true;
  AddEdgesToBucket(START);

  Edge *E = GET_BEST_EDGE();
  while (E != nullptr)
  {
    Node *n1 = E->n1->visited ? E->n2 : E->n1;
    n1->visited = true;
    TOTAL_WEIGHT += E->weight;
    MST_EDGES.push_back(E);
    AddEdgesToBucket(n1);
    E = GET_BEST_EDGE();
  }
}

int main(int argc, char const *argv[])
{
  // Error Handling
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <input file>" << endl;
    return 1;
  }

  ifstream ifs(argv[1]);
  if (!ifs.is_open())
  {
    cerr << "Error: could not open " << argv[1] << endl;
    return 1;
  }

  // ------------- Start -------------------

  // Make Nodes
  string nodeLabels;
  ifs >> nodeLabels; // in >> ABCDEFGHI
  for (char label : nodeLabels)
  {
    string strLabel(1, label);
    nodes[strLabel] = new Node(strLabel); // push new nodes in the hashmap
  }

  int edgesCount; // cin >> 13
  ifs >> edgesCount;
  for (int i = 0; i < edgesCount; i++) // read all edges. example: (label1, label2, weight)
  {
    char label1, label2;
    int weight;
    ifs >> label1 >> label2 >> weight;
    string strLabel1(1, label1), strLabel2(1, label2); // convert char to string
    Node *node1 = nodes[strLabel1];
    Node *node2 = nodes[strLabel2];
    Edge *edge = new Edge(node1, node2, weight); // edge has two nodes.
    node1->edges.push_back(edge);
    node2->edges.push_back(edge); // For undirected graph
  }

  Node *startNode = nodes.begin()->second; //return value of the first elements. begin()== first elements. second == key.
  MST_PRIM(startNode);

  cout << "MST has a weight of " << TOTAL_WEIGHT << " and consists of these edges:\n";
  for (Edge *edge : MST_EDGES)
  {
    cout << edge->n1->label << " - " << edge->n2->label << " " << edge->weight << endl;
  }

  return 0;
}