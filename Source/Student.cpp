#include <Student.hpp>

using namespace std;

Student::Student(string filename) {
    totalCourses = 0;
    passedCourses = 0;
    unexaminedCourses = 0;
    cutCourses = 0;
    degreeGrade = 0;
    degreeGradeWithCutCourses = 0;

    readData(filename);
}

Student::~Student() {
    semesters.clear();
}

void Student::readData(string filename) {
    ifstream data;
    data.open(filename + ".txt");
    if (data) {
        data >> name >> surname >> yearOfRestration;

        correctInputString(name);
        correctInputString(surname);
        setCurrentSemester();

        int coursesPerSemester[currentSemester];
        for (int i = 0; i < currentSemester; i++) {
            coursesPerSemester[i] = 0;
        }

        string input;
        getline(data, input);
        for (int i = -1; !data.eof() && i < currentSemester;) {
            getline(data, input);
            if (input.find("Semester") != string::npos) {
                i++;
            } else {
                coursesPerSemester[i]++;
                totalCourses++;
            }
        }

        data.clear();
        data.seekg(0, data.beg);

        float sumEcts = 0, sumGrades = 0, maxCourseNameLength = 0, sumEctsWithCutCourses = 0, sumGradesWithCutCourses = 0;
        getline(data, input);
        for (int i = 0; i < currentSemester; i++) {
            Semester semester = Semester(i + 1);


            getline(data, input);
            for (int j = 0; j < coursesPerSemester[i]; j++) {
                string courseName = "";
                float ects = 0, grade = 0, cutGrade = 0;
                vector<string> tokens;

                getline(data, input);
                boost::split(tokens, input, boost::is_any_of(" "));

                unsigned tokensAfterCourseName = 2 + 1; // + 1 exists because the counter starts from 0

                string lastToken = tokens.at(tokens.size() - 1);
                if (boost::find_first(lastToken, "(")) {
                    tokensAfterCourseName = 3 + 1; // + 1 exists because the counter starts from 0
                    boost::erase_all(lastToken, "(");
                    boost::erase_all(lastToken, ")");
                }

                for (unsigned int k = 0; k < tokens.size(); k++) {
                    if (k < tokens.size() - tokensAfterCourseName) {
                        courseName += (tokens.at(k) + " ");
                    } else if (k == tokens.size() - tokensAfterCourseName) {
                        courseName += tokens.at(k);
                    } else if (k == tokens.size() - (tokensAfterCourseName - 1)) {
                        ects = stof(tokens.at(k));
                    } else if (k == tokens.size() - (tokensAfterCourseName - 2)) {
                        grade = stof(tokens.at(k));
                    } else {
                        cutGrade = stof(lastToken);
                    }
                }
                correctInputString(courseName);
                if (courseName.size() > maxCourseNameLength)
                    maxCourseNameLength = courseName.size();

                Course course = Course(courseName, ects, grade, cutGrade);
                semester.addCourse(course);

                //calculating degree grade
                if (grade >= 5) {
                    sumEcts += ects;
                    sumGrades += (grade * ects);
                }

                //calculating degree grade with Cut-Courses
                if (grade > cutGrade && grade >= 5) {
                    sumEctsWithCutCourses += ects;
                    sumGradesWithCutCourses += (grade * ects);
                } else if (cutGrade >= 5 && cutGrade > grade && grade < 5) {
                    sumEctsWithCutCourses += ects;
                    sumGradesWithCutCourses += (cutGrade * ects);
                }
            }
            semester.setAverageSemesterTerm();
            semester.setAverageSemesterTermWithCutCourses();
            addSemester(semester);
        }

        for (unsigned int i = 0; i < semesters.size(); i++) {
            passedCourses += semesters.at(i).getPassedCourses();
            unexaminedCourses += semesters.at(i).getUnexaminedCourses();
            coursesForReexamination += semesters.at(i).getCoursesForReexamination();
            cutCourses += semesters.at(i).getCutCourses();
        }

        degreeGrade = round((sumGrades / sumEcts) * 100 + 0.001) / 100;
        degreeGradeWithCutCourses = round((sumGradesWithCutCourses / sumEctsWithCutCourses) * 100 + 0.001) / 100;
    } else
        cerr << "Could not open File " << endl;
}

