#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    int x, y;
};

// Function to calculate Euclidean distance between two points
double distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

// Function to compare points based on their x-coordinate
bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// Function to compare points based on their y-coordinate
bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// Function to find the minimum of two double values
double min(double a, double b) {
    return (a < b) ? a : b;
}

// Function to find the distance between the closest pair of points
double closestUtil(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        double minDist = numeric_limits<double>::max();
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                minDist = min(minDist, distance(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = (left + right) / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, left, mid);
    double dr = closestUtil(points, mid, right);

    double minDist = min(dl, dr);

    vector<Point> strip;
    for (int i = left; i < right; i++) {
        if (abs(points[i].x - midPoint.x) < minDist) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }

    return minDist;
}

// Function to find the closest pair of points using a Divide-and-Conquer algorithm
double closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), compareX);
    return closestUtil(points, 0, points.size());
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {4, 1}, {7, 16}, {5, 5}};
    double minDistance = closestPair(points);
    cout << "Closest pair: Distance = " << minDistance << endl;
    return 0;
}
