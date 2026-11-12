
#include "Fakultatyv.h"
#include <algorithm>

// EducationalItem
EducationalItem::EducationalItem(string n) {
    name = n;
}

// Semester
Semester::Semester(string n, string p)
    : EducationalItem(n) {
    period = p;
}

void Semester::displayInfo() const {
    cout << "Семестр: " << name
        << " (" << period << ")" << endl;
}

string Semester::getName() const {
    return name;
}

// Material
Material::Material(string n, string t, string d)
    : EducationalItem(n) {
    type = t;
    description = d;
}

void Material::displayInfo() const {
    cout << "Матеріал: " << name << endl;
    cout << "Тип: " << type << endl;
    cout << "Опис: " << description << endl;
}

// Schedule
Schedule::Schedule(string d, string t)
    : EducationalItem("Розклад") {
    day = d;
    time = t;
}

void Schedule::displayInfo() const {
    cout << "День: " << day << endl;
    cout << "Час: " << time << endl;
}

// Student
Student::Student(string n) {
    name = n;
}

string Student::getName() const {
    return name;
}

void Student::displayInfo() const {
    cout << "Студент: " << name << endl;
}

// Teacher
Teacher::Teacher(string n) {
    name = n;
}

string Teacher::getName() const {
    return name;
}

void Teacher::displayInfo() const {
    cout << "Викладач: " << name << endl;
}

// Archive
void Archive::addGrade(string student, int grade) {
    for (auto& record : records) {
        if (record.studentName == student) {
            record.grade = grade;
            return;
        }
    }

    records.push_back({ student, grade });
}

void Archive::showGrades() const {
    cout << "\n--- Архів оцінок ---\n";

    if (records.empty()) {
        cout << "Оцінок поки немає.\n";
        return;
    }

    for (const auto& record : records) {
        cout << record.studentName
            << " - " << record.grade << " балів\n";
    }
}

vector<GradeRecord> Archive::getRecords() const {
    return records;
}

// Course
Course::Course(string n, string teacher,
    Semester s, Schedule sch)
    : EducationalItem(n),
    teacherName(teacher),
    semester(s),
    schedule(sch) {}

void Course::displayInfo() const {
    cout << "\nКурс: " << name << endl;
    cout << "Викладач: " << teacherName << endl;
    semester.displayInfo();
}

void Course::enrollStudent(const Student& student) {
    for (const string& s : students) {
        if (s == student.getName()) {
            cout << "Студент вже записаний на курс!\n";
            return;
        }
    }

    students.push_back(student.getName());

    cout << student.getName()
        << " записаний на курс "
        << name << endl;
}

void Course::addMaterial(const Material& material) {
    materials.push_back(material);
    cout << "Матеріал успішно додано!\n";
}

void Course::setGrade(string studentName, int grade) {
    if (grade < 1 || grade > 100) {
        cout << "Оцінка повинна бути від 1 до 100!\n";
        return;
    }

    bool found = false;

    for (const string& s : students) {
        if (s == studentName) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Студент не записаний на цей курс!\n";
        return;
    }

    archive.addGrade(studentName, grade);

    cout << "Оцінку збережено в архіві!\n";
}

void Course::showStudents() const {
    cout << "\n--- Список студентів ---\n";

    if (students.empty()) {
        cout << "Студентів поки немає.\n";
        return;
    }

    for (const string& s : students) {
        cout << s << endl;
    }
}

void Course::showMaterials(string studentName) const {
    bool found = false;

    for (const string& s : students) {
        if (s == studentName) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Немає доступу до матеріалів!\n";
        return;
    }

    cout << "\n--- Навчальні матеріали ---\n";

    if (materials.empty()) {
        cout << "Матеріалів поки немає.\n";
        return;
    }

    for (const Material& m : materials) {
        m.displayInfo();
        cout << "-------------------\n";
    }
}

void Course::showSchedule() const {
    cout << "\n--- Розклад занять ---\n";
    schedule.displayInfo();
}

void Course::showRating() const {
    cout << "\n--- Рейтинг студентів ---\n";

    vector<GradeRecord> rating = archive.getRecords();

    if (rating.empty()) {
        cout << "Оцінок поки немає.\n";
        return;
    }

    sort(rating.begin(), rating.end(),
        [](const GradeRecord& a, const GradeRecord& b) {
            return a.grade > b.grade;
        });

    for (size_t i = 0; i < rating.size(); i++) {
        cout << i + 1 << ". "
            << rating[i].studentName
            << " - " << rating[i].grade << " балів\n";
    }
}

void Course::showArchive() const {
    archive.showGrades();
}
