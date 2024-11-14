#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAX 100001
#define FASTIO cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);

using namespace std;
int Q, N, M;
string S;
deque<int> DQ[MAX];
int FrontIndex[MAX], BackIndex[MAX];
vector<string> Queries;

void input() {
    cin >> Q;
    cin.ignore();
    for (int i = 0; i < Q; i++) {
        getline(cin, S);
        Queries.push_back(S);
    };
}

vector<string> Split(string nowS) {
    vector<string> Result;
    string temp = "";

    for (int i = 0; i < (int)nowS.length(); i++) {
        if (nowS[i] == ' ') {
            Result.push_back(temp);
            temp = "";
        }
        else {
            temp += nowS[i];
        }
    }

    Result.push_back(temp);

    return Result;
}

void install_Factory(vector<string> nowQuery) {
    N = stoi(nowQuery[1]);
    M = stoi(nowQuery[2]);

    for (int i = 0; i < M; i++) {
        int Index = stoi(nowQuery[i + 3]);
        if (!DQ[Index].empty()) {
            int Back = DQ[Index].back();
            BackIndex[Back] = i + 1;
            FrontIndex[i + 1] = Back;
        }
        DQ[Index].push_back(i + 1);
    }
}

void move_Things(vector<string> nowQuery) {
    int From = stoi(nowQuery[1]);
    int To = stoi(nowQuery[2]);

    if (!DQ[To].empty()) {
        int Front = DQ[To].front();
        FrontIndex[Front] = DQ[From].back();
        BackIndex[DQ[From].back()] = Front;
    }

    while (!DQ[From].empty()) {
        int Back = DQ[From].back();
        DQ[From].pop_back();
        DQ[To].push_front(Back);
    };

    cout << (int)DQ[To].size() << "\n";
}

void change_Things(vector<string> nowQuery) {
    int From = stoi(nowQuery[1]);
    int To = stoi(nowQuery[2]);

    int FromFront = -1;
    if (!DQ[From].empty()) {
        FromFront = DQ[From].front();
        DQ[From].pop_front();
    }
    int ToFront = -1;
    if (!DQ[To].empty()) {
        ToFront = DQ[To].front();
        DQ[To].pop_front();
    }

    if ((FromFront != -1) && (ToFront != -1)) {
        if (!DQ[To].empty()) {
            BackIndex[FromFront] = DQ[To].front();
            FrontIndex[DQ[To].front()] = FromFront;
        }
        else {
            BackIndex[FromFront] = 0;
        }

        if (!DQ[From].empty()) {
            BackIndex[ToFront] = DQ[From].front();
            FrontIndex[DQ[From].front()] = ToFront;
        }
        else {
            BackIndex[ToFront] = 0;
        }

        DQ[From].push_front(ToFront);
        DQ[To].push_front(FromFront);
    }
    else if ((FromFront != -1) && (ToFront == -1)) {
        if (!DQ[To].empty()) {
            BackIndex[FromFront] = DQ[To].front();
            FrontIndex[DQ[To].front()] = 0;
        }
        else {
            BackIndex[FromFront] = 0;
        }

        DQ[To].push_front(FromFront);
    }
    else if ((FromFront == -1) && (ToFront != -1)) {
        if (!DQ[From].empty()) {
            BackIndex[ToFront] = DQ[From].front();
            FrontIndex[DQ[From].front()] = 0;
        }
        else {
            BackIndex[ToFront] = 0;
        }

        DQ[From].push_front(ToFront);
    }

    cout << (int)DQ[To].size() << "\n";
}

void divide_Things(vector<string> nowQuery) {
    int From = stoi(nowQuery[1]);
    int To = stoi(nowQuery[2]);
    int FromCount = (int)DQ[From].size();
    if (FromCount == 1) {
        cout << (int)DQ[To].size() << "\n";
        return;
    }

    int End = floor(FromCount / 2);

    deque<int> tempDQ;
    while (End--) {
        tempDQ.push_back(DQ[From].front());
        DQ[From].pop_front();
    };

    FrontIndex[DQ[From].front()] = 0;
    if (!DQ[To].empty()) {
        FrontIndex[DQ[To].front()] = tempDQ.back();
        BackIndex[tempDQ.back()] = DQ[To].front();
    }
    else {
        BackIndex[tempDQ.back()] = 0;
    }

    while (!tempDQ.empty()) {
        DQ[To].push_front(tempDQ.back());
        tempDQ.pop_back();
    }

    cout << (int)DQ[To].size() << "\n";
}

void get_Presents_Info(vector<string> nowQuery) {
    int Index = stoi(nowQuery[1]);

    int Front = -1;
    if (FrontIndex[Index] != 0) {
        Front = FrontIndex[Index];
    }

    int Back = -1;
    if (BackIndex[Index] != 0) {
        Back = BackIndex[Index];
    }

    cout << Front + (2 * Back) << "\n";
}

void get_Belt_Info(vector<string> nowQuery) {
    int Index = stoi(nowQuery[1]);

    int Front = -1;
    if (!DQ[Index].empty()) {
        Front = DQ[Index].front();
    }

    int Back = -1;
    if (!DQ[Index].empty()) {
        Back = DQ[Index].back();
    }

    int Count = (int)DQ[Index].size();

    cout << Front + (2 * Back) + (3 * Count) << "\n";
}

void settings() {
    for (int i = 0; i < Q; i++) {
        vector<string> nowQueries = Split(Queries[i]);
        if (nowQueries[0] == "100") {
            install_Factory(nowQueries);
        }
        else if (nowQueries[0] == "200") {
            move_Things(nowQueries);
        }
        else if (nowQueries[0] == "300") {
            change_Things(nowQueries);
        }
        else if (nowQueries[0] == "400") {
            divide_Things(nowQueries);
        }
        else if (nowQueries[0] == "500") {
            get_Presents_Info(nowQueries);
        }
        else if (nowQueries[0] == "600") {
            get_Belt_Info(nowQueries);
        }
    }

    for (int i = 0; i <= N; i++) {
        DQ[i].clear();
    }
}

int main() {
    FASTIO
    input();
    settings();

    return 0;
}