#ifndef _NODE_H
#define _NODE_H

#include "graph.h"
#include "op.h"

#include <unordered_set>

struct Arc {
    Arc() = delete;
    Arc(NodeID dest) : dest{dest} {}
    NodeID dest;
};

struct Node : BaseNode<std::unordered_set> {
    
};

struct FlowGraph : Graph<Node> {

};

#endif
