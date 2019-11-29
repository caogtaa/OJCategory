#include <utility>
#include <algorithm>
#include <map>
#include "helper.h"

using namespace std;

// implementation of PrimeHelper
void PrimeHelper::init(int n) {
    // init prime table of number [1, n]
    _notPrime.resize(n+1);
    _notPrime[0] = _notPrime[1] = true;

    int end = sqrt(n);
    int i, j;
    for (i = 2; i <= end; ++i) {
        if (_notPrime[i])
            continue;

        for (j = i * i; j <= n; j += i)
            _notPrime[j] = true;
    }
}

void PrimeHelper::initPhi(int n) {
    init(n);
    auto primes = getPrimes(2, n);

    _phi.resize(n+1);
    _phi[1] = 1;

    int k;
    int q, g;
    for (k = 2; k <= n; ++k) {
        if (isPrime(k)) {
            _phi[k] = k-1;
            continue;
        }

        for (auto p : primes) {
            if (k % p == 0) {
                q = k / p;
                g = Util::gcd(p, q);
                _phi[k] = (int)((long long)_phi[p] * _phi[q] * g / _phi[g]);
                break;
            }
        }
    }
}

bool PrimeHelper::_millerRabinTest(long long a, long long n) {
    if (n == 2)
        return true;
    if (n == 1 || (n & 1) == 0)
        return false;
 
    long long d = n-1;
    d = n-1;
    while ((d & 1) == 0) {
        d >>= 1;
    }
    
    long long t = Util::powMod(a, d, n);
    while (d != n-1 && t != 1 && t != n-1) {
        t = (t * t) % n;
        d <<= 1;
    }
    
    return t == n-1 || (d & 1);
}

bool PrimeHelper::millerRabinPrimeTest(long long n) {
    return _millerRabinTest(2, n) &&
        _millerRabinTest(7, n) &&
        _millerRabinTest(61, n);
}

vector<int> PrimeHelper::getPrimes(int start, int end) {
    // return primes in range [start, end]
    vector<int> result;
    for (int i = max(2, start); i <= end; ++i) {
        if (!_notPrime[i])
            result.push_back(i);
    }

    return result;
}

bool PrimeHelper::isCircularPrime(int p) {
    int len = Util::digitCount(p);
    for (int i = 0; i < len; ++i) {
        if (!isPrime(p))
            return false;

        p = p / 10 + (int)pow(10, len-1) * (p % 10);	// rotate
    }

    return true;
}

bool PrimeHelper::isTruncatablePrime(int p) {
    int copyp = p;
    while (p) {
        if (!isPrime(p))
            return false;
        p /= 10;
    }

    int base = (int)pow(10, Util::digitCount(copyp));
    while (copyp) {
        if (!isPrime(copyp))
            return false;

        copyp %= base;
        base /= 10;
    }

    return true;
}

// implementation of Util
bool Util::isPalindromic(int n, int base) {
    if (n == 0)
        return true;

    vector<int> seq;
    while (n) {
        seq.push_back(n % base);
        n /= base;
    }

    return isPalindromic(seq);
}

bool Util::isPalindromic(const std::vector<int>& seq) {
    for (int i = 0; i < seq.size() / 2; ++i) {
        if (seq[i] != seq[seq.size()-1-i])
            return false;
    }

    return true;
}

bool Util::isPalindromic(const string& s) {
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size()-1-i])
            return false;
    }

    return true;
}

int Util::sumOfDivisor(int n) {
    int result = 0;
    for (int i = 2; i <= (int)sqrt(n); ++i) {
        if (n % i == 0) {
            result += i;
            if (n / i != i)
                result += n / i;
        }
    }

    return result + 1;	// +1 to include number 1
}

int Util::fractionCycleLength(int d) {
    // d is expected to be positive
    if (d == 1)
        return 0;

    vector<int> appear(d);
    appear[0] = -1; // break condition when rest % d == 0

    int rest = 1;
    int digit = 1;
    while (!appear[rest]) {
        appear[rest] = digit++;
        rest *= 10;
        rest %= d;
    }

    if (rest == 0)
        // no cycle
        return 0;

    return digit - appear[rest];
}

int Util::digitCount(int n) {
    if (n == 0)
        return 1;

    return (int)log10(n) + 1;
}

int Util::kthDigit(int n, int k) {
    int digitCount = Util::digitCount(n);
    if (k >= digitCount)
        return -1;

    int base = pow(10, digitCount-1);
    while (k > 0) {
        -- k;
        n %= base;
        base /= 10;
    }

    return n / base;
}

