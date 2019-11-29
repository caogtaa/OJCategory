#include "common_headers.h"
#include "helper.h"
#include <memory>

using namespace std;

struct HandDetail
{
	enum Rank {
		HighCard = 0,
		OnePair,
		TwoPairs,
		ThreeOfAKind,
		Staight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush,
		RoyalFlush
	};

	vector<int> _cardSeq;	// in desc order
	bool _sameSuit;
	pair<bool, int> _4values;
	pair<bool, int> _3values;
	vector<int> _pairs;
	pair<bool, int> _consecutive;	// <appear, highest card>
	Rank _rank;
};

struct Hand
{
	vector<int> _cardAppear;
	vector<int> _suitAppear;
};

// typedef int (*ValueFunc)(const HandDetail& detail);

typedef function<int(const HandDetail&)> ValueFunc;

bool cardCompare(
	const pair<shared_ptr<HandDetail>, shared_ptr<HandDetail>>& details,
	const vector<ValueFunc>& funcs) 
{
	for (const auto& f : funcs) {
		auto a = f(*(details.first));
		auto b = f(*(details.second));
		if (a != b)
			return a > b;
	}

	return false;
}


class Solution
{
public:
	shared_ptr<HandDetail> getHandDetail(const Hand& hand) {
		auto result = make_shared<HandDetail>();
		int count;
		for (int i = 0; i < 4; ++i) {
			if (hand._suitAppear[i] == 5) {
				result->_sameSuit = true;
			}
		}

		for (int i = 2; i <= 14; ++i) {
			count = hand._cardAppear[i];
			if (!count)
				continue;

			for (int k = 0; k < count; ++k) {
				result->_cardSeq.push_back(i);
			}

			if (count == 2) {
				result->_pairs.push_back(i);
			} else if (count == 3) {
				result->_3values = make_pair(true, i);
			} else if (count == 4) {
				result->_4values = make_pair(true, i);
			}
		}

		sort(result->_cardSeq.begin(), result->_cardSeq.end(), [](int a, int b) {
			return a > b;
		});

		bool consecutive = checkConsecutive(result->_cardSeq);
		if (consecutive) {
			result->_consecutive = make_pair(true, result->_cardSeq[0]);
		}

		sort(result->_pairs.begin(), result->_pairs.end(), [](int a, int b) {
			return a > b;
		});

		// rank it
		if (result->_sameSuit && result->_consecutive.first && result->_consecutive.second == 14) {
			result->_rank = HandDetail::RoyalFlush;
		} else if (result->_sameSuit && result->_consecutive.first) {
			result->_rank = HandDetail::StraightFlush;
		} else if (result->_4values.first) {
			result->_rank = HandDetail::FourOfAKind;
		} else if (result->_3values.first && result->_pairs.size() >= 1) {
			result->_rank = HandDetail::FullHouse;
		} else if (result->_sameSuit) {
			result->_rank = HandDetail::Flush;
		} else if (result->_consecutive.first) {
			result->_rank = HandDetail::Staight;
		} else if (result->_3values.first) {
			result->_rank = HandDetail::ThreeOfAKind;
		} else if (result->_pairs.size() >= 2) {
			result->_rank = HandDetail::TwoPairs;
		} else if (result->_pairs.size() >= 1) {
			result->_rank = HandDetail::OnePair;
		} else {
			result->_rank = HandDetail::HighCard;
		}
		
		return result;
	}

	bool checkConsecutive(const vector<int>& seq) {
		for (int i = 1; i < seq.size(); ++i) {
			if (seq[i] != seq[i-1]-1)
				return false;
		}

		return true;
	}

	bool checkAWin(const Hand& handA, const Hand& handB) {
		auto detailA = getHandDetail(handA);
		auto detailB = getHandDetail(handB);
		if (detailA->_rank != detailB->_rank)
			return detailA->_rank > detailB->_rank;

		ValueFunc highCardValueFunc = [](const HandDetail& d) {
			return d._cardSeq[0];
		};

		ValueFunc flushHighCardValueFunc = [](const HandDetail& d) {
			return d._consecutive.second;
		};

		auto details = make_pair(detailA, detailB);
		if (detailA->_rank == HandDetail::RoyalFlush ||
			detailA->_rank == HandDetail::StraightFlush) {
			vector<ValueFunc> funcs{
				flushHighCardValueFunc,
				highCardValueFunc
			};
			return cardCompare(details, funcs);
		}

		ValueFunc FourValuesFunc = [](auto d) {
			return d._4values.second;
		};

		if (detailA->_rank == HandDetail::FourOfAKind) {
			vector<ValueFunc> funcs{
				FourValuesFunc,
				highCardValueFunc
			};

			return cardCompare(details, funcs);
		}

		if (detailA->_rank == HandDetail::FullHouse) {
			vector<ValueFunc> funcs{
				[](auto d) { return d._3values.second; },
				[](auto d) { return d._pairs[0]; },
				highCardValueFunc
			};

			return cardCompare(details, funcs);
		}

		if (detailA->_rank == HandDetail::Flush || 
			detailA->_rank == HandDetail::Staight) {
			vector<ValueFunc> funcs{
				highCardValueFunc
			};

			return cardCompare(details, funcs);
		}

		if (detailA->_rank == HandDetail::ThreeOfAKind) {
			vector<ValueFunc> funcs{
				[](auto d) { return d._3values.second; },
				highCardValueFunc
			};

			return cardCompare(details, funcs);
		}

		if (detailA->_rank == HandDetail::TwoPairs) {
			vector<ValueFunc> funcs{
				[](auto d) { return d._pairs[0]; },
				[](auto d) { return d._pairs[1]; },
				highCardValueFunc
			};

			return cardCompare(details, funcs);
		}

		if (detailA->_rank == HandDetail::OnePair) {
			vector<ValueFunc> funcs{
				[](auto d) { return d._pairs[0]; },
				highCardValueFunc
			};

			return cardCompare(details, funcs);
		}

		vector<ValueFunc> funcs{
			highCardValueFunc
		};
		return cardCompare(details, funcs);
	}

	bool getHand(Hand& hand) {
		hand._suitAppear.clear();
		hand._suitAppear.resize(4);
		hand._cardAppear.clear();
		hand._cardAppear.resize(15);

		string card;
		int count = 0;
		char c;
		do {
			if (cin >> card) {
				++ hand._cardAppear[cardOrder[card[0]]];
				++ hand._suitAppear[suitOrder[card[1]]];
			} else {
				// EOF
				return false;
			}
		} while(++count < 5);

		return true;
	}

	int solve() {
		FILE *pf = freopen("0054_input.txt", "r", stdin);
		for (char c = '0'; c <= '9'; ++c) {
			cardOrder[c] = c - '0';
		}

		cardOrder['T'] = 10;
		cardOrder['J'] = 11;
		cardOrder['Q'] = 12;
		cardOrder['K'] = 13;
		cardOrder['A'] = 14;

		suitOrder['H'] = 0;
		suitOrder['C'] = 1;
		suitOrder['S'] = 2;
		suitOrder['D'] = 3;

		int result = 0;
		Hand handA, handB;
		while (getHand(handA) && getHand(handB)) {
			if (checkAWin(handA, handB)) {
				++ result;
			}
		}

		fclose(stdin);
		return result;
	}

	int cardOrder[256];
	int suitOrder[256];
};

int main()
{
	Solution s;
	cout << s.solve() << endl;

	return 0;
}

