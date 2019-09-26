#ifdef DEBUG
#include <bits/stdc++.h>
#endif
namespace automata {
    using namespace std;
    class kmp {
    private:
        string pat;
        vector<int> table;

    public:
        kmp(const string &_pat):
            pat(_pat), table(_pat.size(), 0)
        {
            for (int i = 1; i < static_cast<int>(pat.size()); ++i) {
                int j = table[i-1];
                while (j > 0 && pat[i] != pat[j]) j = table[j-1];
                if (pat[i] == pat[j]) ++j;
                table[i] = j;
            }
        }

        int next(int cur, char ch)
        {
            if (cur == static_cast<int>(pat.size())) return table[cur-1];
            int j = cur;
            while (j > 0 && pat[j] != ch) j = table[j-1];
            if (pat[j] == ch) j++;
            return j;
        }
    };
}
