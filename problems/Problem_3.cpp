//purpose:problem 3
// author:mohamed ahmed shawky
//id:20220275
//section:s3
//Date:12/8/2023
#include <bits/stdc++.h>
#include <algorithm>
#include <utility>
#define s "\n"
#define sp " "
#define End return 0
#define ll long long
#define all(x) x.begin(),x.end()
#define Fast ios_base::sync_with_stdio;cin.tie(0);cout.tie(0);
using namespace std;
class frequency{
private:
    map<string,int>freq;
    string line;
    string file_name;
    vector<string>lines;
public:
    frequency(){
        cout<<"Enter file name: ";
        cin>>file_name;
    }
    frequency( string  n):file_name(std::move(n)){
    }
    void read(){
        fstream file;
        file.open(file_name);
        while (!file.eof()){
            getline(file,line);
            lines.push_back(line);
        }
        file.close();
    }
    void make_frequency_table(){
        string temp,word;
        for (auto & l : lines) {
            temp=l;
            for (char j : temp) {
                if (j!=' '&&!ispunct(j)&&!(j>='0'&&j<='9')) {
                    if (isupper(j))
                        word+= (char)tolower(j);
                    else
                        word += j;
                }
                if (j=='-'){
                    word+=j;
                }
                if (j==' '){
                    if (!word.empty()) {
                        freq[word]++;
                        word.clear();
                    }
                }
            }
            if (!word.empty()) {
                freq[word]++;
                word.clear();
            }
        }
    }
    void display()const{
        cout<<"Words"<<"\t"<<"Frequency"<<s;
        for (const auto& f:freq) {
            cout<<f.first<<"\t"<<f.second<<s;
        }
    }
    ~frequency(){
        freq.clear();
    }
};
int main() {
    Fast
    frequency ob("test.txt");
    ob.read();
    ob.make_frequency_table();
    ob.display();
}
