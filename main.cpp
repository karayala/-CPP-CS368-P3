///////////////////////////////////////////////////////////////////////////////
//
// File:              main.cpp
// Semester:          CS368 Fall 2015
//
// Author:            Kartik Ayalasomayajula; ayalasomayaj@wisc.edu
// CS Login:          ayalasomayajula
// Lecturer's Name:   Okan Akalin
//
////////////////////////////////////////////////////////////////////////////
/**
 * Implement a test to test if CopyConstructors, Destructors, and copy Assignment Operators work in Student Database implementation.



//DEMONSTRATING THE DIFFERENCE! 
//The use of the destructor and better memory-allocation technuiques in this project primarily helped out the needs of SortedList.cpp
//This is because Sorted List has a list of nodes. This list of nodes needs to be effectively freed/deleted or else it would show up
//as an indirectly lost. Now, in doing the testing for this project, I did see that the areas of the heap that were indirectly lost
//were higher for the old implementation than the new implementation. This is understandable, as the indirect memory leaks are higher in the old implementation
//due to the list of nodes not being properly deactivated. 


 */
#include "SortedList.h"
#include "Student.h"
#include <iostream>
using namespace std;

int main() {
	cout<< "Purpose: Test Destructor, Copy Constructor, and Copy Assignment operations"<<endl;
	cout<< "CREATING OBJECTS\n"<<endl;
	Student ted(1);
	cout<< "   STUDENT TED CREATED WITH ID 1 "<<endl;
	ted.update(111, 3, 2015, Fall, 'A');
	cout<< "   STUDENT TED UPDATED WITH: {{ted.update(111, 3, 2015, Fall, 'A');}}"<<endl;
	Student Ryan(5);
	cout<< "   STUDENT RYAN CREATED WITH ID 5 "<<endl;
	Ryan.update(555, 3, 2014, Spring, 'B');
	cout<< "   STUDENT RYAN UPDATED WITH: {{Ryan.update(555, 3, 2014, Spring, 'B');}}"<<endl;
	Student Kartik(7);
	cout<< "   STUDENT KARTIK CREATED WITH ID 7 "<<endl;
	Kartik.update(777, 3, 2013, Fall, 'C');
	cout<< "   STUDENT KARTIK UPDATED WITH: {{Kartik.update(777, 3, 2013, Fall, 'C');}}"<<endl;
	Student Brian(4);
	cout<< "   STUDENT BRIAN CREATED WITH ID 4 "<<endl;
	Brian.update(444, 3, 2012, Fall, 'D');
	cout<< "   STUDENT BRIAN UPDATED WITH: {{Brian.update(444, 3, 2012, Fall, 'D');}}"<<endl;
	SortedList random;
	cout<< "   SORTEDLIST RANDOM CREATED"<<endl;
	SortedList random2;
	cout<< "   SORTEDLIST RANDOM2 CREATED"<<endl;
	random.insert(&ted);
	cout<< "   TED INSERTED INTO RANDOM"<<endl;
	random.insert(&Kartik);
	cout<< "   KARTIK INSERTED INTO RANDOM"<<endl;
	random.insert(&Brian);
	cout<< "   BRIAN INSERTED INTO RANDOM"<<endl;
	random.insert(&Ryan);
	cout<< "   RYAN INSERTED INTO RANDOM"<<endl;

	cout<< "\n\n\nSTARTING COPY CONSTRUCTOR TEST\n\n\n   Testing Students: {{Student kieth = ted;}}"<<endl;
	Student kieth = ted;
	cout<< "      Checking contents of their data:::"<<endl;
	const CourseInfo ** kiethDB = kieth.getCourses();
	const CourseInfo ** tedDB = ted.getCourses();
	int deepCheck = 1;
	for(int i = 0; kiethDB[i]!= NULL; i++){
		if(kiethDB[i]->courseNumber != tedDB[i]->courseNumber || kiethDB[i]->credits != tedDB[i]->credits || kiethDB[i]->year != tedDB[i]->year || kiethDB[i]->cSemester != tedDB[i]->cSemester || kiethDB[i]->studentGrade != tedDB[i]->studentGrade){
			deepCheck = 0;
		}
		if(kiethDB[i+1] == NULL && tedDB[i+1] != NULL){
			deepCheck = 0;
			break;
		}
	}
	if(kieth.getID() == ted.getID() && kieth.getCredits() == ted.getCredits() && kieth.getGPA() == ted.getGPA() && deepCheck==1){
		cout<< "   Student Copy Constructor Test Success!" <<endl;
	}else{
		cout<< "   Student Copy Constructor Test Failed!"<<endl;
	}
	cout<< "   Printing Summary of Kieth's Data:\n      ";
	kieth.print();
	cout<< "\n   Printing Summary of Ted's Data:\n      ";
	ted.print();
	cout<< "\n\n"<<endl;
	cout<< "   Testing SortedList: {{SortedList blank = random;}}"<<endl;
	SortedList blank = random;
	cout<< "      Printing Summary for SortedList random\n__________________________________"<<endl;
	random.print();
	cout << "      Printing Ssmmary for SortedList blank\n__________________________________"<<endl;
	blank.print();
	cout<< "SortedList Test is a success if blank has same data as random. Otherwise failed." <<endl;
	cout<< "COPY CONSTRUCTOR TEST COMPLETE\n\n\nCOPY ASSIGNMENT OPERATOR TEST BEGIN\n\n\n" <<endl;

	cout<< "   Testing Students: {{Kartik = Brian}}"<<endl;
	Kartik = Brian;
	cout<< "      Checking contents of their data:::"<<endl;
	deepCheck = 1;
	kiethDB = Kartik.getCourses();
	tedDB = Brian.getCourses();
	for(int i = 0; kiethDB[i]!= NULL; i++){
		if(kiethDB[i]->courseNumber != tedDB[i]->courseNumber || kiethDB[i]->credits != tedDB[i]->credits || kiethDB[i]->year != tedDB[i]->year || kiethDB[i]->cSemester != tedDB[i]->cSemester || kiethDB[i]->studentGrade != tedDB[i]->studentGrade){
			deepCheck = 0;
		}
		if(kiethDB[i+1] == NULL && tedDB[i+1] != NULL){
			deepCheck = 0;
			break;
		}
	}
	if(Kartik.getID() == Brian.getID() && Kartik.getCredits() == Brian.getCredits() && Kartik.getGPA() == Brian.getGPA() && deepCheck==1){
		cout<< "   Student Copy Constructor Test Success!" <<endl;
	}else{
		cout<< "   Student Copy Constructor Test Failed!"<<endl;
	}
	cout<< "   Printing Summary of Kartik's Data:\n      ";
	Kartik.print();
	cout<< "\n   Printing Summary of Brian's Data:\n      ";
	Brian.print();
	cout<< "\n\n"<<endl;
	cout<< "   Testing SortedList: {{random2 = random;}}"<<endl;
	random2 = random;
	cout<< "      Printing Summary for SortedList random\n__________________________________"<<endl;
	random.print();
	cout << "      Printing Summary for SortedList random2\n__________________________________"<<endl;
	random2.print();
	cout<< "SortedListis a success if random2 has same data as random. Otherwise failed." <<endl;
	cout<< "ASSIGNMENT OPERATOR TEST COMPLETE\n\n\nDESTRUCTOR TEST BEGIN\n\n\n" <<endl;
	cout<< "   This test will allocate 2 students and 2 SortedList objects inside of an arbitrary if block. Upon closing of the if block, both should be destructed. After the program closes, all objects should be destructed. A total of 6 Student destructors and 4 SortedList destructers should be called" <<endl;

	int t = 7;
	while(t == 7){
		Student kelly(6);
		SortedList best;
		t = 9;
	}
	
	//delete ted; 
	return 0;
}
