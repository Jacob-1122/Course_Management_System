#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

struct Course {
    std::string courseID;
    std::string faculty;
    std::string courseInstructor;
    int numStudents;
    std::vector<std::string> roster;
    std::string rosterFile;

    Course();

    std::string getName() const;
    void setName(const std::string& name);
    std::string getFaculty() const;
    void setFaculty(const std::string& fac);
    std::string getInstructor() const;
    void setInstructor(const std::string& instructor);
    const std::vector<std::string>& getRoster() const;
    void setRoster(const std::vector<std::string>& names);
    void clearRoster();
    bool addStudent(const std::string& studentName);
    bool removeStudent(const std::string& studentName);
};

void displayCourseInfo(const std::vector<Course>& courses);
Course* cancelACourse(std::vector<Course>& courses, const std::string& courseName);
void dropTheStudent(std::vector<Course>& courses, const std::string& studentName, const std::string& courseName);
bool enrollTheStudent(Course& course, const std::string& studentName);
std::vector<std::string> getCourseList(const std::vector<Course>& courses, const std::string& studentName);
void addCourse(std::vector<Course>& courses);
void clearInputBuffer();

#endif
