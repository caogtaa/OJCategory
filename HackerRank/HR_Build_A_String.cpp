// Build A String
// https://www.hackerrank.com/challenges/build-a-string
// Suffix Automaton 后缀自动机
// 题意: 从左到右构造一个字符串，每次可以用代价A新建一个字符加到尾部，或者用代价B从左侧拷贝一段字符拼接到尾部
// 思路:
// 假设我们已经知道k位置能从前面拷贝的最大长度copyLen[], 可以简单地用DP来解决，复杂度O(N): F[k] = min(A+F[k+1], B+F[k+copylen[k]])
// 找到copyLen最简单的方法是在构造后缀自动机的同时计算copyLen，在SAM扩展k之前，把从k位置开始的字符串喂入SAM，看看能走多远得到matchLen
// 每个位置都从头走一遍SAM，在最坏情况下会得到O(N^2)的时间复杂度（如果所有字符都相同）
// 优化思路是，matchLen[k+1]至少是matchLen[k]-1，因为S[k+1...?) 是S[k...?)长度-1的后缀
// 更好的情况是S[k+1...?)可以继续往后匹配，判定是否可以继续匹配的条件是，matchLen是否还在SAM当前所在state的长度范围内
// 即minLen(state) <= matchLen <= maxLen(state)
// 如果matchLen < minLen(state)，则state移动至state的suffix link （代码里会解释每次迭代最多移动两次）
// 根据SAM的性质，往suffix link移动相当于减少匹配长度，并感知匹配串在母串中的更多出现位置，以此尝试继续匹配寻找更多的匹配可能性
// 每个字符最多会匹配1次，每个位置最多移动2次suffix link，所以额外维护matchLen的过程复杂度O(N)，SAM构造和DP过程都是O(N)，整体时间复杂度O(N)
int main(int argc, const char * argv[])
{
    int T;
    cin >> T;
   
    SAM sam;
    while (T-- > 0) {
        int N, A, B;
        cin >> N >> A >> B;
       
        string S;
        cin >> S;
        sam.init(N);
       
        vector<int> copyLen(N);
        int node = 0;
        int matchLen = 0;
        for (int i = 0; i < N; ++i) {
            -- matchLen;
            if (matchLen <= 0) {
                matchLen = 0;
                node = 0;
            } else {
                int count = 0;
                while (sam[node].link != -1 && matchLen <= sam[sam[node].link].len) {
                    // matchLen < minLen(currentNode)
                    // shold not stop on current node, move backward to suffix link
                    // which would have more chance to extend match length
                    // for a static SAM, only need to move at most once
                    // but because we use an online construction and matchLen maintainance
                    // matchLen decrease and suffix link may change, so there is a chance that sometimes we have to move backward twice, that's why I use a while loop
                   
                    // to elaborate this case, when maxLen(s) = 4, minLen(s) = 3, maxLen(link(s)) = 2 and matchLen == 3
                    // after one more char is appended, link(s) changed and maxLen(link(s)) = 3
                    // at the same time matchLen decrease to 2, then two step backward is required
                    // this is a property of SAM node that minLen may change (when its suffix link changes), but maxLen never change
                    ++ count;
                    node = sam[node].link;
                }
            }
           
            int k = i + matchLen;
            while (k < N && sam[node].next.count(S[k])) {
                node = sam[node].next[S[k]];
                ++ matchLen;
                ++ k;
            }
           
            copyLen[i] = matchLen;
            sam.extend(S[i]);
        }
       
        // make F, F[i] is minimum cost to build S.substr(i)
        vector<int> F(N + 1);
        F[N] = 0;
        for (int i = N - 1; i >= 0; --i) {
            int v = F[i+1] + A;
            if (copyLen[i] > 0) {
                v = min(v, B + F[i+copyLen[i]]);
            }
           
            F[i] = v;
        }
        cout << F[0] << endl;
    }
    return 0;
}

SAM类
class SAM
{
public:
    struct State {
        int len;
        int link;
        unordered_map<char, int> next;
    };
   
public:
    void init(int predicateLen = 0) {
        if (predicateLen > 0) {
            _st.reserve(predicateLen << 1);
            _st.resize(1);
            _st[0].len = 0;
            _st[0].link = -1;
            _st[0].next.clear();
            _last = 0;
        }
    }
   
    void extend(char c) {
        int cur = addState();
        _st[cur].len = _st[_last].len + 1;
        int p;
        for (p = _last; p != -1 && !_st[p].next.count(c); p = _st[p].link)
            _st[p].next[c] = cur;
        if (p == -1)
            _st[cur].link = 0;
        else {
            int q = _st[p].next[c];
            if (_st[p].len + 1 == _st[q].len)
                _st[cur].link = q;
            else {
                int clone = addState();
                _st[clone].len = _st[p].len + 1;
                _st[clone].next = _st[q].next;
                _st[clone].link = _st[q].link;
                for (; p != -1 && _st[p].next[c] == q; p = _st[p].link)
                    _st[p].next[c] = clone;
               
                _st[q].link = _st[cur].link = clone;
            }
        }
       
        _last = cur;
    }
   
    inline State& operator[](std::size_t idx) {
        return _st[idx];
    }
   
    inline const State& operator[](std::size_t idx) const {
        return _st[idx];
    }
   
private:
    inline int addState() {
        _st.resize(_st.size() + 1);
        _st.back().next.clear();
        return (int)_st.size() - 1;
    }
   
public:
    vector<State> _st;
    int _last;
};