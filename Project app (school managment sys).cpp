#include "Course.h"
#include <fstream>

void createDefaultCourseFile(std::vector<Course>& courseVec) {
    std::ofstream newFile("courseInfo.txt");
    if (!newFile) {
        std::cout << "Error: Unable to create courseInfo.txt\n";
        return;
    }
    std::cout << "No course info found. Please enter details for a new course.\n";
    std::string courseID, faculty, rosterFile;
    int numStudents;

    std::cout << "Enter Course ID: ";
    std::getline(std::cin, courseID);
    std::cout << "Enter Faculty: ";
    std::getline(std::cin, faculty);
    std::cout << "Enter Number of Students: ";
    std::cin >> numStudents;
    std::cin.ignore();
    std::cout << "Enter Roster File Name: ";
    std::getline(std::cin, rosterFile);

    newFile << courseID << " " << faculty << " " << numStudents << " " << rosterFile << "\n";
    newFile.close();

    std::ofstream rosterOut(rosterFile);
    if (!rosterOut) {
        std::cout << "Error: Unable to create roster file " << rosterFile << "\n";
        return;
    }

    Course newCourse;
    newCourse.courseID = courseID;
    newCourse.faculty = faculty;
    newCourse.numStudents = numStudents;
    newCourse.rosterFile = rosterFile;

    std::cout << "Enter names of " << numStudents << " students:\n";
    for (int i = 0; i < numStudents; ++i) {
        std::string studentName;
        std::cout << "Student " << (i + 1) << ": ";
        std::getline(std::cin, studentName);
        newCourse.roster.push_back(studentName);
        rosterOut << studentName << "\n";
    }
    rosterOut.close();

    courseVec.push_back(newCourse);
    std::cout << "Course information and roster saved successfully.\n";
}

int main() {
    std::vector<Course> courseVec;
    std::vector<Course*> vacantCourseList;

    std::ifstream infile("courseInfo.txt");
    if (!infile || infile.peek() == std::ifstream::traits_type::eof()) {
        createDefaultCourseFile(courseVec);
    }
    else {
        std::string courseID, faculty, rosterFile;
        int numStudents;

        while (infile >> courseID >> faculty >> numStudents >> rosterFile) {
            Course newCourse;
            newCourse.courseID = courseID;
            newCourse.faculty = faculty;
            newCourse.numStudents = numStudents;
            newCourse.rosterFile = rosterFile;

            std::ifstream rosterFileIn(newCourse.rosterFile);
            if (rosterFileIn) {
                std::string student;
                while (std::getline(rosterFileIn, student)) {
                    newCourse.roster.push_back(student);
                }
                rosterFileIn.close();
            }
            courseVec.push_back(newCourse);
        }
        infile.close();
    }

    int choice;
    do {
        std::cout << "\nCourse Management System\n";
        std::cout << "------------------------\n";
        std::cout << "1. Cancel a course\n";
        std::cout << "2. Drop a student\n";
        std::cout << "3. Enroll a student\n";
        std::cout << "4. Add a course\n";
        std::cout << "5. Display information on all courses\n";
        std::cout << "6. List of courses taken by a student\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice (1-7): ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            std::string courseName;
            std::cout << "Enter the course name to cancel: ";
            std::getline(std::cin, courseName);
            cancelACourse(courseVec, courseName);
            break;
        }
        case 2: {
            std::string courseName, studentName;
            std::cout << "Enter the course name: ";
            std::getline(std::cin, courseName);
            std::cout << "Enter the student name: ";
            std::getline(std::cin, studentName);
            dropTheStudent(courseVec, studentName, courseName);
            break;
        }
        case 3: {
            std::string courseName, studentName;
            std::cout << "Enter the course name: ";
            std::getline(std::cin, courseName);
            std::cout << "Enter the student name: ";
            std::getline(std::cin, studentName);
            auto it = std::find_if(courseVec.begin(), courseVec.end(),
                [&courseName](const Course& c) { return c.getName() == courseName; });
            if (it != courseVec.end()) {
                enrollTheStudent(*it, studentName);
                std::cout << "Adding student...\n";
            }
            else {
                std::cout << "Error: Course not found.\n";
            }
            break;
        }
        case 4:
            createDefaultCourseFile(courseVec);
            break;
        case 5:
            displayCourseInfo(courseVec);
            break;
        case 6:
            std::cout << "Functionality to list courses taken by a student is not implemented yet.\n";
            break;
        case 7:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 7.\n";
        }
    } while (choice != 7);

    return 0;
}
