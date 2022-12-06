#pragma once
#include <iostream>
#include <curses.h>
#include <vector>

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
    void read_array(array_member* current_array_member, std::vector <int> numbers, int input_array_size);
    void print_array(array_member* current_array_member, std::vector<int> &transfer_array);
    int max_of_array_members(array_member* current_array_member, int max);
    void resize_array_length(array_member* current_array_member, int additional_information);
    void sort_array(array_member* current_array_member);
};

