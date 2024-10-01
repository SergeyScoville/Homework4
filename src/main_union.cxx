#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <set>
#include <numeric>  // For std::iota

std::vector<int> latticeMaker(int size, double probability) {
    std::vector<int> lattice(size * size, 0);
    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<double> u(0, 1);

    for (int i = 0; i < lattice.size(); ++i) {
        lattice[i] = (u(e) < probability) ? 1 : 0;
    }
    return lattice;
}

// Union-Find Structure
class UnionFind {
public:
    UnionFind(int size) : parent(size) {
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent to self
    }

    int find(int a) {
        if (parent[a] != a) {
            parent[a] = find(parent[a]); // Path compression
        }
        return parent[a];
    }

    void unionSets(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            parent[rootB] = rootA; // Union
        }
    }

private:
    std::vector<int> parent;
};

std::vector<int> clusterAlgorithm(const std::vector<int>& lattice, int L) {
    UnionFind uf(L * L);
    for (int i = 0; i < L * L; ++i) {
        if (lattice[i] == 1) {
            if ((i + 1 < L * L) && (lattice[i + 1] == 1) && ((i + 1) % L != 0)) {
                uf.unionSets(i, i + 1);
            }
            if ((i + L < L * L) && (lattice[i + L] == 1)) {
                uf.unionSets(i, i + L);
            }
        }
    }
    std::vector<int> clusterLattice(L * L);
    for (int i = 0; i < L * L; ++i) {
        clusterLattice[i] = uf.find(i);
    }
    return clusterLattice;
}

bool compareFirstAndLastRow(const std::vector<int>& clusterLattice, int L) {
    std::set<int> firstRow, lastRow;
    for (int i = 0; i < L; ++i) {
        if (clusterLattice[i] != 0) {
            firstRow.insert(clusterLattice[i]);
        }
    }
    for (int j = L * (L - 1); j < L * L; ++j) {
        if (clusterLattice[j] != 0) {
            lastRow.insert(clusterLattice[j]);
        }
    }
    for (const auto& elem : firstRow) {
        if (lastRow.count(elem)) {
            return true; // Same number found in both rows
        }
    }
    return false; // No matching number found
}

int main() {
    for (int L = 50; L <= 50; L += 2) {
        std::ofstream outFile("../data/percolation_data_L_" + std::to_string(L) + ".txt");
        outFile << "p,fraction\n";
        for (double p = 0.01; p <= 1; p += 0.01) {
            int runs = 100;
            int pass = 0;
            for (int run = 0; run < runs; ++run) {
                std::vector<int> lattice = latticeMaker(L, p);
                std::vector<int> latticeClusters = clusterAlgorithm(lattice, L);
                if (compareFirstAndLastRow(latticeClusters, L)) {
                    pass += 1;
                }
            }
            double fraction = static_cast<double>(pass) / runs;
            outFile << p << "," << fraction << "\n";
        }
        outFile.close();
        std::cout << "Generated L=" << L << std::endl;
    }
    return 0;
}
