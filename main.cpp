#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Bar{
    string name;
    int dateStart = 0;
    int dateEnd = 0;
    int monthStart = 0;
    int monthEnd = 0;
    int absStart = 0;
    int absEnd = 0;
    int column = 0;
};

const vector<string> Month = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

void calcAbsDate(const Bar& bar, int& absA, int& absB){
    const vector<int> daylength = {0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    absA = 0;
    absB = 0;

    for(int i = 0; i < bar.monthStart; i++){
        absA += daylength[i];
    }
    absA += bar.dateStart;
    for(int j = 0; j < bar.monthEnd; j++){
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

    // cari column terkecil yang tidak bentrok dengan bar lain
    bool columnTaken = true;
    while(columnTaken){
        columnTaken = false;
        for(size_t i = 0; i < mainBar.size(); i++){
            if(mainBar[i].column == userBar.column && isOverlapping(mainBar[i], userBar)){
                userBar.column++;
                columnTaken = true;
                break;   // cek ulang dari awal dengan column yang baru
            }
        }
    }

    mainBar.push_back(userBar);
}

void displayBars(vector<Bar> &mainBar, const vector<string> &month){
    for(size_t i = 0; i < mainBar.size(); i++){
        cout << mainBar[i].name << "\n";
        cout << mainBar[i].dateStart << " - " << mainBar[i].dateEnd << "\n";
        cout << month[mainBar[i].monthStart - 1] << " - " << month[mainBar[i].monthEnd - 1] << "\n";
        cout << "column: " << mainBar[i].column << "\n";
        cout << "date in 365 format: " << mainBar[i].absStart << " - " << mainBar[i].absEnd << "\n";
    }
}

// ===================== HARI & JAM SEKARANG =====================

const vector<string> DayName = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

struct NowInfo{
    string dayName;   // nama hari (Senin, Selasa, ...)
    int date;         // tanggal 1-31
    int month;        // bulan 1-12
    int year;
    int hour;         // jam 0-23
    int minute;
    int absDay;       // hari ke-berapa dalam 365 hari (format sama dengan absStart/absEnd)
};

NowInfo getCurrentTime(){
    const vector<int> daylength = {0 , 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    time_t raw = time(nullptr) + 7 * 3600;   // paksa WIB (UTC+7), server bisa pakai UTC
    tm* lt = gmtime(&raw);

    NowInfo now;
    now.dayName = DayName[lt->tm_wday];
    now.date    = lt->tm_mday;
    now.month   = lt->tm_mon + 1;
    now.year    = lt->tm_year + 1900;
    now.hour    = lt->tm_hour;
    now.minute  = lt->tm_min;

    now.absDay = 0;
    for(int i = 0; i < now.month; i++){
        now.absDay += daylength[i];
    }
    now.absDay += now.date;
    return now;
}//ambil hari, tanggal, bulan, jam sekarang

void showCurrentTime(){
    NowInfo now = getCurrentTime();
    cout << "=== sekarang ===\n";
    cout << now.dayName << ", " << now.date << " " << Month[now.month - 1] << " " << now.year << "\n";
    cout << "jam: " << (now.hour < 10 ? "0" : "") << now.hour << ":"
         << (now.minute < 10 ? "0" : "") << now.minute << "\n";
    cout << "date in 365 format: " << now.absDay << "\n";
    cout << "================\n";
}

// ===============================================================

void mainMenu(vector<Bar>& mainBar, const vector<string> &month){
    bool running = true;
    while(running){
        cout << "what u wanna do? 1 to insert bars, 2 to display em, 3 to quit" << endl;
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
}//current interface for prototyping

int main(){
    vector<Bar> mainBar;
    showCurrentTime();
    mainMenu(mainBar, Month);
    return 0;
}
