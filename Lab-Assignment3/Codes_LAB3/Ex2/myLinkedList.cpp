/*Ex2 - a3 CSI2372A*/

#include "myLinkedList.h"

int main()
{
	//initialize missing variables................
	Evaluation* first = nullptr; //head
	int number = 0; //num of elements in linked lsit
	int choice;
	do
	{
		cout << endl << endl << "1) Display  of the complete linked list.\n";
		cout << "2) Insert an element\n";
		cout << "3) Remove an element.\n";
		cout << "4) Calculation of the class average.\n";
		cout << "5) Exit the program.\n" << endl << endl;
		cout << "Your choice ??:";
		cin >> choice;

		switch (choice)
		{
		case 1: display(first);
			break;
		case 2: first = add(first, number);
			break;
		case 3: first = remove(first, number);
			break;
		case 4: average(first, number);
			break;
		case 5: exit(0);
		default:
			break;
		}
	} while (1);
	return 0;
}



/*
*add() Function*
**/
Evaluation* add(Evaluation* p, int& number)
{
	//YOUR CODE COMES HERE
	//create a new evaluation pointer
	Evaluation* newEvaluation = new Evaluation;
	int desiredPosition;
	cout << "After which element do you want to insert? (0 for start): ";
	cin >> desiredPosition; 
	if(desiredPosition < 0 || desiredPosition > number){ //check if insert is out of bounds
		cout << "You have entered an invalid position :("  << endl;
		//delete the created new evaluation
		delete newEvaluation;
		return p; //return control to main with p as is. 
	}
	cout << "Entering the item into the chained list" << endl;
	cout << endl;
	cout << "Ender the student: ";
	cin.ignore();
	cin.getline(newEvaluation->student, capacity);
	cout << "Enter the grade: ";
	cin >> newEvaluation->grade;

	//insert
	if(desiredPosition == 0){  //at begining
		newEvaluation->next = p;
		number++;
		return newEvaluation;
	}
	else{
		Evaluation* temp = p;
		for(int offset = 0; offset < desiredPosition - 1 ; offset++){
			temp = temp->next; //move untill we reach the desired insertion point
		}
		newEvaluation->next = temp->next;
		temp->next = newEvaluation;
		number++;
		return p;
	}
}


/**
*remove() Function*
**/

Evaluation* remove(Evaluation* p, int& number)
{
	//YOUR CODE COMES HERE
	int userIndex;
	std::cout << "what is the number of the element to delete?: ";
	std::cin >> userIndex;

	int removalIndex = userIndex - 1;

	if(number == 0){ //empty list... 
		std::cout << "The list is empty, nothing to remove." << endl;
		return p;
	}

	if(userIndex < 0 || userIndex > number){ //validation
		std::cout << "Removal index is out of valid range." << endl;
		return p;
	}
	
	//removing the first element (p) 
	if(removalIndex == 0){
		Evaluation* deleteEntity = p;
		p = p->next;
		delete deleteEntity;
		number--;
		return p;
	}
	Evaluation* temp = p; 
	for(int i = 0; i < removalIndex - 1; i++){ //move to appropriate index
		//to be deleted - 1 (right before deletion)
		temp = temp->next;
	}
	//removal
	Evaluation* deleteEntity = temp->next;
	temp->next = deleteEntity->next;
	delete deleteEntity;
	number--;
	return p;

}



/**
*display() Function *
**/
void display(Evaluation* p) {
    if (!p) {
        std::cout << "The list is empty.\n";
        return;
    }

    Evaluation* temp = p;
    while (temp != nullptr) {
		std:: cout << endl;
        std::cout << "Student: " << temp->student << "\n";
        std::cout << "The grade is: " << temp->grade << endl;
        temp = temp->next; //Move 2 next node
    }
}



/**
*average() Function *
***/
int average(Evaluation* p, int const& nbre)
{
	Evaluation* temp =p; //will use this to cycle throught the linked list. 
	int gradeTotalSum = 0;
	//valdiation
	if (nbre == 0){
		std::cout << "There are no students yet." << endl;
		return 0;
	}
	while(temp != nullptr) 
	{
		gradeTotalSum += temp->grade;
		temp = temp->next;
	}
	std::cout << endl; //buffer 1 line. 
	std::cout << "The average fo the class is: " << (gradeTotalSum / nbre) << endl;
	return 1;
	
}






