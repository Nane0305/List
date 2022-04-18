
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
    {"�����", nullptr, AlwaysDisplay},
    {"������� �������� ������", CreateTestingData, Empty},
    {"��������", Add, AlwaysDisplay },
    {"�������������", Edit, NotEmpty},
    {"�������", Remove, NotEmpty},
    {"������� ��� ������", Clear, NotEmpty},
    {"���������", Save, AlwaysDisplay},
    {"��������� ��� �����...", SaveAsText, NotEmpty},
    {"����������� �� ����������", SortByPriority, MoreThanOne},
    {"����������� �� ����", SortByData, MoreThanOne},
    {"����� �� ��������", FilterByName, MoreThanOne},
    {"����� �� ����������", FilterByPriority, MoreThanOne},
    {"����� �� ��������", FilterByDescription, MoreThanOne},
    {"����� �� ����", FilterByData, MoreThanOne},
    {"����������� ��� �� ����", DisplayForDay, MoreThanOne},
    {"����������� ��� �� ������", DisplayForWeek, MoreThanOne},
    {"����������� ��� �� �����", DisplayForMonth, MoreThanOne},

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