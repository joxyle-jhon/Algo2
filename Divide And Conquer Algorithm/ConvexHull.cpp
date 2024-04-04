#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Point structure to represent 2D points
struct Point {
    int x, y;
};

// Utility function to find the orientation of three points (p, q, r)
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;     // Collinear
    return (val > 0) ? 1 : 2;   // Clockwise or counterclockwise
}

// Utility function to compare two points based on their polar angle
bool compare(Point p1, Point p2) {
    int o = orientation({0, 0}, p1, p2);
    if (o == 0)
        return (p1.x * p1.x + p1.y * p1.y) < (p2.x * p2.x + p2.y * p2.y);
    return o == 2;
}

// Function to find the convex hull using Divide and Conquer algorithm
vector<Point> convexHullUtil(vector<Point>& points, int n) {
    // Base case: If there are 3 or fewer points, they form the convex hull
    if (n <= 3) return points;

    // Sort points based on their x-coordinate
    sort(points.begin(), points.end(), [](Point p1, Point p2) {
        return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
    });

    // Divide the points into two halves
    int mid = n / 2;
    vector<Point> left_half(points.begin(), points.begin() + mid);
    vector<Point> right_half(points.begin() + mid, points.end());

    // Recursively find the convex hull for both halves
    vector<Point> left_hull = convexHullUtil(left_half, mid);
    vector<Point> right_hull = convexHullUtil(right_half, n - mid);

    // Merge the convex hulls of the two halves
    vector<Point> merged_hull;
    merge(left_hull.begin(), left_hull.end(), right_hull.begin(), right_hull.end(), back_inserter(merged_hull), compare);

    return merged_hull;
}

// Function to find the convex hull of a set of points
vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    // If there are fewer than 3 points, no need to calculate the convex hull
    if (n < 3) return {};

    // Find the convex hull using Divide and Conquer algorithm
    return convexHullUtil(points, n);
}

// Utility function to print points
void printPoints(const vector<Point>& points) {
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;
}

int main() {
    // Sample input points
    vector<Point> points = {{1, 1}, {4, 6}, {8, 2}, {5, 4}, {2, 3}};

    cout << "Given points: ";
    printPoints(points);

    // Find the convex hull
    vector<Point> hull = convexHull(points);

    cout << "Convex Hull: ";
    printPoints(hull);

    return 0;
}
