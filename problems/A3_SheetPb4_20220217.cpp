//File name : A3_SheetPb4_20220217.cpp
//Purpose : template-based class that implements a set of
//items.
//Author : Ammar Yasser
//Id : 20220217
//section : s3
//Date: 9/12/2023
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
template <class t>
class Set{
private:
    vector<t>v;
public:
//to add new item
    void add(t s)
    {
//Check whether the item already exists or not
        auto it = find(v.begin(),v.end(),s);
        if (it == v.end())
        {
// if not found add it
            v.push_back(s);
        }
    }
//to remove item
    void remove(t s)
    {
        auto it = find(v.begin(),v.end(),s);
        v.erase(it);
    }
    int size()
    {
// return the size of vector
        return v.size();
    }
//Check whether the item already exists or not
    bool search(t s)
    {
        auto it = find(v.begin(),v.end(),s);
        if (it != v.end())
        {
            return true;
        }
        else
            return false;
    }
    t* dynamicarray()
    {
        t* array = new t[v.size()];
        for (int i = 0; i < v.size() ; ++i) {
            array[i]= v[i];
        }
        return array;
    }
    bool operator == (Set s)
    {
        if (v.size()!=s.size())
        {
            return false;
        }
        for (int i = 0; i < v.size(); ++i) {
            auto it = find(v.begin(),v.end(),s.v[i]);
            if (it == v.end())
            {
                return false;
            }
        }
        return true;
    }
    bool operator != (Set s)
    {
        if (v.size()!=s.size())
        {
            return true;
        }
        for (int i = 0; i < v.size(); ++i) {
            auto it = find(v.begin(),v.end(),s.v[i]);
            if (it == v.end())
            {
                return true;
            }
        }
        return false;
    }
};
int main() {
    Set<string> s, f;
    s.add("ammar");
    s.add("yasser");
    s.add("ammar");
    cout << s.size() << endl;
    s.remove("yasser");
    cout << s.search("ammar")<<"\n";
    f.add("ammar");
    f.add("yasser");
    if (s == f) {
        cout << "YES\n";
    }
    f.remove("ammar");
    if (s != f)
    {
        cout<<"NO\n";
    }
    string *ptr = s.dynamicarray();
    cout<<ptr<<"\n";
    return 0;
}
