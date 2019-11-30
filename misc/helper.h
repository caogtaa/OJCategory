#include <vector>
#include <string>
#include <tuple>

class PrimeHelper {
public:
    std::vector<bool> _notPrime;
    std::vector<int> _phi;

public:
    void init(int n);

    inline bool isPrime(int n) {
        return !_notPrime[n];
    }

    static bool millerRabinPrimeTest(long long n);

    std::vector<int> getPrimes(int start, int end);

    // init phi function array, depend on primes
    void initPhi(int n);

    // Euler's Totient Function
    inline int phi(int n) {
        return _phi[n];
    }

    // e.g. 13 and its rotation 31 are both prime
    bool isCircularPrime(int p);

    // e.g. 3797 and its truncation 797, 97, 7, 379, 37, 3 are both prime
    bool isTruncatablePrime(int p);

private:
    static bool _millerRabinTest(long long a, long long n);
};

class Util {
public:
    static bool isPalindromic(int n, int base = 10);

    static bool isPalindromic(const std::vector<int>& seq);

    // time: O(len(s))
    static bool isPalindromic(const std::string& s);

    // return the sum of proper divisor (not include n itself)
    // time: O(sqrt(n))
    // space: O(1)
    static int sumOfDivisor(int n);

    // fraction cycle length of 1/d
    // time: O(d) in worst case
    // space: O(d) in worst case
    static int fractionCycleLength(int d);

    static int digitCount(int n);

    // kth digit of number, index k start from 0
    static int kthDigit(int n, int k);

    // IDF: irrational decimal fraction, index k start from 0
    // IDF = 0.123456789101112131415...
    static int kthDigitOfIDF(int k);

    // return sum of the factorial of the digits
    // e.g. F(145) = 1! + 4! + 5!
    static int digitFactorialSum(int n);

    // greatest common divisor
    static long long gcd(long long a, long long b);

    // least common multiplier
    static long long lcm(long long a, long long b);

    // return (n^e) % mod for large result
    static unsigned long long powMod(unsigned long long n, unsigned long long e, unsigned long long mod);

    static std::vector<int> getDigits(int n);

    static int getNumber(const std::vector<int>& digits);

    static std::vector<int> sqrtContinuedFraction(int n);

    static std::string intToRoman(int num);

    static int romanToInt(const std::string& s);

    static int bitCount(uint32_t n);

    static std::vector<int> factorSums(int n);

    static int lowBit(int n);

    // y = F(x)
    // use Lagrange Interpolation to construct Q which fit top n items from y = F(x)
    // then return Q(k)
    // note: make sure pow(xi, len(x)) never overflow a long long variant in worst case, otherwise use BigNum library instead
    // referrence: https://www.zhihu.com/question/58333118
    static long long lagrangeInterpolation(const std::vector<long long>& x, const std::vector<long long>& y, int n, int k);
};

class SpecialNumber {
public:
    // return tuple<A,B,C> which satisfy A*B = C and digit 1~9 appear exactly once
    // e.g. 48*159 = 7632
    // note C = 5346 appears in 2 tuples
    // from ProjectEuler 0032
    static std::vector<std::tuple<int,int,int>> pandigitalProducts();

    static bool isPandigital(int n);

    // from ProjectEuler 0041
    static int largestNPandigitalPrime();

    static bool isPentagonalNumber(long long n);

    static bool isTriangleNumber(long long n);

    static bool isSquareNumber(long long n);
};

class SuDokuHelper {
public:
    SuDokuHelper(std::vector<std::vector<int>>& board);
    bool solve();

protected:
    bool search();

private:
    std::vector<std::vector<int>>& _board;
    std::vector<int> _number;
    std::vector<std::pair<int,int>> _rest;
    int _row[9];
    int _col[9];
    int _group[3][3];
};
