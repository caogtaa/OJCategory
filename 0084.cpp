#include "common_headers.h"
#include "helper.h"

using namespace std;

#define DICE_FACE 4
typedef vector<vector<double>> vector2D;

#define L00_JAIL	false

class Matrix
{
public:
    Matrix(int r, int c) {
		data.resize(4*40);
		for (int i = 0; i < 4*40; ++i) {
			data[i].resize(4*40);
		}
        row = r;
        column = c;
    }
    
public:
    void operator += (const Matrix &m) {
        for (int i = 0; i < row; ++i) {
            for (int k = 0; k < column; ++k) {
                data[i][k] += m.data[i][k];
            }
        }
    }
    
    Matrix operator *(const Matrix &m) const {
        Matrix result(row, m.column);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < m.column; ++j) {
                double v = 0.0;
                for (int k = 0; k < column; ++k) {
                    v += data[i][k] * m.data[k][j];
                }
                
                result.data[i][j] = v;
            }
        }
        
        return result;
    }
    
public:
	vector<vector<double>> data;
    int row;
    int column;
};

Matrix OP(const Matrix &X, const Matrix &T, long long x)
{
    Matrix result = X;
    Matrix t = T;
    while (x > 0) {
        if (x & 1) {
            result = result * t;
        }
        
        t = t * t;
        x >>= 1;
    }
    
    return result;
}

unordered_map<string, int> gridIndex;
vector<string> grids = {
	"GO", "A1", "CC1", "A2", "T1",
	"R1", "B1", "CH1", "B2", "B3",
	"JAIL", "C1", "U1", "C2", "C3",
	"R2", "D1", "CC2", "D2", "D3",
	"FP", "E1", "CH2", "E2", "E3",
	"R3", "F1", "F2", "U2", "F3",
	"G2J", "G1", "G2", "CC3", "G3",
	"R4", "CH3", "H1", "T2", "H2"
};

#define L00(x)	(x)
#define L01(x)	(40 + (x))
#define L10(x)	(80 + (x))
#define L11(x)	(120 + (x))

class Solution
{
public:
	void initGridIndex() {
		for (int i = 0; i < grids.size(); ++i) {
			gridIndex[grids[i]] = i;
		}
	}

	void special_trans(Matrix& S, const int& from, const int& to, double p, bool gotoL00 = false) {
		if (gotoL00)
			S.data[from][to%40] += p;
		else
			S.data[from][from/40*40 + to%40] += p;
	}

	void special_trans(Matrix& S, const int& from, const string& to, double p, bool gotoL00 = false) {
		if (gotoL00)
			S.data[from][gridIndex[to]] += p;
		else
			S.data[from][from/40*40 + gridIndex[to]] += p;
	}

