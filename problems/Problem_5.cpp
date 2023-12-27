// File name:A3_SheetPb5_20220229.cpp
// Purpose: solving problem 5 which is a task manager
// Author(s): Omar Mahfouz Mohammed
// ID(s): 20220220
// Section: S4
// Date: 9/12/2023
#include <bits./stdc++.h>

using namespace std;
struct Process { // creating a struct for the process . no need for it to be a class
    string ImageName;
    int PID;
    string SessionName;
    string SessionNumber;
    long long MemUsage;
};

class TaskManager {
private:
    vector <Process> v;
public:
    TaskManager() {
        system("tasklist > test.txt"); // taking the process list from the OS
        ifstream f("test.txt");
        string s, c;
        getline(f, s);
        getline(f, s);
        getline(f, s);
        // ignoring first line which is an empty line and two that has no processes to take
        while (getline(f, s)) {
            Process current;
            stringstream stream(s); // making the line a stringstream
            string name;
            // this loop is to check if the image name has multiple strings in it and not just one name
            while (stream >> name) {
                bool flag = 0;
                for (auto letter: name) { // check if the string is an integer if true then stop
                    if (!isdigit(letter)) {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    current.ImageName += (current.ImageName != "" ? " " : "") + name;
                else {
                    current.PID = stoi(name);
                    break;
                }
            }
            stream >> current.SessionName >> current.SessionNumber >> s >> c; // continue taking input and store it in process variable
            remove(s.begin(), s.end(), ',');
            current.MemUsage = stoll(s);
            v.push_back(current);
        }
    }

    void print_sorted_by_name() {
        sort(v.begin(), v.end(), [](const Process &a, const Process &b) { return a.ImageName < b.ImageName; });
        // lambda function to sort by name ascending
        print();
    }

    void print_sorted_by_PID() {
        sort(v.begin(), v.end(), [](const Process &a, const Process &b) { return a.PID < b.PID; });
        // lambda function to sort by PID ascending
        print();
    }

    void print_sorted_by_memory() {
        sort(v.begin(), v.end(), [](const Process &a, const Process &b) { return a.MemUsage < b.MemUsage; });
        // lambda function to sort by memory usage ascending
        print();
    }

    void print() {
        cout << "Image Name                     PID Session Name        Session#    Mem Usage\n"
                "========================= ======== ================ =========== ============\n";
        for (const auto &p: v) {
            // utilizing iomanip header to format the output like the input that was given
            cout << p.ImageName << setw(34 - p.ImageName.length()) << p.PID << " " << p.SessionName;
            cout << setw(20 - (p.SessionName[0] == 'S')) << p.SessionNumber << setw(11) << p.MemUsage << " K\n";
        }
    }

};

int main() {
    TaskManager x;
    //x.print_sorted_by_PID();
    x.print_sorted_by_memory();
    //x.print_sorted_by_name();
}
