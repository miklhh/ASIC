/*
 * Regular directed graphs
 */
#ifndef _GRAPH_H
#define _GRAPH_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>

//
// Identification for nodes in Graphs
//
using NodeID = int;
constexpr NodeID NO_NODE = NodeID{ -1 };

//
// Basic nodes for Graphs
//
template<typename SetT = std::unordered_set<NodeID>>
struct BaseNode {
    SetT inputs{};
    SetT outputs{};
};

//
// The Graph
//
template <
    typename NodeT,
    typename AssociativeArrayT = std::unordered_map<NodeID, NodeT>,
    typename SetT = std::unordered_set<NodeID>>
class Graph {
public:
    // Create a new node in the class. Returns the newly created nodes identification
    NodeID create_node() {
        NodeID id = next_id++;
        hash_map[id] = NodeT{};
        return id;
    }

    // Create a new directional arc between two nodes in the Graph
    // Can throw std::out_of_range if one of the nodes does not exist
    void create_arc(NodeID from, NodeID to) {
        // Make sure both nodes exists before creating arc
        hash_map.at(from); hash_map.at(to);

        // Add the arc
        hash_map[from].outputs.insert(to);
        hash_map[to].inputs.insert(from);

    }

    // Create two new directional arcs, back and forth, between two nodes in the Graph
    // Can throw std::out_of_range if one of the nodes does not exist
    void create_bidirectional_arc(NodeID node1, NodeID node2) {
        create_arc(node1, node2);
        create_arc(node2, node1);
    }

    // Delete a node from the Graph. Associated arcs are automatically removed
    // Can throw std::out_of_range if the node does not exist in the graph
    void delete_node(NodeID id) {
        // Remove all arcs going into this node
        for (auto &from_id : hash_map.at(id).inputs) {
            hash_map[from_id].outputs.erase(id);
        }
        // Remove all arcs going out of this node
        for (auto &to_id : hash_map.at(id).outputs) {
            hash_map[to_id].inputs.erase(id);
        }
        // Remove the node from the hash map
        hash_map.erase(id);
    };

    // Delete an arc from the graph.
    void delete_arc(NodeID from, NodeID to) {
        // Make sure both nodes exists before deleting arc
        hash_map.at(from); hash_map.at(to);

        // Remove the arc
        hash_map[from].outputs.erase(to);
        hash_map[to].inputs.erase(from);
    }

    // Generate a DOT graph from this Graph
    void generate_dot_graph(std::ostream &os) const {
        // Write dot header
        os << "strict digraph {" << std::endl;

        // Write all nodes and associated arcs
        for (const auto &node_pair : hash_map) {
            const NodeID &nodeID = node_pair.first;
            const NodeT &node = node_pair.second;
            os << "    " << nodeID << " -> { ";
            for (const auto out : node.outputs) {
                os << out << " ";
            }
            os << "}" << std::endl;
        }

        // Write dot footer
        os << "}";
    }

    // Write a DOT graph of this Graph to a file
    void generate_dot_graph(const std::string &filename) const {
        std::ofstream f(filename);
        generate_dot_graph(f);
    }
protected:
    AssociativeArrayT hash_map{};

private:
    NodeID next_id{ NO_NODE+1 };
};

#endif
