#ifndef _SFG_H
#define _SFG_H

#include "graph.h"
#include "op.h"

#include <vector>

struct SFGNode {
    Op type{};
    std::string name{};
    std::vector<NodeID> inputs{};
    std::vector<NodeID> outputs{};
};

class SFG : public Graph<SFGNode> {
    
};

#endif
