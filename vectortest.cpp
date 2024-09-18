#include <immintrin.h>
#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include <map>

#define SIMD_THRESHOLD 1

// Fonction pour générer des nombres aléatoires
float random_float() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}

// Remplit un tableau avec des valeurs aléatoires
template <typename T>
void fill_random_tab(T* tab, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        tab[i] = random_float();
    }
}

// Version SIMD pour remplir des tableaux avec des valeurs aléatoires
template <typename T>
void simd_fill_random_tab(T* tab, size_t n) {
    if (n >= SIMD_THRESHOLD) {
#ifdef __AVX__
        size_t i = 0;
        for (; i < n; ++i) {
            tab[i] = random_float();
        }
#else
        fill_random_tab(tab, n);
#endif
    } else {
        fill_random_tab(tab, n);
    }
}

// SIMD avec AVX multadd
std::vector<float> simd_multadd(const std::vector<float>& tab1, const std::vector<float>& tab2, const std::vector<float>& tab3) {
    size_t n = tab1.size();
    std::vector<float> newtab(n);

#ifdef __AVX__
    size_t i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256 a = _mm256_loadu_ps(&tab1[i]);
        __m256 b = _mm256_loadu_ps(&tab2[i]);
        __m256 c = _mm256_loadu_ps(&tab3[i]);
        __m256 result = _mm256_fmadd_ps(a, b, c);  // fused multiply-add
        _mm256_storeu_ps(&newtab[i], result);
    }
    for (; i < n; ++i) {
        newtab[i] = tab1[i] * tab2[i] + tab3[i];
    }
#else
    for (size_t i = 0; i < n; ++i) {
        newtab[i] = tab1[i] * tab2[i] + tab3[i];
    }
#endif

    return newtab;
}

// SIMD sans AVX multadd
std::vector<float> simd_no_multadd(const std::vector<float>& tab1, const std::vector<float>& tab2, const std::vector<float>& tab3) {
    size_t n = tab1.size();
    std::vector<float> newtab(n);

#ifdef __AVX__
    size_t i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256 a = _mm256_loadu_ps(&tab1[i]);
        __m256 b = _mm256_loadu_ps(&tab2[i]);
        __m256 c = _mm256_loadu_ps(&tab3[i]);
        __m256 mul = _mm256_mul_ps(a, b);  // multiplication
        __m256 result = _mm256_add_ps(mul, c);  // addition
        _mm256_storeu_ps(&newtab[i], result);
    }
    for (; i < n; ++i) {
        newtab[i] = tab1[i] * tab2[i] + tab3[i];
    }
#else
    for (size_t i = 0; i < n; ++i) {
        newtab[i] = tab1[i] * tab2[i] + tab3[i];
    }
#endif

    return newtab;
}

// Non-SIMD avec AVX multadd
std::vector<float> no_simd_multadd(const std::vector<float>& tab1, const std::vector<float>& tab2, const std::vector<float>& tab3) {
    size_t n = tab1.size();
    std::vector<float> newtab(n);
    
    for (size_t i = 0; i < n; ++i) {
        newtab[i] = tab1[i] * tab2[i] + tab3[i];  // pas de SIMD mais multadd
    }

    return newtab;
}

// Non-SIMD sans AVX multadd
std::vector<float> no_simd_no_multadd(const std::vector<float>& tab1, const std::vector<float>& tab2, const std::vector<float>& tab3) {
    size_t n = tab1.size();
    std::vector<float> newtab(n);

    for (size_t i = 0; i < n; ++i) {
        newtab[i] = tab1[i] * tab2[i] + tab3[i];
    }

    return newtab;
}