	int solve() {
		initGridIndex();
		int result = 0;
		Matrix P(1, 4*40);
		P.data[0][0] = 1.0;

		vector<double> prob(13);	// probability of rolling 2~12
		for (int i = 1; i <= DICE_FACE; ++i) {
			for (int k = 1; k <= DICE_FACE; ++k) {
				prob[i+k] += 1.0;
			}
		}

		for (int i = 2; i <= 2 * DICE_FACE; ++i) {
			prob[i] /= DICE_FACE * DICE_FACE;
		}

		// normal rule, equal probability to next DICE_FACE grids
		// pre-dice and pre-pre-dice should be recorded, so total state is 2*2*40
		Matrix T(4*40, 4*40);
		for (int r = 0; r < 40; ++r) {
			// if roll double, mark as 1 (+1 dangerous level), otherwise 0
			// roll a double
			T.data[L00(r)][L01((r+2) % 40)] += prob[2];
			T.data[L01(r)][L11((r+2) % 40)] += prob[2];
			T.data[L10(r)][L01((r+2) % 40)] += prob[2];
			if (L00_JAIL)
				T.data[L11(r)][L00(gridIndex["JAIL"])] += prob[2];
			else
				T.data[L11(r)][L11(gridIndex["JAIL"])] += prob[2];
			// todo: replace with jail logic
			// T.data[L11(r)][L11((r+2) % 40)] += prob[2];

			// roll other
			for (int k = 3; k <= 2*DICE_FACE; ++k) {
				T.data[L00(r)][L00((r+k) % 40)] += prob[k];

				// 0,1 to 1,0
				T.data[L01(r)][L10((r+k) % 40)] += prob[k];

				// 1,0 to 0,0
				T.data[L10(r)][L00((r+k) % 40)] += prob[k];

				// 1,1 to 1,0	// safe
				T.data[L11(r)][L10((r+k) % 40)] += prob[k];
			}
		}

		auto checkType = [](int id, const string &prefix) {
			id %= 40;
			return grids[id].find(prefix) == 0;
		};

		// special rule
		Matrix GJ(4*40, 4*40);
		for (int i = 0; i < 4*40; ++i) {
			GJ.data[i][i] = 1.0;
			if (checkType(i, "G2J")) {
				GJ.data[i][i] = 0.0;
				special_trans(GJ, i, "JAIL", 1.0, L00_JAIL);	// todo: check
			}
		}

		Matrix CC(4*40, 4*40);
		for (int i = 0; i < 4*40; ++i) {
			CC.data[i][i] = 1.0;
			if (checkType(i, "CC")) {
				CC.data[i][i] = 0.0;
				special_trans(CC, i, "GO", 1.0/16);
				special_trans(CC, i, "JAIL", 1.0/16, L00_JAIL);	// todo: check
				special_trans(CC, i, i, 14.0/16);	// stay
			}
		}

		Matrix CH(4*40, 4*40);
		for (int i = 0; i < 4*40; ++i) {
			CH.data[i][i] = 1.0;
			if (checkType(i, "CH")) {
				CH.data[i][i] = 0.0;
				special_trans(CH, i, "GO", 1.0/16);
				special_trans(CH, i, "JAIL", 1.0/16, L00_JAIL);
				special_trans(CH, i, "C1", 1.0/16);
				special_trans(CH, i, "E3", 1.0/16);
				special_trans(CH, i, "H2", 1.0/16);
				special_trans(CH, i, "R1", 1.0/16);
				for (int k = i+1; ;++k) {
					k %= 40;
					if (checkType(k, "R")) {
						special_trans(CH, i, k, 2.0/16);
						break;
					}
				}
				for (int k = i+1; ;++k) {
					k %= 40;
					if (checkType(k, "U")) {
						special_trans(CH, i, k, 1.0/16);
						break;
					}
				}
				special_trans(CH, i, i-3, 1.0/16);
				special_trans(CH, i, i, 6.0/16);	// stay
			}
		}

		T = T * GJ;
		T = T * CC;
		T = T * CH;
		auto Q = OP(P, T, 1000000);

		auto findProb = [](const Matrix& M, int index) {
			return M.data[0][L00(index)] +
				M.data[0][L01(index)] +
				M.data[0][L10(index)] +
				M.data[0][L11(index)];
		};

		auto x1 = findProb(Q, 0);
		auto x2 = findProb(Q, 10);
		auto x3 = findProb(Q, 24);

		vector<pair<int, double>> qu;
		for (int i = 0; i < 40; ++i) {
			qu.emplace_back(i, findProb(Q, i));
		}

		sort(qu.begin(), qu.end(), [](pair<int, double>& p1, pair<int, double>& p2) {
			return p1.second > p2.second;
		});

		return result;
	}

	PrimeHelper helper;
};

int main()
{
	Solution* s = new Solution();
	cout << s->solve() << endl;
	delete s;
	return 0;
}

// https://projecteuler.net/problem=60
// 状态转移，矩阵求幂
// 难点在于规则的理解以及转换矩阵T的构造
// 规则理解重点：
// 1. 例子有2个6面筛子，求解时用2个4面筛子
// 2. 连续仍3次2会直接送进JAIL
// 3. 送进JAIL后连续2的计数是否清零？

// 构造矩阵T
// 格子有40个，加上需要记录最近两次筛子“是否为2”的状态，总的状态数量是40*4
// (可以优化成最近出现的连续2数量，（0，1，2），优化为40*3)

// 注意：2个6面筛子的计算概率结果和示例数据有出入，但是答案相符
// 2个4面筛子的计算结果也是正确答案