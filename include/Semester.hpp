#ifndef SEMESTER_H
#define SEMESTER_H

#include <Course.hpp>
#include <vector>
#include <string>


class Semester {
private:
    int semesterId;
    int numberOfCourses;
    int passedCourses;
    int unexaminedCourses;
    int coursesForReexamination;
    int cutCourses;
    double averageSemesterTerm;
    double averageSemesterTermWithCutCourses;
    vector<Course> courses;

    string visualOpt();

public:
    Semester(int);

    Semester(const Semester &);

    ~Semester();

    int getSemesterId();

    int getNumberOfCourses();

    int getPassedCourses();

    int getUnexaminedCourses();

    int getCoursesForReexamination();

    int getCutCourses();

    void setAverageSemesterTerm();

    double getAverageSemesterTerm();

    void setAverageSemesterTermWithCutCourses();

    double getAverageSemesterTermWithCutCourses();

    void addCourse(Course);

    Course getCourse(int);

    string getCourseId(int);

    void printSemesterResults();


};

#endif // SEMESTER_H
