#include <iostream>
#include <algorithm>
#include <list>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

vector <int> randomize(int n)
{
    vector <int> numbers = { 1,2,3,4,5,6,7,8,9 };
    vector <int> numbers_gen;

    int rnd = 10;
    int rmd = 0;
    
    if (n == 1) numbers.push_back(0);
    
    for (int i = 0; i < n; i++)
    {
        if (i == 1) numbers.push_back(0);

        if (numbers_gen.size() > 0)
        {
            for (int a = 0; a < numbers.size(); a++)
            {
                if (numbers_gen[i - 1] == numbers[a])
                    rmd = a;
            }
            swap(numbers[rmd], numbers[numbers.size() - 1]);
            numbers.pop_back();
        }

        numbers_gen.push_back(numbers[rand() % rnd]);
        rnd--;
    }
    return numbers_gen;
}

int main()
{
    setlocale(LC_ALL, "russian");
    srand(time(NULL));

    vector <int> numbers_gen;

    int n;
    int zxc = 0;

    cout << "Введите длинну числа (от 1 до 10): ";
    cin >> n;

    while (n < 1 || n > 10)
    {
        cout << endl << "Вы указали неверное число. Укажите число, длинной от 1 до 9 :";
        cin >> n;
    }

    cout << endl;

    numbers_gen = randomize(n);

    cout << "1 - самостоятельно угадать число" << endl;
    cout << "2 - компьютер угадывает число" << endl << endl;
    cout << "Выберите способ: ";

    cin >> zxc;

    if (zxc == 1)
    {        
        vector <int> numbers_input;
        
        int number_input;

        while (numbers_input != numbers_gen)
        {
            int cows = 0;
            int bulls = 0;

            cout << "Введите число: ";
            cin >> number_input;
            cout << endl;

            while (number_input > 0)
            {
                numbers_input.push_back(number_input % 10);
                number_input /= 10;
            }
            reverse(numbers_input.begin(), numbers_input.end());

            while (numbers_input.size() != n)
            {
                cout << "Вы ввели неверное число, длинна числа должна быть равна " << n << ": ";
                cin >> number_input;
                cout << endl;

                numbers_input.clear();

                while (number_input > 0)
                {
                    numbers_input.push_back(number_input % 10);
                    number_input /= 10;
                }
                reverse(numbers_input.begin(), numbers_input.end());
            }

            for (int i = 0; i < n; i++)
            {
                if (numbers_gen[i] == numbers_input[i])
                    bulls++;
                for (int a = 0; a < n; a++)
                    if (numbers_gen[i] == numbers_input[a])
                        cows++;
            }

            cout << "Быки = " << bulls << endl;
            cout << "Коровы = " << cows << endl << endl;

            if (bulls == cows && cows == n && bulls == n) break;

            bulls = 0;
            cows = 0;

            numbers_input.clear();
            cout << "Неверно, попробуйте ещё раз" << endl;
        }

        cout << "Вы правы!" << endl;
    }

    if (zxc == 2)
    {
        vector <int> numbers_PC;
        vector <int> numbers = { 1,2,3,4,5,6,7,8,9 };

        int tries = 0;

        if (n == 1) numbers.push_back(0);
        sort(numbers.begin(), numbers.end());

        for (int i = 0; i < numbers_gen.size(); i++)
            numbers_PC.push_back(0);

        cout << endl;

        for (int i = 0; i < numbers_gen.size(); i++)
        {
            if (i == 1) numbers.push_back(0);
            sort(numbers.begin(), numbers.end());

            for (int a = 0; a < numbers.size(); a++)
            {
                tries++;
                if (numbers[a] == numbers_gen[i])
                {
                    numbers_PC[i] = numbers[a];
                    swap(numbers[a], numbers[numbers.size() - 1]);
                    numbers.pop_back();
                    continue;
                }
            }
        }

        cout << "Количество потраченных попыток: " << tries << endl << endl;
        cout << "Загаданное число :";

        for (int i = 0; i < numbers_PC.size(); i++)
            cout << numbers_PC[i];

        cout << endl;
    }
    return 0;
}