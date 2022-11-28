#include "menu.h"
#include <string>
#include "array_member.h"

using namespace std;

void start_menu()
{
    initscr();
    cbreak();

    int y_max, x_max;
    getmaxyx(stdscr, y_max, x_max);

    WINDOW* frame_1 = newwin(12, 60, 2, 2);
    box(frame_1, 0, 0);
    refresh();
    wrefresh(frame_1);


    WINDOW* answer_zone = newwin(5, 45, 8, 15);
    box(answer_zone, 0, 0);
    refresh();
    wrefresh(answer_zone);

    move(16, 16);
    mvwprintw(answer_zone, 0, 5, "Output");
    wrefresh(answer_zone);


    WINDOW* input_zone = newwin(5, 45, 3, 15);
    box(input_zone, 0, 0);
    refresh();
    wrefresh(input_zone);

    move(16, 16);
    mvwprintw(input_zone, 0, 5, "Input");
    wrefresh(input_zone);


    WINDOW* menuwin = newwin(10, 10, 3, 4);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);


    keypad(menuwin, true);

    array_member* start_array_member = new array_member;

    string choises[8] = { "Create", "Delete", "Resize", "Read", "Print", "Sort", "Max", "     EOW"};
    
    int choise;
    int highlight = 0;

    int size_rmd;

    bool work = 1;

    while (work)
    {
        while (1 && work == 1)
        {
            for (int i = 0; i < 8; i++)
            {
                if (i == highlight)
                    wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin, i + 1, 1, choises[i].c_str());
                wattroff(menuwin, A_REVERSE);
            }
            choise = wgetch(menuwin);

            switch (choise)
            {
            case KEY_UP:
                highlight--;
                if (highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 8)
                    highlight = 7;
                break;

            }
            //create array
            if (choise == 10 && highlight == 0)
            {
                mvwprintw(input_zone, 1, 2, "                            ");

                char size;
                mvwscanw(input_zone, 1, 2, "%d", &size);
                wrefresh(input_zone);

                size_rmd = size;

                start_array_member->create_array_member(start_array_member, size);

                choise = 0;

                break;
            }
            //delete (bugged)
            if (choise == 10 && highlight == 1)
            {
                start_array_member->resize_array_length(start_array_member, size_rmd - 1);
                delete[] start_array_member;
                work = 0;
            }
            //resize 
            if (choise == 10 && highlight == 2)
            {
                char size;
                int info;

                mvwscanw(input_zone, 1, 2, "%d", &size);
                wrefresh(input_zone);

                info = size_rmd - size;
                size_rmd = size;

                start_array_member->resize_array_length(start_array_member, info);

                refresh();
                wrefresh(input_zone);

                //start_array_member->print_array(answer_zone, start_array_member, 1, 2);
            }
            //read
            if (choise == 10 && highlight == 3)
            {
                mvwprintw(answer_zone, 1, 2, "                            ");
                mvwprintw(input_zone, 1, 2, "                            ");

                start_array_member->read_array(input_zone, start_array_member, 1, 2);
            }
            //print
            if (choise == 10 && highlight == 4)
            {
                mvwprintw(answer_zone, 1, 2, "                            ");

                start_array_member->print_array(answer_zone, start_array_member, 1, 2);
            }
            //sort
            if (choise == 10 && highlight == 5)
            {
                mvwprintw(input_zone, 1, 2, "                            ");
                refresh();
                wrefresh(input_zone);

                start_array_member->sort_array(start_array_member);
            }
            //max
            if (choise == 10 && highlight == 6)
            {
                mvwprintw(answer_zone, 1, 2, "                            ");
                refresh();
                wrefresh(answer_zone);

                start_array_member->max_of_array_members(answer_zone, start_array_member, -1e2);
            } 
            //end of work
            if (choise == 10 && highlight == 7)
            {
                work = 0;
                break;
            }
        }
    }

    endwin();
}
