#include "catch.hpp"
#include "../graph.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

//
// Use graph with regular map (instead of unordered_map) and set (instead of unordered_set) in the unit tests, so that
// nodes are in total order, which makes reproducing tests a lot easier.
//
using UnitTestArc = BaseArc;
using UnitTestNode = BaseNode<std::set>;
using UnitTestGraph = Graph<UnitTestNode, UnitTestArc, std::map>;

//
// Read all content from a file (until EOF) and return a string with it's content
//
std::string read_file_to_string(const std::string &filename) {
    std::ifstream fs(filename);
    std::stringstream res{};
    res << fs.rdbuf();
    return res.str();
}

TEST_CASE("Insert nodes and arcs to a new graph")
{
    UnitTestGraph graph{};
    NodeID n0 = graph.create_node();
    NodeID n1 = graph.create_node();
    NodeID n2 = graph.create_node();
    graph.create_bidirectional_arc(n0, n1);
    graph.create_arc(n0, n2);
    graph.create_arc(n1, n2);

    std::stringstream s;
    graph.generate_dot_graph(s);
    graph.generate_dot_graph("dot-graphs/test-graph1.dot");
    REQUIRE( read_file_to_string("dot-graphs/ref-graph1.dot") == s.str() );
}

TEST_CASE("Test removing nodes from the graph")
{
    UnitTestGraph graph{};
    NodeID n0 = graph.create_node();
    NodeID n1 = graph.create_node();
    NodeID n2 = graph.create_node();
    NodeID n3 = graph.create_node();
    NodeID n4 = graph.create_node();
    graph.create_bidirectional_arc(n0, n1);
    graph.create_bidirectional_arc(n1, n2);
    graph.create_bidirectional_arc(n2, n3);
    auto arcs = graph.create_bidirectional_arc(n3, n4);
    graph.delete_node(n2);
    graph.delete_arc(arcs.first);

    std::stringstream s;
    graph.generate_dot_graph(s);
    graph.generate_dot_graph("dot-graphs/test-graph2.dot");
    REQUIRE( read_file_to_string("dot-graphs/ref-graph2.dot") == s.str() );

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

    std::stringstream s;
    graph.generate_dot_graph(s);
    graph.generate_dot_graph("dot-graphs/test-graph3.dot");
    REQUIRE( read_file_to_string("dot-graphs/ref-graph3.dot") == s.str() );

}
