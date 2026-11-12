
#ifndef FAKULTATYV_H
#define FAKULTATYV_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Абстрактний базовий клас
class EducationalItem {
protected:
    string name;

public:
    EducationalItem(string n);

    virtual void displayInfo() const = 0;

    virtual ~EducationalItem() {}
};

// Клас Семестр
class Semester : public EducationalItem {
private:
    string period;

public:
    Semester(string n, string p);

    void displayInfo() const override;
    string getName() const;
};

// Клас Навчальний матеріал
class Material : public EducationalItem {
private:
    string type;
    string description;

public:
    Material(string n, string t, string d);

    void displayInfo() const override;
};

// Клас Розклад
class Schedule : public EducationalItem {
private:
    string day;
    string time;

public:
    Schedule(string d, string t);

    void displayInfo() const override;
};

// Клас Студент
class Student {
private:
    string name;

public:
    Student(string n);

    string getName() const;
    void displayInfo() const;
};

// Клас Викладач
class Teacher {
private:
    string name;

public:
    Teacher(string n);

    string getName() const;
    void displayInfo() const;
};

// Структура для зберігання оцінок
struct GradeRecord {
    string studentName;
    int grade;
};

// Клас Архів
class Archive {
private:
    vector<GradeRecord> records;

public:
    void addGrade(string student, int grade);
    void showGrades() const;

    vector<GradeRecord> getRecords() const;
};

// Клас Курс
class Course : public EducationalItem {
private:
    string teacherName;
    Semester semester;
    Schedule schedule;

    vector<string> students;
    vector<Material> materials;
    Archive archive;

public:
    Course(string n, string teacher, Semester s, Schedule sch);

    void displayInfo() const override;

    void enrollStudent(const Student& student);
    void addMaterial(const Material& material);
    void setGrade(string studentName, int grade);

    void showStudents() const;
    void showMaterials(string studentName) const;
    void showSchedule() const;
    void showRating() const;
    void showArchive() const;
};

#endif
