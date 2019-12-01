//
//  by caogtaa
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

#define WHITE   true
#define BLACK   false
#define ROW     4
#define COL     4
#define BLANK   ' '

enum ChessType {
    QUEEN = 0,
    BISHOP,
    ROOK,
    KNIGHT,
    PAWN
};

int G, W, B, M;
char board[ROW][COL];
ChessType g_chessType[256];

unordered_map<string, int> F;   // 0 for loose, 1 for win, -1 for unknown (visiting)

string g_serialize_reuse;

void outputBoard()
{
    for (int i = ROW-1; i >= 0; --i) {
        for (int k = 0; k < COL; ++k) {
            printf("%c ", board[i][k]);
        }
        printf("\n");
    }
}

string serializeBoard(int remainMove)
{
    int idx = 0;
    for (int i = 0; i < ROW; ++i) {
        for (int k = 0; k < COL; ++k) {
            g_serialize_reuse[idx++] = board[i][k];
        }
    }
    
    g_serialize_reuse[16] = remainMove + '0';
    return g_serialize_reuse;   // copy return
}


inline bool onBoard(const pair<int, int> &pos)
{
    return 0 <= pos.first && pos.first < ROW && 0 <= pos.second && pos.second < COL;
}

inline bool onBoard(int r, int c)
{
    return 0 <= r && r < ROW && 0 <= c && c < COL;
}

inline bool isRole(char x, bool role)
{
    if (role)
        return ('A' <= x && x <= 'Z');  // is upper case letter (is white)
    
    return ('a' <= x && x <= 'z');
    // always return false for empty
}

vector<pair<int, int>> getStraightMoves(const pair<int, int> &pos)
{
    vector<pair<int, int>> res;
    
    // vertical moves up
    for (int i = pos.first + 1; i < ROW; ++i) {
        auto p = make_pair(i, pos.second);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
    }
    
    // vertical moves down
    for (int i = pos.first - 1; i >= 0; --i) {
        auto p = make_pair(i, pos.second);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
    }
    
    // horizontal moves right
    for (int i = pos.second + 1; i < COL; ++i) {
        auto p = make_pair(pos.first, i);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
    }
    
    // horizontal moves left
    for (int i = pos.second - 1; i >= 0; --i) {
        auto p = make_pair(pos.first, i);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
    }
    
    return res;
}

vector<pair<int, int>> getDiagonalMoves(const pair<int, int> &pos)
{
    vector<pair<int, int>> res;
    
    // up-right diagonal
    int r = pos.first + 1;
    int c = pos.second + 1;
    while (r < ROW && c < COL) {
        auto p = make_pair(r, c);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
        
        ++r;
        ++c;
    }
    
    // bottom-left diagonal
    r = pos.first - 1;
    c = pos.second - 1;
    while (r >= 0 && c >= 0) {
        auto p = make_pair(r, c);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
        
        --r;
        --c;
    }
    
    // up-left diagonal
    r = pos.first + 1;
    c = pos.second - 1;
    while (r < ROW && c >= 0) {
        auto p = make_pair(r, c);
        res.push_back(p);
        if (board[p.first][p.second] != BLANK)
            break;
        
        ++r;
        --c;
    }
    
    // bottom-right diagonal
    r = pos.first - 1;
    c = pos.second + 1;
    while (r >= 0 && c < COL) {
        auto p = make_pair(r, c);
        res.push_back(p);
        if(board[p.first][p.second] != BLANK)
            break;
        
        --r;
        ++c;
    }
    
    return res;
}

vector<pair<int, int>> getKnightMoves(const pair<int, int> &pos)
{
    vector<pair<int, int>> res;
    int r, c;
    
    static int rs[] = {1,2,2,1,-1,-2,-2,-1};
    static int cs[] = {-2,-1,1,2,2,1,-1,-2};
    for (int i = 0; i < 8; ++i) {
        r = pos.first + rs[i];
        c = pos.second + cs[i];
        if (onBoard(r, c))
            res.push_back(make_pair(r, c));
    }
    
    return res;
}

vector<pair<int, int>> getPawnMoves(bool role, const pair<int, int> &pos)
{
    vector<pair<int, int>> res;
    if (role) {
        // white move up
        static int rs[] = {1, 1, 1};
        static int cs[] = {-1, 0, 1};
        static bool eat[] = {true, false, true};
        
        for (int i = 0; i < 3; ++i) {
            auto p = make_pair(pos.first + rs[i], pos.second + cs[i]);
            if (p.first < 0 || p.first >= ROW || p.second < 0 || p.second >= COL)
                // out of bound
                continue;
            
            char targetX = board[p.first][p.second];
            if (eat[i] && isRole(targetX, !role)) {
                // diagonal eat
                res.push_back(p);
            } else if (!eat[i] && targetX == BLANK) {
                // straight move
                res.push_back(p);
            }
        }
    } else {
        // black move down
        
        static int rs[] = {-1, -1, -1};
        static int cs[] = {-1, 0, 1};
        static bool eat[] = {true, false, true};
        
        for (int i = 0; i < 3; ++i) {
            auto p = make_pair(pos.first + rs[i], pos.second + cs[i]);
            if (p.first < 0 || p.first >= ROW || p.second < 0 || p.second >= COL)
                // out of bound
                continue;
            
            char targetX = board[p.first][p.second];
            if (eat[i] && isRole(targetX, !role)) {
                // diagonal eat
                res.push_back(p);
            } else if (!eat[i] && targetX == BLANK) {
                // straight move
                res.push_back(p);
            }
        }
    }
    
    return res;
}

