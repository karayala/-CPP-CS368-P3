///////////////////////////////////////////////////////////////////////////////
//
// File:              SortedList.cpp
// Semester:          CS368 Fall 2015
//
// Author:            Kartik Ayalasomayajula; ayalasomayaj@wisc.edu
// CS Login:          ayalasomayajula
// Lecturer's Name:   Okan Akalin
//
////////////////////////////////////////////////////////////////////////////
/**
 * The goal of Class: To provide for framework of a list to hold all students
 * -> Sets up a linked list to access a list of Students in order by their ID.
 * -> Utilizes accessors and mutators to manipulate that list
 * -> Provides means to obtain holistic data about entire classes.
 */

#include "SortedList.h"
#include <iostream>
using namespace std;

// Constructs an empty list.
SortedList::SortedList(){
	head = NULL;
}

//Destructor. Frees up the lit of nodes.
SortedList::~SortedList(){
	cout << "      Destructor called for Sorted List"<<endl;
	if(head != NULL){freeList(head);}
}

//Copy COnstructor. Ensures that the list of nodes are copied
//When a copy constructor is invoked. Without this, the address of the new list simply
//points to the address of the copied list. With this implementation, a copy of the
//copied list gets made to the new list.
SortedList:: SortedList(const SortedList& Original){
	head = NULL;
	head = copyList(Original.head);
	cout << "      Copy Constructor called for Sorted List"<<endl;
}

//The Copy Assignment Opperation Operator defines a protocol to use
//in the event that a copy assignment needs to be used (x = y).
SortedList & SortedList::operator =(const SortedList & Original){
	cout << "      Copy assignment operator called for sorted list." << endl;
	if(this != &Original){
		freeList(head); //Frees the current heap
		head = NULL; 
		head = copyList(Original.head); //Copies over the nodes from the old to the enw.
	}
	return *this;
}

//CopyList copies all of the nodes from an old linked list to a new linked list.
SortedList::Listnode* SortedList::copyList(Listnode *L){
	Listnode *headP = new Listnode; 
	Listnode *box = NULL;
	Listnode *currList = L;

	if(currList != NULL){
		box = new Listnode; 
		box->student = new Student(*(L->student));
		box-> next = NULL;
		headP = box;
		while(currList->next != NULL){
			currList=currList->next;
			box = box->next = new Listnode();
			box->student = new Student(*(currList->student));
			box-> next = NULL;
		}
		
	}
	return headP;
}

//FreeList frees up the linked list nodes on the heap.
void SortedList::freeList (Listnode* L){
	if(L == NULL) return;
	Listnode *kill;
	while(L!= NULL){
		kill = L;
		L = L->next;
		delete kill;
	}

}

// If a student with the same ID is not already in the list, inserts
// the given student into the list in the appropriate place and returns
// true.  If there is already a student in the list with the same ID
// then the list is not changed and false is returned.
bool SortedList::insert(Student *s){
	int counter = -1;
	if(head == NULL){
		head = new Listnode;
		head->student = s;
		head ->next = NULL;
		return true;
	}else{
		if(find(s->getID()) != NULL){
			return false;
		}else{
			Listnode *box = new Listnode;
			box->student = s;
			Listnode *Parser = head;
			while(Parser->next!=NULL && Parser->next->student->getID() < box->student->getID()){
				counter++;
				Parser = Parser->next;
			}
			if(counter == -1 && Parser->student->getID() > box->student->getID()){
				box->next = Parser;
				head = box;
			}else{
				if(Parser->next == NULL){
					box->next = NULL;
				}else{
					box->next = Parser->next;
				}
				Parser->next = box;
			}
			return true;
		}
	}

}

// Searches the list for a student with the given student ID.  If the
// student is found, it is returned; if it is not found, NULL is returned.
Student* SortedList:: find(int studentID){
	Listnode *box = head;
	while(box !=NULL){
		if(box->student->getID() == studentID){
			return box->student;
		}
		box = box->next;
	}
	return NULL;
}


// Searches the list for a student with the given student ID.  If the
// student is found, the student is removed from the list and returned;
// if no student is found with the given ID, NULL is returned.
// Note that the Student is NOT deleted - it is returned - however,
// the removed list node should be deleted.
Student * SortedList::remove(int studentID){
	Listnode *box = head;
	int counter = -1;
	Student *holder = NULL;
	while(box!=NULL){
		counter++;
		holder = box->student;
		//***
		if(holder->getID() == studentID){
			if(counter ==0){
				head = head->next;
				return holder;
			}else if(counter > 0){
				box = head;
				for(int i = 0; i<counter-1; i++){
					box = box->next;
				}
				if(box->next->next == NULL){
					box->next= NULL;
				}else{
					box->next = box->next->next;
				}
				return holder;
			}
		}
		box = box->next;
	}
	return NULL;
}



