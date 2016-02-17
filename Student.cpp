///////////////////////////////////////////////////////////////////////////////
//
// File:              Student.cpp
// Semester:          CS368 Fall 2015
//
// Author:            Kartik Ayalasomayajula; ayalasomayaj@wisc.edu
// CS Login:          ayalasomayajula
// Lecturer's Name:   Okan Akalin
//
////////////////////////////////////////////////////////////////////////////
/**
 * The goal of Class: To support the operations on the Student-end of the calculations.
 * -> Sets up the Student framework and provides resources for a specific student.
 * -> Utilizes accessors and mutators along with a list of classes a student can take.
 */

#include "Student.h"
#include <stddef.h>
#include <iostream>
using namespace std;

// Constructs a default student with an ID of 0, 0 credits, and 0.0 GPA.
Student::Student() {
	studentID = 0;
	nCoursesTaken = 0;
}

//The Student Destructor destroys the entire student database.
Student:: ~Student(){
	cout << "      Student Destructor called for:: ID: "<< studentID <<endl;
}

// This is the copy Constructor. It specifies a custom-made protocol to follow in the event that a copy constructor needs to be used.
Student:: Student(const Student& Original){
	cout << "      Student.cpp Copy Constructor Called!"<<endl;
	studentID = Original.getID();
	nCoursesTaken = 0;

	const CourseInfo ** CourseDB1 = Original.getCourses();

	for(int i = 0; CourseDB1[i]!= NULL; i++){
		update(CourseDB1[i]->courseNumber, CourseDB1[i]->credits, CourseDB1[i]->year, CourseDB1[i]->cSemester, CourseDB1[i]->studentGrade);
	}
}

//The Assignment Opperation Operator follows a protocol (custom-made) to follow in the event that an assignment protocol operator needs to be used.
Student& Student::operator =(const Student &Original){

	if(this != &Original){
		cout << "      Copy Assignment Opperator Called!"<<endl;
		studentID = Original.getID();
		nCoursesTaken = 0;

		const CourseInfo ** CourseDB1 = Original.getCourses();

		for(int i = 0; CourseDB1[i]!= NULL; i++){
			update(CourseDB1[i]->courseNumber, CourseDB1[i]->credits, CourseDB1[i]->year, CourseDB1[i]->cSemester, CourseDB1[i]->studentGrade);
		}
	}
	return *this;
}

// Constructs a student with the given ID, 0 credits, and 0.0 GPA.
Student::Student(int ID){
	studentID = ID;
	nCoursesTaken = 0;
}

// Constructs a student with the given ID and the list of taken courses.
// You can assume that courses pointer list will end with a NULL pointer.
Student::Student(int ID, CourseInfo ** courses){
	studentID = ID;
	nCoursesTaken = 0;
	int i;
	for(i = 0; courses[i] != NULL; i++){
		coursesTaken[i] = *courses[0];
	}
	nCoursesTaken = i;
}

// returns the student ID
int Student::getID() const{
	return studentID;
}

// returns the GPA
double Student::getGPA() const{
	//GPA Calculator  Implementation:
		double rawScore = 0.0;
		int totalCredits = 0;
	for(int i = 0; i<nCoursesTaken; i++){
		//Getting current GPA:
		char currGrade = coursesTaken[i].studentGrade;
		double cgpa = 0.0;
		switch(currGrade){
			case 'A':
				cgpa = 4.0;
				break;
			case 'a':
				cgpa = 4.0;
				break;
			case 'B':
				cgpa = 3.0;
				break;
			case 'b':
				cgpa = 3.0;
				break;
			case 'C':
				cgpa = 2.0;
				break;
			case 'c':
				cgpa = 2.0;
				break;
			case 'D':
				cgpa = 1.0;
				break;
			case 'd':
				cgpa = 1.0;
				break;
			case 'F':
				cgpa = 0.0;
				break;
			case 'f':
				cgpa = 0.0;
				break;
		}
		totalCredits = totalCredits+ coursesTaken[i].credits;
		rawScore = rawScore + (cgpa * coursesTaken[i].credits);
	}

	if(totalCredits == 0.0){
		return 0;
	}
	return (rawScore/totalCredits);
}

// returns the number of credits
int Student::getCredits() const{
	int creditCount = 0;
	int i;
	for(i = 0; i<nCoursesTaken; i++){
		creditCount = creditCount + coursesTaken[i].credits;
	}
	return creditCount;
}

// creates a list of pointers to the CourseInfo structures in the student record
// returned list should end with a NULL pointer
const CourseInfo ** Student::getCourses() const{
	if(nCoursesTaken == 0) return NULL;

    const CourseInfo **infoStructAddr = new const CourseInfo*[nCoursesTaken+1];
    for(int i = 0; i < nCoursesTaken; i++) {
        infoStructAddr[i] = &coursesTaken[i];
    }
    infoStructAddr[nCoursesTaken] = NULL;

    return  infoStructAddr;
}

// Update the student record by adding a new course. You should add a new CourseInfo
// instance to takenCourses member.
void Student::update(int courseNumber, int credits, int year, Semester cSemester, char grade){
	if(!tookCourse(courseNumber, year, cSemester)){
		CourseInfo *temp = new CourseInfo;
		temp->courseNumber = courseNumber;
		temp->credits = credits;
		temp->year = year;
		temp->cSemester = cSemester;
		temp->studentGrade = grade;
		if(nCoursesTaken < 100){
			coursesTaken[nCoursesTaken] = *temp;
			nCoursesTaken++;
		}
	}
}

// returns true if student took the specified course
bool Student::tookCourse(int courseNumber, int year, Semester cSemester){
	for(int i = 0; i< nCoursesTaken; i++){
		if(coursesTaken[i].cSemester == cSemester && coursesTaken[i].year == year && coursesTaken[i].courseNumber == courseNumber){
			return true;
		}
	}
	return false;
}


// Prints out the student to standard output in the format:
//   ID,credits,GPA
// Note: the end-of-line is NOT printed after the student information
void Student::print() const{
	double GPA = getGPA();
	cout<<studentID<<","<< getCredits() << "," << GPA;

}
