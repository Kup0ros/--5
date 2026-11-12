
#include "Fakultatyv.h"
#include <windows.h>
#include <limits>

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Створення викладача
    Teacher teacher1("Іваненко Іван");

    // Створення семестру та розкладу
    Semester semester1("Осінній семестр",
        "Вересень - Грудень 2026");

    Schedule schedule1("Понеділок", "10:00");

    // Створення курсу
    Course course1("Програмування на C++",
        teacher1.getName(),
        semester1,
        schedule1);

    // Створення студентів
    Student student1("Петренко Арсеній");
    Student student2("Коваленко Андрій");
    Student student3("Мельник Олександр");

    // Створення навчальних матеріалів
    Material material1("Основи C++",
        "Презентація",
        "Вступ до програмування");

    Material material2("Практична робота №1",
        "Завдання",
        "Робота з класами та об'єктами");

    // Демонстрація поліморфізму
    cout << "===== ДЕМОНСТРАЦІЯ ПОЛІМОРФІЗМУ =====\n";

    vector<EducationalItem*> items;

    items.push_back(&semester1);
    items.push_back(&schedule1);
    items.push_back(&material1);
    items.push_back(&course1);

    for (EducationalItem* item : items) {
        item->displayInfo();
        cout << "----------------------\n";
    }

    // Додавання навчальних матеріалів
    course1.addMaterial(material1);
    course1.addMaterial(material2);

    int choice = -1;

    do {
        cout << "\n========== СИСТЕМА ФАКУЛЬТАТИВ ==========\n";
        cout << "1. Переглянути інформацію про курс\n";
        cout << "2. Записати студента на курс\n";
        cout << "3. Переглянути список студентів\n";
        cout << "4. Додати навчальний матеріал\n";
        cout << "5. Переглянути матеріали курсу\n";
        cout << "6. Переглянути розклад\n";
        cout << "7. Виставити оцінку студенту\n";
        cout << "8. Переглянути архів оцінок\n";
        cout << "9. Переглянути рейтинг студентів\n";
        cout << "0. Вихід\n";

        cout << "Ваш вибір: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введіть номер пункту меню!\n";
            continue;
        }

        switch (choice) {

        case 1:
            course1.displayInfo();
            break;

        case 2: {
            int studentChoice;

            cout << "\nОберіть студента:\n";
            cout << "1. Петренко Арсеній\n";
            cout << "2. Коваленко Андрій\n";
            cout << "3. Мельник Олександр\n";

            cout << "Ваш вибір: ";
            cin >> studentChoice;

            if (studentChoice == 1)
                course1.enrollStudent(student1);

            else if (studentChoice == 2)
                course1.enrollStudent(student2);

            else if (studentChoice == 3)
                course1.enrollStudent(student3);

            else
                cout << "Неправильний вибір!\n";

            break;
        }

        case 3:
            course1.showStudents();
            break;

        case 4: {
            string name, type, description;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Назва матеріалу: ";
            getline(cin, name);

            cout << "Тип матеріалу: ";
            getline(cin, type);

            cout << "Опис матеріалу: ";
            getline(cin, description);

            Material newMaterial(name, type, description);

            course1.addMaterial(newMaterial);

            break;
        }

        case 5: {
            string studentName;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Введіть ім'я студента: ";
            getline(cin, studentName);

            course1.showMaterials(studentName);

            break;
        }

        case 6:
            course1.showSchedule();
            break;

        case 7: {
            string studentName;
            int grade;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Ім'я студента: ";
            getline(cin, studentName);

            cout << "Оцінка (1-100): ";
            cin >> grade;

            course1.setGrade(studentName, grade);

            break;
        }

        case 8:
            course1.showArchive();
            break;

        case 9:
            course1.showRating();
            break;

        case 0:
            cout << "Завершення програми.\n";
            break;

        default:
            cout << "Неправильний вибір!\n";
        }

    } while (choice != 0);

    return 0;
}
