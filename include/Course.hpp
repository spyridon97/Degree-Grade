#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include <cmath>

using namespace std;


class Course {
private:
    string name;
    float ects;
    float grade;
    float cutGrade;

    string visualOptName();

    string visualOptEcts();

    string visualOptGrade();

public:
    Course(string, float, float, float);

    Course(const Course &);

    ~Course();

    string getName();

    float getEcts();

    float getGrade();

    float getCutGrade();

    void printCourse();
};

#endif // COURSE_H
