#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
    double valuePerWeight; // Value per unit weight
};

// Comparator function for sorting items based on value per unit weight
bool compareItems(const Item& item1, const Item& item2) {
    return item1.valuePerWeight > item2.valuePerWeight;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    double totalValue = 0.0;
    int remainingCapacity = capacity;

    // Calculate value per unit weight for each item
    for (Item& item : items) {
        item.valuePerWeight = static_cast<double>(item.value) / item.weight;
    }

    // Sort items based on value per unit weight
    sort(items.begin(), items.end(), compareItems);

    // Greedy selection
    for (const Item& item : items) {
        if (remainingCapacity >= item.weight) {
            // Add entire item
            totalValue += item.value;
            remainingCapacity -= item.weight;
        } else {
            // Add fraction of item
            totalValue += (static_cast<double>(remainingCapacity) / item.weight) * item.value;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    // Sample input
    vector<Item> items = {{2, 60}, {3, 90}, {4, 100}};
    int capacity = 5;

    // Solve fractional knapsack problem
    double maxValue = fractionalKnapsack(items, capacity);

    // Output
    cout << "Items: ";
    for (int i = 0; i < items.size(); ++i) {
        cout << "(" << items[i].weight << ", " << items[i].value << ") ";
    }
    cout << endl;

    cout << "Knapsack weight limit: " << capacity << endl;
    cout << "Maximum value: " << maxValue << " (Take ";
    for (int i = 0; i < items.size(); ++i) {
        if (capacity >= items[i].weight) {
            cout << "all of item " << i + 1;
        } else {
            cout << capacity << "/" << items[i].weight << " of item " << i + 1;
        }
        capacity -= min(capacity, items[i].weight);
        if (i < items.size() - 1 && capacity > 0) cout << " and ";
    }
    cout << ")" << endl;

    return 0;
}
