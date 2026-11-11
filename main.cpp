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
    if(bar.monthEnd < bar.monthStart){
        absB += 365;
    }
}//returns the day in 365 days format

bool isOverlapping(const Bar& barA, const Bar& barB){
    return(barA.absStart <= barB.absEnd && barA.absEnd >= barB.absStart);
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

    int start = 0;
    int end = 0;
    calcAbsDate(userBar, start, end);
    userBar.absStart = start;
    userBar.absEnd = end;
    userBar.column = 0;

    for(int i=0; i<mainBar.size(); i++){
        if(mainBar[i].column == userBar.column && isOverlapping(mainBar[i], userBar)){
            userBar.column++;
        }
    }

    mainBar.push_back(userBar);
}

int simplifyInput(int b, int c) {
    while (true) {
        cout << "Input number between " << b << " and " << c << ": ";
        int input;
        cin >> input;
        if (input >= b && input <= c) {
            return input;
        }

        cout << "Invalid input. Try again.\n";
    }
}//index input simplification pipeline for prototyping, part of optimization

int availableCol(vector<Bar> &mainBar, int index){
    int candidate = 0;
    while(true){
        bool conflict = false;
        for(int i=0;i<mainBar.size();i++){
            if(i==index) continue;
            if(mainBar[i].column == candidate && isOverlapping(mainBar[i], mainBar[index])){
                conflict = true;
                break;
            }
        }
        if(!conflict) return candidate;
        candidate++;
    }
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

void displayBars(vector<Bar> &mainBar, const vector<string> &month){
    for(int i = 0; i < mainBar.size(); i++){
         int length = calcBarLength(mainBar[i]);
        cout << mainBar[i].name << "\n";
        cout << mainBar[i].dateStart << " - " << mainBar[i].dateEnd << "\n";
        cout << month[mainBar[i].monthStart - 1] << " - " << month[mainBar[i].monthEnd - 1] << "\n";
        cout << "length: " << length << " days\n";
        cout << "column: " << mainBar[i].column << "\n";
        cout << "date in 365 format: " << mainBar[i].absStart << " - " << mainBar[i].absEnd << "\n";
    }
}

void barToedit(vector<Bar> &mainBar){
    bool editing = true;
    bool editingBar = false;
    while(editing){
        cout << "pick an index to edit\n";
        int input; cin >> input;
        if(input > 0 && input <= mainBar.size()){
            int index = input - 1;
            editingBar = true;
            while(editingBar){
                cout << "what to do with bar " << mainBar[index].name << endl;
                cout << "1. change name, 2. change date, 3. change Month, 4. finish";
                int choice = simplifyInput(1, 4);
                if(choice==1){
                    string newName;
                    cout << "input new name for bar " << mainBar[index].name << endl;
                    cin >> newName;
                    mainBar[index].name = newName;
                }else if (choice==2) {
                    int newDatestart; int newDateend;
                    cout << "input new date start and date end\n";
                    cin >> newDatestart >> newDateend;
                    mainBar[index].dateStart = newDatestart;
                    mainBar[index].dateEnd = newDateend;
                }else if (choice==3) {
                    int newMonthstart; int newMonthend;
                    cout << "input new starting and ending month\n";
                    cin >> newMonthstart >> newMonthend;
                    mainBar[index].monthStart = newMonthstart;
                    mainBar[index].monthEnd = newMonthend;
                }else if (choice==4) {
                    int start = 0;
                    int end = 0;
                    calcAbsDate(mainBar[index], start, end);
                    mainBar[index].absStart = start;
                    mainBar[index].absEnd = end;
                    mainBar[index].column = availableCol(mainBar, index);
                    editingBar = false;
                }
            }
        }
    }
}

void barTodelete(vector<Bar> &mainBar){
    bool picking = true;
    while(picking == true){
        cout << "pick an index to delete\n";
        int input; cin >> input;
        if(input > 0 && input <= mainBar.size()){
            int index = input - 1;
            mainBar.erase(mainBar.begin() + index);
            cout << "bar at index " << index << " is done for.\n";
        }else{
            picking = false;
        }
    }
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
            barTodelete(mainBar);
        }else if(input == 4){
            barToedit(mainBar);
        }
    }
}//current interface for prototyping

//int main(){
    //vector<Bar> mainBar;
    //mainMenu(mainBar, Month);
    //return 0;
//}


//devlog for mainR.cpp so i would mind it:
// apply DRY to code for optimization
// reorganize the system to be tidier
