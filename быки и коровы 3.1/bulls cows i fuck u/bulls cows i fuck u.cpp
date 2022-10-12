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
vector <int> unique_alphabet_f(int n)
{
    vector <int> alpha;
    vector <int> beta;

    int L = pow(10, n - 1);
    int R = pow(10, n);

    for (int i = L; i < R; i++)
    {
        int counter = 0;
        int btw = i;
        while (btw > 0)
        {
            beta.push_back(btw % 10);
            btw /= 10;
        }
        for (int z = 0; z < beta.size(); z++)
        {
            for (int x = z + 1; x < beta.size(); x++)
            {
                if (beta[z] == beta[x])
                    counter++;
            }
        }
        if (counter == 0)
            alpha.push_back(i);

        beta.clear();
    }

    return alpha;
}
vector <int> to_numbers(int number)
{
    vector <int> zzz;

    int zxc = number;

    while (zxc > 0)
    {
        zzz.push_back(zxc % 10);
        zxc /= 10;
    }

    reverse(zzz.begin(), zzz.end());

    return zzz;
}

int bulls_f(vector<int> a, vector <int> b)
{
    int bulls = 0;

    for (int i = 0; i < a.size(); i++)
        if (a[i] == b[i]) bulls++;

    return bulls;
}
int cows_f(vector<int> a, vector <int> b)
{
    int cows = 0;

    for (int i = 0; i < a.size(); i++)
    {
        for (int z = 0; z < b.size(); z++)
            if (a[i] == b[z]) cows++;
    }

    cows -= bulls_f(a, b);
    return cows;
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

            numbers_input = to_numbers(number_input);

            while (numbers_input.size() != n)
            {
                cout << "Вы ввели неверное число, длинна числа должна быть равна " << n << ": ";
                cin >> number_input;
                cout << endl;

                numbers_input = to_numbers(number_input);
            }

            bulls = bulls_f(numbers_gen, numbers_input);
            cows = cows_f(numbers_gen, numbers_input);

            cout << "Быки = " << bulls << endl;
            cout << "Коровы = " << cows << endl << endl;

            if (bulls == n) break;

            cout << "Неверно, попробуйте ещё раз" << endl;
        }

        cout << "Вы правы!" << endl;
    }

    if (zxc == 2)
    {
        vector <int> bulls_cows(2, 0);

        vector<vector<int>> qwe;
        vector<vector<int>> btw;

        vector <int> numbers_input;
        vector <int> unique_alphabet;
        vector <int> beta;

        int bulls;
        int ftm;
        int cows;
        int rmd = 0;
        int attempts = 0;
        int stage = 0;
        int proov;

        while (numbers_input.size() != n)
        {
            int number_input;
            cout << endl << "Загадайте число:";
            cin >> number_input;

            numbers_input = to_numbers(number_input);

            if (numbers_input.size() != n)
                cout << endl << "Число должно быть длинной " << n << ". Попробуйте ещё раз" << endl;
        }

        unique_alphabet = unique_alphabet_f(n);

        if (stage == 0)
        {
            for (int i = 0; i < unique_alphabet.size() && stage == 0; i++)
            {
                ftm = unique_alphabet[i];

                beta = to_numbers(ftm);

                cows = cows_f(numbers_input, beta);
                bulls = bulls_f(numbers_input, beta);
                bulls_cows[0] = bulls;
                bulls_cows[1] = cows;

                if (bulls + cows > 0)
                {
                    qwe.push_back(beta);
                    btw.push_back(bulls_cows);
                    stage++;

                    cout << unique_alphabet[i] << endl;
                    cout << "Быки: " << bulls << endl;
                    cout << "Коровы: " << cows << endl << endl;
                }
            }
        }

        if (stage > 0)
        {
            for (int i = 0; i < unique_alphabet.size(); i++)
            {
                proov = 0;
                int zxc = unique_alphabet[i];
                beta = to_numbers(zxc);

                for (int z = 0; z < stage; z++)
                {
                    bulls = bulls_f(qwe[z], beta);
                    cows = cows_f(qwe[z], beta);

                    if (bulls == btw[z][0] && cows == btw[z][1])
                        proov++;
                }
                if (proov == qwe.size())
                {
                    bulls = bulls_f(numbers_input, beta);
                    cows = cows_f(numbers_input, beta);

                    bulls_cows[0] = bulls;
                    bulls_cows[1] = cows;

                    qwe.push_back(beta);
                    btw.push_back(bulls_cows);

                    stage++;

                    cout << unique_alphabet[i] << endl;
                    cout << "Быки: " << bulls << endl;
                    cout << "Коровы: " << cows << endl << endl;

                    if (bulls == numbers_input.size())
                    {
                        cout << "Загаданное число: ";
                        for (int v=0; v < n; v++)
                        {
                            cout << qwe[qwe.size() - 1][v];
                        }
                        break;
                    }
                }
            }
        }
    }
    return 0;
}