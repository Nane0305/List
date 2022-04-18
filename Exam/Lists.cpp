
#define _CRT_SECURE_NO_WARNINGS

#include "Lists.h"
#include "Entering.h"
#include "DateTime.h"

#include <conio.h>
#include <iomanip>
#include <fstream>

using namespace std;

struct TableAttr {
    int NumWide = 2;
    int NameWide = 14;
    int PriorityWide = 10;
    int DescriptionWide = 15;
    int DataWide = 20;
};

TableAttr ta;

List** arr = nullptr;
size_t length = 0;

void OutTableHead() {
    cout << left 
        << " | " << setw(ta.NumWide) << "№" 
        << " | " << setw(ta.NameWide) << "Название"
        << " | " << setw(ta.PriorityWide) << "Приоритет"
        << " | " << setw(ta.DescriptionWide) << "Описание"
        << right
        << " | " << setw(ta.DataWide) << "Дата"
        << " | " << endl;
    int wide = ta.NumWide + ta.NameWide + ta.PriorityWide + ta.DescriptionWide + ta.DataWide + 6*3 - 2;
    cout << " " << setfill('-') << setw(wide) << '-' << endl << setfill(' ');
}

void OutTableRow(List* pObj, size_t num) {
    cout << left
        << " | " << setw(ta.NumWide) << num
        << " | " << setw(ta.NameWide) << pObj->Name
        << " | " << setw(ta.PriorityWide) << pObj->Priority
        << " | " << setw(ta.DescriptionWide) << pObj->Description
        << right
        << " | " << setw(ta.DataWide) << pObj->Data
        << " | " << endl;
}

List* ElementAt(size_t index) {
    if (index >= 0 && index < length)
        return arr[index];
    return nullptr;
}

void OutObjectDetails() {
    size_t num = EnterNumber("Номер записи", 1, (int)GetLength());
    List* p = ElementAt(num - 1);
    Print(cout, p);
}

void OutTable() {
    cout << setprecision(12);
    if (Empty()) {
        cout << "Список дел пустой!\n";
    }
    else {
        cout << "Список дел:\n";
        OutTableHead();
        size_t len = GetLength();
        for (size_t i = 0; i < len; i++) {
            OutTableRow(ElementAt(i), i + 1);
        }
    }
}

List testArr[] = {
    {"Покупки", "ср.", "Купить продукты", "2022.03.15 до 13:00"},
    {"Задание", "выс.", "Дом. задание", "2022.02.18 до 17:00"},
    {"Работа", "выс.", "Работа", "2022.02.13 до 07:30"},
    {"Кино", "низ.", "Встреча", "2022.04.16 до 17:00"},
    {"Работа", "выс.", "Работа", "2022.03.15 до 07:30"},
    {"Почта", "ср.", "Забрать посылку", "2022.04.20 до 15:30"},
};

const size_t TEST_ARR_SIZE = sizeof testArr / sizeof(List);

size_t GetLength() {
    return length;
}

bool Empty() {
    return arr == nullptr;
}

void CreateTestingData() {
    arr = new List * [TEST_ARR_SIZE];
    for (size_t i = 0; i < TEST_ARR_SIZE; i++) {
        arr[i] = new List();
        *arr[i] = testArr[i];
    }
    length = TEST_ARR_SIZE;
}

void Clear() {
    
    for (size_t i = 0; i < length; i++) {
        delete arr[i];
    }
    delete[] arr;
    arr = nullptr;
    length = 0;
}

void OutObject(List* pObj, size_t num) {
    cout << left <<
        setw(4) << num << " " <<
        setw(20) << pObj->Name <<
        setw(12) << pObj->Priority <<
        setw(40) << pObj->Description <<
        setw(16) << pObj->Data << endl;
}

void Print(ostream& stream, List* pObj, int wide) {
    stream << setw(wide) << "Название" << ": " << pObj->Name << "\n"
        << setw(wide) << "Приоритет" << ": " << pObj->Priority << "\n"
        << setw(wide) << "Описание" << ": " << pObj->Description << "\n"
        << setw(wide) << "Дата" << ": " << pObj->Data << "\n";
}

void Print(ostream& stream) {
    stream << setprecision(12);
    for (size_t i = 0; i < length; i++) {
        Print(stream, arr[i]);
    }
}

void Out() {
    cout << setprecision(12);
    if (Empty()) {
        cout << "List is empty!\n";
    }
    else {
        cout << "List:\n";
        for (size_t i = 0; i < length; i++) {
            OutObject(arr[i], i + 1);
        }
    }
}

List* Create() {
    List* p = new List();
    cout << "Enter lists data\n";
    cout << "\tName: ";
    cin.getline(p->Name, NAME_SIZE);
    cout << "\tPriority: ";
    cin.getline(p->Priority, PRIORITY_NAME_SIZE);
    cout << "Description:\n";
    cin.getline(p->Description, DESCRIPTION_SIZE);
    cout << "Data:\n";
    cin.getline(p->Data, DATA_SIZE);
    return p;
}

void Add(List* p) {
    if (Empty()) {
        arr = new List * [1];
        arr[0] = p;
    }
    else {
        List** newArr = new List * [length + 1];
        for (size_t i = 0; i < length; i++) {
            newArr[i] = arr[i];
        }
        newArr[length] = p;
        delete[] arr;
        arr = newArr;
    }
    length++;
}

void Add() {
    Add(Create());
}

