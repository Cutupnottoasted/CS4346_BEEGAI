// CS4345_PROJECT 1 By BeegAI
// This project will diagnose what substance the patient has been poisioned by
// The AI will diagnose the poison by using backwards chaining
// and then will recommend the treatment through forward chaining
// the AI will be supplemented by a nurse who will enter the symptoms of the patient. 
// FUNCTIONS
#include "CS4345_Project1.h"
#include <iostream>
using namespace std;
// prototypes




int main ()
{
	//example class
	//artificialInteligence* intel = new artificialInteligence();
    artificialIntelligence intel;
	int variable = 1;
	//intel->search_cvl(variable);
    // Instantiate the Clause Variable List
    // rule 1
    clauseVarList[0] = "Sick";
    clauseVarList[1] = "-1";
    clauseVarList[2] = "-1";
    clauseVarList[3] = "-1";
    // rule 2
    clauseVarList[4] = "Sick";
    clauseVarList[5] = "-1";
    clauseVarList[6] = "-1";
    clauseVarList[7] = "-1";
    // rule 3
    clauseVarList[8] = "Irregular Breathing";
    clauseVarList[9] = "-1";
    clauseVarList[10] = "-1";
    clauseVarList[11] = "-1";
    // rule 4
    clauseVarList[12] = "Irregular Breathing";
    clauseVarList[13] = "Cognitive Problems";
    clauseVarList[14] = "Eye Problems";
    clauseVarList[15] = "-1";
    // rule 5
    clauseVarList[16] = "Irregular Breathing";
    clauseVarList[17] = "Cognitive Problems";
    clauseVarList[18] = "Eye Problems";
    clauseVarList[19] = "-1";
    // rule 6
    clauseVarList[20] = "Irregular Breathing";
    clauseVarList[21] = "Cognitive Problems";
    clauseVarList[22] = "Muscle Pain";
    clauseVarList[23] = "-1";
    // rule 7
    clauseVarList[24] = "Irregular Breathing";
    clauseVarList[25] = "Cognitive Problems";
    clauseVarList[26] = "Muscle Pain";
    clauseVarList[27] = "-1";
    // rule 8
    clauseVarList[28] = "Irregular Breathing";
    clauseVarList[29] = "Muscle Pain";
    clauseVarList[30] = "-1";
    clauseVarList[31] = "-1";
    // rule 9
    clauseVarList[32] = "Irregular Breathing";
    clauseVarList[33] = "Muscle Pain";
    clauseVarList[34] = "-1";
    clauseVarList[35] = "-1";
    // rule 10
    clauseVarList[36] = "Irregular Breathing";
    clauseVarList[37] = "Muscle Pain";
    clauseVarList[38] = "-1";
    clauseVarList[39] = "-1";
    // rule 11
    clauseVarList[40] = "Irregular Breathing";
    clauseVarList[41] = "Muscle Pain";
    clauseVarList[42] = "-1";
    clauseVarList[43] = "-1";
    // rule 12
    clauseVarList[44] = "Irregular Breathing";
    clauseVarList[45] = "Muscle Pain";
    clauseVarList[46] = "-1";
    clauseVarList[47] = "-1";
    bool start = true;/*
	for (int i = 0; i < 12; i++)
        {
            current_conclusion = intel -> search_con ( variable );
            int ri = variable;
            int ci = intel -> rule_to_clause ( ri );
            intel -> update_VLBackwards ( ci );
            intel -> validate_RIBackwards ( ri, current_conclusion );
            variable++;
            cout << variable;
        }*/
    for (int i = 0; i < 12; i++)
    {
        current_conclusion = intel.search_con(variable);
        cout << "hello";
    }
    return 0;
	//delete intel;
}


void validate_RIBackwards ( int ri, string conclusion )
 {
    int rule_number_index = ri - 1;
    string truth_value;
    
    // if the global list is empty then skip straight to the variable list
    if ( derivedGlobalConclusionList.empty() )
    {
      cout << "Global list is empty" << endl;
      // iterate through all if clauses
      for ( int i = 0; i < 4; i++ )
      {
        
        // if -1 then no valid choices, which means test was passed
        if ( ifThenList[rule_number_index][i] == "-1")
        {
          // store the proper conclusion
          cout << "The test has passed" << endl;
          conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
          return; // exit function
        }
        // A condition is given
        else if ( ifThenList[rule_number_index][i] != "-1" )
        {
          
          cout << "A condition is given" << endl;
          conclusion = ifThenList[rule_number_index][i]; // reference the condition
          truth_value = ifThenKey[rule_number_index][i]; // reference the truth_value
          // iterate through entire variable list
          for ( int j = 0; j < VARIABLE_LIST_SIZE; j++ )
          {
            cout << "variable: " << j << endl;
            // if both the conclusion and the truth match
            if (conclusion == variableList[j][0] && truth_value == variableList[j][1])
            {
                cout << "A conclusion has been confirmed and pushed into vector" << endl;
              derivedGlobalConclusionList.push_back (conclusion);
              derivedGlobalKeyList.push_back (truth_value);
              break; // break to look through if clauses
            }
            // if conclusion match but truth does not
            if (conclusion == variableList[j][0] && truth_value != variableList[j][1])
            {
                cout << "The test has failed" << endl;
              conclusionList[rule_number_index][1] = "No";
              return; // leave the function
            }

          }

        }

      }
      // if end of loop is reached, then test was passed
      conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
      return; // exit function
    }
    // else if the global list is not empty
    else if ( !derivedGlobalConclusionList.empty() )
    {
      // iterate through all if clauses
      for ( int i = 0; i < 4; i++ )
      {
        // if -1 then no valid choices and test succesful
        if ( ifThenList[rule_number_index][i] == "-1" )
        {
          conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
          return;
        }
        // a condition is given
        if ( ifThenList[rule_number_index][i] != "-1")
        {
          conclusion = ifThenList[rule_number_index][i];
          truth_value = ifThenKey[rule_number_index][i];

          // global list is not empty; must check global list with conclusion and truth_value
          string* list_pointer;
          string* key_pointer;
          
          //derivedGlobalConclusionList.begin();
          //derivedGlobalKeyList.begin();
          // go through the globals first
          // push_back adds element at the end
          // -"conclusion"-> then -"conclusion"-"conclusion2"->
          //       1                    1             2
          for ( int offset = 0; offset < derivedGlobalKeyList.size(); offset++ )
          {
            // if conclusion variables and truth values match 
            if ( conclusion == derivedGlobalConclusionList.front() 
                && truth_value == derivedGlobalKeyList.front()  )
                break; // find another clause
            if ( conclusion == derivedGlobalConclusionList.front() 
                && truth_value != derivedGlobalKeyList.front()  )
            {
              conclusionList[rule_number_index][1] = "No";
              return; //exit the function
            }

          }
          // at end of derrivedGlobal for loop then check variable list
          for ( int j = 0; j < VARIABLE_LIST_SIZE; j++ )
          {
            // if both the conclusion and the truth match
            if (conclusion == variableList[j][0] && truth_value == variableList[j][1])
            {
              derivedGlobalConclusionList.push_back (conclusion);
              derivedGlobalKeyList.push_back (truth_value);
              break; // break to look through if clauses
            }
            // if conclusion match but truth does not
            if (conclusion == variableList[j][0] && truth_value != variableList[j][1])
            {
              conclusionList[rule_number_index][1] = "No";
              return; // leave the function
            }

          }

        }

      }
      // if end of loop is reached then test succesful
      conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
      return; // exit function 
    }