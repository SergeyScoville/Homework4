#include <iostream>
#include <vector>
#include <random>
#include <fstream>

std::vector<int> latticeMaker(int size, double probability) {
    std::vector<int> lattice(size * size, 0);
    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_real_distribution<double> u(0, 1);

    for (int i = 0; i < lattice.size(); ++i) {
        if (u(e) < probability) {
            lattice[i] = 1;
        }
    }
    return lattice;
}

int root(std::vector<int> cluster, int c) {
    while (cluster[c] != 0) {
        c = cluster[c];
    }
    return c;
}

std::vector<int> clusterAlgorithm(std::vector<int> lattice, std::vector<int> clusterLattice, int L) {
    std::vector<int> cluster(L*L);
    int cnum = 1;
    for (int i = 0; i < (L * L); ++i) {
        if (lattice[i] == 1 and lattice[i+1] == 1 and ((i+1) % L) != 0) {
            if (clusterLattice[i] == 0 and clusterLattice[i+1] == 0) {
                clusterLattice[i] = cnum;
                clusterLattice[i+1] = cnum;
                cluster[cnum] = 0;
                cnum += 1;
            } else if (clusterLattice[i] != 0 and clusterLattice[i+1] == 0) {
                clusterLattice[i+1] = clusterLattice[i];
            } else if (clusterLattice[i] == 0 and clusterLattice[i+1] != 0) {
                clusterLattice[i] = clusterLattice[i+1];
            } else if (clusterLattice[i] != 0 and clusterLattice[i+1] != 0 and root(cluster, clusterLattice[i]) != root(cluster,clusterLattice[i+1])) {
                int mx = std::max(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i+1]));
                int mn = std::min(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i+1]));
                cluster[mx] = mn;
            }
        }
        if (lattice[i] == 1 and lattice[i+L] == 1 and (i+L) < (L*L)) {
            if (clusterLattice[i] == 0 and clusterLattice[i+L] == 0) {
                clusterLattice[i] = cnum;
                clusterLattice[i+L] = cnum;
                cluster[cnum] = 0;
                cnum += 1;
            } else if (clusterLattice[i] != 0 and clusterLattice[i+L] == 0) {
                clusterLattice[i+L] = clusterLattice[i];
            } else if (clusterLattice[i] == 0 and clusterLattice[i+L] != 0) {
                clusterLattice[i] = clusterLattice[i+L];
            } else if (clusterLattice[i] != 0 and clusterLattice[i+L] != 0 and root(cluster, clusterLattice[i]) != root(cluster,clusterLattice[i+L])) {
                int mx = std::max(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i+L]));
                int mn = std::min(root(cluster, clusterLattice[i]), root(cluster, clusterLattice[i+L]));
                cluster[mx] = mn;
            }
        }
    }
    for (int i = 0; i < (L * L); ++i) {
        clusterLattice[i] = root(cluster, clusterLattice[i]);
    }
    return clusterLattice;
}

void printLattice(std::vector<int> lattice, int L) {
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            std::cout << lattice[i * L + j] << " ";
        }
        std::cout << std::endl;
    }
}

bool compareFirstAndLastRow(const std::vector<int>& matrix, int L) {
    // Loop over the elements in the first row (indices 0 to L-1)
    for (int i = 0; i < L; ++i) {
        // Loop over the elements in the last row (indices L*(L-1) to L*L-1)
        for (int j = L * (L - 1); j < L * L; ++j) {
            if (matrix[i] == matrix[j] and matrix[i] != 0) {
                return true; // Same number found in both rows
            }
        }
    }
    return false; // No matching number found
}

int main() {

    for (int L = 50; L <= 50; L += 2) {  // Loop through L from 2 to 50
        std::ofstream outFile;
        std::string fileName = "../data/percolation_data_L_" + std::to_string(L) + ".txt";
        outFile.open(fileName);
        outFile << "p,fraction\n";
        for (double p = 0.01; p <= 1; p += 0.01) {
            double run = 1;
            double pass = 0;
            double runs = 100;
            while (run < runs) {
                std::vector<int> lattice = latticeMaker(L, p);
                std::vector<int> latticeClusters =  latticeMaker(L, 0);
                latticeClusters = clusterAlgorithm(lattice, latticeClusters, L);
                if (compareFirstAndLastRow(latticeClusters, L)) {
                    pass += 1;
                }
                run += 1;
            }
            double fraction = pass / runs;
            outFile << p << "," << fraction << "\n";
        }
        outFile.close();
        std::cout << "Generated L=" << L << std::endl;
    }

    /*
    double p = 0.5;  // Probability of a site being open
    std::vector<int> lattice = latticeMaker(L, p);
    std::vector<int> latticeClusters =  latticeMaker(L, 0);

    // Print the lattice in 2D form
    std::cout << "Initial Lattice: " << std::endl;
    printLattice(lattice, L);

    latticeClusters = clusterAlgorithm(lattice, latticeClusters, L);
    std::cout << "Final clusterLattice: " << std::endl;
    printLattice(latticeClusters, L);
    if (compareFirstAndLastRow(latticeClusters, L)) {
        std::cout << "Percolation definition, make the computers go loco" << std::endl;
    } else {
        std::cout << "Boo you suck bozo, try again!" << std::endl;
    }*/
    return 0;


}