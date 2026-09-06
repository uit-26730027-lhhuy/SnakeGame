// snake_macos.cpp — chạy trên macOS
// Windows: <conio.h>, <windows.h>
// macOS:   <termios.h>, <unistd.h>, <fcntl.h>, <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

void gotoxy(int column, int line);
void VeKhung();
int kbhit();
char getch();

struct Point {
    int x, y;
};
class CONRAN {
   public:
    struct Point A[100];
    int DoDai;
    CONRAN() {
        DoDai = 3;
        A[0].x = 10;
        A[0].y = 10;
        A[1].x = 11;
        A[1].y = 10;
        A[2].x = 12;
        A[2].y = 10;
    }
    void Ve(Point Qua) {
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "X";
        }
        gotoxy(Qua.x, Qua.y);
        cout << "*";
    }
    // return false nếu đụng khung → kết thúc game
    bool DiChuyen(int Huong, Point& Qua) {
        for (int i = DoDai - 1; i > 0; i--) A[i] = A[i - 1];
        if (Huong == 0) A[0].x = A[0].x + 1;
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1;
        if (Huong == 3) A[0].y = A[0].y - 1;

        // chạm khung (viền +) → thua
        if (A[0].x <= MINX || A[0].x >= MAXX || A[0].y <= MINY || A[0].y >= MAXY)
            return false;

        if ((A[0].x == Qua.x) && (A[0].y == Qua.y)) {
            DoDai++;
            // quả chỉ spawn bên trong khung
            Qua.x = rand() % (MAXX - MINX - 1) + MINX + 1;
            Qua.y = rand() % (MAXY - MINY - 1) + MINY + 1;
        }
        return true;
    }
};

int main() {
    CONRAN r;
    int Huong = 0;
    char t;
    Point Qua;
    srand((int)time(0));
    Qua.x = rand() % (MAXX - MINX - 1) + MINX + 1;
    Qua.y = rand() % (MAXY - MINY - 1) + MINY + 1;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's') Huong = 1;
        }
        printf("\033[2J\033[H");  // thay system("cls")
        VeKhung();
        r.Ve(Qua);
        cout.flush();
        if (!r.DiChuyen(Huong, Qua)) {
            gotoxy(MINX, MAXY + 2);
            cout << "Game Over!" << endl;
            break;
        }
        usleep(300 * 1000);  // thay Sleep(300)
    }

    return 0;
}

void gotoxy(int column, int line) {
    printf("\033[%d;%dH", line + 1, column + 1);
}

void VeKhung() {
    for (int i = MINX; i <= MAXX; i++)
        for (int j = MINX; j <= MAXY; j++)
            if ((i == MINX) || (i == MAXX) || (j == MINY) || (j == MAXY)) {
                gotoxy(i, j);
                printf("+");
            }
}

static int g_pending = -1;

static void initTerminal() {
    static bool ready = false;
    if (ready) return;
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    ready = true;
}

int kbhit() {
    initTerminal();
    if (g_pending != -1) return 1;

    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (n == 1) {
        g_pending = (unsigned char)c;
        return 1;
    }
    return 0;  // không block vòng lặp game
}

char getch() {
    initTerminal();
    if (g_pending != -1) {
        char c = (char)g_pending;
        g_pending = -1;
        return c;
    }
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) != 1) return 0;
    return c;
}
