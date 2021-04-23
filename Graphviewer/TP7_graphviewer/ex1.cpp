#include "graphviewer.h"

using namespace std;
using Node = GraphViewer::Node;
using Edge = GraphViewer::Edge;

void ex1() {
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(300, 300));

    Node &node0 = gv.addNode(0, sf::Vector2f(200, 300));
    node0.setColor(GraphViewer::PINK);

    Node &node1 = gv.addNode(1, sf::Vector2f(400, 500));
    node1.setColor(GraphViewer::CYAN);

    //Edge &edge1 = gv.addEdge(1, node0, node1, Edge::UNDIRECTED); //for bidirectional edges
    Edge &edge2 = gv.addEdge(2, node0, node1, Edge::DIRECTED); //for directed edges

    Node &node2 = gv.addNode(2, sf::Vector2f(500, 300));
    node2.setColor(GraphViewer::YELLOW);

    Edge &edge3 = gv.addEdge(3, node0, node2, Edge::DIRECTED);

    node2.setLabel("This is a vertex");
    edge3.setLabel("This is an edge");

    for(Edge *edge: gv.getEdges()) edge->setColor(GraphViewer::LIGHT_GRAY);

    //gv.setBackground("../TP7_graphviewer/resources/background.png");

    gv.createWindow(600, 600);

    gv.join();
}