int main() {
    std::vector<size_t> sizes = {3, 5, 7, 10, 20, 30, 40, 50, 75, 100, 150, 200, 250, 500, 750, 1000, 1250, 1500, 1750, 2000, 2500, 300, 4000, 5000, 7500, 10000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 25000, 50000, 75000, 100000};  // Different sizes to test
    size_t iterations = 1000;

    // Structure to store results: size -> list of times
    struct Result {
        double creation_fill_time = 0;
        double no_multadd_operation_time = 0;
        double multadd_operation_time = 0;
        double total_time = 0;
    };

    std::map<size_t, Result> simd_results, no_simd_results;

    for (size_t size : sizes) {
        
        for (size_t i = 0; i < iterations; ++i) {
            std::vector<float> tab1(size), tab2(size), tab3(size);

            // Start timing
            auto start = std::chrono::high_resolution_clock::now();

            // Fill random data (NO SIMD)
            fill_random_tab(tab1.data(), size);
            fill_random_tab(tab2.data(), size);
            fill_random_tab(tab3.data(), size);

            auto creation_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> creation_duration = creation_time - start;

            // No SIMD, no multadd
            auto no_simd_start = std::chrono::high_resolution_clock::now();
            auto result_no_simd = no_simd_no_multadd(tab1, tab2, tab3);
            auto no_simd_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> no_simd_duration = no_simd_time - creation_time;

            // No SIMD, with multadd
            auto multadd_start = std::chrono::high_resolution_clock::now();
            auto result_multadd = no_simd_multadd(tab1, tab2, tab3);
            auto multadd_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> multadd_duration = multadd_time - no_simd_time;

            // Total time for no SIMD
            auto no_simd_total_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> total_duration_no_simd = no_simd_total_time - start;

            // Store no SIMD results
            no_simd_results[size].creation_fill_time += creation_duration.count();
            no_simd_results[size].no_multadd_operation_time += no_simd_duration.count();
            no_simd_results[size].multadd_operation_time += multadd_duration.count();
            no_simd_results[size].total_time += total_duration_no_simd.count();

            // SIMD fill
            auto simd_start = std::chrono::high_resolution_clock::now();
            simd_fill_random_tab(tab1.data(), size);
            simd_fill_random_tab(tab2.data(), size);
            simd_fill_random_tab(tab3.data(), size);

            auto simd_creation_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> simd_creation_duration = simd_creation_time - simd_start;

            // SIMD without multadd
            auto simd_no_multadd_start = std::chrono::high_resolution_clock::now();
            auto simd_result_no_multadd = simd_no_multadd(tab1, tab2, tab3);
            auto simd_no_multadd_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> simd_no_multadd_duration = simd_no_multadd_time - simd_no_multadd_start;

            // SIMD with multadd
            auto simd_multadd_start = std::chrono::high_resolution_clock::now();
            auto simd_result_multadd = simd_multadd(tab1, tab2, tab3);
            auto simd_multadd_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> simd_multadd_duration = simd_multadd_time - simd_multadd_start;

            // Total time for SIMD
            auto simd_total_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> total_duration_simd = simd_total_time - simd_start;

            // Store SIMD results
            simd_results[size].creation_fill_time += simd_creation_duration.count();
            simd_results[size].no_multadd_operation_time += simd_no_multadd_duration.count();
            simd_results[size].multadd_operation_time += simd_multadd_duration.count();
            simd_results[size].total_time += total_duration_simd.count();
        }

        // Calculate and store the average for this size after all iterations
        no_simd_results[size].creation_fill_time /= iterations;
        no_simd_results[size].no_multadd_operation_time /= iterations;
        no_simd_results[size].multadd_operation_time /= iterations;
        no_simd_results[size].total_time /= iterations;

        simd_results[size].creation_fill_time /= iterations;
        simd_results[size].no_multadd_operation_time /= iterations;
        simd_results[size].multadd_operation_time /= iterations;
        simd_results[size].total_time /= iterations;
    }

    // Display final results in a format suitable for plotting

    std::cout << "SIMD Results:\n";
    std::cout << "Size,Creation_Fill_Time,No_MultAdd_Operation_Time,MultAdd_Operation_Time,Total_Time\n";
    for (const auto& [size, result] : simd_results) {
        std::cout << size << "," << result.creation_fill_time << "," << result.no_multadd_operation_time << "," 
                  << result.multadd_operation_time << "," << result.total_time << "\n";
    }

    std::cout << "\nNO SIMD Results:\n";
    std::cout << "Size,Creation_Fill_Time,No_MultAdd_Operation_Time,MultAdd_Operation_Time,Total_Time\n";
    for (const auto& [size, result] : no_simd_results) {
        std::cout << size << "," << result.creation_fill_time << "," << result.no_multadd_operation_time << "," 
                  << result.multadd_operation_time << "," << result.total_time << "\n";
    }

    return 0;
}