vector<pair<int, int>> availableMoves(bool role, const pair<int, int> &from)
{
    vector<pair<int, int>> result;
    vector<pair<int, int>> tmp;
    
    ChessType chessType = g_chessType[board[from.first][from.second]];
    switch(chessType)
    {
        case QUEEN:
            result = getStraightMoves(from);
            tmp = getDiagonalMoves(from);
            result.insert(result.end(), tmp.begin(), tmp.end());
            break;
        case BISHOP:
            result = getDiagonalMoves(from);
            break;
        case ROOK:
            result = getStraightMoves(from);
            break;
        case KNIGHT:
            result = getKnightMoves(from);
            break;
        case PAWN:
            result = getPawnMoves(role, from);
            break;
        default:
            break;
            //            cout << "! " << figureType << endl;
            //            assert(false);
    }
    
    return result;
}


bool canWin(bool role, int remainMove)
{
    static bool debug = false;
    if (debug)
        outputBoard();
    
    if (remainMove <= 0)
        // if game is not end, BLACK (false) win
        return !role;
    
    vector<pair<int, int>> froms;
    for (int i = 0; i < ROW; ++i) {
        for (int k = 0; k < COL; ++k) {
            if (isRole(board[i][k], role))
                froms.push_back(make_pair(i, k));
        }
    }
    
    bool ret = false;
    char sourceX, targetX;
    for (const auto &pos : froms) {
        sourceX = board[pos.first][pos.second];
        auto moves = availableMoves(role, pos);
        for (const auto &move : moves) {
            // pre-check capture queen
            targetX = board[move.first][move.second];
            if (g_chessType[sourceX] == PAWN) {
                if (isRole(targetX, !role) && g_chessType[targetX] == QUEEN)
                    // capture queen
                    return true;
                
            } else {
                if (isRole(targetX, role))
                    // do not eat my chess
                    continue;
                
                if (isRole(targetX, !role) && g_chessType[targetX] == QUEEN)
                    // capture queen
                    return true;
            }
        }
        
        for (const auto &move : moves) {
            targetX = board[move.first][move.second];
            if (g_chessType[sourceX] == PAWN) {
                if (isRole(targetX, !role) && g_chessType[targetX] == QUEEN)    // no need after precheck
                    // capture queen
                    return true;
                
                if ((role && move.first == ROW-1) || (!role && move.first == 0)) {
                    static char prompt[2][3] = {{'n', 'b', 'r'}, {'N', 'B', 'R'}};
                    for (int t = 0; t < 3; ++t) {
                        // move and change
                        board[pos.first][pos.second] = BLANK;
                        board[move.first][move.second] = prompt[role][t];
                        bool opWin = canWin(!role, remainMove-1);
                        
                        // backtrace
                        board[pos.first][pos.second] = sourceX;
                        board[move.first][move.second] = targetX;
                        if (!opWin) {
                            ret = true;    // todo: record?
                            return true;
                        }
                    }
                } else {
                    // do simple move
                    board[pos.first][pos.second] = BLANK;//targetX;
                    board[move.first][move.second] = sourceX;
                    bool opWin = canWin(!role, remainMove-1);
                    
                    // backtrace
                    board[pos.first][pos.second] = sourceX;
                    board[move.first][move.second] = targetX;
                    if (!opWin) {
                        ret = true;    // todo: record?
                        return true;
                    }
                }
            } else {
                if (isRole(targetX, role))
                    // do not eat my chess
                    continue;
                
                if (isRole(targetX, !role) && g_chessType[targetX] == QUEEN)    // no need after precheck
                    // capture queen
                    return true;
                
                // do move
                board[pos.first][pos.second] = BLANK;//targetX;
                board[move.first][move.second] = sourceX;
                bool opWin = canWin(!role, remainMove-1);
                
                // backtrace
                board[pos.first][pos.second] = sourceX;
                board[move.first][move.second] = targetX;
                if (!opWin) {
                    ret = true;    // todo: record?
                    return true;
                }
            }
        }
    }
    
    return ret;
}

int main()
{
    g_chessType['Q'] = g_chessType['q'] = QUEEN;
    g_chessType['N'] = g_chessType['n'] = KNIGHT;
    g_chessType['B'] = g_chessType['b'] = BISHOP;
    g_chessType['R'] = g_chessType['r'] = ROOK;
    g_chessType['P'] = g_chessType['p'] = PAWN;
    
    g_serialize_reuse.resize(17);
    
    scanf("%d", &G);
    while (G--) {
        scanf("%d %d %d", &W, &B, &M);
        memset(board, ' ', sizeof(board));
        char x[2], row[2], col[2];
        
        for (int i = 0; i < W; ++i) {
            scanf("%s %s %s", x, col, row);
            board[row[0]-'1'][col[0]-'A'] = x[0];
        }
        
        for (int i = 0; i < B; ++i) {
            scanf("%s %s %s", x, col, row);
            board[row[0]-'1'][col[0]-'A'] = x[0] - 'A' + 'a';
        }
        
        // outputBoard();
        if (canWin(WHITE, M)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}