int Util::kthDigitOfIDF(int k) {
    // sum[x] is decimal length of concatent of all x digit numbers
    static int sum[] = {0, 9, 180, 2700, 36000, 450000, 5400000, 63000000, 720000000};

    // check count of digit of that number
    int d = 1;
    while (k >= sum[d]) {
        k -= sum[d++];
    }

    int base = (int)pow(10, d-1);
    int n = base + k / d;       // n is the number hold kth digit
    return kthDigit(n, k % d);
}

int Util::digitFactorialSum(int n) {
    static int M[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    int result = 0;
    while (n) {
        result += M[n % 10];
        n /= 10;
    }

    return result;
}

int Util::gcd(int a, int b) {
    int tmp;
    while (b) {
        tmp = a;
        a = b;
        b = tmp % b;
    }
   
    return a;
}

unsigned long long Util::powMod(unsigned long long n, unsigned long long e, unsigned long long mod) {
    unsigned long long result = 1LL;
    while (e) {
        if (e & 1) {
            result = (result * n) % mod;
            -- e;
        } else {
            n = (n * n) % mod;
            e >>= 1;
        }
    }

    return result;
}

vector<int> Util::getDigits(int n) {
    int d = Util::digitCount(n);
    vector<int> result(d);
    while (d--) {
        result[d] = n % 10;
        n /= 10;
    }

    return result;
}

int Util::getNumber(const vector<int>& digits) {
    int result = 0;
    for (auto d : digits) {
        result *= 10;
        result += d;
    }

    return result;
}

int Util::lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

vector<int> Util::sqrtContinuedFraction(int n) {
    // https://www.yuque.com/caomou/mgxqtg/melatw#d2SMO
    int a0 = (int)sqrt(n);
    vector<int> result;
    if (SpecialNumber::isSquareNumber(n)) {
        result.push_back(a0);
    } else {
        int ai_1 = 0, Pi_1 = 0, Qi_1 = n;
        int ai = 0, Pi, Qi;

        // stop when a = 2a0
        for (int i = 0; ai != (a0 << 1); ++i) {
            Pi = ai_1 * Qi_1 - Pi_1;
            Qi = (n - Pi * Pi) / Qi_1;
            ai = (a0 + Pi) / Qi;

            ai_1 = ai;
            Pi_1 = Pi;
            Qi_1 = Qi;
            result.push_back(ai);
        }
    }

    return result;
}

string Util::intToRoman(int num) {
    string result;
    while (num >= 1000) {
        result += 'M';
        num -= 1000;
    }
    
    if (num / 100 == 9) {
        result += "CM";
        num -= 900;
    }
    
    if (num / 100 == 4) {
        result += "CD";
        num -= 400;
    }
    
    if (num >= 500) {
        result += 'D';
        num -= 500;
    }
    
    while (num >= 100) {
        result += 'C';
        num -= 100;
    }
    
    if (num / 10 == 9) {
        result += "XC";
        num -= 90;
    }
    
    if (num / 10 == 4) {
        result += "XL";
        num -= 40;
    }
    
    if (num >= 50) {
        result += 'L';
        num -= 50;
    }
    
    while (num >= 10) {
        result += 'X';
        num -= 10;
    }
    
    if (num == 9) {
        result += "IX";
        num -= 9;
    }
    
    if (num == 4) {
        result += "IV";
        num -= 4;
    }
    
    if (num >= 5) {
        result += 'V';
        num -= 5;
    }
    
    while (num) {
        result += 'I';
        -- num;
    }
    
    return result;
}

int _extract(string& s, const string& pattern, int delta) {
    int result = 0;
    while (s.find(pattern) == 0) {
        result += delta;
        s = s.substr(pattern.size());
    }
    
    return result;
}

int Util::romanToInt(const string& origin) {
    int result = 0;

    auto s = origin;
    result += _extract(s, "M", 1000);
    result += _extract(s, "CM", 900);
    result += _extract(s, "CD", 400);
    result += _extract(s, "D", 500);
    result += _extract(s, "C", 100);
    result += _extract(s, "XC", 90);
    result += _extract(s, "XL", 40);
    result += _extract(s, "L", 50);
    result += _extract(s, "X", 10);
    result += _extract(s, "IX", 9);
    result += _extract(s, "IV", 4);
    result += _extract(s, "V", 5);
    result += _extract(s, "I", 1);
    return result;
}

int Util::bitCount(uint32_t n) {
    n -= (n & 0xAAAAAAAA)>>1;
    n = (n >> 2 & 0x33333333) + (n & 0x33333333);
    n = (n + (n>>4)) & 0x0f0f0f0f;
    n = (n + (n>>8));
    n = (n + (n>>16)) & 0x000000ff;
    return n; 
}

vector<int> Util::factorSums(int n)
{
    // Get sum of all factors of n, excluding n itself
    // e.g. S(28)=1+2+4+7+14
    // Note: this is not O(N) algorithm.
    // But with its simplicity, it's still fast enough for N <= 1e^6
    // A real O(N) algorithm require all primes <= N being calculated, see PE 0095 for detail
    vector<int> result;
    result.resize(n+1);
    for (int i = 1; i <= n; ++i) {
        for (int k = i<<1; k <= n; k+=i) {
            result[k] += i;
        }
    }

    return result;
}

int Util::lowBit(int n) {
    return n & (n^(n-1));
}

// implementation of SpecialNumber
vector<tuple<int,int,int>> SpecialNumber::pandigitalProducts() {
    typedef tuple<int,int,int> T;
    return vector<T>{
        T{4, 1738, 6952},
        T{4, 1963, 7852},
        T{12, 483, 5796},
        T{18, 297, 5346},
        T{27, 198, 5346},
        T{28, 157, 4396},
        T{39, 186, 7254},
        T{42, 138, 5796},
        T{48, 159, 7632}
    };
}

bool SpecialNumber::isPandigital(int n) {
    int digitCount = Util::digitCount(n);
    int d;
    vector<bool> appear(digitCount+1);
    do {
        d = n % 10;
        if (d <= 0 || d > digitCount || appear[d])
            return false;

        appear[d] = true;
        n /= 10;
    } while (n);

    return true;
}

int SpecialNumber::largestNPandigitalPrime() {
    return 7652413;
}

bool SpecialNumber::isPentagonalNumber(long long n) {
    // https://en.wikipedia.org/wiki/Pentagonal_number
    if (n <= 0)
        return false;

    long long y = (long long)sqrt(24 * n + 1);
    return (y + 1) % 6 == 0 && y * y == 24 * n + 1;
}

bool SpecialNumber::isTriangleNumber(long long n) {
    long long y = (long long)sqrt(n * 2);
    return y * (y+1) / 2 == n;
}

bool SpecialNumber::isSquareNumber(long long n) {
    long long y = (long long)sqrt(n);
    return y * y == n;
}

// implementation of SuDokuHelper
#define SUDOKU_N_WEIGHT(x)	    (1 << (x-1))
#define SUDOKU_HAS_N(x, n)	    ((x) & SUDOKU_N_WEIGHT(n))
#define SUDOKU_REMOVE_N(x, n)	((x) & ~SUDOKU_N_WEIGHT(n))
#define SUDOKU_FULL()	        (SUDOKU_N_WEIGHT(10)-1)

SuDokuHelper::SuDokuHelper(vector<vector<int>> &board) : _board(board) {
    _number.resize(1<<9);
    for (int i = 0; i < 9; ++i) {
        _number[1<<i] = i;
    }
}

bool SuDokuHelper::solve() {
    // fill row
    for (int r = 0; r < 9; ++r) {
        _row[r] = SUDOKU_FULL();
        for (int k = 0; k < 9; ++k) {
            if (_board[r][k])
                _row[r] = SUDOKU_REMOVE_N(_row[r], _board[r][k]);
        }
    }

    // fill col
    for (int c = 0; c < 9; ++c) {
        _col[c] = SUDOKU_FULL();
        for (int k = 0; k < 9; ++k) {
            if (_board[k][c])
                _col[c] = SUDOKU_REMOVE_N(_col[c], _board[k][c]);
        }
    }

    // fill group
    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            _group[i][k] = SUDOKU_FULL();
        }
    }

    int gr, gc;
    for (int i = 0; i < 9; ++i) {
        gr = i/3;
        for (int k = 0; k < 9; ++k) {
            gc = k/3;
            if (_board[i][k])
                _group[gr][gc] = SUDOKU_REMOVE_N(_group[gr][gc], _board[i][k]);
            else
                _rest.emplace_back(i, k);
        }
    }

    return search();
}

bool SuDokuHelper::search() {
    if (_rest.size() == 0)
        return true;

    auto p = _rest.back();
    int r = p.first;
    int c = p.second;

    // guess is all possible choice for current grid
    int guess = _row[r] & _col[c] & _group[r/3][c/3];
    if (guess == 0)
        // no choice for this grid
        return false;

    _rest.pop_back();
    int lb;
    int mask = 0;
    while (guess) {
        lb = Util::lowBit(guess);
        _board[r][c] = _number[lb] + 1;
        _row[r] ^= lb;
        _col[c] ^= lb;
        _group[r/3][c/3] ^= lb;
        guess ^= lb;
        if (search())
            return true;

        _row[r] ^= lb;
        _col[c] ^= lb;
        _group[r/3][c/3] ^= lb;
    }

    _board[r][c] = 0;
    _rest.push_back(p);
    return false;
}
