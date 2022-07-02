#ifndef _OP_H
#define _OP_H

#include <unordered_map>

enum class Op {
    INPUT,
    OUTPUT,
    ADD,
    SUB,
    MULT,
    CONSTMULT,
    DELAY,
};

struct OpOption {
    int inputs;
    int outputs;
};

// Map of options for the different operators
const std::unordered_map<Op,OpOption> OP_OPTIONS{
    { Op::INPUT,        OpOption{ .inputs = 0, .outputs = 1 } },
    { Op::OUTPUT,       OpOption{ .inputs = 1, .outputs = 0 } },
    { Op::ADD,          OpOption{ .inputs = 2, .outputs = 1 } },
    { Op::SUB,          OpOption{ .inputs = 2, .outputs = 1 } },
    { Op::MULT,         OpOption{ .inputs = 2, .outputs = 1 } },
    { Op::CONSTMULT,    OpOption{ .inputs = 1, .outputs = 1 } },
    { Op::DELAY,        OpOption{ .inputs = 1, .outputs = 1 } },
};

#endif
