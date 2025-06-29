#include "raylib.h"
#include <vector>
#include <cmath>

struct S {
    Vector2 p;
};

int main() {
    const int w = 800, h = 600, s = 20;
    InitWindow(w, h, "My Snake Game");
    SetTargetFPS(10);

    std::vector<S> snk;
    for (int i = 0; i < 5; i++) snk.push_back({ Vector2{100.0f - i * s, 100.0f} });

    Vector2 d = {1, 0};
    Vector2 a = {400.0f, 300.0f};
    float r = s / 2.0f;
    int sc = 0;
    bool over = false;

    while (!WindowShouldClose()) {
        if (!over) {
            if (IsKeyPressed(KEY_RIGHT) && d.x != -1) d = {1, 0};
            else if (IsKeyPressed(KEY_LEFT) && d.x != 1) d = {-1, 0};
            else if (IsKeyPressed(KEY_UP) && d.y != 1) d = {0, -1};
            else if (IsKeyPressed(KEY_DOWN) && d.y != -1) d = {0, 1};

            for (int i = (int)snk.size() - 1; i > 0; i--) snk[i].p = snk[i - 1].p;

            snk[0].p.x += d.x * s;
            snk[0].p.y += d.y * s;

            if (snk[0].p.x < 0 || snk[0].p.y < 0 || snk[0].p.x >= w || snk[0].p.y >= h) over = true;

            for (int i = 1; i < (int)snk.size(); i++) {
                if (snk[0].p.x == snk[i].p.x && snk[0].p.y == snk[i].p.y) {
                    over = true;
                    break;
                }
            }

            float dx = snk[0].p.x + s/2.0f - a.x;
            float dy = snk[0].p.y + s/2.0f - a.y;
            float dist = sqrtf(dx*dx + dy*dy);
            if (dist < r + s/2.0f) {
                sc++;
                snk.push_back({ snk.back().p });
                a.x = (float)(GetRandomValue(0, w/s - 1) * s + s/2);
                a.y = (float)(GetRandomValue(0, h/s - 1) * s + s/2);
            }
        }

        BeginDrawing();
        ClearBackground((Color){144, 238, 144, 255});

        if (!over) {
            for (size_t i = 0; i < snk.size(); i++) {
                Color c = i == 0 ? BLUE : DARKBLUE;
                DrawRectangleV(snk[i].p, (Vector2){s, s}, c);
            }
            DrawCircleV(a, r, RED);
            DrawText(TextFormat("Score: %d", sc), 10, 10, 30, DARKGRAY);
        } else {
            DrawText("GAME OVER!", w/2 - 120, h/2 - 40, 50, RED);
            DrawText(TextFormat("Final Score: %d", sc), w/2 - 110, h/2 + 20, 30, DARKGRAY);
            DrawText("Press R to Restart", w/2 - 110, h/2 + 60, 20, DARKGRAY);
            if (IsKeyPressed(KEY_R)) {
                snk.clear();
                for (int i = 0; i < 5; i++) snk.push_back({ Vector2{100.0f - i * s, 100.0f} });
                d = {1, 0};
                sc = 0;
                over = false;
                a = {400.0f, 300.0f};
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/*
g++ main.cpp -o game.exe -I"C:/raylib/include" -L"C:/raylib/lib" -lraylib -lopengl32 -lgdi32 -lwinmm && ./game.exe



*/