void Edit() {
    int num = EnterNumber("Номер записи", 1, length);
    List* p = arr[num - 1];
    char buff[128];
    cout << "Редактировать данные дела\n";
    cout << "\tНазвание (" << p->Name << "): ";
    cin.getline(buff, NAME_SIZE);
    if (*buff != '\0') {
        strncpy(p->Name, buff, NAME_SIZE);
    }
    cout << "Описание: ";
    cin.getline(buff, sizeof buff);
    if (*buff != '\0') {
        strncpy(p->Description, buff, DESCRIPTION_SIZE);
    }
    cout << "Дата:\n";
    cin.getline(p->Data, DATA_SIZE);
   
}

void SortByPriority() {
    for (size_t i = 1; i < length; i++) {
        List* tmp = arr[i];
        int j = i - 1;
        for (; j >= 0 && _stricmp(arr[j]->Priority, tmp->Priority) > 0; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
}

void SortByData() {
    for (size_t i = 1; i < length; i++) {
        List* tmp = arr[i];
        int j = i - 1;
        for (; j >= 0 && _stricmp(arr[j]->Data, tmp->Data) > 0; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = tmp;
    }
}

void FilterByName() {
    cout << "Начало названия: ";
    char buff[40];
    cin.getline(buff, sizeof buff);
    for (size_t i = 0; i < length; i++) {
        if (strstr(arr[i]->Name, buff) == arr[i]->Name) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

void FilterByPriority() {
    cout << "Приоритет: ";
    char buff[4];
    cin.getline(buff, sizeof buff);
    for (size_t i = 0; i < length; i++) {
        if (strstr(arr[i]->Priority, buff) == arr[i]->Priority) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

void FilterByDescription() {
    cout << "Начало описания: ";
    char buff[68];
    cin.getline(buff, sizeof buff);
    for (size_t i = 0; i < length; i++) {
        if (strstr(arr[i]->Description, buff) == arr[i]->Description) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

void FilterByData() {
    cout << "Введите дату: ";
    char buff[16];
    cin.getline(buff, sizeof buff);
    for (size_t i = 0; i < length; i++) {
        if (strstr(arr[i]->Data, buff) == arr[i]->Data) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

void Remove() {
    int num = EnterNumber("Номер записи", 1, length);
    List** newArr = new List * [length - 1];
    for (size_t i = 0; i < num - 1; i++) {
        newArr[i] = arr[i];
    }
    delete arr[num - 1];
    for (size_t i = num; i < length; i++) {
        newArr[i - 1] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    length--;
}

void DisplayForDay() {
    cout << "Введите искомую дату: ";
    char buff[16];
    cin.getline(buff, sizeof buff);
    for (size_t i = 0; i < length; i++) {
        if (strstr(arr[i]->Data, buff) == arr[i]->Data) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

void DisplayForWeek() {
    cout << "Введите искомую дату: ";
    char buff1[16];
    cin.getline(buff1, sizeof buff1);
    char buff2[16];
    strcpy(buff2, AddWeek(buff1));

    char buff[32];
    for (size_t i = 0; i < length; i++) {
        strcpy(buff, arr[i]->Data);
        buff[10] = '\0';
        if (strcmp(buff, buff1) >= 0 && strcmp(buff, buff2) <= 0) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

void DisplayForMonth() {
    cout << "Введите искомую дату: ";
        char buff1[16];
    cin.getline(buff1, sizeof buff1);
    char buff2[16];
    strcpy(buff2, AddMonth(buff1));

    char buff[32];
    for (size_t i = 0; i < length; i++) {
        strcpy(buff, arr[i]->Data);
        buff[10] = '\0';
        if (strcmp(buff, buff1) >= 0 && strcmp(buff, buff2) <= 0) {
            OutObject(arr[i], i + 1);
        }
    }
    cout << "\nНажмите любую клавишу...\n";
    _getch();
}

char binFileName[_MAX_FNAME] = "ListsInfo.bin";

void Save() {
    fstream stream(binFileName, ios::trunc | ios::out | ios::binary);
    if (!stream.is_open()) {
        cout << "Ошибка открытия файла " << binFileName << " для записи\n";
        return;
    }
    for (size_t i = 0; i < GetLength(); i++) {
        stream.write((char*)ElementAt(i), sizeof(List));
    }
    stream.close();
}

void Load() {
    fstream stream(binFileName, ios::in | ios::out | ios::binary);
    if (!stream.is_open()) {
        cout << "Ошибка открытия файла " << binFileName << " для чтения\n";
        return;
    }
    while (true) {
        List* p = new List;
        if (!stream.read((char*)p, sizeof(List)))
            break;
        Add(p);
    }
    stream.close();
}

char textFileName[_MAX_FNAME] = "List.txt";

char* InputFileName(const char* defaultName) {
    static char fName[_MAX_FNAME];
    cout << "\tВведите имя файла (" << defaultName << "): ";
    cin.getline(fName, _MAX_PATH);
    if (fName[0] == '\0') {
        strcpy(fName, defaultName);
    }
    else if (strstr(fName, ".txt") == nullptr) {
        strcat(fName, ".txt");
    }
    return fName;
}

void SaveAsText(const char* fName) {
    ofstream fout(fName);
    if (!fout.is_open())
        return;
    Print(fout);
    fout.close();
}

void SaveAsText() {
    char* fName = InputFileName(textFileName);
    SaveAsText(fName);
}

//void LoadFromText() {
//    char* fName = InputFileName(textFileName);
//    LoadFromText(fName);
//}