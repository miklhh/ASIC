#include "catch.hpp"
#include "../graph.h"

#include <sstream>
#include <iostream>
#include <map>
#include <set>

//
// Use graph with regular map (instead of unordered_map) and set (instead of unordered_set) in the unit tests, so that
// nodes are in total order, which makes reproducing tests a lot easier.
//
using UnitTestNode = BaseNode<std::set<NodeID>>;
using UnitTestGraph = Graph<UnitTestNode, std::map<NodeID, UnitTestNode>>;


TEST_CASE("Insert nodes and arcs to a new graph")
{
    const std::string DOT_REFERENCE{
        "strict digraph {\n"
        "    0 -> { 1 2 }\n"
        "    1 -> { 0 2 }\n"
        "    2 -> { }\n"
        "}"
    };

    UnitTestGraph graph{};
    NodeID n0 = graph.create_node();
    NodeID n1 = graph.create_node();
    NodeID n2 = graph.create_node();
    graph.create_bidirectional_arc(n0, n1);
    graph.create_arc(n0, n2);
    graph.create_arc(n1, n2);

    std::stringstream s;
    graph.generate_dot_graph(s);
    graph.generate_dot_graph("dot-graphs/graph1.dot");
    REQUIRE(DOT_REFERENCE == s.str());
}

TEST_CASE("Test removing nodes from the graph")
{
    const std::string DOT_REFERENCE {
        "strict digraph {\n"
        "    0 -> { 1 }\n"
        "    1 -> { 0 }\n"
        "    3 -> { }\n"
        "    4 -> { 3 }\n"
        "}"
    };
    UnitTestGraph graph{};
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
    REQUIRE(DOT_REFERENCE == s.str());
}

TEST_CASE("Create a Graph with 50 nodes in a circle")
{
    UnitTestGraph graph{};
    NodeID first_node = graph.create_node();
    NodeID prev_node = first_node;
    for (int i=0; i<49; ++i) {
        NodeID curr_node = graph.create_node();
        graph.create_bidirectional_arc(curr_node, prev_node);
        prev_node = curr_node;
    }
    graph.create_bidirectional_arc(prev_node, first_node);

    graph.generate_dot_graph("dot-graphs/graph3.dot");
}
