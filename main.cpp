#include <iostream>
#include <vector>

using namespace std;

struct Bar{
    string name;
    int dateStart;
    int dateEnd;
    int monthStart;
    int monthEnd;
};

void inputBar(vector<Bar>& mainBar){
    Bar userBar;
    cout << "insert bar name\n";
    cin >> userBar.name;
    cout << "insert starting date\n";
    cin >> userBar.dateStart;
    cout << "insert end date\n";
    cin >> userBar.dateEnd;
    cout << "insert monthStart\n";
    cin >> userBar.monthStart;
    cout << "insert monthEnd\n";
    cin >> userBar.monthEnd;

    mainBar.push_back(userBar);
}

void displayBars(vector<Bar>& mainBar){
    for(int i = 0; i < mainBar.size(); i++){
        cout << mainBar[i].name << "\n";
        cout << mainBar[i].dateStart << " - " << mainBar[i].dateEnd << "\n";
        cout << mainBar[i].monthStart << " - " << mainBar[i].monthEnd << "\n";
    }
}

int main(){
    vector<Bar> mainBar;
    inputBar(mainBar);
    displayBars(mainBar);
    return 0;
}
