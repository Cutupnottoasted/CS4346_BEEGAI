// CS4345_PROJECT 1 By BeegAI
// This project will diagnose what substance the patient has been poisioned by
// The AI will diagnose the poison by using backwards chaining
// and then will recommend the treatment through forward chaining
// the AI will be supplemented by a nurse who will enter the symptoms of the patient. 
// FUNCTIONS
//
//
// search_con (double var):
// finds the matching variable in conclusion list
// and the corresponding rule number ri
// calls rule_to_clause (int ri):
//
// rule_to_clause (int ri):
// Converts ri to clause variable list number, cvi using the formula:
// cvi = 4 * (ri / 10 - 1) + 1 *numbers are seq. 10,20,30..
// check if cvi in variable list is instantiated
// if not, then ask with update_VL(cvi)
//
// update_VL (int cvi):
// checks if the cvi is avaliable to update, then prompt 
// process(cvi) will define the value of the variable list
// if cvi is not in variable list, or is already instantiated
// then find a variable in the clause to instantiate
//
// validate_ri (int ri, string conclusion):
// check if the variables in the 'if' clause of the rules
// are satisfied. if yes then assign conclusion of rule (yes or no)
// to the string 'conclusion' otherwise no value is assigned.

#ifndef CS4345_PROJECT1_H
#define CS4345_PROJECT1_H
#include <iostream>

class Patient 
{
    public:
        // CONSTRUCTOR/DECONSTRUCTOR
        static const int DEFAULT_CAPACITY = 3;
        Patient(int initial_capacity = DEFAULT_CAPACITY);
        Patient(const Patient& src);
        ~Patient();
        int size() const; // returns number of symptoms
        bool isEmpty() const; // checks if there are symptoms
        bool contains(string symptom) // checks if the patient has a certain symptom
        void addSymptom(string symptom) // adds a Symptom into the symptom
        
    private:
        std::string* symptoms; // dynamic array containing variable list
        int capacity; // capacity of symptoms array
        int used; // current number of symptoms
        int current_index; // the current index of the symptoms array
        void resize(int new_capacity); 
}

#endif