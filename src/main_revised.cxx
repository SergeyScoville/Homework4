#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>

std::vector<int> latticeMaker(int size, double probability) {
    std::vector<int> lattice(size * size, 0);
    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<double> u(0, 1);

    for (int i = 0; i < lattice.size(); ++i) {
        if (u(e) < probability) {
            lattice[i] = 1; // Fill the site
        }
    }
    return lattice;
}

int root(std::vector<int> &cluster, int c) {
    while (cluster[c] != 0) {
        c = cluster[c];
    }
    return c;
}

std::vector<int> clusterAlgorithm(std::vector<int> lattice, std::vector<int> clusterLattice, int L) {
    std::vector<int> cluster(L * L);
    int cnum = 1;

    for (int i = 0; i < (L * L); ++i) {
        // Check right
        if (lattice[i] == 1 && (i + 1) < (L * L) && lattice[i + 1] == 1 && (i + 1) % L != 0) {
            if (clusterLattice[i] == 0 && clusterLattice[i + 1] == 0) {
                clusterLattice[i] = cnum;
                clusterLattice[i + 1] = cnum;
                cluster[cnum] = 0;
                cnum += 1;
            } else if (clusterLattice[i] != 0 && clusterLattice[i + 1] == 0) {
                clusterLattice[i + 1] = clusterLattice[i];
            } else if (clusterLattice[i] == 0 && clusterLattice[i + 1] != 0) {
                clusterLattice[i] = clusterLattice[i + 1];
            } else if (clusterLattice[i] != 0 && clusterLattice[i + 1] != 0 && root(cluster, clusterLattice[i]) != root(cluster, clusterLattice[i + 1])) {
                int mx = std::max(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i + 1]));
                int mn = std::min(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i + 1]));
                cluster[mx] = mn;
            }
        }

        // Check down
        if (lattice[i] == 1 && (i + L) < (L * L) && lattice[i + L] == 1) {
            if (clusterLattice[i] == 0 && clusterLattice[i + L] == 0) {
                clusterLattice[i] = cnum;
                clusterLattice[i + L] = cnum;
                cluster[cnum] = 0;
                cnum += 1;
            } else if (clusterLattice[i] != 0 && clusterLattice[i + L] == 0) {
                clusterLattice[i + L] = clusterLattice[i];
            } else if (clusterLattice[i] == 0 && clusterLattice[i + L] != 0) {
                clusterLattice[i] = clusterLattice[i + L];
            } else if (clusterLattice[i] != 0 && clusterLattice[i + L] != 0 && root(cluster, clusterLattice[i]) != root(cluster, clusterLattice[i + L])) {
                int mx = std::max(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i + L]));
                int mn = std::min(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i + L]));
                cluster[mx] = mn;
            }
        }
    }

    // Final pass to ensure all clusters are connected
    for (int i = 0; i < (L * L); ++i) {
        clusterLattice[i] = root(cluster, clusterLattice[i]);
    }

    return clusterLattice;
}

bool compareFirstAndLastRow(const std::vector<int>& matrix, int L) {
    std::vector<int> firstRow, lastRow;
    
    // Fill the first row
    for (int i = 0; i < L; ++i) {
        if (matrix[i] != 0) {
            firstRow.push_back(matrix[i]);
        }
    }
    
    // Fill the last row
    for (int j = L * (L - 1); j < L * L; ++j) {
        if (matrix[j] != 0) {
            lastRow.push_back(matrix[j]);
        }
    }

    // Check for common elements
    for (int i : firstRow) {
        for (int j : lastRow) {
            if (i == j) {
                return true; // Common element found
            }
        }
    }
    return false; // No common elements
}

int main() {
    for (int L = 200; L <= 700; L += 25) {
        auto start = std::chrono::high_resolution_clock::now();
        std::ofstream outFile;
        std::string fileName = "../data/percolation_data_L_" + std::to_string(L) + ".txt";
        outFile.open(fileName);
        outFile << "p,fraction\n";

        for (double p = 0.01; p <= 1; p += 0.01) {
            double runs = 100;
            double pass = 0;

            for (int run = 0; run < runs; ++run) {
                std::vector<int> lattice = latticeMaker(L, p);
                std::vector<int> latticeClusters(L * L, 0); // Initialize clusterLattice
                latticeClusters = clusterAlgorithm(lattice, latticeClusters, L);

                if (compareFirstAndLastRow(latticeClusters, L)) {
                    pass += 1;
                }
            }
            double fraction = pass / runs;
            outFile << p << "," << fraction << "\n";
        }
        outFile.close();
        std::cout << "Generated L=" << L << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << "Iteration " << L << " took " << duration.count() << " seconds.\n";
    }
    return 0;
}

