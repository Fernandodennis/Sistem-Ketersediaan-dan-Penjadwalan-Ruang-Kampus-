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
const vector<string> Month = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void displayBars(vector<Bar> &mainBar, const vector<string> &month){
    for(int i = 0; i < mainBar.size(); i++){
        cout << mainBar[i].name << "\n";
        cout << mainBar[i].dateStart << " - " << mainBar[i].dateEnd << "\n";
        cout << month[mainBar[i].monthStart - 1] << " - " << month[mainBar[i].monthEnd - 1] << "\n";
    }
}

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
    cout << "all data inserted\n";

    mainBar.push_back(userBar);
}
//testcases
//input format sdate,ndate,smonth,nmonth
//input: 1, 28, 10, 12
int calcBarLength(const Bar& bar){
    const vector<int> daylength = {0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int sum;
    int currDay = bar.dateStart;
    int currMonth = bar.monthStart;

    while(currDay != bar.dateEnd || currMonth != bar.monthEnd){
        sum++;
        currDay++;
        if (currDay > daylength[currMonth]){
            currDay = 1;
            currMonth++;
            if(currMonth > 12){
                currMonth = 1;
            }
        }
    }
    return sum;
}

void mainMenu(vector<Bar>& mainBar, const vector<string> &month){
    bool running = true;
    while(running){
        cout << "what u wanna do? 1 to insert bars, 2 to display em" << endl;
        int input;
        cin >> input;
        if (input == 1){
            inputBar(mainBar);
        }else if(input == 2){
            displayBars(mainBar, month);
        }else if(input == 3){
            cout << "quitting" << endl;
            running = false;
        }else{
            cout << "invalid input\n";
        }
    }
}

int main(){
    vector<Bar> mainBar;
    mainMenu(mainBar, Month);
    return 0;
}


//devlog: currently developing bar length calculator
// to calculate how long a bar should be based on the date and month
// it starts from to the date and month its gonna end
