#include <iostream>
#include <vector>

using namespace std;

// Function to find the majority element in an array using Divide-and-Conquer
int majorityElementUtil(vector<int>& nums, int left, int right) {
    if (left == right) {
        return nums[left];
    }

    // Divide
    int mid = left + (right - left) / 2;
    int leftMajority = majorityElementUtil(nums, left, mid);
    int rightMajority = majorityElementUtil(nums, mid + 1, right);

    // Combine
    if (leftMajority == rightMajority) {
        return leftMajority;
    }

    // Count occurrences in the entire array
    int leftCount = 0, rightCount = 0;
    for (int num : nums) {
        if (num == leftMajority) {
            leftCount++;
        } else if (num == rightMajority) {
            rightCount++;
        }
    }

    // Return the majority element with more occurrences
    return (leftCount > rightCount) ? leftMajority : rightMajority;
}

// Function to find the majority element in an array
int majorityElement(vector<int>& nums) {
    return majorityElementUtil(nums, 0, nums.size() - 1);
}

int main() {
    vector<int> nums = {3, 2, 3, 1, 3, 4, 3, 8, 3};
    cout << "Given array: [";
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i];
        if (i < nums.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    int majority = majorityElement(nums);
    cout << "Majority element: " << majority << " (appears ";
    int count = 0;
    for (int num : nums) {
        if (num == majority) {
            count++;
        }
    }
    cout << count << " times)" << endl;

    return 0;
}
