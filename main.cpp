#include "minCostFlow.h"

int main() {
    minCostFlow mcf;
    cout << "HERE_1" << endl;
    mcf.readInput();
    cout << "HERE_2" << endl;
    mcf.minCost(mcf.cap, mcf.cost);
    cout << "HERE_3" << endl;
    return 0;
}
