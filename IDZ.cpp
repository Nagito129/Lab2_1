#include <iostream>
#include <fstream> 
#include <string>
#include <Windows.h>
using namespace std;
string path = "C:\\Users\\MAX\\Desktop\\Prog\\Dormitory.txt";
struct Student {
	string name;
	string sex;
	int group;
	int ID;
	int grades[8];
	string location;
	float income;
	string social;
};
int CountStudents() {
	ifstream database;
	database.open(path);
	if (database.is_open())
	{
		int temp = 0;
		string data;
		while (!database.eof())
		{
			getline(database, data);
			temp++;
		}
		database.close();
		int n;
		n = temp / 8;
		return n;
	}
	else return 0;
}
void CreateMassStudents(Student* students, int size) {
	char trash;
	ifstream database;
	database.open(path);
	if (!database.is_open())
		cout << "Ошибка открытия файла!\n";
	else {
		if (size == 0)
			cout << "Файл пуст!";
		else {
			for (Student* p = students; p < students + size; p++) {
				getline(database, p->name);
				getline(database, p->sex);
				database >> p->group >> p->ID;
				for (int i = 0; i < 8; i++)
					database >> p->grades[i];
				database.get(trash);
				getline(database,p->location);
				database >> p->income;
				database.get(trash);
				getline(database, p->social);
			}
		}
	}
}
void Income(Student* students, int size) {
	int n;
	cout << "Будут выведены студенты с доходом меньше N. Введите N: ";
	cin >> n;
	for (Student* p = students; p < students + size; p++)
		if (p->income < n) {
			cout << p->name << "\tДоход:" << p->income << "\n";
		}
}
void Sort(Student* students, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (students[j].income > students[j + 1].income)
				swap(students[j], students[j + 1]);
			else if (students[size - j - 1].income < students[size - j - 2].income)
				swap(students[size - j - 1], students[size - j - 2]);
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (students[j].location == "Местный" && students[j + 1].location == "Иногородний")
				swap(students[j], students[j + 1]);
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (students[j].social == "Нет" && students[j + 1].social == "Да")
				swap(students[j], students[j + 1]);
		}
	}
	int j = 1;
	cout << "10 студентов, которые обязательно получат материальную помощь:\n";
	for (Student* p = students; p < students + size; p++, j++) {
		cout << j << ". " << p->name << "\n";
		if (j == 10)
			break;
	}
}

int main() {
	setlocale(0, "");
	int size;
	size = CountStudents();
	Student* students = new Student[size];
	CreateMassStudents(students, size);
	Income(students, size);
	system("pause");
	system("cls");
	Sort(students, size);
	system("pause");
	delete[] students;
}
