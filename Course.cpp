#include "Course.h"

Course::Course() : numStudents(0) {}

std::string Course::getName() const {
    return courseID;
}

void Course::setName(const std::string& name) {
    courseID = name;
}

std::string Course::getFaculty() const {
    return faculty;
}

void Course::setFaculty(const std::string& fac) {
    faculty = fac;
}

std::string Course::getInstructor() const {
    return courseInstructor;
}

void Course::setInstructor(const std::string& instructor) {
    courseInstructor = instructor;
}

const std::vector<std::string>& Course::getRoster() const {
    return roster;
}

void Course::setRoster(const std::vector<std::string>& names) {
    roster = names;
    numStudents = names.size();
}

void Course::clearRoster() {
    roster.clear();
    numStudents = 0;
}

bool Course::addStudent(const std::string& studentName) {
    if (std::find(roster.begin(), roster.end(), studentName) != roster.end()) {
        return false;
    }
    roster.push_back(studentName);
    numStudents++;
    return true;
}

bool Course::removeStudent(const std::string& studentName) {
    auto it = std::find(roster.begin(), roster.end(), studentName);
    if (it != roster.end()) {
        roster.erase(it);
        numStudents--;
        return true;
    }
    return false;
}

void displayCourseInfo(const std::vector<Course>& courses) {
    if (courses.empty()) {
        std::cout << "No courses available.\n";
        return;
    }
    for (const auto& course : courses) {
        std::cout << "\nCourse Information:\n";
        std::cout << "----------------\n";
        std::cout << "Course ID: " << course.courseID << "\n";
        std::cout << "Faculty: " << course.faculty << "\n";
        std::cout << "Number of Students: " << course.numStudents << "\n";
        std::cout << "Students:\n";
        if (course.roster.empty()) {
            std::cout << "No students enrolled\n";
        }
        else {
            for (const auto& student : course.roster) {
                std::cout << "- " << student << "\n";
            }
        }
        std::cout << "----------------\n";
    }
}

Course* cancelACourse(std::vector<Course>& courses, const std::string& courseName) {
    auto it = std::find_if(courses.begin(), courses.end(),
        [&courseName](const Course& c) { return c.getName() == courseName; });
    if (it != courses.end()) {
        it->clearRoster();
        return &(*it);
    }
    std::cout << "Error: Course " << courseName << " not found.\n";
    return nullptr;
}

void dropTheStudent(std::vector<Course>& courses, const std::string& studentName, const std::string& courseName) {
    auto it = std::find_if(courses.begin(), courses.end(),
        [&courseName](const Course& c) { return c.getName() == courseName; });
    if (it != courses.end()) {
        if (it->removeStudent(studentName)) {
            std::cout << "Student " << studentName << " has been dropped from " << courseName << ".\n";
        }
        else {
            std::cout << "Error: Student " << studentName << " not found in " << courseName << ".\n";
        }
    }
    else {
        std::cout << "Error: Course " << courseName << " not found.\n";
    }
}

bool enrollTheStudent(Course& course, const std::string& studentName) {
    if (course.addStudent(studentName)) {
        return true;
    }
    std::cout << "Error: Student " << studentName << " is already enrolled in this course.\n";
    return false;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
