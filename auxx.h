#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <string>

using namespace std;

namespace genogram {

typedef string Name;
typedef char Gender;
typedef int day;
typedef int month;
typedef int year;

struct PersonElem;

typedef PersonElem* Genogram;

const Genogram emptyGm = NULL;

Genogram createEmptyGenogram();


bool AddPerson (Name, Gender, Genogram&);
bool AddRelFather (Name, Name, Genogram&);
bool AddRelMother (Name, Name, Genogram&);
bool AddRelCouple (Name, Name, Genogram&); 
bool AddRelChildToCouple (Name, Name, Name, Genogram&);
bool SetBorn (Name, day, month, year, Genogram&);
bool SetDeath (Name, day, month, year, Genogram&);
bool IsValid (const Genogram&);
bool DeletePerson(Name, Genogram&);

}

void printGenogram(const genogram::Genogram&);

