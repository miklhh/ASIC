#include "catch.hpp"
#include "../graph.h"

#include <sstream>
#include <iostream>

TEST_CASE("Insert nodes and arcs to a new graph")
{
    Graph<NodeBase> graph{};
    NodeID n0 = graph.create_node();
    NodeID n1 = graph.create_node();
    NodeID n2 = graph.create_node();
    graph.create_bidirectional_arc(n0, n1);
    graph.create_arc(n0, n2);
    graph.create_arc(n1, n2);

    std::stringstream s;
    graph.generate_dot_graph(s);
    graph.generate_dot_graph("dot-graphs/graph1.dot");
    std::cout << s.str();
}

TEST_CASE("Test removing nodes from the graph")
{
    Graph<NodeBase> graph{};
    NodeID n0 = graph.create_node();
    NodeID n1 = graph.create_node();
    NodeID n2 = graph.create_node();
    NodeID n3 = graph.create_node();
    NodeID n4 = graph.create_node();

    graph.create_bidirectional_arc(n0, n1);
    graph.create_bidirectional_arc(n1, n2);
    graph.create_bidirectional_arc(n2, n3);
    graph.create_bidirectional_arc(n3, n4);

    graph.delete_node(n2);
    graph.delete_arc(n3, n4);
    std::stringstream s;
    graph.generate_dot_graph(s);
    graph.generate_dot_graph("dot-graphs/graph2.dot");
    std::cout << s.str();

}
