#include "array_member.h"
#include <iostream>
#include <curses.h>
#include <vector>

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

int array_member::max_of_array_members(array_member* current_array_member, int max)
{
    if (current_array_member->data > max)
        max = current_array_member->data;
    if (current_array_member->pointer_to_next != nullptr)
        max_of_array_members(current_array_member->pointer_to_next, max);
    else
        return max;
}
void array_member::print_array(array_member* current_array_member, std::vector <int> &transfer_array)
{
    transfer_array.push_back(current_array_member->data);

    if (current_array_member->pointer_to_next != nullptr)
        print_array(current_array_member->pointer_to_next, transfer_array);
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
void array_member::read_array(array_member* current_array_member, vector <int> numbers, int input_array_size)
{
    current_array_member->data = numbers[input_array_size - 1];
    numbers.pop_back();
    input_array_size--;

    if (current_array_member->pointer_to_next != nullptr)
        read_array(current_array_member->pointer_to_next, numbers, input_array_size);
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
 