#include "minCostFlow.h"

int main() {
    string fileName = "inCost.txt";
    int finalCost1, finalCost2;

    minCostFlow mcf;

    mcf.debuggMode = 1;
    mcf.readInput(fileName);
    finalCost1 = mcf.minCostBellmanFord(mcf.cap, mcf.cost);

    cout << "minimalny koszt naprawy wynoszi: " << finalCost1 << endl;
    //mcf.minCostDijkstra(mcf.cap, mcf.cost);

    return 0;
}
