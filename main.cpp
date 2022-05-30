#include "minCostFlow.h"

int main() {
    string fileName = "inCost.txt";
    int finalCost1, finalCost2;

    minCostFlow mcf;

    mcf.debuggMode = 0;
    mcf.testMode = 0;
    mcf.readInput(fileName);
    finalCost1 = mcf.minCostBellmanFord(mcf.cap, mcf.costBellmanFord);
    if(mcf.testMode) {
        finalCost2 = mcf.minCostDijkstra(mcf.cap, mcf.costDijkstra);

        if(finalCost1 == finalCost2) {
            cout << "COMPLETE. Min cost: " << finalCost1 << " == " << finalCost2 << endl;
        } else {
            cout << "ERROR:  BellmanFord: " << finalCost1 << " != Dijkstra: " << finalCost2 << endl;
        }
    } else {
        cout << "minimalny koszt naprawy wynoszi: " << finalCost1 << endl;
    }

    return 0;
}
