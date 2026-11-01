#include <iostream>
#include <vector>

using namespace std;

struct Bar{
    string name;
    int dateStart;
    int dateEnd;
    int monthStart;
    int monthEnd;
    int absStart;
    int absEnd;
    int column;
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
}//calculate the length of a bar

void calcAbsDate(const Bar& bar, int& absA, int& absB){
    const vector<int> daylength = {0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    absA = 0;
    absB = 0;

    for(int i=0; i<bar.monthStart; i++){
        absA += daylength[i];
    }
    absA += bar.dateStart;
    for(int j=0; j<bar.monthEnd; j++){
        absB += daylength[j];
    }
    absB += bar.dateEnd;
}//returns the day in 365 days format

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
            for(int i=0; i<mainBar.size(); i++){
                int length = calcBarLength(mainBar[i]); // Pass the specific bar here
                cout << mainBar[i].name << " length: " << length << " days\n";
            }
        }else if(input == 3){
            cout << "quitting" << endl;
            running = false;
        }else{
            cout << "invalid input\n";
        }
    }
}//current interface for prototyping

int main(){
    vector<Bar> mainBar;
    mainMenu(mainBar, Month);
    return 0;
}


//devlog: bar length done
// next to be developed is column
// if there are 2 or more schedules overlapping on the same
// date or length, make a new column

// next to develop too is fetching user's current date and month
// translate them into data and process it, put the user's current
// date and month in the table, thats it
// if the date and month of an event exceeds its length
// (klo event nya udah selesai kayak kemaren or etc)
// the bar remains there until the next year's month starting to render.


//in development reminder so i wont forget:
// im developing the column calculator to see if 2 schedule overlap together on the
// same date, need date converter to raw 365 day for cleaner later bool function.
// bool checks if 2 dates or more are overlapping with each other by comparing each bar's
// length
