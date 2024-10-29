#include <cstdlib> 
using namespace std;

class SetInt
{
public:
	SetInt() : elem(NULL), size(0) {};
	SetInt(int[], int);
	~SetInt();
	SetInt(const SetInt&);  // copy constructor
	void add(int);
	void remove(int);
	bool contains(int);
	int nbElem();
	int* tabElem();
private:
	int* elem;
	int size;
	bool containsIn(int n, int&);
};


SetInt:: SetInt(int* newArray, int newArraySize){
	elem = new int[size = newArraySize];
	for (int i = 0; i < size; i++){
		elem[i] = newArray[i];
	}
}

SetInt:: SetInt(const SetInt& newSetInt){ 
	elem = new int[size = newSetInt.size];
	for(int i = 0; i < size; i++){
		elem[i] = newSetInt.elem[i];
	}
}
SetInt::~SetInt(){ 
	delete[] elem;
}

bool SetInt::contains(int target){ 
	for(int i = 0; i < size; i++){
		if(elem[i] == target){
			return true;
		}
	}
	return false;
}

void SetInt:: add(int target){ 
	if(!contains(target)){ //add if the target is not already in the set
		int* newElem = new int[size+1]; //allocate more memory to array. 
		for(int i = 0; i< size; i++){ //copy olf values
			newElem[i] = elem[i];
		}
		newElem[size] = target; //add new element
		delete[]elem; //delete old
		elem = newElem; //replace
		size++; //inc size
	}
}

int SetInt:: nbElem(){ //nbElem func
	return size;
}

int* SetInt:: tabElem(){ //tabElem func
	if(nbElem() == 0){
		return NULL;
	}
	else{
		int* arr = new int[nbElem()];
		for(int i = 0; i < nbElem(); i++){
			arr[i] = elem[i];
		}
		return arr;
	}
}

void SetInt:: remove(int target){
	int index = -1;
	if(contains(target)){
		//get index of target element 
		for(int i = 0; i < size; i++){
			if(elem[i] == target){
				index = i;
				break;
			}
		}
	}
	if(index != -1){ //this means target found at index = i
		for(int i = index; i < size - 1; i++){
			elem[i] = elem[i+1]; //shift items from left to delete target.
		}
		size--;
	}
}



