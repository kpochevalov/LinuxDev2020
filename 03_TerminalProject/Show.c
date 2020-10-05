#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void print_one_string(FILE *f, WINDOW *win, int width){
    char s[width + 2];
    if ((fgets(s, width + 1, f)) != NULL) {
        if (s[strlen(s) - 1] == '\n') {
            wprintw(win, " %s", s);
        } else {
            wprintw(win, " %s\n", s);
        }
    }
}

int main(int argc, char *argv[]){
    FILE *inp = fopen(argv[1], "r");
    if (!inp){
        fprintf(stderr, "Open failure\n");
        return 1;
    }
    initscr();
    noecho();
    cbreak();
    printw("%s", argv[1]);
    int height = LINES - 4, width = COLS - 4;
    WINDOW *win = newwin(height, width, 2, 2);
    waddch(win, '\n');
    scrollok(win, TRUE);
    width -= 2;
    height -= 2;
    int i = 0;
    for( ; i < height; ++i){
        print_one_string(inp, win, width);
    }
    box(win, 0, 0);
    refresh();
    wrefresh(win);
    int c;
    while((c = wgetch(win)) != 27){
        if (c == ' '){
            print_one_string(inp, win, width);
            box(win, 0, 0);
            refresh();
            wrefresh(win);
        }
    }
    endwin();
}