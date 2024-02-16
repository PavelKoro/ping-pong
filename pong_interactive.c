#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

void edge(void);
void table(void);
void bat(char key);
void score(int score1, int score2);

const int HEIGHT = 25;
const int WIDTH = 82;
int x_ball = WIDTH / 2;
int y_ball = HEIGHT / 2;
int x_move = 1;
int y_move = 1;
int bat1_y1 = 11;
int bat1_y2 = 12;
int bat1_y3 = 13;
int bat2_y1 = 11;
int bat2_y2 = 12;
int bat2_y3 = 13;
int bat1_x = 15;
int bat2_x = 65;
int score1 = 0;
int score2 = 0;
char key;

int main(void) {
    initscr();
    noecho();
    nodelay(stdscr, 1);
    do {
        clear();
        score(score1, score2);
        edge();
        table();
        edge();
        if (score1 == 21 || score2 == 21) {
            break;
        }
        if (x_ball == 0) {
            score2 += 1;
            x_ball = WIDTH / 2;
            y_ball = HEIGHT / 2;
            bat1_y1 = 11;
            bat1_y2 = 12;
            bat1_y3 = 13;
            bat2_y1 = 11;
            bat2_y2 = 12;
            bat2_y3 = 13;

        } else if (x_ball == 79) {
            score1 += 1;
            x_ball = WIDTH / 2;
            y_ball = HEIGHT / 2;
            bat1_y1 = 11;
            bat1_y2 = 12;
            bat1_y3 = 13;
            bat2_y1 = 11;
            bat2_y2 = 12;
            bat2_y3 = 13;
        }
        key = getch();

        if (key == 'A' || key == 'Z' || key == 'K' || key == 'M' || key == 'a' || key == 'z' || key == 'k' ||
            key == 'm') {
            bat(key);
        }
        usleep(70000);
    } while (1);
    clear();
    endwin();
    if (score1 == 21) {
        printf("Player ONE wins!\n");
        printf("Player 1 - %d \nPlayer 2 - %d\n", score1, score2);
    }
    if (score2 == 21) {
        printf("Player TWO wins!\n");
        printf("Player 1 - %d \nPlayer 2 - %d\n", score1, score2);
    }
}

void edge(void) {
    for (int i = 0; i < 80; i++) {
        printw("-");
    }
    printw("\n");
}

void table(void) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == 79) {
                printw("|");
            } else if (x == x_ball && y == y_ball) {
                printw("*");
            } else if ((y == bat1_y1 || y == bat1_y2 || y == bat1_y3) && (x == bat1_x)) {
                printw("|");
            } else if ((y == bat2_y1 || y == bat2_y2 || y == bat2_y3) && (x == bat2_x)) {
                printw("|");
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
    if (y_ball == 24 || y_ball == 0) {
        y_move *= -1;
    }
    if ((x_ball == bat1_x + 1) && (y_ball == bat1_y1 || y_ball == bat1_y3)) {
        x_move *= -1;
        x_ball += x_move;

    } else if ((x_ball == bat2_x - 1) && (y_ball == bat2_y1 || y_ball == bat2_y3)) {
        x_move *= -1;
        x_ball += x_move;
    } else if ((x_ball == bat1_x + 1) && y_ball == bat1_y2) {
        x_move *= -1;
    } else if ((x_ball == bat2_x - 1) && y_ball == bat2_y2) {
        x_move *= -1;
    }
    x_ball += x_move;
    y_ball += y_move;
}

void bat(char key) {
    if (key == 'A' || key == 'a') {
        if (bat1_y1 != 0) {
            bat1_y1 -= 1;
            bat1_y2 -= 1;
            bat1_y3 -= 1;
        }
    }
    if (key == 'Z' || key == 'z') {
        if (bat1_y3 != 24) {
            bat1_y1 += 1;
            bat1_y2 += 1;
            bat1_y3 += 1;
        }
    }
    if (key == 'K' || key == 'k') {
        if (bat2_y1 != 0) {
            bat2_y1 -= 1;
            bat2_y2 -= 1;
            bat2_y3 -= 1;
        }
    }
    if (key == 'M' || key == 'm') {
        if (bat2_y3 != 24) {
            bat2_y1 += 1;
            bat2_y2 += 1;
            bat2_y3 += 1;
        }
    }
}

void score(int score1, int score2) {
    edge();
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == 79) {
                printw("|");
            } else if (x == 30 && y == 1) {
                printw("%d", score1);
            } else if (x == 52 && y == 1) {
                printw("%d", score2);
            } else {
                printw(" ");
            }
        }
        printw("\n");
    }
}