string Student::getName() {
    return this->name;
}

string Student::getSurname() {
    return this->surname;
}

int Student::getYearOfRegistration() {
    return this->yearOfRestration;
}

int Student::getCurrentSemester() {
    return this->currentSemester;
}

int Student::getPassedCourses() {
    return this->passedCourses;
}

int Student::getUnexaminedCourses() {
    return this->unexaminedCourses;
}

int Student::getCutCourses() {
    return this->cutCourses;
}

double Student::getDegreeGrade() {
    return this->degreeGrade;
}

double Student::getDegreeGradeWithCutCourses() {
    return this->degreeGradeWithCutCourses;
}

void Student::addSemester(Semester semester) {
    semesters.push_back(semester);
}

Semester Student::getSemester(int index) {
    return semesters.at(index);
}

void Student::printDataOfStudent() {
    cout << "Name : " << name << " , Surname : " << surname << " , Year of Registration : " << yearOfRestration << endl;
    for (int i = 0; i < currentSemester; i++) {
        getSemester(i).printSemesterResults();
    }

    cout << endl << "Final results : " << endl;
    cout << endl << "Total Course(s): " << totalCourses << endl;
    if (passedCourses > 0) {
        cout << "Passed Course(s): " << passedCourses << endl;
    }
    if (coursesForReexamination >= 1) {
        cout << "Course(s) for Reexamination: " << coursesForReexamination << endl;
    }
    if (cutCourses >= 1) {
        cout << "Cut-Course(s): " << getCutCourses() << endl;
    }
    if (unexaminedCourses >= 1) {
        cout << "Unexamined Course(s) : " << unexaminedCourses << endl;
    }
    if (cutCourses >= 1) {
        cout << endl << "Your Degree Grade With The " << getCutCourses() << " Cut-Course(s): "
             << degreeGradeWithCutCourses;
    }

    cout << endl << "Your Degree Grade = " << degreeGrade << endl;


}

void Student::correctInputString(string &input) {
    int length = input.length();

    for (int i = 0; i < length; i++) {
        if ((int) input[i] == -13)
            input[i] = input[i] - 74;
        else if ((int) input[i] == -14)
            input[i] = input[i] - 72;
        else if ((int) input[i] == -7)
            input[i] = input[i] - 25;
        else if ((int) input[i] >= -31 && (int) input[i] <= -8)
            input[i] = input[i] - 73;
        else if ((int) input[i] >= -36 && (int) input[i] <= -34)
            input[i] = input[i] + 5;
        else if ((int) input[i] == -6)
            input[i] = input[i] - 22;
        else if ((int) input[i] == -33)
            input[i] = input[i] + 6;
        else if ((int) input[i] == -4 || (int) input[i] == -3)
            input[i] = input[i] - 22;
        else if ((int) input[i] == -5)
            input[i] = input[i] - 19;
        else if ((int) input[i] == -2)
            input[i] = input[i] - 21;
        else if ((int) input[i] >= -63 && (int) input[i] <= -47)
            input[i] = input[i] - 65;
        else if ((int) input[i] >= -45 && (int) input[i] <= -39)
            input[i] = input[i] - 66;
        else if ((int) input[i] == -94)
            input[i] = input[i] + 72;
        else if ((int) input[i] >= -72 && (int) input[i] <= -70)
            input[i] = input[i] + 51;
        else if ((int) input[i] == -68)
            input[i] = input[i] + 50;
        else if ((int) input[i] == -66 || (int) input[i] == -65)
            input[i] = input[i] + 49;
    }
}

void Student::setCurrentSemester() {
    int y, m, d;

    time_t t = time(0);
    struct tm *now = localtime(&t);
    y = now->tm_year + 1900;
    m = now->tm_mon + 1;
    d = now->tm_mday;

    if (y > yearOfRestration)
        currentSemester = 2 * (y - yearOfRestration) + (m > 2 || (m == 2 && d >= 15)) + (m > 9) - 1;
    else
        currentSemester = (y == yearOfRestration && m > 9);
    //currentSemester += 0;
}

