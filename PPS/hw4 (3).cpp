/* 22100396 송예지 
Hyperscale AI ChatGPT
*/
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
// struct Node {
//     int level;
//     int benefit;
//     int weight;
//     Node(int l, int b, int w) {
//         level = l;
//         benefit = b;
//         weight = w;
//     }
//     public:
//     int value;
//     int priority;

//     Node(int value, int priority) : value(value), priority(priority) {}

//     bool operator<(const Node& other) const {
//         return priority < other.priority;
//     }
// };

struct Node {
    int level;
    int benefit;
    int weight;
    int bound;

    Node(int l, int b, int w, int bound) : level(l), benefit(b), weight(w), bound(bound) {}

    bool operator<(const Node& other) const {
        return bound < other.bound;
    }
};

int rand_num(int a, int b);
int brute_force(vector<Item>& items, int W, int idx);
double greedy(vector<Item>& items, int W);
int dynamic_programming(vector<Item>& items, int W);
int branch_and_bound(vector<Item>& items, int W);
int bound(Node node, vector<Item>& items, int W);


int main() {
    srand(100);
    int n = 1000; // number of items    0~10000
    int W = n*25; // maximum weight of knapsack
    vector<Item> items;

    cout << "[1] Brute force" << endl;
    int brute[3] = {11, 21, 31};
    cout << "-------------------------------------------------------------------------------"<<endl;
    cout << "|   Number of Items  |   Processing in milliseconds  /  Maximum benefit value   |"<< endl;
    cout << "-------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i<3; i++) {
        for(int j = 0; j<brute[i]; j++) {
            int benefit = rand_num(1, 500);
            int weight = rand_num(1, 100);
            items.push_back(Item(benefit, weight));
        }
        auto start_time_brute = chrono::high_resolution_clock::now();
        int max_benefit = brute_force(items, W, 0);
        auto end_time_brute = chrono::high_resolution_clock::now();
        double duration_brute = chrono::duration_cast<chrono::microseconds>(end_time_brute - start_time_brute).count()/1000000.0;
        cout << "|         "<<  brute[i] << "         |     " << fixed << setprecision(2) << "          " << duration_brute << "            /           " << setw(5) << max_benefit <<  "          |"<< endl;
        items.clear();
    }
    cout << "-------------------------------------------------------------------------------"<<endl;

    cout << endl <<endl;
    cout << "[2] Greedy / D.P. / B.&B." << endl;
    int GDB[4] = {10, 100, 1000, 10000};
    cout << "---------------------------------------------------------------------------------"<<endl;
    cout << "|   Number of Items  |    Processing in milliseconds / Maximum benefit value     |"<< endl;
    cout << "                      ------------------------------------------------------------"<<endl;
    cout << "|                    |      Greedy      |       D.P.       |        B. & B.      |"<< endl;
    cout << "----------------------------------------------------------------------------------"<<endl;
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<GDB[i]; j++) {
            int benefit = rand_num(1, 500);
            int weight = rand_num(1, 100);
            items.push_back(Item(benefit, weight));
        }
        cout << "!" << endl;
        auto start_time_greedy = chrono::high_resolution_clock::now();
        int max_benefit_greedy = greedy(items, W);
        auto end_time_greedy = chrono::high_resolution_clock::now();
        double duration_greedy = chrono::duration_cast<chrono::microseconds>(end_time_greedy - start_time_greedy).count()/1000000.0;
        cout << "1" << endl;
        auto start_time_dp = chrono::high_resolution_clock::now();
        int max_benefit_dp = dynamic_programming(items, W);
        auto end_time_dp = chrono::high_resolution_clock::now();
        double duration_dp = chrono::duration_cast<chrono::microseconds>(end_time_dp - start_time_dp).count()/1000000.0;
        cout << "2" << endl;
        auto start_time_bb = chrono::high_resolution_clock::now();
        int max_benefit_bb = branch_and_bound(items, W);
        auto end_time_bb = chrono::high_resolution_clock::now();
        double duration_bb = chrono::duration_cast<chrono::microseconds>(end_time_bb - start_time_bb).count() / 1000000.0;
        cout << "3" << endl;
        cout << "|      "<<  setw(4) << GDB[i] << "          |  " <<  setw(6) << max_benefit_greedy << " / " << duration_greedy;
        cout << "   |   " <<  setw(6) << max_benefit_dp << " / " << duration_dp;
        cout << "   |   " <<  setw(6) << max_benefit_bb << " / " << duration_bb << "    |" << endl;

        cout << "|      "<<  setw(4) << GDB[i] << "          |  " <<  setw(6) << max_benefit_greedy << " / " << duration_greedy;
        cout << "   |   " <<  setw(6) << max_benefit_dp << " / " << duration_dp;
        cout << "   |   " <<  setw(6) << max_benefit_bb << " / " << duration_bb << "    |" << endl;

        items.clear();
    }
    cout << "----------------------------------------------------------------------------------"<<endl;

    return 0;
}


