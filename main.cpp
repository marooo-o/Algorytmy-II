#include "minCostFlow.h"

int main() {
    string fileName = "inCost.txt";
    int finalCost1, finalCost2;

    minCostFlow mcf;

    mcf.debuggMode = 0;
    mcf.testMode = 1;
    mcf.readInput(fileName);
    finalCost1 = mcf.minCostBellmanFord(mcf.cap, mcf.cost);

    if(mcf.testMode) {
        finalCost2 = mcf.minCostDijkstra(mcf.cap, mcf.cost);

        if(finalCost1 == finalCost2) {
            cout << "COMPLETE. Min cost: " << finalCost1 << " == " << finalCost2 << endl;
        } else {
            cout << "ERROR: " << finalCost1 << " != " << finalCost2 << endl;
        }
    } else {
        cout << "minimalny koszt naprawy wynoszi: " << finalCost1 << endl;
    }
    //mcf.minCostDijkstra(mcf.cap, mcf.cost);

    return 0;
}
