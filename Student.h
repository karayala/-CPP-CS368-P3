#ifndef STUDENT_H
#define STUDENT_H

enum Semester {Spring, Fall};

/*
 * Course Information structure
 *
 * Stores the grade information for every course student took
 */
struct CourseInfo {
    int courseNumber;
    int credits;
    int year;
    char studentGrade;
    Semester cSemester;     
};

/*
 * Student class
 *
 * A Student object contains a student ID, the number of credits, and an
 * overall GPA.
 */
class Student {
  public:
    
    Student();
    // Constructs a default student with an ID of 0, 0 credits, and 0.0 GPA.

    Student(int ID);
    // Constructs a student with the given ID, 0 credits, and 0.0 GPA.

    ~Student(); //Destructor

    Student & operator=(const Student &Original); //Copy Assignment Operator
 
    Student(const Student& original); //Copy Constructor     

    Student(int ID, CourseInfo ** courses);
    // Constructs a student with the given ID and the list of taken courses.
    // You can assume that courses pointer list will end with a NULL pointer.

    // Accessors
    int getID() const;       // returns the student ID
    int getCredits() const;  // returns the number of credits
    double getGPA() const;   // returns the GPA
    CourseInfo const ** getCourses() const;
    // creates a list of pointers to the CourseInfo structures in the student record
    // returned list should end with a NULL pointer

    // Other methods

    void update(int courseNumber, int credits, int year, Semester cSemester, char grade);
    // Update the student record by adding a new course. You should add a new CourseInfo
    // instance to takenCourses member.

    void print() const;  
    // Prints out the student to standard output in the format:
    //   ID,credits,GPA
    // Note: the end-of-line is NOT printed after the student information 

    bool tookCourse(int courseNumber, int year, Semester cSemester); 
    // returns true if student took the specified course 

  private:
    int studentID;
    CourseInfo coursesTaken[100]; int nCoursesTaken;
    // You can assume that none of the students will have more than 100 courses in their record.
};

#endif
