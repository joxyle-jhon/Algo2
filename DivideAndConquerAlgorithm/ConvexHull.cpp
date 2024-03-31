#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Function to compute the cross product of vectors (p1p2) x (p1p3)
int crossProduct(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

// Function to find the convex hull of a set of points using the Divide-and-Conquer algorithm
vector<Point> convexHullUtil(vector<Point>& points) {
    int n = points.size();
    if (n <= 3) {
        return points;
    }

    // Sort points based on x-coordinate
    sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
    });

    // Divide the points into two halves
    vector<Point> leftHalf(points.begin(), points.begin() + n / 2);
    vector<Point> rightHalf(points.begin() + n / 2, points.end());

    // Recursively find the convex hulls of the two halves
    vector<Point> convexHullLeft = convexHullUtil(leftHalf);
    vector<Point> convexHullRight = convexHullUtil(rightHalf);

    // Merge the convex hulls of the two halves
    vector<Point> mergedHull;
    for (const Point& point : convexHullLeft) {
        while (mergedHull.size() >= 2 && crossProduct(mergedHull[mergedHull.size() - 2], mergedHull.back(), point) <= 0) {
            mergedHull.pop_back();
        }
        mergedHull.push_back(point);
    }
    for (int i = convexHullRight.size() - 2; i >= 0; --i) {
        while (mergedHull.size() >= 2 && crossProduct(mergedHull[mergedHull.size() - 2], mergedHull.back(), convexHullRight[i]) <= 0) {
            mergedHull.pop_back();
        }
        mergedHull.push_back(convexHullRight[i]);
    }

    return mergedHull;
}

// Function to find the convex hull of a set of points
vector<Point> convexHull(vector<Point>& points) {
    return convexHullUtil(points);
}

int main() {
    vector<Point> points = {{1, 1}, {4, 6}, {8, 2}, {5, 4}, {2, 3}};
    cout << "Given points: [";
    for (size_t i = 0; i < points.size(); ++i) {
        cout << "(" << points[i].x << ", " << points[i].y << ")";
        if (i < points.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    vector<Point> convexHullPoints = convexHull(points);

    cout << "Convex Hull: [";
    for (size_t i = 0; i < convexHullPoints.size(); ++i) {
        cout << "(" << convexHullPoints[i].x << ", " << convexHullPoints[i].y << ")";
        if (i < convexHullPoints.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
