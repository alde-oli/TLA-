#include "inc/math/math.hpp"

#include <iostream>
#include <cmath>
#include <limits> // Pour comparer les résultats avec une tolérance
#include <functional> // Pour utiliser std::function

template <typename T>
bool compare(std::function<T(T)> tlapFunc, std::function<T(T)> stdFunc, T value, T tolerance = std::numeric_limits<T>::epsilon()) {
    T result1 = tlapFunc(value);
    T result2 = stdFunc(value);
    return std::abs(result1 - result2) < tolerance;
}

#include <random>
#include <chrono>
// main to test the time taken by tlap::atan2 compared to std::
int main() {
    // test du temps pris par tlap::atan2 et std::atan2 pour differentes valeurs random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1000.0, 1000.0);
    int iterations = 25000000;
    std::cout << "Testing tlap::atan2 vs std::atan2 for " << iterations << " random values between -1000 and 1000..." << std::endl;
    //store time taken by tlap and std atan2 in a table as well as the result of each function
    std::vector<double> tlapTimes;
    std::vector<double> stdTimes;
    std::vector<double> tlapResults;
    std::vector<double> stdResults;
    for (int i = 0; i < iterations; i++) {
        double x = dis(gen);
        double y = dis(gen);
        auto start = std::chrono::high_resolution_clock::now();
        double tlapResult = tlap::atan2(x, y);
        auto end = std::chrono::high_resolution_clock::now();
        tlapTimes.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        tlapResults.push_back(tlapResult);
        start = std::chrono::high_resolution_clock::now();
        double stdResult = std::atan2(x, y);
        end = std::chrono::high_resolution_clock::now();
        stdTimes.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
        stdResults.push_back(stdResult);
        if (tlapTimes[i] > 2000) {
        std::cout << "values: x = " << x << ", y = " << y << std::endl;
        std::cout << "Test " << i << ": tlap::atan2 = " << tlapResult << " vs std::atan2 = " << stdResult << std::endl;
        std::cout << "Time taken: tlap::atan2 = " << tlapTimes[i] << " ns vs std::atan2 = " << stdTimes[i] << " ns" << std::endl;
        }
    }
    //print average time taken by tlap and std atan2 and average difference between the results
    double tlapTime = 0;
    double stdTime = 0;
    double tlapDiff = 0;
    for (int i = 0; i < iterations; i++) {
        tlapTime += tlapTimes[i];
        stdTime += stdTimes[i];
        tlapDiff += std::abs(tlapResults[i] - stdResults[i]);
    }
    tlapTime /= iterations;
    stdTime /= iterations;
    tlapDiff /= iterations;
    std::cout << "Average time taken by tlap::atan2: " << tlapTime << " ns" << std::endl;
    std::cout << "Average time taken by std::atan2: " << stdTime << " ns" << std::endl;
    std::cout << "average time overhead (%) = " << (tlapTime - stdTime) / stdTime * 100 << std::endl;
    std::cout << "Average difference between tlap::atan2 and std::atan2: " << tlapDiff << std::endl;
}

// int main() {
//     // Valeurs de test
//     double x = 2;
//     double y = 0.5;
//     int n = 3;
//     double base = 2.0;
    
//     std::cout << std::fixed;

//     // Power
//     std::cout << "Pow (2^3): " << tlap::pow(x, n) << " vs std::pow: " << std::pow(x, n) << std::endl;
//     std::cout << "Pow (2^0.5): " << tlap::pow(x, y) << " vs std::pow: " << std::pow(x, y) << std::endl;

//     // Exponentiation and Logarithms
//     std::cout << "Exp (e^2): " << tlap::exp(x) << " vs std::exp: " << std::exp(x) << std::endl;
//     std::cout << "Ln (ln(2)): " << tlap::ln(x) << " vs std::log: " << std::log(x) << std::endl;
//     std::cout << "Log10 (log10(2)): " << tlap::log10(x) << " vs std::log10: " << std::log10(x) << std::endl;
//     std::cout << "Log2 (log2(2)): " << tlap::log2(x) << " vs std::log2: " << std::log2(x) << std::endl;
//     std::cout << "Log base (log2(2)): " << tlap::log(x, base) << " vs std::log(x)/std::log(base): " << std::log(x)/std::log(base) << std::endl;

