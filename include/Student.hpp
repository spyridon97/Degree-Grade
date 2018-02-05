#ifndef STUDENT_H
#define STUDENT_H

#include <Semester.hpp>
#include <Course.hpp>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/algorithm/string.hpp>

class Student {
private:
    string name;
    string surname;
    int yearOfRestration;
    int currentSemester;
    int totalCourses;
    int passedCourses;
    int unexaminedCourses;
    int coursesForReexamination;
    int cutCourses;
    double degreeGrade;
    double degreeGradeWithCutCourses;
    vector<Semester> semesters;

    void readData(string);

    void correctInputString(string &);

    void setCurrentSemester();

public:
    Student(string);

    ~Student();

    string getName();

    string getSurname();

    int getYearOfRegistration();

    int getCurrentSemester();

    int getPassedCourses();

    int getUnexaminedCourses();

    int getCutCourses();

    double getDegreeGrade();

    double getDegreeGradeWithCutCourses();

    void addSemester(Semester);

    Semester getSemester(int);

    void printDataOfStudent();
};

#endif // STUDENT_H