// Function to generate random numbers between a and b
int rand_num(int a, int b) {
    return rand() % (b - a + 1) + a;
}

// Brute force solution
// int brute_force(vector<Item>& items, int W) {
//     int n = items.size();
//     int max_val = 0;
    
//     for (long int i = 0; i < n; i++) {
//         int total_weight = 0;
//         int total_val = 0;

//         for (int j = 0; j < n; j++) {
//             if (i | j && total_weight + items[j].weight <= W) {
//                 total_weight += items[j].weight;
//                 total_val += items[j].benefit;
//             }
//         }

//         if (total_weight <= W) {
//             max_val = max(max_val, total_val);
//         }
//     }

//     return max_val;
// }
int brute_force(vector<Item>& items, int W, int idx) {
    if (idx == items.size()) {
        return 0;
    }

    int without_item = brute_force(items, W, idx + 1);

    if (W - items[idx].weight < 0) {
        return without_item;
    }

    int with_item = items[idx].benefit + brute_force(items, W - items[idx].weight, idx + 1);

    return max(with_item, without_item);
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
// int branch_and_bound(vector<Item>& items, int W) {
//     int n = items.size();
//     int max_benefit = 0;

//     // Sort items by benefit-to-weight ratio
//     sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
//         return ((double)a.benefit / a.weight) > ((double)b.benefit / b.weight);
//     });

//     // Create root node
//     Node root(-1, 0, 0);
//     priority_queue<Node> pq;
//     pq.push(root);

//     while (!pq.empty()) {
//         Node node = pq.top();
//         pq.pop();

//         // Check if node can be expanded
//         if (node.level == n - 1) {
//             // Leaf node
//             max_benefit = max(max_benefit, node.benefit);
//         }
//         else {
//             // Non-leaf node
//             int level = node.level + 1;
//             int weight = node.weight;
//             int benefit = node.benefit;

//             // Take the item at this level
//             if (weight + items[level].weight <= W) {
//                 pq.push(Node(level, benefit + items[level].benefit, weight + items[level].weight));
//             }

//             // Do not take the item at this level
//             int potential_benefit = benefit;
//             for (int i = level + 1; i < n; i++) {
//                 potential_benefit += items[i].benefit;
//             }
//             if (potential_benefit > max_benefit) {
//                 pq.push(Node(level, benefit, weight));
//             }
//         }
//     }

//     return max_benefit;
// }

int branch_and_bound(vector<Item>& items, int W) {
    int n = items.size();
    int max_benefit = 0;

    // Sort items by benefit-to-weight ratio
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return ((double)a.benefit / a.weight) > ((double)b.benefit / b.weight);
    });

    // Create root node
    Node root(-1, 0, 0, 0);
    root.bound = bound(root, items, W);
    priority_queue<Node> pq;
    pq.push(root);

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        // Check if node can be expanded
        if (node.bound > max_benefit) {
            if (node.level == n - 1) {
                // Leaf node
                max_benefit = max(max_benefit, node.benefit);
            } else {
                // Non-leaf node
                int level = node.level + 1;
                int weight = node.weight;
                int benefit = node.benefit;

                // Take the item at this level
                if (weight + items[level].weight <= W) {
                    Node take_node(level, benefit + items[level].benefit, weight + items[level].weight, 0);
                    take_node.bound = bound(take_node, items, W);
                    if (take_node.bound > max_benefit) {
                        pq.push(take_node);
                    }
                }

                // Do not take the item at this level
                Node not_take_node(level, benefit, weight, 0);
                not_take_node.bound = bound(not_take_node, items, W);
                if (not_take_node.bound > max_benefit) {
                    pq.push(not_take_node);
                }
            }
        }
    }

    return max_benefit;
}

int bound(Node node, vector<Item>& items, int W) {
    int n = items.size();
    int bound = node.benefit;

    if (node.weight >= W) {
        return 0;
    }

    int i;
    for (i = node.level + 1; i < n && node.weight + items[i].weight <= W; i++) {
        bound += items[i].benefit;
        node.weight += items[i].weight;
    }

    if (i < n) {
        bound += (W - node.weight) * ((double)items[i].benefit / items[i].weight);
    }

    return bound;
}