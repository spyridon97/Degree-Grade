#include <Course.hpp>

using namespace std;

Course::Course(string name, float ects, float grade, float cutGrade) {
    this->name = name;
    this->ects = ects;
    this->grade = grade;
    this->cutGrade = cutGrade;
}

Course::Course(const Course &course) {
    name = course.name;
    ects = course.ects;
    grade = course.grade;
    cutGrade = course.cutGrade;

}

Course::~Course() = default;

string Course::getName() {
    return this->name;
}

float Course::getEcts() {
    return this->ects;
}

float Course::getGrade() {
    return this->grade;
}

float Course::getCutGrade() {
    return this->cutGrade;
}

void Course::printCourse() {
    cout << name << visualOptName() << "  " << ects;
    if (cutGrade == 0) {
        cout << visualOptEcts() << "  " << grade << visualOptGrade() << "-" << endl;
    } else {
        cout << visualOptEcts() << "  " << grade << visualOptGrade() << cutGrade << endl;
    }
}

string Course::visualOptName() {
    int sp, i;
    char space[60];

    sp = 60 - (int)name.length();

    for (i = 0; i < sp; i++)
        space[i] = ' ';
    space[i] = '\0';

    return string(space);

}

string Course::visualOptEcts() {
    int sp, i;
    char space[60];

    for (i = 0; ects != rint(ects); ects += ects, i++);
    sp = 5 - (int)(floor(log10(abs(ects))) + 1);

    if (i != 0)
        sp -= 1;
    for (i = 0; i < sp + 4; i++)
        space[i] = ' ';
    space[i] = '\0';

    return string(space);
}

string Course::visualOptGrade() {
    int sp, i;
    char space[60];

    if (grade != 0) {
        for (i = 0; grade != rint(grade); grade += grade, i++);

        sp = 8 - (int)(floor(log10(abs(grade))) + 1);
        if (i != 0) {
            sp -= 1;
        }
    } else {
        sp = 8 - 1;
    }
    for (i = 0; i < sp + 4; i++)
        space[i] = ' ';
    space[i] = '\0';

    return string(space);
}
