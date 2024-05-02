#include <bits/stdc++.h>
using namespace std;

struct Edge;
struct Node
{
  string label;
  vector<Edge*> edges;
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

vector<Edge *> busket;
vector<Edge *> MST_EDGES;
int TOTAL_WEIGHT = 0;
map<string, Node *> nodes;


int main(int argc, char const *argv[])
{

  ifstream ifs(argv[1]);
  string nodeLabels;
  ifs >> nodeLabels;
  for(char label : nodeLabels)
  {
    string strLabel(1, label);
    nodes[strLabel] = new Node (strLabel);
  }

  int edgesCount;
  ifs >> edgesCount;
  for(int i =0; i < edgesCount; i++)
  {
    char label1, label2;
    int weight;
    ifs >> label1 >> label2 >> weight;
    string strLabel1(1, label1);
    string strLabel2(1, label2);
    Node *node1 = nodes[strLabel1];
    Node *node2 =nodes[strLabel2];
    Edge *edge = new Edge(node1, node2, weight);
    node1->edges.push_back(edge);
    node2->edges.push_back(edge);
  }

  Node *startNode = nodes.begin()->second;
  MST_PRIM(startNode);

  cout << "MST has a weight of " << TOTAL_WEIGHT << " and consists of these edges:\n";
  for(Edge *edge : MST_EDGES)
  {
    cout << edge->n1->label << " - " << edge->n2->label << " " << edge->weight << endl;
  }

  return 0;
}