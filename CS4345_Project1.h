

#ifndef CS4345_PROJECT1_H
#define CS4345_PROJECT1_H
#include <iostream>
// global variables/arrays
// 0 = No 1 = Yes\
// order pair for conclusion nodes to know if looked at or not
string conclusionList[12][1] = {"Poison", "Qualify", "Poison", 
                                "Poison", "Poison", "Poison", 
                                "Poison", "Poison", "Poison", 
                                "Poison", "Poison", "Poison", }
string variableList[10][1] = { {"Sick", "0"}, {"Irregular Breathing", "0"} {"Sweating", "0"}, {"Cognitive Problems", "0"}, {"Eye Problems", "0"},
                                {"Muscle Pain", "0"}, {"Dizzyness", "0"}, {"Irritability", "0"}, {"Paranoia", "0"}, {"Sweating", "0"} }
string ifThenList[12][5] = { {"Sick", "0", "0", "0", "No"}, // 1
                            {"Sick", "0", "0", "0", "Yes"}, // 2
                            {"Irregular Breathing", "Sweating", "0", "0", "Asprin"}, // 3
                            {"Irregular Breathing", "Cognitive Problems", "Eye Problems", "0", "Benzodiazepines"}, // 4
                            {"Irregular Breathing", "Cognitive Problems", "Eye Problems", "0", "Alcohol"}, // 5
                            {"Irregular Breathing", "Cognitive Problems", "Muscle Pain", "Dizzy", "Iodine"}, // 6
                            {"Irregular Breathing", "Cognitive Problems", "Muscle Pain", "Dizzy", "Sitmulant"}, // 7
                            {"Irregular Breathing", "Muscle Pain", "Irritable", "0", "Lead"}, // 8
                            {"Irregular Breathing", "Muscle Pain", "Irritable", "0", "Carbon Monoxide"}, // 9
                            {"Irregular Breathing", "Muscle Pain", "Paranoia", "0", "Cannabis"}, // 10
                            {"Irregular Breathing", "Muscle Pain", "Eye Problems", "0", "Antidepressants"}, // 11
                            {"Irregular Breathing", "Muscle Pain", "Sweating", "0", "Paracetamol"} } // 12
string ifThenKey[12][4] = { { "0","","","" }, // 1 
                            { "1", "", "", ""}, // 2
                            { "1", "1", "", ""}, // 3
                            { "1", "1", "1", ""}, // 4
                            { "1", "1", "0", ""}, // 5
                            { "1", "0", "1", "1"}, // 6
                            { "1", "0", "1", "0"}, // 7
                            { "0", "1", "1", ""}, // 8  
                            { "0", "1", "0", ""}, // 9
                            { "0", "0", "1", ""}, // 10
                            { "0", "0", "1", ""}, // 11
                            { "0", "0", "1", ""} } // 12
string clauseVarList[50];
string derivedGlobalConclusionList[10];
/*
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
        bool contains(std::string symptom); // checks if the patient has a certain symptom
        void addSymptom(std::string symptom); // adds a Symptom into the symptom
        
    private:
        std::string* symptoms; // dynamic array containing variable list
        int capacity; // capacity of symptoms array
        int used; // current number of symptoms
        int current_index; // the current index of the symptoms array
        void resize(int new_capacity); 
};
*/

// prototypes
// search_con (string var):
// finds the matching variable in conclusion list
// and the corresponding rule number ri
// calls rule_to_clause (int ruleNum):
void search_con (double var);
//
// rule_to_clause (int ri):
// Converts ri to clause variable list number, cvi using the formula:
// cvi = 4 * (ri / 10 - 1) + 1 *numbers are seq. 10,20,30..
// check if cvi in variable list is instantiated
// if not, then ask with update_VL(cvi)
void rule_to_clause(int ri);
// process(int cvi);
void process(int cvi);
//
// update_VL (int cvi):
// checks if the cvi is avaliable to update, then prompt 
// process(cvi) will define the value of the variable list
// if cvi is not in variable list, or is already instantiated
// then find a variable in the clause to instantiate
void update_vl (int cvi);
// validate_ri (int ri, string conclusion):
// check if the variables in the 'if' clause of the rules
// are satisfied. if yes then assign conclusion of rule (yes or no)
// to the string 'conclusion' otherwise no value is assigned.
void validate_ri(int ri, std::string conclusion);

#endif
