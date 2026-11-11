#include "raylib.h"

int main(){
    InitWindow(800, 450, "test window");
    SetTargetFPS(60);
    int a = 0;
    int b = 0;
    int c = 0;

    while(!WindowShouldClose()){
        if(a<100){
            a+=4;
            b+=5;
            c+=1;
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("It all starts here", a, b, c, RED);
        EndDrawing();
    }

    return 0;
}

//to be implemented so i wont forget
// implementation of reusable function to render the
// row and column of month and date, slide-able infinitely
// develop rendering rule to limit the scroll only to the
// furthest event upcoming in a year or month to avoid lag

//where to start so i wont forgor
// column and event renderer
// after those are implemented, fit them into the bigger
// table of months, then year
// develop a camera for user to scroll left and right
// develop ui to crud events
// develop hover and click checker for ui interactions
// tidy up the event calendar.
