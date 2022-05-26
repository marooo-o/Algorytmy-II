#include <iostream>
#include <fstream>
#include <string>
#include<climits>
#include<vector>

using namespace std;

class minCostFlow {
public:
    bool debuggMode = false;
    vector<vector<int>> cap, cost;
    void readInput(string fileName);
    int miniDist(vector<int> dist, vector<bool> found);
    void DijkstraAlgo(vector<vector<int>> cost, int src, bool print);
    int minCost(vector<vector<int>>, vector<vector<int>>);
};
