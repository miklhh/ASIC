
#include "../op.h"
#include "../sfg.h"
#include "catch.hpp"

TEST_CASE("3 tap FIR filter")
{
    SFG fir{};
    NodeID input1 = fir.create_node();
    NodeID input2 = fir.create_node();
    NodeID output = fir.create_node();
    fir.add_adder(input1, input2, output);

}

