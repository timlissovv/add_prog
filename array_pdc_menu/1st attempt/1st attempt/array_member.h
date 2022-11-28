#pragma once
#include <iostream>
#include <curses.h>

class array_member
{
private:

    int data;

    array_member* pointer_to_next;
    array_member* pointer_to_previous;

    array_member* head_of_array;
    array_member* tail_of_array;

    int set_data();
    void get_data(array_member* current_array_member);

    void swap(array_member* array_member_1, array_member* array_member_2);


public:

    array_member();

    void create_array_member(array_member* currernt_array_member, int additional_information);
    void read_array(WINDOW* win, array_member* current_array_member, int y, int x);
    void print_array(WINDOW* win, array_member* current_array_member, int x, int y);
    void max_of_array_members(WINDOW* win, array_member* current_array_member, int max);
    void resize_array_length(array_member* current_array_member, int additional_information);
    void sort_array(array_member* current_array_member);
};

