//File name : A3_SheetPb1_20220217.cpp
//Purpose : label generator that allows the client to define arbitrary sequences
//of labels,
//Author : Ammar Yasser
//Id : 20220217
//section : s3
//Date : 9/12/2023
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class LabelGenerator{
private:
    string name;
    int num;
public:
    LabelGenerator(string s, int n)
    {
        name = s;
        num = n;
    }
    string nextLabel()
    {
        string t = name + " " + to_string(num);
        num++;
        return t;
    }
};
class FileLabelGenerator: public LabelGenerator
{
private:
    string filename;
    vector<string>v;
    int i = 0;
public:
    FileLabelGenerator(string s, int n,string f):LabelGenerator(s,n)
    {
        filename = f;
        ifstream in(filename);
        string line;
        while(getline(in,line))
        {
            v.push_back(line);
        }
    }

    string nextLabel()
    {
       string s =  LabelGenerator::nextLabel();
       s += " " + v[i];
       i++;
        return  s;
    }
};
int main() {
    LabelGenerator figureNumbers("Figure", 1);
    LabelGenerator pointNumbers("P", 0);
    FileLabelGenerator figureLables("Figure",1,"ammar.txt");
    cout << "Figure numbers: ";
    for (int i = 0; i< 3; i++) {
        cout << figureNumbers.nextLabel() << ", ";
    }
    cout << endl << "Point numbers: ";
    for (int i = 0; i < 5; i++) {
        cout << pointNumbers.nextLabel() << ", ";
    }
    cout << endl << "More figures: ";
    for (int i = 0; i < 3; i++) {
        cout << figureNumbers.nextLabel() << ", ";
    }
    cout<<endl;
    for (int i = 0; i < 3; i++) {
        cout << figureLables.nextLabel() << ", ";
    }
    cout << endl;
    return 0;
}
