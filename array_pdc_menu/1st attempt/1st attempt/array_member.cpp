#include "array_member.h"
#include <iostream>
#include <curses.h>

using namespace std;

int array_member::set_data()
{
    int number;
    cin >> number;
    return number;
}
void array_member::get_data(array_member* current_array_member)
{
    cout << current_array_member->data;
}
void array_member::swap(array_member* array_member_1, array_member* array_member_2)
{
    int rmd = array_member_1->data;
    array_member_1->data = array_member_2->data;
    array_member_2->data = rmd;
}

array_member::array_member()
{
    this->data = 0;

    pointer_to_next = nullptr;
    pointer_to_previous = nullptr;

    head_of_array = nullptr;
    tail_of_array = nullptr;
}

void array_member::create_array_member(array_member* currernt_array_member, int additional_information)
{
    additional_information--;

    if (additional_information > 0)
    {
        array_member* pointer_to_next = new array_member;

        pointer_to_next->pointer_to_previous = currernt_array_member;

        if (currernt_array_member->pointer_to_previous == nullptr)
            currernt_array_member->head_of_array = currernt_array_member;
        else
            currernt_array_member->head_of_array = currernt_array_member->pointer_to_previous->head_of_array;

        currernt_array_member->pointer_to_next = pointer_to_next;

        create_array_member(pointer_to_next, additional_information);
    }
}
void array_member::read_array(WINDOW* win, array_member* current_array_member, int y, int x)
{
    int additional_information;
    int kostil = 0;
    int x_0;
    int y_0;

    mvwscanw(win, y, x, "%d", &additional_information);
    current_array_member->data = additional_information;

    if (additional_information > 0)
    {
        while (additional_information > 0)
        {
            additional_information /= 10;
            kostil++;
        }

        x += kostil + 1;

        getmaxyx(win, y_0, x_0);

        if (x + 4 >= x_0)
        {
            y++;
            x = 2;
        }
    }
    else
    {
        x += 2;

        getmaxyx(win, y_0, x_0);

        if (x + 2 >= x_0)
        {
            y++;
            x = 2;
        }
    }

    if (current_array_member->pointer_to_next != nullptr)
        read_array(win, current_array_member->pointer_to_next, y, x);

}
void array_member::print_array(WINDOW* win, array_member* current_array_member, int y, int x)
{
    int additional_information;
    int kostil = 0;
    int x_0;
    int y_0;

    mvwprintw(win, y, x, "%d", current_array_member->data);
    wrefresh(win);

    additional_information = current_array_member->data;

    if (additional_information > 0)
    {
        while (additional_information > 0)
        {
            additional_information /= 10;
            kostil++;
        }

        x += kostil + 1;

        getmaxyx(win, y_0, x_0);

        if (x + 2 >= x_0)
        {
            y++;
            x = 2;
        }
    }
    else
    {
        x += 2;

        getmaxyx(win, y_0, x_0);

        if (x + 2 >= x_0)
        {
            y ++;
            x = 2;
        }
    }

    if (current_array_member->pointer_to_next != nullptr)
        print_array(win, current_array_member->pointer_to_next, y, x);
}
void array_member::max_of_array_members(WINDOW* win, array_member* current_array_member, int max)
{
    if (current_array_member->data > max)
        max = current_array_member->data;
    if (current_array_member->pointer_to_next != nullptr)
        max_of_array_members(win, current_array_member->pointer_to_next, max);
    else
    {
        mvwprintw(win,1,2, "%d", max);
        refresh();
        wrefresh(win);
    }
}
void array_member::resize_array_length(array_member* current_array_member, int additional_information)
{

    if (additional_information < 0 && additional_information != 0)
    {
        if (current_array_member->pointer_to_next == nullptr)
        {
            additional_information++;

            array_member* pointer_to_next = new array_member;

            pointer_to_next->pointer_to_previous = current_array_member;

            if (current_array_member->pointer_to_previous == nullptr)
                current_array_member->head_of_array = current_array_member;
            else
                current_array_member->head_of_array = current_array_member->pointer_to_previous->head_of_array;

            current_array_member->pointer_to_next = pointer_to_next;

            resize_array_length(pointer_to_next, additional_information);
        }
        else if (additional_information < 0 && current_array_member->pointer_to_next != nullptr)
            resize_array_length(current_array_member->pointer_to_next, additional_information);
    }
    else if (additional_information != 0)
    {
        if (current_array_member->pointer_to_next->pointer_to_next == nullptr)
        {
            additional_information--;
            delete[] current_array_member->pointer_to_next;
            current_array_member->pointer_to_next = nullptr;
            if (additional_information > 0)
                resize_array_length(current_array_member->pointer_to_previous, additional_information);
        }
        else if (current_array_member->pointer_to_next != nullptr && additional_information > 0)
            resize_array_length(current_array_member->pointer_to_next, additional_information);
    }
}
void array_member::sort_array(array_member* current_array_member)
{
    int additional_information = 0;

    {
        if (current_array_member->pointer_to_next != nullptr)
        {
            if (current_array_member->data > current_array_member->pointer_to_next->data)
            {
                additional_information++;

                swap(current_array_member, current_array_member->pointer_to_next);
                sort_array(current_array_member->pointer_to_next);
            }
            sort_array(current_array_member->pointer_to_next);
        }
    }

    if (additional_information > 0)
        sort_array(current_array_member->head_of_array);

}
 