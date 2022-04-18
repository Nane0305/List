
#include "Running.h"
#include "Lists.h"
#include "Entering.h"

#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

typedef void (*Command) ();
typedef bool (*Display) ();

const size_t COMMAND_NAME_SIZE = 64;

struct CommandInfo {
    char name[COMMAND_NAME_SIZE];
    Command command;
    Display display;
};

bool AlwaysDisplay() { return true; }
bool NotEmpty() { return !Empty(); }
bool MoreThanOne() { return GetLength() > 1; }

CommandInfo commandsinfo[] = {
    {"Выход", nullptr, AlwaysDisplay},
    {"Создать тестовые данные", CreateTestingData, Empty},
    {"Добавить", Add, AlwaysDisplay },
    {"Редактировать", Edit, NotEmpty},
    {"Удалить", Remove, NotEmpty},
    {"Удалить все записи", Clear, NotEmpty},
    {"Сохранить", Save, AlwaysDisplay},
    {"Сохранить как текст...", SaveAsText, NotEmpty},
    {"Сортировать по приоритету", SortByPriority, MoreThanOne},
    {"Сортировать по дате", SortByData, MoreThanOne},
    {"Поиск по названию", FilterByName, MoreThanOne},
    {"Поиск по приоритету", FilterByPriority, MoreThanOne},
    {"Поиск по описанию", FilterByDescription, MoreThanOne},
    {"Поиск по дате", FilterByData, MoreThanOne},
    {"Отображение дел на день", DisplayForDay, MoreThanOne},
    {"Отображение дел на неделю", DisplayForWeek, MoreThanOne},
    {"Отображение дел на месяц", DisplayForMonth, MoreThanOne},

};

const size_t COMMANDS_COUNT = sizeof commandsinfo / sizeof(CommandInfo);

void ShowMenu() {
    cout << "\nCommands: \n";
    for (size_t i = 0; i < COMMANDS_COUNT; i++) {
        if(commandsinfo[i].display())
            cout << setw(4) << i << " - " << commandsinfo[i].name << endl;
    }

}

Command EnterCommand() {
    int index = EnterNumber("Command number", 0, COMMANDS_COUNT - 1);
    return commandsinfo[index].command;
}

void Run() {
    Load();
    while (true) {
        system("cls");
        //Out();
        OutTable();
        ShowMenu();
        Command command = EnterCommand();
        if (command == nullptr) {
            return;
        }
        command();

    }
}