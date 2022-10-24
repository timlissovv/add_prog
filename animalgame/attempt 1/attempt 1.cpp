#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct knot
{
    string question = "";
    string animal_guess = "";

    knot* yesnode = nullptr;
    knot* nonode = nullptr;//указатель конечного узла
};
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
void new_branch(knot *current_branch, string &answer)
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
            game(current_branch->yesnode);//ретюрн не нужен)))

        if (answer == "нет")
            game(current_branch->nonode);
        
    }
    else
    {
        new_branch(current_branch, answer);
    }

}
bool game_continue()
{
    cout << "Вы хотите играть с новым деревом? ";
    string s;
    cin >> s;
    if (s == "да") return 1;
    else return 0;
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   
    knot* zxc = new knot; // указателю присваиваю адресс новой переменной структуры, которая будет отвечать за новый узел
    zxc->animal_guess = "Волк";

    do
    {
        game(zxc);
    } while (game_continue());

    return 0;
}