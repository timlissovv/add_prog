#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>

using namespace std;

struct knot
{
    string question = "";
    string animal_guess = "";

    knot* yesnode = nullptr;
    knot* nonode = nullptr;//указатель конечного узла
};

knot* newnode, * cb, * start;

void input(knot*& cb, fstream& file)
{
    string s;

    if (!file.eof())
    {
        getline(file, s);
        cin.clear();
    }
    else
        return;

    if (s != "*")
    {
        if (s.find("?") == -1)
        {
            cb = new knot;
            cb->animal_guess = s;
        }
        else
        {
            cb = new knot;
            cb->question = s;

            input(cb->yesnode, file);
            input(cb->nonode, file);
        }
    }
    else
        cb= nullptr;
}
void output(knot*& cb, fstream &file)
{
    if (cb== nullptr)
    {
        file << "*" << endl;
    }
    else
    {
        if (cb->animal_guess != "")
            file << cb->animal_guess << endl;
        else
        {
            file << cb->question << endl;
            output(cb->yesnode, file);
            output(cb->nonode, file);
        }
    }
}

void new_information(string& question, string& animal_guess)
{
    cout << "Какое животное вы хотите загадать? ";
    cin >> animal_guess;

    cin.ignore();

    cout << "Какой вопрос вы хотите задать к этому животному ";
    getline(cin, question);
} //добавляем новую информацию
void persons_answer(string& answer) // функция записывает адрес переменной, в которой хранится ответ
{
    cin >> answer;

    while (answer != "да" && answer != "нет")
    {
        cout << "Вы ввели неправильный ответ. Ответ должен быть да или нет ";
        cin >> answer;
    }
}
void new_branch(knot* current_branch, string& answer)
{
    string new_question;
    string new_animal_guess;
    string new_answer;

    cout << "Вы загадали это животное: " << current_branch->animal_guess << "?";

    persons_answer(answer);

    if (answer == "да")
        cout << "Компьютер угадал ";

    if (answer == "нет")
    {
        new_information(new_question, new_animal_guess);

        knot* yesnode = new knot; //указатели на да или нет узлы
        knot* nonode = new knot;

        yesnode->animal_guess = new_animal_guess;
        nonode->animal_guess = current_branch->animal_guess;

        current_branch->animal_guess = "";
        current_branch->question = new_question;
        current_branch->nonode = nonode;
        current_branch->yesnode = yesnode;
    }

}
void game(knot* current_branch)
{
    string answer;

    if (current_branch->question != "")
    {
        cout << current_branch->question << endl;

        persons_answer(answer);

        if (answer == "да")
            game(current_branch->yesnode);

        if (answer == "нет")
            game(current_branch->nonode);

    }
    else
    {
        new_branch(current_branch, answer);
    }

}
bool game_continue(knot* current_branch)
{
    cout << "Вы хотите играть с новым деревом? ";
    int i = 0;
    string s;
    cin >> s;
    if (s == "да")
        return 1;
    else
    {
        return 0;
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    fstream file;

    
   
    file.open("output.txt", ios::in);
    input(start, file);
    file.close();
    do
    {
        game(start);
    } while (game_continue(start));

    file.open("output.txt", ios::out);
    output(start, file);
    file.close();
}