// File name: A3_SheetPb2_20220229.cpp
// Purpose: making a string set and finding similarity between two sets
// Author(s): Omar Mahfouz Mohammed
// ID(s): 20220229
// Section: S4
// Date: 9/12/2023
#include <bits./stdc++.h>

using namespace std;

class StringSet {
private:
    vector <string> v;
public:
    StringSet(string filename) {
        string temp = filename;
        if (filename.find(".txt") == string::npos) {
            temp += ".txt";
        }
        ifstream in(temp);
        stringstream ss(filename);
        string s;
        if (in.fail()) {
            while (ss >> s) {
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                while (ispunct(s.back()))
                    s.pop_back();
                while (ispunct(s.front()))
                    s.erase(s.begin());
                add(s);
            }
        } else {
            while (in >> s) {
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                while (ispunct(s.back()))
                    s.pop_back();
                while (ispunct(s.front()))
                    s.erase(s.begin());
                add(s);
            }
        }
    };

    StringSet(vector <string> x) {
        v = move(x);
    }

    void add(string s) {
        if (!exist(s))
            v.push_back(s);
    };

    void remove(string s) {
        if (exist(s))
            v.erase(find(v.begin(), v.end(), s));
    };

    bool exist(string s) {
        return find(v.begin(), v.end(), s) != v.end();
    };

    void clear() {
        v.clear();
    };

    int size() {
        return v.size();
    };

    void print() {
        for (const auto &word: v)
            cout << word << " ";
        cout << endl;
    };

    StringSet operator*(const StringSet &other) {
        vector <string> ans;
        for (auto word: other.v) {
            if (exist(word))
                ans.push_back(word);
        }
        return ans;
    }

    StringSet operator+(const StringSet &other) {
        vector <string> ans(v.begin(), v.end());
        for (auto word: other.v) {
            if (!exist(word))
                ans.push_back(word);
        }
        return StringSet(ans);
    }

    long double similarity(const StringSet &other) {
        StringSet ref = other;
        StringSet x = *this * ref;
        if (!size() || !ref.size())
            return 0;
        return x.size() / (sqrt(size()) * sqrt(ref.size()));
    };
};

int main() {
    StringSet a("is OK YEars chocolate? ice ");
    StringSet b("Chocolate years,!!! ice...??? is ok");
    cout << a.similarity(b); // 1
}
