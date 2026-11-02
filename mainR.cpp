#include "raylib.h"
#include <iostream>
using namespace std;

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
