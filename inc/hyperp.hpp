#ifndef HYPERP_HPP
# define HYPERP_HPP

# include <limits>

# define PI 3.14159265358979323846
# define E 2.71828182845904523536
# define MAX_RECURSION 1000
# define EPSILON std::numeric_limits<double>::epsilon()
# define EXP_LIMIT 709
# define EXP_TERMS 50
# define LN2 0.69314718055994530942
# define LN10 2.30258509299404568402
# define LN_TERMS 50
# define PHI 1.61803398874989484820
# define FACTORIAL_SWITCH 20

# ifndef SIMD
#  define SIMD 0
# endif

# ifndef MULTITHREAD
#  define MULTITHREAD 0
# endif

#endif