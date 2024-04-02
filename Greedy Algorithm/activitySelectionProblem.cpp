#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an activity
struct Activity {
    int start, end;
};

// Comparator function to sort activities based on end times
bool compareEndTimes(const Activity& a1, const Activity& a2) {
    return a1.end < a2.end;
}

int maxActivities(vector<Activity>& activities) {
    // Sort activities based on end times
    sort(activities.begin(), activities.end(), compareEndTimes);

    // Select the first activity by default
    int count = 1;
    int prevFinishTime = activities[0].end;

    // Iterate through the sorted list of activities
    for (int i = 1; i < activities.size(); ++i) {
        // If the start time of the current activity is greater than or equal to the finish time of the previously selected activity
        // Select the current activity and update prevFinishTime
        if (activities[i].start >= prevFinishTime) {
            count++;
            prevFinishTime = activities[i].end;
        }
    }

    return count;
}

int main() {
    vector<Activity> activities = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}};

    int maxCount = maxActivities(activities);

    cout << "Activities: ";
    for (int i = 0; i < activities.size(); ++i) {
        cout << "(" << activities[i].start << ", " << activities[i].end << ") ";
    }
    cout << endl;

    cout << "Maximum activities: " << maxCount << " (Selection: ";
    int selected = 0;
    for (int i = 0; i < activities.size(); ++i) {
        if (activities[i].start >= selected) {
            cout << "(" << activities[i].start << ", " << activities[i].end << ") ";
            selected = activities[i].end;
        }
    }
    cout << ")" << endl;

    return 0;
}
