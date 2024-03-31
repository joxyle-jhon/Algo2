#include <iostream>

// Function to compute a^b using Divide-and-Conquer
long long power(int a, int b) {
    if (b == 0) return 1; // Base case: a^0 = 1
    long long half_power = power(a, b / 2); // Divide
    if (b % 2 == 0)
        return half_power * half_power; // Combine for even exponent
    else
        return a * half_power * half_power; // Combine for odd exponent
}

int main() {
    int a = 3, b = 5;
    std::cout << "Compute " << a << "^" << b << std::endl;
    std::cout << "Result: " << power(a, b) << std::endl;
    return 0;
}
