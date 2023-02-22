

#ifndef CS4345_PROJECT1_H
#define CS4345_PROJECT1_H
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
// global variables/arrays
// 0 = No 1 = Yes\
// order pair for conclusion nodes to know if looked at or not
std::string conclusionList[12][2] = { {"Poison", "-1"}, {"Qualify", "-1"}, {"Poison", "-1"},
                                    {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"},
                                    {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"} };
std::string variableList[9][2] = { {"Sick", "-1"}, {"Irregular Breathing", "-1"}, {"Cognitive Problems", "-1"}, {"Eye Problems", "-1"},
                                {"Muscle Pain", "-1"}, {"Dizzyness", "-1"}, {"Irritability", "-1"}, {"Paranoia", "-1"}, {"Sweating", "-1"} };
std::string ifThenList[12][5] = { {"Sick", "-1", "-1", "-1", "No"}, // 1
                            {"Sick", "-1", "-1", "-1", "Yes"}, // 2
                            {"Irregular Breathing", "Sweating", "-1", "-1", "Asprin"}, // 3
                            {"Irregular Breathing", "Cognitive Problems", "Eye Problems", "-1", "Benzodiazepines"}, // 4
                            {"Irregular Breathing", "Cognitive Problems", "Eye Problems", "-1", "Alcohol"}, // 5
                            {"Irregular Breathing", "Cognitive Problems", "Muscle Pain", "Dizzy", "Iodine"}, // 6
                            {"Irregular Breathing", "Cognitive Problems", "Muscle Pain", "Dizzy", "Sitmulant"}, // 7
                            {"Irregular Breathing", "Muscle Pain", "Irritable", "-1", "Lead"}, // 8
                            {"Irregular Breathing", "Muscle Pain", "Irritable", "-1", "Carbon Monoxide"}, // 9
                            {"Irregular Breathing", "Muscle Pain", "Paranoia", "-1", "Cannabis"}, // 10
                            {"Irregular Breathing", "Muscle Pain", "Eye Problems", "-1", "Antidepressants"}, // 11
                            {"Irregular Breathing", "Muscle Pain", "Sweating", "-1", "Paracetamol"} }; // 12
std::string ifThenKey[12][4] = { { "0","-1","-1","-1" }, // 1 
                            { "1", "-1", "-1", "-1"}, // 2
                            { "1", "1", "-1", "-1"}, // 3
                            { "1", "1", "1", "-1"}, // 4
                            { "1", "1", "0", "-1"}, // 5
                            { "1", "0", "1", "1"}, // 6
                            { "1", "0", "1", "0"}, // 7
                            { "0", "1", "1", "-1"}, // 8  
                            { "0", "1", "0", "-1"}, // 9
                            { "0", "0", "1", "-1"}, // 10
                            { "0", "0", "1", "-1"}, // 11
                            { "0", "0", "1", "-1"} }; // 12
string clauseVarList[50];
vector<string> derivedGlobalConclusionList;     
int dGCLSize=0;//number of items being used in 'derivedGlobalConclusionList'

static const int RULE_SIZE = 12;
static const int VARIABLE_LIST_SIZE = 9;
static const int IF_THEN_SIZE = 5;
// is false until is recursively called, when returned flag is set back to false;
bool processFlag = false;

class artificialInteligence
{
	/////////////////////////////////////
	//TODO: fix return types on functions
	/////////////////////////////////////
	
	//just making it all public for now
	public:
	/**************************************************************** 
  ********************BACKWARDS CHAINING***************************
  ****************************************************************/
  // find matching variable in conclusion list
  // conclusion list and rule list have matching indexes
  // ****************** DONE *******************
	std::string search_con(int variable)
	{
    // return conclusion list variable name
    return conclusionList[variable - 1][0];
	}
  // ****************** DONE ********************
  // converts the variable and returns the ci
	int rule_to_clause(int variable) { return (4 * (variable - 1)) + 1; }

  // ****************** DONE ********************
    // looks at ci + 4 and instantiates all variables starting from the location of ci in the variable list, if var is not in the var list, it could be in the then clause of some rule : call Process(var) to find its value, it will be a recursive call
	void update_VLBackward(int ci)
  {
    // align ci to correct index
    int clause_variable_index = ci - 1;
    // look at only 4 variables in the clause variable list
    // compare each clause variable with variable list to check if variable is instantiated
    for (int i = 0; i < clause_variable_index + 4; i++)
    {
      // if null then there are no more valid inputs
      // go to second loop
      if ( clauseVarList[i] == "" )
        break;
      
      // iterate through the entire variable list and find the matching variable
      for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
      {
        // clause variable matches the variable in variableList and it is not instantiated
        if ( clauseVarList[i] == variableList[j][0] && variableList[j][0] == "-1" )
        {
          // sends the index of the variable list to process the variable
          processFlag = true;
          processBackwards(j);
          // break loop to find new clause variable
          break;
        }
      }
    }
  
    // search through the ifThenList for matching variables
    // convert the ci back into the rule number
    // rule # = ci / 4 + 1

    int rule_number = (ci / 4) + 1;
    int rule_number_index = rule_number - 1;
    // iterate through the if variables of the ifThenList using the correspoinding rule number and the size - 1
    for (int i = 0; i < IF_THEN_SIZE - 1; i++)
      {
        // if the if variable is invalid then there are no more if variables to instantiate then break
        if (ifThenList[rule_number_index][i] == "")
          break;
        // iterate through the entire variable list to find the matching if variable
        for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
          {
            // if the if variable matches the variable in the variable list then process that variable
            if ( variableList[j][0] == ifThenList[rule_number_index][i] && variableList[j][1] == "-1")
            {
              processFlag = true;
              processBackwards(j);
              break;
            }
            // else if the if variable matches and it has been instantiated then break
            else break;
          }
      }
  }

  // processBackwards is given the variable list number (non indexed)
  void processBackwards ( int variable_num )
  {
    bool start = true;
    int ri, ci;
    // start a loop
    if (processFlag == false)
    {
        // ************************************************* NEED TO FINISH PROCESS WHILE LOOP ****************************************************
      while (start)
      {
        // 1. search_con (variable) looks for the matching variable in the conclusion/rule list
        string current_conclusion = search_con ( variable_num );
        // instantiate the corresponding rule number
        ri = variable_num;
        // 2. rule_to_claues( ri ) will convert the rule number into the clause number
        ci = rule_to_clause( ri );
        // 3. update_VLBackwards( ci )
        update_VLBackward(ci);


      }
    }

    if (processFlag == true)
    {
      // when true, variable_num is passed as the index
      // reference variable_num as variable_list_index for clarity
      int variable_list_index = variable_num;

      string response;
      cout << "Does the patient feel/have " << variableList[variable_list_index][0] << "? (Reply Yes or No)" << endl;

      while (cin >> response)
      {
          // if yes then instantiate the variable
          if (response == "Yes" || response == "yes")
          {
            variableList[variable_list_index][1] = "1";
            processFlag = false;
            break;
          }
          // else break and return
          else if (response == "No" || response == "no")
          {
            variableList[variable_list_index][1] = "0";
            processFlag = false;
            break;
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
	void validate_RiBackward( int ri )
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
