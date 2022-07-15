#ifndef _SFG_H
#define _SFG_H

#include "graph.h"

#include <vector>

/*
 * Each Arc in an SFG is associated with an operand.
 */
enum class OperandType {

    // Delay operand type
    DELAY,

    // Addition operand types: SUM = TERM + TERM 
    TERM,

    // Subtraction operand types: ??? = 

    // Multiplication operand types: PRODUCT = MULTIPLIER * MULTIPLICAND
    MULTIPLIER,
    MULTIPLICAND,

    // Division operand types: QUOTIENT = DIVISOR / DIVIDEND ???
    DIVISOR,
    DIVIDEND,
};

struct SFGArc : public BaseArc {
    SFGArc(NodeID src, NodeID dst, OperandType op) : BaseArc(src, dst), op{op} {}
    OperandType op;
};

struct SFGNode : public BaseNode<> {
    std::string name{};
};

class SFG : public Graph<SFGNode, SFGArc> {
public:
    // Add a delay element to the SFG
    void add_delay(NodeID in, NodeID out) {
        create_arc( SFGArc(in, out, OperandType::DELAY) );
    }

    // Add an adder to the SFG.
    void add_adder(NodeID in1, NodeID in2, NodeID res) {
        create_arc( SFGArc(in1, res, OperandType::TERM) );
        create_arc( SFGArc(in2, res, OperandType::TERM) );
    }

    // Add an multiplier to the SFG.
    void add_multiplier(NodeID in1, NodeID in2, NodeID res) {
        create_arc( SFGArc(in1, res, OperandType::MULTIPLIER) );
        create_arc( SFGArc(in2, res, OperandType::MULTIPLICAND) );
    }

};

#endif