// Prints out the list of students to standard output.  The students are
// printed in order of student ID (from smallest to largest), one per line
// If the student list is empty, output "Empty student list.\n"
void SortedList::print() const{
	int ctr = 0;
	Listnode *box = new Listnode;
	box = head; 
	while(box!= NULL){
		ctr++;
		if(box->student != NULL){box->student->print();}
		cout <<endl;
		box = box->next;
	}
	if(ctr == 0){
		cout <<"Empty student list." <<endl;
	}

}

// Returns the number of students who have taken the specified course in that semester
// and year.
int SortedList::getNStudents(int courseNumber, int inYear, Semester inSemester){
	int sCounter = 0; //Universal student counter.

	//1. Iterate through the list of Linked NOdes that hold each student.
	Listnode *box = head;
	while(box!=NULL){
		if(box->student->tookCourse(courseNumber, inYear, inSemester)) sCounter++;
		box= box->next;
	}
	return sCounter;
}

// Returns the list of (pointers to) students who have taken the specified course in that semester
// and year.  The students are returned in order of student ID (from smallest to largest)
// The list should end with a NULL pointer.
Student ** SortedList::getClassRoster(int courseNumber, int inYear, Semester inSemester){
	Listnode *box = head;
	int totalClasses = getNStudents(courseNumber, inYear, inSemester);
	Student **studentList = new  Student*[totalClasses +1];

	int i = -1;
	while(box!=NULL){
		if(box->student->tookCourse(courseNumber, inYear, inSemester)){
			i++;
			studentList[i] = box->student;
		}
		box = box->next;
	}
	studentList[totalClasses] = NULL;

	return studentList;
}


// Prints out the list of students who have taken the specified course in that semester
// and year to standard output.  The students are printed in order of student ID
// (from smallest to largest), one per line
// If there is not a student in the student list who took that course, output
// "Course " << courseNumber << " was not offered in " << (fall or spring) << " of " << inYear << "." << endl
void SortedList::printClassRoster(int courseNumber, int inYear, Semester inSemester){
	Student **studentList = getClassRoster(courseNumber, inYear, inSemester);
	int i;
	for(i = 0; studentList[i] != NULL; i++){
		int num = studentList[i]->getID();
		cout <<num<<endl;
	}
	if(i==0){
		if(inSemester == Fall){
			cout << "Course " << courseNumber << " was not offered in " << "Fall" << " of " << inYear << "." << endl;
		}else{
			cout << "Course " << courseNumber << " was not offered in " << "Spring" << " of " << inYear << "." << endl;
		}
	}
}

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
void SortedList::printClassmates(int * studentGroup, int nStudents){

	int idHolder[nStudents];
	int idCap = 0;
	bool taken = false;
	int pairs = 0;

	for(int i = 0; i<nStudents; i++){
		Student *temp = find(studentGroup[i]); //Finding if the given student ID exists.
		if(temp != NULL){ //IF the given studentID even exists:
			idHolder[idCap] = studentGroup[i];
			idCap++;
		}
	}
	int jBase = 1;
	for(int i = 0; i<idCap; i++){
		int ID1 = idHolder[i];
		Student *S1 = find(ID1);
		const CourseInfo ** CourseDB1 = S1->getCourses();

		for(int j = jBase; j<idCap; j++){

			int ID2 = idHolder[j];
			Student *S2 = find(ID2);
			for(int k = 0; CourseDB1[k] != NULL && !taken; k++){
				int cn = CourseDB1[k]->courseNumber;
				int y = CourseDB1[k]->year;
				Semester temp = CourseDB1[k]->cSemester;
				taken = S2->tookCourse(cn, y, temp);
			}

			if(taken){
				if(ID1<ID2){
					cout << ID1 << ", " << ID2 << endl;
				}else{
					cout << ID2 << ", " << ID1 << endl;
				}
				pairs++;
				taken = false;
			}
		}
		jBase++;
	}
	if(pairs == 0){
		cout << "Cannot find a valid pair."<<endl;
	}

}
