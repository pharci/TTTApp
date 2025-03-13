#include <iostream>
#include "pch.h"
#include "Manager.h"
#include "Windows.h"
#include <ctime>
#include <cstdlib> 

int main() {
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::srand(std::time(0));

    Manager manager;

    if (!manager.Init()) {
        cout << "Неверные данные, выходим...";
        _getch();
        return 0;
    }
    while (!manager.IsGameFinished()) {
        manager.MakeMove();
    }
}