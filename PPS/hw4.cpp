#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip> // std::setprecision
using namespace std;

// Define a struct for items
struct Item {
    int benefit;
    int weight;
    Item(int b, int w) {
        benefit = b;
        weight = w;
    }
};

// Node for branch and bound
struct Node {
    int level;
    int benefit;
    int weight;
    Node(int l, int b, int w) {
        level = l;
        benefit = b;
        weight = w;
    }
    public:
    int value;
    int priority;

    Node(int value, int priority) : value(value), priority(priority) {}

    bool operator<(const Node& other) const {
        return priority < other.priority;
    }
};

int rand_num(int a, int b);
int brute_force(vector<Item>& items, int W);
double greedy(vector<Item>& items, int W);
int dynamic_programming(vector<Item>& items, int W);
int branch_and_bound(vector<Item>& items, int W);



int main() {
    srand(time(NULL));
    int n = 1000; // number of items    0~10000
    int W = n*25; // maximum weight of knapsack
    vector<Item> items;
    for (int i = 0; i < n; i++) {
        int benefit = rand_num(10, 100);
        int weight = rand_num(1, 20);
        items.push_back(Item(benefit, weight));
    }

    cout << "Brute force solution:" << endl;
    auto start_time = chrono::high_resolution_clock::now();
    int max_benefit = brute_force(items, W);
    auto end_time = chrono::high_resolution_clock::now();
    cout << "Max benefit: " << max_benefit << endl;
    double duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()/1000000.0;
    cout << "Time taken: " << duration << " microseconds" << endl << endl;

    cout << "Greedy solution:" << endl;
    start_time = chrono::high_resolution_clock::now();
    double max_benefit_greedy = greedy(items, W);
    end_time = chrono::high_resolution_clock::now();
    cout << "Max benefit: " << max_benefit_greedy << endl;
    duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()/1000000.0;
    cout << "Time taken: " << duration << " microseconds" << endl << endl;

    cout << "Dynamic programming solution:" << endl;
    start_time = chrono::high_resolution_clock::now();
    int max_benefit_dp = dynamic_programming(items, W);
    end_time = chrono::high_resolution_clock::now();
    cout << "Max benefit: " << max_benefit_dp << endl;
    duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count()/1000000.0;
    cout << "Time taken: " << fixed << setprecision(2) << duration << " seconds\n" << endl;

    cout << "Branch and bound solution:" << endl;
    start_time = chrono::high_resolution_clock::now();
    int max_benefit_bb = branch_and_bound(items, W);
    end_time = chrono::high_resolution_clock::now();
    cout << "Max benefit: " << max_benefit_bb << endl;
    // duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    // cout << "Time taken: " << duration << " microseconds" << endl;
    duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000000.0;
    cout << "Time taken: " << fixed << setprecision(2) << duration << " seconds" << endl;
    // auto dur = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    // cout << "Time taken: " << dur << " milliseconds" << endl;

    return 0;
}


// Function to generate random numbers between a and b
int rand_num(int a, int b) {
    return rand() % (b - a + 1) + a;
}

// Brute force solution
int brute_force(vector<Item>& items, int W) {
    int n = items.size();
    int max_val = 0;
    
    for (int i = 0; i < (1 << n); i++) {
        int total_weight = 0;
        int total_val = 0;

        for (int j = 0; j < n; j++) {
            if (i | (1 << j) && total_weight + items[j].weight <= W) {
                total_weight += items[j].weight;
                total_val += items[j].benefit;
            }
        }

        if (total_weight <= W) {
            max_val = max(max_val, total_val);
        }
    }

    return max_val;
}



// Greedy solution (for fractional knapsack problem)
double greedy(vector<Item>& items, int W) {
    int n = items.size();
    double max_benefit = 0.0;
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return ((double)a.benefit / a.weight) > ((double)b.benefit / b.weight);
    });
    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        if (total_weight + items[i].weight <= W) {
            total_weight += items[i].weight;
            max_benefit += items[i].benefit;
        }
        else {
            int remaining_weight = W - total_weight;
            max_benefit += ((double)remaining_weight / items[i].weight) * items[i].benefit;
            break;
        }
    }
    return max_benefit;
}

// Dynamic programming solution
int dynamic_programming(vector<Item>& items, int W) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (items[i - 1].weight <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - items[i-1].weight] + items[i - 1].benefit);
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][W];
}

// Branch and bound solution
int branch_and_bound(vector<Item>& items, int W) {
    int n = items.size();
    int max_benefit = 0;

    // Sort items by benefit-to-weight ratio
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return ((double)a.benefit / a.weight) > ((double)b.benefit / b.weight);
    });

    // Create root node
    Node root(-1, 0, 0);
    priority_queue<Node> pq;
    pq.push(root);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        // Check if node can be expanded
        if (node.level == n - 1) {
            // Leaf node
            max_benefit = max(max_benefit, node.benefit);
        }
        else {
            // Non-leaf node
            int level = node.level + 1;
            int weight = node.weight;
            int benefit = node.benefit;

            // Take the item at this level
            if (weight + items[level].weight <= W) {
                pq.push(Node(level, benefit + items[level].benefit, weight + items[level].weight));
            }

            // Do not take the item at this level
            int potential_benefit = benefit;
            for (int i = level + 1; i < n; i++) {
                potential_benefit += items[i].benefit;
            }
            if (potential_benefit > max_benefit) {
                pq.push(Node(level, benefit, weight));
            }
        }
    }

    return max_benefit;
}