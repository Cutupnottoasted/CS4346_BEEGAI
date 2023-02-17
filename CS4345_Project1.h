#ifndef CS4345_PROJECT1_H
#define CS4345_PROJECT1_H
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

static const int RULE_SIZE = 12; // current number of rules; conclusionList, ifThenList, and ifThenKey share this size
static const int VARIABLE_LIST_SIZE = 9; // current number of symptoms
static const int IF_THEN_SIZE = 5; // total size of all if/then clause variables

vector<string> derivedGlobalConclusionList; // vector implemented as a queue; contains validated symptoms
string clauseVarList[50]; // the clause variable list

// The conclusionList[][]: Contains all the conclusion variables.
// The order pair represents the rules "then" clause and it's associated value
// eg. [0][0], [0][1] == "Poison", "No" or [2][0], [2][1] == "Poison", "Asprin"
std::string conclusionList[12][2] = { {"Poison", "-1"}, {"Qualify", "-1"}, {"Poison", "-1"},
                                        {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"},
                                        {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"} };

// The variableList[][]: Contains all the symptoms and their truth value
// The order pair represents the symptom and if it is present
// -1 = uninstantiated, 0 = false, 1 = true
std::string variableList[9][2] = { {"Sick", "-1"}, {"Irregular Breathing", "-1"}, {"Cognitive Problems", "-1"}, {"Eye Problems", "-1"},
                                {"Muscle Pain", "-1"}, {"Dizzyness", "-1"}, {"Irritability", "-1"}, {"Paranoia", "-1"}, {"Sweating", "-1"} };

// The ifThenList[][]: Represents the rule list.
// Contains up to 4 symptoms per rule and conclusion assignment at the end. eg [2][4] = "Asprin"
// The conclusion assignment is only assigned when the ifThenKey's requirements are satsified  
// Otherwise the conclusion is assigned "No"                                 
std::string ifThenList[12][5] = { {"Sick", "-1", "-1", "-1", "No"}, // if not sick, then poison = no
                                    {"Sick", "-1", "-1", "-1", "Yes"}, // if sick, then qualify = yes
                                    {"Irregular Breathing", "Sweating", "-1", "-1", "Asprin"}, 
                                    {"Irregular Breathing", "Cognitive Problems", "Eye Problems", "-1", "Benzodiazepines"}, 
                                    {"Irregular Breathing", "Cognitive Problems", "Eye Problems", "-1", "Alcohol"}, 
                                    {"Irregular Breathing", "Cognitive Problems", "Muscle Pain", "Dizzy", "Iodine"}, 
                                    {"Irregular Breathing", "Cognitive Problems", "Muscle Pain", "Dizzy", "Sitmulant"}, 
                                    {"Irregular Breathing", "Muscle Pain", "Irritable", "-1", "Lead"}, 
                                    {"Irregular Breathing", "Muscle Pain", "Irritable", "-1", "Carbon Monoxide"}, 
                                    {"Irregular Breathing", "Muscle Pain", "Paranoia", "-1", "Cannabis"}, 
                                    {"Irregular Breathing", "Muscle Pain", "Eye Problems", "-1", "Antidepressants"}, 
                                    {"Irregular Breathing", "Muscle Pain", "Sweating", "-1", "Paracetamol"} }; 

// The ifThenKey[][]: Used to confirm requirements for if clause.
// Depending on ifThenKey matches the truth value of a symptom in the variableList
// then the correspoinding conclusionList[][] is assigned its value
std::string ifThenKey[12][4] = { { "0","","","" }, 
                                    { "1", "", "", ""}, 
                                    { "1", "1", "", ""}, 
                                    { "1", "1", "1", ""}, 
                                    { "1", "1", "0", ""}, 
                                    { "1", "0", "1", "1"}, 
                                    { "1", "0", "1", "0"}, 
                                    { "0", "1", "1", ""},   
                                    { "0", "1", "0", ""}, 
                                    { "0", "0", "1", ""}, 
                                    { "0", "0", "1", ""}, 
                                    { "0", "0", "1", ""} }; 
bool processVariable = false,
     processConclusion = false;
string current_conclusion;

class artificialIntelligence
{
    public:
  /********************************************************************************************* 
  ***********************************BACKWARDS CHAINING*****************************************
  **********************************************************************************************/

 // returns the conclusion variable name using variable_num
 string search_con (int variable_num) { return conclusionList[variable_num - 1][0]; }

 // converts ri into ci and returns ci
 int rule_to_clause (int ri) { return (4 * (variable - 1)) + 1; }

 // update_VLBackwards(ci): This function finds the corresponding variableList element with the clause variable list element.
 // If found, processBackwards(i) is called so that the user can verify the symptoms presence
 void update_VLBackwards (int ci)
 {
    int clause_variable_index = ci - 1; // reference ci - 1 for clarity
    int current_clause = clause_variable_index; // current clause identified 
    bool found;
    // checks only the current and 3 more
    while ( current_clause < clause_variable_index + 4 )
    {
        // if "" then there are no more valid clause variables
        if ( clauseVarList[current_clause] == "" )
            break;

        found = false; // set/reset

        // iterate through entire variable list
        for ( int i = 0; i < VARIABLE_LIST_SIZE; i++ )
        {
            // if the current clause is in the variable list and is uninstantiated
            if ( clauseVarList[current_clause] == variableList[i][0] && variableList[i][1] == "-1" )
            {
                found = true;
                processVariable = true; // set processBackwards() path
                processBackwards(i); // pass i; corresponds with current_clause 
                current_clause++; // increment to next clause variable
                break; 
            }
        }

        // if not found in variable list then search conclusion list
        if ( !found )
        {
            for ( int i = 0; i < RULE_SIZE; i++ )
            {
                if ( clauseVarList[current_clause] == conclusionList[i][0] && conclusionList[i][1] = "-1" )
                {
                    found = true;
                    processConclusion = true; // set processBackwards() path
                    processBackwards(i);
                    current_clause++; // increment to next clause variable
                    break;
                }
            }
        }
    }
 }

 void processBackwards ( int variable_num )
 {
    if ( processVariable == false && processConclusion == false )
    {
        while (true)
        {
            current_conclusion = search_con ( variable_num );
            int ri = variable_num;
            int ci = rule_to_clause ( ri );
            update_VLBackwards ( ci );
            valdiate_RIBackwards ( ri, current_conclusion );
            variable_num++;
        }
    }

    if ( processVariable == true )
    {
      // when processVariable = true then variable_num = variable_list_index
      int variable_list_index = variable_num;

      string response;
      cout << "Does the patient feel/have " << variableList[variable_list_index][0] << "? (Reply Yes or No)" << endl;

      while (cin >> response)
      {
          // if yes then instantiate the variable
          if (response == "Yes" || response == "yes")
          {
            variableList[variable_list_index][1] = "1";
            processVariable = false;
            return;
          }
          // else break and return
          else if (response == "No" || response == "no")
          {
            variableList[variable_list_index][1] = "0";
            processVariable = false;
            return;
          }
          else
            cout << "Enter a correct response. (Yes or No)\n";   
      }
    }

    if ( processConclusion == true )
    {
      // when processConclusion == true then variable_num = conclusion_list_index
      int conclusion_list_index = variable_num;

      string response;
      cout << "Does the patient feel/have " << conclusionList[conclusion_list_index][0] << "? (Reply Yes or No)" << endl;

      while (cin >> response)
      {
          // if yes then instantiate the variable
          if (response == "Yes" || response == "yes")
          {
            conclusionList[conclusion_list_index][1] = "Yes";
            processConclusion = false;
            return;
          }
          // else break and return
          else if (response == "No" || response == "no")
          {
            conclusionList[conclusion_list_index][1] = "No";
            processConclusion = false;
            return;
          }
          else
            cout << "Enter a correct response. (Yes or No)\n";   
      }
    }
 }

  // check if the ifThenList variables match the ifThenKey
  // check by searching through the variable list and any instantiated global variables
  // if the key matches the variable's truth value 
  // then assign the ifThenList[rule_number_index][4] to the conclusion value and return;
  // if the key does not match the variable's truth value
  // then assign the conclusion value to "No" and continue;
  // recieves ri which is non indexed
  // ************************************************************ NEED TO FINISH **************************************************************
	void validate_RiBackward( int ri, string conclusion )
	{
    int rule_number_index = ri - 1;
    bool exitToken = false;
    // checks vars in ifThenList to see if the key is satisfied
    // 1. find the rule if vars
    for (int i = 0; i < 4; i++)
    {
      if ( ifThenList[rule_number_index][i] == "-1")
        break;
      if ( ifThenList[rule_number_index][i] != "-1")
      {
        for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
        {
          if (ifThenList[rule_number_index][i] == variableList[j][0])
          {
            if (ifThenKey[rule_number_index][i] == variableList[j][1])
            {
              conclusionList[rule_number_index][1] = ifThenList[rule_number_index][IF_THEN_SIZE - 1];
              derivedGlobalConclusionList.push_back(ifThenList[rule_number_index][IF_THEN_SIZE - 1]);
              return;
            }
            else return;
          }
        }
      }
    }
    // 2. check truth of that var in variableList and/or globalDerivedVariableList
    // 3. check if truth matches key
    // if matches, then assign ifThenKey[][5] to the conclusion variable return
    // if not then continue;
		return;
	}

  
	/****************************************************************** 
  *********************FORWARD CHAINING *****************************
  ******************************************************************/
  // this function will search for an entry in the CVI
	int search_cvl(int variable)
	{
		//find Ci
		int Ci = variable;//clause number
		update_VLForward(Ci);
		
    return clause_to_rule(Ci);
	}

	int clause_to_rule(int clauseNum)
	{
    int rule = ((clauseNum/4)+1)*10;
    validate_RiForward(rule);
    return rule;
	}

	//For each variable (Max 4) starting at Ci, check if variable is instantiated, if not promp user provide the values of variables and instantiate them
	void update_VLForward(int Ci)
	{
    //for each variable(max 4) starting at Ci, check if instantiated in variable list. If not, prompt user.
		for(int i=0; i<4; i++)
		{
      if(variableList[Ci+i][1] == "-1")//if the variable is not instantiated
      {
        std::string response;
        // prompt user to answer if symptom is present or not
        cout << "Does the patient feel/have " << variableList[Ci+i][0] << "? (Reply Yes or No)" << endl;
        // Ensures correct response 
       while (cin >> response)
       {
            if (response == "Yes" || response == "yes")
            {
                variableList[Ci+i][1] = "1";
                return;
           }
           else if (response == "No" || response == "no")
               return;
            else
            {
               cout << "Enter a correct response. (Yes or No)\n";
            }
       }
      }
		}
	}



	bool validate_RiForward(int variable)
	{
    //check if the values of the variable in the ‘if’ clauses of the rule, Ri, are satisfied with the values in the variable list.
    if(variableList[variable][1] != "-1")
    {
      //add the conclusion of the rule to the global derived conclusions list as well as to the Global Conclusion Variable Queue and 
      derivedGlobalConclusionList[dGCLSize] = variableList[variable][0];
      dGCLSize++;
      return true;
    }
    return false;
	}
/*)
  void processFowards(variable)
  {
    //instantiate the value of the variable in the variable list.
    search_cvl(variable);
    //return
  }
//shared
*/
};

#endif
