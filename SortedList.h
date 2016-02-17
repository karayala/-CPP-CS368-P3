#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include "Student.h"

/*
 * SortedList class
 *
 * A SortedList is an ordered collection of Students.  The Students are ordered
 * from lowest numbered student ID to highest numbered student ID.
 */
class SortedList {

  public:
    
    SortedList();
    // Constructs an empty list.

    ~SortedList(); //Destructor

    SortedList(const SortedList& Original); //Copy Constructor

    SortedList & operator=(const SortedList &L); //Assignment Copy Operator

    bool insert(Student *s);
    // If a student with the same ID is not already in the list, inserts 
    // the given student into the list in the appropriate place and returns
    // true.  If there is already a student in the list with the same ID
    // then the list is not changed and false is returned.

    Student * find(int studentID);
    // Searches the list for a student with the given student ID.  If the
    // student is found, it is returned; if it is not found, NULL is returned.

    Student * remove(int studentID);
    // Searches the list for a student with the given student ID.  If the 
    // student is found, the student is removed from the list and returned;
    // if no student is found with the given ID, NULL is returned.
    // Note that the Student is NOT deleted - it is returned - however,
    // the removed list node should be deleted.

    int getNStudents(int courseNumber, int inYear, Semester inSemester);
    // Returns the number of students who have taken the specified course in that semester 
    // and year. 

    Student ** getClassRoster(int courseNumber, int inYear, Semester inSemester);
    // Returns the list of (pointers to) students who have taken the specified course in that semester 
    // and year.  The students are returned in order of student ID (from smallest to largest)
    // The list should end with a NULL pointer.

    void printClassRoster(int courseNumber, int inYear, Semester inSemester) ;
    // Prints out the list of students who have taken the specified course in that semester 
    // and year to standard output.  The students are printed in order of student ID 
    // (from smallest to largest), one per line
    // If there is not a student in the student list who took that course, output
    // "Course " << courseNumber << " was not offered in " << (fall or spring) << " of " << inYear << "." << endl

    void printClassmates(int * studentGroup, int nStudents);
    // Prints out the list of ID pairs of students from studentGroup who have taken a course
    // together to standard output.  Every valid student ID pair is printed such that the lower
    // student ID comes first, the IDs are separated by a comma, and every pair is displayed once.
    // In the output, pairs should be ordered lexicographically (with respect to the ID of the first
    // student in the pair and then the second student. 
    // nStudents gives the number of students in studentGroup variable. 
    // If studentGroup contains invalid IDs, you should simply ignore them. If there is no 
    // such pair, output "Cannot find a valid pair.\n" 
    // Note that the list of IDs in studentGroup may not be sorted.
    // eg. if the valid pairs are (111, 123), (223, 111), (223, 221), you should output
    // 111, 123
    // 111, 223
    // 221, 223


    void print() const;
    // Prints out the list of students to standard output.  The students are
    // printed in order of student ID (from smallest to largest), one per line
    // If the student list is empty, output "Empty student list.\n"


  private:

    // Since Listnodes will only be used within the SortedList class,
    // we make it private.
    struct Listnode {    
        Student *student;
        Listnode *next;
    };

    Listnode *head; // pointer to first node in the list
    static Listnode *copyList (Listnode *L);
    static void freeList (Listnode* box);
};





#endif
