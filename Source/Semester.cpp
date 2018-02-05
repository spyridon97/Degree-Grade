#include <Semester.hpp>

using namespace std;

Semester::Semester(int semesterId) {
    this->semesterId = semesterId;

    numberOfCourses = 0;
    passedCourses = 0;
    unexaminedCourses = 0;
    coursesForReexamination = 0;
    cutCourses = 0;
    averageSemesterTerm = 0;
    averageSemesterTermWithCutCourses = 0;
}

Semester::Semester(const Semester &semester) {
    semesterId = semester.semesterId;
    numberOfCourses = semester.numberOfCourses;
    passedCourses = semester.passedCourses;
    unexaminedCourses = semester.unexaminedCourses;
    coursesForReexamination = semester.coursesForReexamination;
    cutCourses = semester.cutCourses;
    averageSemesterTerm = semester.averageSemesterTerm;
    averageSemesterTermWithCutCourses = semester.averageSemesterTermWithCutCourses;
    courses = semester.courses;
}

Semester::~Semester() {
    courses.clear();
}

int Semester::getSemesterId() {
    return this->semesterId;
}

int Semester::getNumberOfCourses() {

    return this->numberOfCourses;
}

int Semester::getPassedCourses() {
    return this->passedCourses;
}

int Semester::getUnexaminedCourses() {
    return this->unexaminedCourses;
}

int Semester::getCoursesForReexamination() {
    return this->coursesForReexamination;
}

int Semester::getCutCourses() {
    return this->cutCourses;
}

void Semester::setAverageSemesterTerm() {
    float sumGrades = 0, sumEcts = 0;

    for (unsigned int i = 0; i < courses.size(); i++) {
        if (courses.at(i).getGrade() >= 5) {
            sumGrades += (courses.at(i).getGrade() * courses.at(i).getEcts());
            sumEcts += courses.at(i).getEcts();
        }
    }

    if (sumEcts > 0) {
        averageSemesterTerm = sumGrades / sumEcts;
        averageSemesterTerm = round(averageSemesterTerm * 100 + 0.001) / 100;
    }
}

double Semester::getAverageSemesterTerm() {
    return this->averageSemesterTerm;
}

void Semester::setAverageSemesterTermWithCutCourses() {
    float sumGrades = 0, sumEcts = 0;

    for (unsigned int i = 0; i < courses.size(); i++) {
        if (courses.at(i).getCutGrade() >= 5) {
            sumGrades += (courses.at(i).getCutGrade() * courses.at(i).getEcts());
            sumEcts += courses.at(i).getEcts();
        } else if (courses.at(i).getGrade() >= 5) {
            sumGrades += (courses.at(i).getGrade() * courses.at(i).getEcts());
            sumEcts += courses.at(i).getEcts();
        }
    }
    if (sumEcts > 0) {
        averageSemesterTermWithCutCourses = sumGrades / sumEcts;
        averageSemesterTermWithCutCourses = round(averageSemesterTermWithCutCourses * 100 + 0.001) / 100;
    }
}

double Semester::getAverageSemesterTermWithCutCourses() {
    return this->averageSemesterTermWithCutCourses;
}

void Semester::addCourse(Course course) {
    numberOfCourses++;
    courses.push_back(course);
    if (course.getGrade() >= 5) {
        passedCourses++;
    } else if (course.getGrade() == 0) {
        unexaminedCourses++;
    } else if (course.getGrade() > 0 && course.getGrade() < 5) {
        coursesForReexamination++;
    }

    if (course.getCutGrade() > 0) {
        cutCourses++;
    }
}


Course Semester::getCourse(int index) {
    return courses.at(index);
}

string Semester::getCourseId(int index) {
    string courseId = "C";

    if (semesterId > 9)
        courseId = courseId + "-" + to_string(semesterId);
    else
        courseId = courseId + "-0" + to_string(semesterId);

    if (index > 9)
        courseId = courseId + "-" + to_string(index);
    else
        courseId = courseId + "-0" + to_string(index);

    return courseId;
}

void Semester::printSemesterResults() {
    cout << endl << "Semester : " + to_string(semesterId) << endl;
    cout << endl << "Code:      Course :" << visualOpt() << "  " << "ECTS:      Grade:      Cut-Grade:" << endl;

    for (int i = 0; i < numberOfCourses; i++) {
        cout << getCourseId(i + 1) << "    ";
        getCourse(i).printCourse();
    }

    if (averageSemesterTermWithCutCourses > 0 && averageSemesterTermWithCutCourses != averageSemesterTerm) {
        cout << endl << "Semester's Average Term With The " << getCutCourses() << " Cut-Course(s): "
             << averageSemesterTermWithCutCourses;
    }
    if (averageSemesterTerm > 0) {
        cout << endl << "Semester's Average Term : " << averageSemesterTerm << endl;
    } else {
        cout << endl << "Semester's Average Term : 0      !You have not been examined in any course." << endl;
    }

}

string Semester::visualOpt() {
    int sp, i;
    char space[60];
    string course = "Course :";

    sp = 60 - course.length();

    for (i = 0; i < sp; i++)
        space[i] = ' ';
    space[i] = '\0';

    return string(space);

}

