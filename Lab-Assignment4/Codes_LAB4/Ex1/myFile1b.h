/*myFile1b.h, Ex1 a4 CSI2372A*/


#include <iostream>
using namespace std;

class Student {
	int numID;
	int nbCourses;
	int maxCourses;
	int* List_grades;
	Course** List_courses;
public:
	Student(int, int); 	//constructor
	~Student(); 		//destructor
	double average();
	int totalHours();
	bool addCourse(Course*, int);
};


Student:: Student(int nId, int numCourses){
	numID = nId;
	nbCourses = 0;
	maxCourses = numCourses;
	List_grades = new int[maxCourses];
	List_courses = new Course*[maxCourses]; //create array of pointers to course objects
};

Student:: ~Student(){
	delete[] List_grades;
	delete[] List_courses;
};

double Student:: average(){
	int sum = 0;
	for (int i = 0; i < nbCourses; i++){
		sum += List_grades[i];
	}
	double average = sum / nbCourses;
	return average;
};

int Student:: totalHours(){
	int sumHours = 0; 
	for (int i = 0; i < nbCourses; i++) sumHours += List_courses[i]->getHours();
	return sumHours;
};

bool Student:: addCourse(Course* newCourse, int a){ 

	if(nbCourses == maxCourses) return false;
	else{
		List_courses[nbCourses] = newCourse;
		List_grades[nbCourses] = a;
		nbCourses++;
	}
	return true; 
}