//     // Root
//     std::cout << "Sqrt (sqrt(2)): " << tlap::sqrt(x) << " vs std::sqrt: " << std::sqrt(x) << std::endl;
//     std::cout << "Cbrt (cbrt(2)): " << tlap::cbrt(x) << " vs std::cbrt: " << std::cbrt(x) << std::endl;
//     std::cout << "Root (2^(1/3)): " << tlap::root(x, n) << " vs std::pow: " << std::pow(x, 1.0/n) << std::endl;

//     // Trigonometry
//     std::cout << "Sin (sin(0.5)): " << tlap::sin(y) << " vs std::sin: " << std::sin(y) << std::endl;
//     std::cout << "Cos (cos(0.5)): " << tlap::cos(y) << " vs std::cos: " << std::cos(y) << std::endl;
//     std::cout << "Tan (tan(0.5)): " << tlap::tan(y) << " vs std::tan: " << std::tan(y) << std::endl;
//     std::cout << "Asin (asin(0.5)): " << tlap::asin(y) << " vs std::asin: " << std::asin(y) << std::endl;
//     std::cout << "Acos (acos(0.5)): " << tlap::acos(y) << " vs std::acos: " << std::acos(y) << std::endl;
//     std::cout << "Atan (atan(0.5)): " << tlap::atan(y) << " vs std::atan: " << std::atan(y) << std::endl;
//     std::cout << "Atan2 (atan2(2, 2)): " << tlap::atan2(x, x) << " vs std::atan2: " << std::atan2(x, x) << std::endl;

//     // Hyperbolic functions
//     std::cout << "Sinh (sinh(2)): " << tlap::sinh(x) << " vs std::sinh: " << std::sinh(x) << std::endl;
//     std::cout << "Cosh (cosh(2)): " << tlap::cosh(x) << " vs std::cosh: " << std::cosh(x) << std::endl;
//     std::cout << "Tanh (tanh(2)): " << tlap::tanh(x) << " vs std::tanh: " << std::tanh(x) << std::endl;

//     // Rounding
//     double z = 3.14;
//     std::cout << "Floor (floor(3.14)): " << tlap::floor(z) << " vs std::floor: " << std::floor(z) << std::endl;
//     std::cout << "Ceil (ceil(3.14)): " << tlap::ceil(z) << " vs std::ceil: " << std::ceil(z) << std::endl;
//     std::cout << "Round (round(3.14)): " << tlap::round(z) << " vs std::round: " << std::round(z) << std::endl;

//     // Other
//     std::cout << "Abs (-2.0): " << tlap::abs(-x) << " vs std::abs: " << std::abs(-x) << std::endl;
//     std::cout << "Mod (5 mod 2): " << tlap::mod(5.0, 2.0) << " vs fmod: " << std::fmod(5.0, 2.0) << std::endl;
//     std::cout << "Factorial (3!): " << tlap::factorial(n) << " vs expected: " << 6 << std::endl;
//     std::cout << "RoughEq (2 ≈ 2.0001): " << tlap::rougheq(2.0, 2.0001, 0.001) << " vs expected: " << true << std::endl;
//     std::cout << "Lerp (lerp(2, 4, 0.5)): " << tlap::lerp(2.0, 4.0, 0.5) << " vs expected: " << 3.0 << std::endl;
//     std::cout << "Clamp (clamp(5, 1, 4)): " << tlap::clamp(5.0, 1.0, 4.0) << " vs expected: " << 4.0 << std::endl;

//     return 0;
// }

// g++ ./test.cpp -O2 -march=native -std=c++17 -Wall -Wextra -Werror -o test && ./test && rm test