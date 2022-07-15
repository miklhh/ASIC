/*
 * Regular directed Graphs
 * Author: Mikael Henriksson (2022)
 */
#ifndef _GRAPH_H
#define _GRAPH_H

#include "trait.h"

#include <assert.h>

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <type_traits>

//
// Identification for Arcs in Graphs
//
using ArcID = int;
constexpr ArcID NO_ARC = ArcID{ -1 };

//
// Identification for Nodes in Graphs
//
using NodeID = int;
constexpr NodeID NO_NODE = NodeID{ -1 };

//
// Base Arc types for Graphs
//
struct BaseArc {
    // Source and destination nodes
    NodeID src;
    NodeID dst;
    BaseArc(NodeID src, NodeID dst) : src{src}, dst{dst} {}
};

//
// Base Node types for Graphs
//
template<template<class...> class SetT = std::unordered_set>
struct BaseNode {
    static_assert(
        is_set_type<SetT<NodeID>>::value,
        "Set container expected"
    );
    SetT<ArcID> inputs{};
    SetT<ArcID> outputs{};
};

//
// Basic Graphs
//
template<
    typename NodeT,     // Nodes in the Graph, should inherit from BaseNode
    typename ArcT,      // Arcs in the Graph, should inherit from BaseArc
    template<class...> class AssociativeArrayT = std::unordered_map>
class Graph {
public:
    virtual ~Graph() = default;

    // Create a new node in the Graph. Returns the newly created nodes identification
    NodeID create_node() {
        NodeID id = next_node_id++;
        node_map[id] = NodeT{};
        return id;
    }

    // Create a new directional arc between two nodes in the Graph
    // Can throw std::out_of_range if one of the NodeIDs refer to a non-existing node.
    ArcID create_arc(const ArcT &arc) {
        // Make sure both arc source node and arc destination node exist before creating arc
        node_map.at(arc.src); node_map.at(arc.dst);

        // Add arc to arc container
        ArcID arcID = next_arc_id++;
        arc_map.insert( {arcID, arc} );

        // Add ArcID to associated Nodes and return
        node_map[arc.src].outputs.insert(arcID);
        node_map[arc.dst].inputs.insert(arcID);
        return arcID;
    }

    // Default construct a new directional arc between two nodes in the Graph
    // Can throw std::out_of_range if one of the NodeIDs refer to a non-existing node.
    ArcID create_arc(NodeID src, NodeID dst)
    {
        // Default construct an arc and insert it
        return create_arc( ArcT(src, dst) );
    }

    // Default construct two new directional arcs, back and forth, between two nodes in the Graph
    // Can throw std::out_of_range if one of the NodeIDs refer to a non-existing node.
    std::pair<ArcID, ArcID> create_bidirectional_arc(NodeID node1, NodeID node2) {
        return { create_arc(node1, node2), create_arc(node2, node1) };
    }

    // Delete a node from the Graph. Associated arcs are automatically removed
    // Can throw std::out_of_range if the node does not exist in the graph
    void delete_node(NodeID nodeID) {
        // Make sure the NodeID refers to a node in the graph
        NodeT &node = node_map.at(nodeID);

        // Remove all arcs going into this node
        // NOTE: Make sure to use an loop-erase idom which does not invalidate the loop iterator variable
        for (auto it=node.inputs.begin(); it != node.inputs.end();) {
            delete_arc(*it++);
        }

        // Remove all arcs going out of this node
        for (auto it=node.outputs.begin(); it != node.outputs.end();) {
            delete_arc(*it++);
        }

        // Remove this node from the node map
        node_map.erase(nodeID);
    };

    // Delete an arc from the graph.
    // Can throw std::out_of_range if the ArcID refers to non-existing arc
    void delete_arc(ArcID arcID) {
        // Make sure the arc exists before removing
        ArcT &arc = arc_map.at(arcID);
        node_map.at(arc.src); node_map.at(arc.dst);
        assert(node_map[arc.src].outputs.count(arcID) > 0);
        assert(node_map[arc.dst].inputs.count(arcID) > 0);
        assert(arc.src != arc.dst);

        // Remove the arc information from source and destination nodes
        node_map[arc.src].outputs.erase(arcID);
        node_map[arc.dst].inputs.erase(arcID);

        // Remove the arc
        arc_map.erase(arcID);
    }

    // Generate a DOT graph from this Graph
    virtual void generate_dot_graph(std::ostream &os) const {
        // Write dot header
        os << "strict digraph {" << std::endl;

        // Write all nodes and associated arcs
        for (const auto &node_pair : node_map) {
            const NodeID &nodeID = node_pair.first;
            const NodeT &node = node_pair.second;
            os << "    " << nodeID << " -> { ";
            for (ArcID arcID: node.outputs) {
                os << arc_map.at(arcID).dst << " ";
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
    static_assert(
        is_associative_array_type<AssociativeArrayT<NodeID, NodeT>>::value,
        "Associate container expected"
    );
    AssociativeArrayT<NodeID, NodeT> node_map{};
    AssociativeArrayT<ArcID, ArcT> arc_map{};

private:
    NodeID next_node_id{ NO_NODE+1 };
    ArcID next_arc_id{ NO_ARC+1 };
};

#endif
