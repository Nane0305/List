#pragma once

#include <iostream>
using std::ostream;

enum { NAME_SIZE = 40 };
enum { PRIORITY_NAME_SIZE = 8 };
enum { DESCRIPTION_SIZE = 68 };
enum { DATA_SIZE = 20 };

struct List {
    char Name[NAME_SIZE];
    char Priority[PRIORITY_NAME_SIZE];
    char Description[DESCRIPTION_SIZE];
    char Data[DATA_SIZE];
};

List*ElementAt(size_t index);
void Print(ostream& stream, List* pObj, int wide = 12);
void Print(ostream& stream);
void Save();
void Load();
void SaveAsText();

size_t GetLength();
bool Empty();
void CreateTestingData();
void Clear();
void Out();
void OutTable();

void Add();
void Edit();
void RunFiltering();
void FilterByName();
void FilterByPriority();
void FilterByDescription();
void FilterByData();
void SortByPriority();
void SortByData();
void Remove();
void DisplayForDay();
void DisplayForWeek();
void DisplayForMonth();
