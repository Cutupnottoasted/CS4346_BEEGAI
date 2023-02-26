#include <iostream>
#include <string.h>
#include <stack>
using namespace std;
static const int RULE_SIZE = 12; // current number of rules; conclusionList, ifThenList, and ifThenKey share this size
static const int VARIABLE_LIST_SIZE = 9; // current number of symptoms
static const int IF_THEN_SIZE = 5; // total size of all if/then clause variables

stack<string> derivedGlobalConclusionStack; // vector implemented as a queue; contains validated symptoms followed by truth value
stack<string> helper_out;

string derivedGlobalConclusionQueue; // an array implemented as a queue
string clauseVarList[50]; // the clause variable list

// The conclusionList[][]: Contains all the conclusion variables.
// The order pair represents the rules "then" clause and it's associated value
// eg. [0][0], [0][1] == "Poison", "No" or [2][0], [2][1] == "Poison", "Asprin"
std::string conclusionList[12][2] = { {"Poison", "-1"}, {"Qualify", "-1"}, {"Poison", "-1"},
                                        {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"},
                                        {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"}, };
std::string antidote[22][2] = { {"Alchohol", "fomepizole"}, {"cannabis", "antagonist naloxone"}, {"stimulant", "Diazepam / lorazepam (ValiumTM / AtivanTM)"},
                                        {"Antidepressants", "Sodium bicarbonate"}, {"Benzodiazepines", "Flumazenil (RomaziconTM)"}, {"Asprin", "Sodium bicarbonate"},
                                        {"Paracetamol", "Intravenous acetylcysteine"}, {"Lead", "Calcium disodium EDTA (VersenateTM)"}, {"Iodine", "Stabilization and airway protection"},
										{"Carbon Monoxide", "hyperbaric oxygen therapy"}, {"Inhalent Abuse", "Decomtamination and stablilization"}, {"Rat Poison", "Phytonadione / Vitamin K1 (AquaMEPHYTONTM / MephytonTM)"},
										{"Mushrooms", "Pyridoxine / Vitamin B6"}, {"Spider Bite", "Antivenom"}, {"Herbicide", "Decomtamination and aggresive support therapy"},
										{"Fumigants", "Decontamination of skin and eyes"}, {"Pain Killers", "Naloxone (NarcanTM)"}, {"Opioids", "Naloxone (NarcanTM)"},
										{"Arsenic", "Dimercaprol / BAL"}, {"Calcium Channel Blockers", "Glucagon"}, {"Snake Bite", "Crotalinae polyvalent immune FAB (CroFabTM)"},
										{"Iron Poisoning", "Deferoxamine mesylate (DesferalTM)"}
										};
// The variableList[][]: Contains all the symptoms and their truth value
// The order pair represents the symptom and if it is present
// -1 = uninstantiated, 0 = false, 1 = true
std::string variableList[23][2] = { {"Sick", "-1"}, {"Irregular Breathing", "-1"}, {"Cognitive Problems", "-1"}, {"Eye Problems", "-1"},                                    {"Muscle Soreness", "-1"},
                                {"Muscle Pain", "-1"}, {"Dizzyness", "-1"}, {"Irritable", "-1"}, {"Paranoia", "-1"}, {"Sweating", "-1"} ,
								{"Dialated Pupils", "-1"}, {"Numbness", "-1"}, {"Vomiting", "-1"}, {"Tremors", "-1"}, {"Drowsiness", "-1"},
								{"Low Blood Pressure", "-1"}, {"Irritable Eyes", "-1"}, {"Poison Induced Pain", "-1"}, 
                {"Non Pain Inducing Poison", "-1"}, {"Patient Possibly Envenomed", "-1"},
                {"Non Muscle Related", "-1"}, {"Possible Medical Drug Abuse", "-1"}, {"Likely Ingested Substance", "-1"}
								};

// The ifThenList[][]: Represents the rule list.
// Contains up to 4 symptoms per rule and conclusion assignment at the end. eg [2][4] = "Asprin"
// The conclusion assignment is only assigned when the ifThenKey's requirements are satsified  
// Otherwise the conclusion is assigned "No"                                 
std::string ifThenList[30][5] = { {"Sick", "-1", "-1", "-1", "No"}, // if not sick, then poison = no
                                    {"Sick", "-1", "-1", "-1", "Yes"}, // if sick, then qualify = yes
                                    {"Sick", "Irregular Breathing", "Sweating", "-1", "Asprin"}, // 3
                                    {"Sick", "Irregular Breathing", "Cognitive Problems", "Eye Problems",  "Benzodiazepines"}, // 4
                                    {"Sick", "Irregular Breathing", "Cognitive Problems", "Eye Problems", "Alcohol"}, // 5
                                    {"Sick","Irregular Breathing", "Cognitive Problems", "Muscle Soreness", "Poison Induced Pain"}, // 6
                                    {"Poison Induced Pain", "Dizzyness", "-1", "-1", "Iodine"}, //7
                                    {"Poison Induced Pain", "Dizzyness", "-1", "-1", "Sitmulant"}, // 8
                                    {"Irregular Breathing", "Cognitive Problems", "Muscle Soreness", "-1", "Non-Pain Inducing Poison"}, //9
									                  {"Non-Pain Inducing Poison", "Pinpoint Pupils", "Pale Complexion", "-1", "Opioids"}, // 10
								                  	{"Non-Pain Inducing Poison","Pinpoint Pupils", "Pale Complexion", "-1", "Painkillers"}, // 11
						                  			{"Non-Pain Inducing Poison", "Pinpoint Pupils", "Hair Loss", "-1", "Rat Poison"}, // 12
                                    {"Non-Pain Inducing Poison", "Pinpoint Pupils", "Hair Loss", "-1", "Patient Possibly Envenomed"},//13
							                   		{"Patient Possibly Envenomed", "Cramping", "-1", "-1", "Spider Bite"}, // 14
							                   		{"Patient Possibly Envenomed","Cramping", "Vomiting Blood", "-1", "Iron Poisoning"}, // 15
					                   				{ "Patient Possibly Envenomed","Cramping", "Vomiting Blood", "Irritable Eyes", "Herbicide"}, // 16
						                  			{"Patient Possibly Envenomed","Cramping", "Vomiting Blood", "Irritable Eyes", "Snake Bite"}, // 17
                                    {"Sick", "Irregular Breathing", "Muscle Pain", "-1", "Possible Medical Drug Abuse"}, //18
						                  			{"Possible Medical Drug Abuse","Paranoia", "-1", "-1", "Cannabis"},//19
                                    {"Possible Medical Drug Abuse", "Paranoia", "Dialated Pupils", "-1", "Anti Depressants"}, //20
							                   		{"Possible Medical Drug Abuse", "Paranoia", "Dialated Pupils", "Sweating", "Paracetamol"}, //21
							                  		{"Possible Medical Drug Abuse", "Paranoia", "Dialated Pupils", "Sweating", "Likely Ingested Substance"}, //22
                                    {"Likely Ingested Substance", "Vomiting", "-1", "-1", "Inhalent Abuse"}, //23
							                   		{"Likely Ingested Substance", "Vomiting", "Tremors", "-1", "Fumigants"}, //24
								                  	{"Likely Ingested Substance", "Vomiting", "Tremors", "-1", "Mushrooms"}, //25
                                    {"Sick", "Irregular Breathing", "Muscle Pain", "-1", "Non Muscle Related"}, //26
					                   				{"Non Muscle Related", "Irritable", "Low Blood Pressure", "-1", "Calcium"}, //27
					                   				{"Non Muscle Related", "Irritable", "Low Blood Pressure", "-1", "lead"},//28
					                   				{"Non Muscle Related", "Irritable", "Numbness", "-1", "Carbon Monoxide"},//29
						                  			{"Non Muscle Related", "Irritable", "Numbness", "-1", "Arsenic"},//30
							               		};
									

// The ifThenKey[][]: Used to confirm requirements for if clause.
// Depending on ifThenKey matches the truth value of a symptom in the variableList
// then the correspoinding conclusionList[][] is assigned its value
// start at rule 5, irregular breathing = yes, cognitive problems = yes, eye problems = no
// rule 4 contains the correct answer how do i find the right answer given the conditions
// if there are three.. just loop until you find the answer. what condition?
// if the key confirm all but the last symptom in the ifThenList, iterate through entire ifThenList indexed at the last symptom
// 
std::string ifThenKey[30][5] = {    { "0","-1","-1","-1"}, // 1
                                    {"1", "-1", "-1", "-1"}, // 2 
                                    {"1", "1", "1", "-1"}, // 3
                                    {"1", "1", "1", "1"}, // 4
                                    {"1", "1", "1", "0"}, // 5
                                    {"1", "1", "0", "1"}, // 6
                                    {"1", "1", "-1", "-1"}, // 7
                                    {"1", "0", "-1", "-1"}, //8
                                    {"1", "0", "0", "-1"}, // 9
									                  {"1", "1", "1", "-1"}, // 10
									                  {"1", "1", "0", "-1"}, // 11
								                  	{"1", "0", "1", "-1"}, // 12
									
						                  			{"1", "0", "0", "-1"}, // 13
							                   		{"1", "1", "-1", "-1"}, // 14
									{"1", "0", "1", "-1"}, // 15
									{"1", "0", "0", "1"}, // 16
                                    { "1", "0", "0", "0"}, // 17
									{ "1", "0", "0", "-1"},  // 18
									{ "1", "1", "-1", "-1"},  // 19
									{ "1", "0", "1", "-1"},  // 20
									{ "1", "0", "0", "1"},  // 21
									{ "1", "0", "0", "0"},  // 22
									{ "1", "0", "-1", "-1"},  // 23
									{ "1", "1", "1", "-1"},  // 24
									{ "1", "1", "0", "-1"},  // 25
									{ "1", "0", "1", "-1"},  // 26
									{ "1", "1", "1", "-1"},  // 27
                  { "1", "1", "-1", "-1"}, //28
                  { "1", "-1", "-1", "-1"}, //29
                  { "1", "0", "1", "-1"} //30
									};
bool processVariable = false,
     processConclusion = false,
     diagnosis = false; // if true then loop done
string current_conclusion;
/********************************************************************************************* 
  ***********************************BACKWARDS CHAINING*****************************************
  **********************************************************************************************/

 // returns the conclusion variable name using variable_num
 string search_con (int variable_num) { return conclusionList[variable_num - 1][0]; }

 // converts ri into ci and returns ci
 int rule_to_clause (int ri) { return (4 * (ri - 1)) + 1; }

 // update_VLBackwards(ci): This function finds the corresponding variableList element with the clause variable list element.
 // If found, processBackwards(i) is called so that the user can verify the symptoms presence
 void update_VLBackwards (int ci);

 void processBackwards ( int variable_num );
 
 void validate_RIBackwards ( int ri, string conclusion );
 
 // test functinos

 void test_search_con (int variable_num)
 {
    current_conclusion = search_con (variable_num);
    cout << current_conclusion << endl;
 }

 int test_rule_to_clause (int ri)
 {
    int cvi = rule_to_clause(ri);
    cout << cvi << endl;
    return cvi;
 }

 void test_update_VLBackwards (int cvi)
 {
    update_VLBackwards(cvi);
    
 }

 void test_validate_RIBackwards(int ri)
 { 
    string conclusion;
    validate_RIBackwards(ri, conclusion);
 }

 bool check_if_validated(string symptom)
 {
    return false;
 }


//5, 8, 12, 17, 21, 25
 bool double_check(int rule_number)
 {
   cout << "RULE_NUMBER" << rule_number << endl;
   if(rule_number == 5 || rule_number == 8 || rule_number == 12 || rule_number == 17 || rule_number == 21 || rule_number == 25)
   {
      return false;
   }
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
      {
        if(ifThenList[rule_number][i] == variableList[j][0] && ifThenKey[rule_number][i] == variableList[j][1])
          continue;
        else if (ifThenList[rule_number][i] == variableList[j][0] && ifThenKey[rule_number][i] != variableList[j][1])
          return false;
      }
    }
    return true;
 }
void printClauseList()  
{  
    cout << "Printing clauseVarList elements:"<< endl;  
    for (int i = 0; i < 50; i++)  
    {  
                   cout<<clauseVarList[i]<<"\n";    
    }  
}  
int main ()
{
    int variable = 1;
	//intel->search_cvl(variable);
    // Instantiate the Clause Variable List
	int count =0;
	int objectNum = 0;
    while(count<25)
	{
		clauseVarList[count]=ifThenList[objectNum][0];
		clauseVarList[count+1]=ifThenList[objectNum][1];
		clauseVarList[count+2]=ifThenList[objectNum][2];
		clauseVarList[count+3]=ifThenList[objectNum][3];
		count+=4;
		objectNum++;
	}
	/*
	for(int i=0;i<(22-4);i++)
	{
		clauseVarList[i]=ifThenList[i][0];
		clauseVarList[i+1]=ifThenList[i][1];
		clauseVarList[i+2]=ifThenList[i][2];
		clauseVarList[i+3]=ifThenList[i][3];
	}
	*/
	/*
	printClauseList();
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
	printClauseList();
     // rule 3
    clauseVarList[8] = "Irregular Breathing";
    clauseVarList[9] = "Sweating";
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
    clauseVarList[30] = "Irritable";
    clauseVarList[31] = "-1";
    // rule 9
    clauseVarList[32] = "Irregular Breathing";
    clauseVarList[33] = "Muscle Pain";
    clauseVarList[34] = "Irritable";
    clauseVarList[35] = "-1";
    // rule 10
    clauseVarList[36] = "Irregular Breathing";
    clauseVarList[37] = "Muscle Pain";
    clauseVarList[38] = "Paranoia";
    clauseVarList[39] = "-1";
    // rule 11
    clauseVarList[40] = "Irregular Breathing";
    clauseVarList[41] = "Muscle Pain";
    clauseVarList[42] = "Eye Problems";
    clauseVarList[43] = "-1";
    // rule 12
    clauseVarList[44] = "Irregular Breathing";
    clauseVarList[45] = "Muscle Pain";
    clauseVarList[46] = "Sweating";
    clauseVarList[47] = "-1";*/
	
	
    int i = 1;
    while (i < RULE_SIZE && !diagnosis )
    {
    test_search_con(i);
    int cvi = test_rule_to_clause(i);
    test_update_VLBackwards(cvi);
    test_validate_RIBackwards(i);
    i++;
    cout << i << endl;
    }
    cout << variableList[i][0] << " " << variableList[i][1] << endl;
	cout << "The patient is poisoned with: " << ifThenList[i-2][4] << endl;
    return 0;
}

// implementations
void update_VLBackwards(int ci)
  {
    // align ci to correct index
    int clause_variable_index = ci - 1;
    // look at only 4 variables in the clause variable list
    // compare each clause variable with variable list to check if variable is instantiated
    for (int i = clause_variable_index; i < clause_variable_index + 4; i++)
    {
      // if null then there are no more valid inputs
      // go to second loop
       if ( clauseVarList[i] == "-1" )
      {
        cout << "Next rule" << endl;
        cout << "Clause Variable List has been exhausted\n";
        return;
      }
      
      // iterate through the entire variable list and find the matching variable
      for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
      {
        //cout << "Variable " << j << " is shown" << endl;
        // clause variable matches the variable in variableList and it is not instantiated
        if ( clauseVarList[i] == variableList[j][0] && variableList[j][1] == "-1" )
        {
          // sends the index of the variable list to process the variable
          processVariable = true;
          //cout << "in processBackwards variable..." << endl;
          processBackwards(j);
          //cout << "back into updateVL..." << endl;
          // break loop to find new clause variable
          break;
        }
        // if matching but not null then break to find new clause var
        else if ( clauseVarList[i] == variableList[j][0] && variableList[j][1] != "-1"){break;}
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
        if (ifThenList[rule_number_index][i] == "-1")
        {
            cout << "No more valid if clauses.." << endl;
            break;
        }
        // iterate through the entire variable list to find the matching if variable
        for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
          {
            cout << "Variable " << j << " is shown (processConclusion)" << endl;
            // if the if variable matches the variable in the variable list then process that variable
            if ( variableList[j][0] == ifThenList[rule_number_index][i] && variableList[j][1] == "-1")
            {
              processConclusion = true;
              cout << "in processBackwards...conclusion" << endl;
              processBackwards(j);
              cout << "back into updateVL..." << endl;
              break;
            }
            // else if the if variable matches and it has been instantiated then break
            else if ( ifThenList[rule_number_index][i] == variableList[j][0] && variableList[j][1] != "-1"){break;}
          }
      }
  }

  // processBackwards is given the variable list number (non indexed)
   void processBackwards ( int variable_num )
 {
    /*// if both flags are false then start loop
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
    }*/
    
    if ( processVariable == true )
    {
      // when processVariable = true then variable_num = variable_list_index
      int variable_list_index = variable_num;
      //if (variableList[variable_list_index][1] != "-1")
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
  // PROBLEM A SECOND IRREGULAR BREATHING IS PUSHED INTO THE VECTOR
  // ************************************************************ NEED TO FINISH **************************************************************
	void validate_RIBackwards ( int ri, string conclusion )
 {
    int rule_number_index = ri - 1;
    string truth_value;
    bool helped = false;
    
    // if the global list is empty then skip straight to the variable list
    if ( derivedGlobalConclusionStack.empty() )
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
              if (variableList[0][1] == ifThenKey[0][0])
              {
                cout << "This person is not sick" << endl;
                diagnosis = true;
                return;
              }
              derivedGlobalConclusionStack.push (conclusion);
              derivedGlobalConclusionStack.push (truth_value);
              // catches case if person not sick
              
              break; // break to look t_back hrough if clauses
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
    else if ( !derivedGlobalConclusionStack.empty() )
    {
      bool satisfied = false;
      // iterate through all if clauses in ifThenList
      for ( int i = 0; i < 4; i++ )
      {
        // if -1 then no valid choices then double check if true
        if ( ifThenList[rule_number_index][i] == "-1" )
        {
          
          conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
          diagnosis = double_check(rule_number_index);
          return;
        }
        // a condition is given
        else if ( ifThenList[rule_number_index][i] != "-1")
        {
          conclusion = ifThenList[rule_number_index][i];
          truth_value = ifThenKey[rule_number_index][i];
          
          // if conclusion stack is not empty and helper is empty then
          // stack all conclusions into helper
          if ( !derivedGlobalConclusionStack.empty() && !helped)
          {
            if ( helper_out.empty() )
              while ( !derivedGlobalConclusionStack.empty() )
              {
                helper_out.push (derivedGlobalConclusionStack.top());
                derivedGlobalConclusionStack.pop();
              }
            helped = true;
          }
          // while helper is not empty look for matching conclusions/truth values
          // if satisfied then break loop to for another clause
          while ( !helper_out.empty() )
          {
            if (conclusion == helper_out.top()) // if not then next
            {
                derivedGlobalConclusionStack.push(helper_out.top());
                helper_out.pop();
                if (truth_value == helper_out.top()) // if true then look for another clause
                {
                    derivedGlobalConclusionStack.push(helper_out.top());
                    helper_out.pop();
                    i++;
                    conclusion = ifThenList[rule_number_index][i];
                    truth_value = ifThenKey[rule_number_index][i];
                    continue;
                }
                else if (truth_value != helper_out.top()) // if incorrect truth value
                {
                    conclusionList[rule_number_index][1] = "No";
                    while ( !helper_out.empty() )
                    {
                        derivedGlobalConclusionStack.push(helper_out.top());
                        helper_out.pop();
                    }
                    return; // exit function
                }
            }
            else if (conclusion != helper_out.top())
            {
              derivedGlobalConclusionStack.push(helper_out.top());
              helper_out.pop();
              derivedGlobalConclusionStack.push(helper_out.top());
              helper_out.pop();
            }
          }
          // if you reach this point then ifThenList still needs verifying
          // which means the rest of the clause variables have not been verified
          if (!satisfied && helper_out.empty()) // if not satisfied and helper is empty
          {

             for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
            {
                cout << "variable: " << j << endl;
                // if both the conclusion and the truth match
                 if (conclusion == variableList[j][0] && truth_value == variableList[j][1])
                {
                    cout << "A conclusion has been confirmed and pushed into vector" << endl;
                    derivedGlobalConclusionStack.push (conclusion);
                    derivedGlobalConclusionStack.push (truth_value);
                    conclusion = ifThenList[rule_number_index][i];
                    truth_value = ifThenKey[rule_number_index][i];
                    break; // break to look t_back hrough if clauses
                }
                /*else if (conclusion == variableList[j][0] && variableList[j][1] == "-1")
                {
                    cout << "Symptom unvalidated" << endl;
                    processVariable = true;
                    processBackwards(j);
                    break;
                }*/
                // if conclusion match but truth does not
                else if (conclusion == variableList[j][0] && truth_value != variableList[j][1])
                {
                    cout << "The test has failed" << endl;
                    conclusionList[rule_number_index][1] = "No";
                    return; // leave the function
                }
            }
          }
         }
        }
        // if here, then all 4 clauses were verified
        conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
        diagnosis = true;
        return; 
    }
 }