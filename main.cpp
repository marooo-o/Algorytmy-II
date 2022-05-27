#include "minCostFlow.h"

int main() {
    string fileName = "inCost.txt";

    minCostFlow mcf;

    mcf.debuggMode = 1;
    //mcf.readInput(fileName);

    mcf.minCost(mcf.cap, mcf.cost);

    return 0;
}
