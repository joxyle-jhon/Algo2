#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a job
struct Job {
    int weight;
    int deadline;
};

// Comparator function for sorting jobs based on deadlines
bool compareJobs(const Job& job1, const Job& job2) {
    return job1.deadline < job2.deadline;
}

int scheduleJobs(vector<Job>& jobs) {
    int maxJobs = 0;

    // Sort jobs based on deadlines
    sort(jobs.begin(), jobs.end(), compareJobs);

    // Greedy selection
    vector<bool> slots(jobs.size(), false);
    for (const Job& job : jobs) {
        for (int i = min(job.deadline - 1, (int)jobs.size() - 1); i >= 0; --i) {
            if (!slots[i]) {
                slots[i] = true;
                maxJobs++;
                break;
            }
        }
    }

    return maxJobs;
}

int main() {
    // Sample input
    vector<Job> jobs = {{2, 1}, {5, 2}, {4, 1}, {6, 3}};

    // Solve job scheduling problem
    int maxJobs = scheduleJobs(jobs);

    // Output
    cout << "Jobs: ";
    for (int i = 0; i < jobs.size(); ++i) {
        cout << "(" << jobs[i].weight << ", " << jobs[i].deadline << ") ";
    }
    cout << endl;

    cout << "Maximum jobs: " << maxJobs << " (Selection: ";
    for (int i = 0; i < jobs.size(); ++i) {
        if (i < maxJobs) {
            cout << "(" << jobs[i].weight << ", " << jobs[i].deadline << ")";
            if (i < maxJobs - 1) cout << ", ";
        }
    }
    cout << ")" << endl;

    return 0;
}
