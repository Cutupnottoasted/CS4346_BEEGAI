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
                                        {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"},
                                        {"Poison", "-1"}, {"Poison", "-1"}, {"Poison", "-1"} };

// The variableList[][]: Contains all the symptoms and their truth value
// The order pair represents the symptom and if it is present
// -1 = uninstantiated, 0 = false, 1 = true
std::string variableList[9][2] = { {"Sick", "-1"}, {"Irregular Breathing", "-1"}, {"Cognitive Problems", "-1"}, {"Eye Problems", "-1"},
                                {"Muscle Pain", "-1"}, {"Dizzyness", "-1"}, {"Irritable", "-1"}, {"Paranoia", "-1"}, {"Sweating", "-1"} };

// The ifThenList[][]: Represents the rule list.
// Contains up to 4 symptoms per rule and conclusion assignment at the end. eg [2][4] = "Asprin"
// The conclusion assignment is only assigned when the ifThenKey's requirements are satsified  
// Otherwise the conclusion is assigned "No"                                 
std::string ifThenList[12][5] = { {"Sick", "-1", "-1", "-1", "No"}, // if not sick, then poison = no
                                    {"Sick", "-1", "-1", "-1", "Yes"}, // if sick, then qualify = yes
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

// The ifThenKey[][]: Used to confirm requirements for if clause.
// Depending on ifThenKey matches the truth value of a symptom in the variableList
// then the correspoinding conclusionList[][] is assigned its value
// start at rule 5, irregular breathing = yes, cognitive problems = yes, eye problems = no
// rule 4 contains the correct answer how do i find the right answer given the conditions
// if there are three.. just loop until you find the answer. what condition?
// if the key confirm all but the last symptom in the ifThenList, iterate through entire ifThenList indexed at the last symptom
// 
std::string ifThenKey[12][4] = { { "0","-1","-1","-1"}, // 1
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
bool processVariable = false,
     processIfClause = false,
     diagnosis = false; // if true then loop done
string current_conclusion; 

string search_con (int variable_num) { return conclusionList[variable_num - 1][0]; }

int rule_to_clause (int ri) { return (4 * (ri - 1)) + 1; }

 void update_VLBackwards (int ci);

 void processBackwards ( int variable_num );
 
 void validate_RIBackwards ( int ri, string conclusion );

 bool double_check(int rule_number_index)
 {
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
      {
        if(ifThenList[rule_number_index][i] == variableList[j][0] && ifThenKey[rule_number_index][i] == variableList[j][1])
          continue;
        else if (ifThenList[rule_number_index][i] == variableList[j][0] && ifThenKey[rule_number_index][i] != variableList[j][1])
          return false;
      }
    }
    return true;
 }

 void update_VLBackwards (int ci)
 {
    int clause_variable_index = ci - 1;

    // looks through clause variable index
    for (int i = clause_variable_index; i < clause_variable_index + 4; i++)
    {
        if (clauseVarList[i] == "-1") // then no more valid clause variables
        {
            cout << "There are no more valid choices in the Clause Variable List" << endl;
            return; // returns main
        }
        
        // find the matching variable between variableList and clauseVarList
        for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
        {
            cout << "Search for matching variables between varList and clauseList" << endl;
            
            // if varList & clauseList match but is null
            if ( clauseVarList[i] == variableList[j][0] && variableList[j][1] == "-1")
            {
                processVariable = true;
                cout << "processing variable " << clauseVarList[i] << endl;
                processBackwards(j);
                cout << "processed. returning to updateVL" << endl;
                break; // break j for loop, return to i for loop
            }
            // this match has already been processed
            else if ( clauseVarList[i] == variableList[j][0] && variableList[j][1] != "-1" )
            { break; }
        }

        int rule_number_index = ( (ci / 4) + 1 ) - 1; // convert ci into ri

        // search for a match between clauseVarList and ifThenList
        for (int k = 0; k < IF_THEN_SIZE - 1; k++)
        {
            cout << "searching for a between ifThenList and clauseVarList" << endl;
            // if -1 then ifThenList exhausted
            if ( ifThenList[rule_number_index][k] == "-1" )
            {
                cout << "ifThenList is exhausted" << endl;
                break;
            }
            // if clauseVarList matches with ifThenList
            if ( clauseVarList[i] == ifThenList[rule_number_index][k] )
            {
                cout << "a match between clauseVarList and ifThenList has been found" << endl;
                cout << "Checking to see if instantiate in the variableList" << endl;
                // search through variableList to find a match that is null
                for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
                {
                    // if variableList and ifThenList match but it is null then process
                    if ( variableList[j][0] == ifThenList[rule_number_index][i] && variableList[j][1] == "-1" )
                    {
                        processIfClause = true;
                        cout << "processing ifClause " << clauseVarList[i] << endl;
                        processBackwards(j);
                        cout << "processed. returning to updateVL" << endl;
                        break;
                    }
                    // if they match but not null
                    else if ( ifThenList[rule_number_index][i] == variableList[j][0] && variableList[j][1] != "-1")
                    {break;}
                }
            } 
        }  
    }

 }

 void processBackwards (int variable_num )
 {
    int variable_list_index = variable_num;
    string response;
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
          { cout << "Enter a correct response. (Yes or No)\n"; }   
    }
    

    if ( processIfClause == true )
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
              processIfClause = false;
              return;
            }
            // else break and return
            else if (response == "No" || response == "no")
            {
              conclusionList[conclusion_list_index][1] = "No";
              processIfClause = false;
              return;
            }
            else
            { cout << "Enter a correct response. (Yes or No)\n"; }   
      }
    }
 }

 void validate_RIBackwards ( int ri, string conclusion )
 {
    cout << "Validating if the rule is true" << endl;
    int rule_number_index = ri - 1;
    string truth_value;
    bool helped = false;

    // if empty then first look
    if ( derivedGlobalConclusionStack.empty() )
    {
        cout << "global stack is empty " << endl;

        // iterate through all the if clauses
        // if loop ends then ifThenKey matched with all variableList truth values
        for (int i = 0; i < IF_THEN_SIZE - 1; i++) 
        {
            // ifThenKey matched with all variableList truth values
            if ( ifThenList[rule_number_index][i] == "-1" )
            {
                cout << "The ifThenKey has been satisfied " << endl;
                cout << "The person has " << ifThenList[rule_number_index][4] << endl;
                cout << "The rule number was " << rule_number_index + 1 << endl;
                conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
                return;
            }
            // ifThenList has given a valid input
            else if ( ifThenList[rule_number_index][i] != "-1" )
            {
                cout << ifThenList[rule_number_index][i] << " is to be validated" << endl;
                conclusion = ifThenList[rule_number_index][i]; // reference the conclusion
                truth_value = ifThenKey[rule_number_index][i]; // reference the truth_value

                // search the entire variableList for a matching conclusion and truth_value
                for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
                {
                    cout << "searching for a match between varList, conclusion and truth_value " << endl;

                    // if the there is a match
                    if (conclusion == variableList[j][0] && truth_value == variableList[j][1])
                    {
                        cout << "MATCH IS FOUND" << endl;
                        cout << "TRUTH IS MATCHING" << endl;
                        cout << "PUSHING ONTO GLOBAL STACK" << endl;
                        derivedGlobalConclusionStack.push (conclusion);
                        derivedGlobalConclusionStack.push (truth_value);
                        break;
                    }
                    // a match but not incorrect variableList truth
                    else if (conclusion == variableList[j][0] && truth_value != variableList[j][1])
                    {
                        cout << "MATCH IS FOUND" << endl;
                        cout << "TRUTH IS NOT MATCHING" << endl;
                        cout << "ASSIGNING NO TO CONCLUSIONLIST" << endl;
                        conclusionList[rule_number_index][1] = "No";
                        return;
                    }
                }
            }
        }
        // The end of the ifThenList, then ifThenKey was satisfied
        cout << "The ifThenKey has been satisfied " << endl;
        cout << "The person has " << ifThenList[rule_number_index][4] << endl;
        cout << "The rule number was " << rule_number_index + 1 << endl;
        conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
        return; 
    }
    else if ( !derivedGlobalConclusionStack.empty() )
    {
      cout << "The global stack is not empty " << endl;
      cout << "Stacking onto the helper to reorder correctly" << endl;
      bool helped = false;

      // order the derived variables correctly
      if ( helper_out.empty() )
        while ( !derivedGlobalConclusionStack.empty() )
        {
            helper_out.push(derivedGlobalConclusionStack.top());
            derivedGlobalConclusionStack.pop();
        }
      helped = true;
      // iterate through the entire ifThenList
      for (int i = 0; i < IF_THEN_SIZE - 1; i++)
      {
          cout << "Searching through the ifThenList " << endl;
          // if the ifThenList is null then test possibly passed
          if ( ifThenList[rule_number_index][i] == "-1" )
          {
              cout << "The ifThenList has been exhausted. double check if the rule is the correct diagnosis." << endl;
              conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
              diagnosis = double_check(rule_number_index);
              return;
          }
          // a valid input is given
          else if ( ifThenList[rule_number_index][i] != "-1" )
          {
              cout << ifThenList[rule_number_index][i] << " is to be validated" << endl;
              conclusion = ifThenList[rule_number_index][i]; // reference the conclusion
              truth_value = ifThenKey[rule_number_index][i]; // reference the truth_value
              
              // while the helper stack is full
              while ( !helper_out.empty() )
              {
                  if ( conclusion == helper_out.top() )
                  {
                      derivedGlobalConclusionStack.push(helper_out.top());
                      helper_out.pop();

                      if (truth_value == helper_out.top())
                      {
                          derivedGlobalConclusionStack.push(helper_out.top());
                          helper_out.pop();
                          // move to next rule
                          i++;
                          conclusion = ifThenList[rule_number_index][i];
                          truth_value = ifThenKey[rule_number_index][i];
                          // if the ifThenList is null or i >= 4 then key satisfied
                          if ( conclusion == "-1" || i >= 4 )
                          {
                              cout << "The ifThenList has been exhausted. double check if the rule is the correct diagnosis. " << endl;
                              conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
                              diagnosis = double_check(rule_number_index);
                              return;
                          }
                          continue;
                      }
                      // if truth is not matching then return to main
                      else if ( truth_value != helper_out.top() )
                      {
                          conclusionList[rule_number_index][1] = "No";
                          // restack all derived conclusions
                          while ( !helper_out.empty() )
                          {
                              derivedGlobalConclusionStack.push(helper_out.top());
                              helper_out.pop();
                          }
                          return;
                      }
                      // if not matching conclusion then get next in stack
                      else if (conclusion != helper_out.top())
                      {
                          derivedGlobalConclusionStack.push(helper_out.top());
                          helper_out.pop();
                          derivedGlobalConclusionStack.push(helper_out.top());
                          helper_out.pop();
                      }
                  }
              }
              // if here then ifThenList has yet to be validated
              // and the global derived conclusion stack has been exhausted
              if ( helper_out.empty() )
              {
                  for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
                  {
                    if (conclusion == variableList[j][0] && truth_value == variableList[j][1])
                    {
                        cout << "MATCH IS FOUND" << endl;
                        cout << "TRUTH IS MATCHING" << endl;
                        cout << "PUSHING ONTO GLOBAL STACK" << endl;
                        derivedGlobalConclusionStack.push (conclusion);
                        derivedGlobalConclusionStack.push (truth_value);
                        break;
                    }
                    else if (conclusion == variableList[j][0] && truth_value != variableList[j][1])
                    {
                        cout << "MATCH IS FOUND" << endl;
                        cout << "TRUTH IS NOT MATCHING" << endl;
                        cout << "ASSIGNING NO TO CONCLUSIONLIST" << endl;
                        conclusionList[rule_number_index][1] = "No";
                        return;
                    }
                  }
              }
          }
      }
      cout << "The ifThenKey has been satisfied " << endl;
      cout << "The person has " << ifThenList[rule_number_index][4] << endl;
      cout << "The rule number was " << rule_number_index + 1 << endl;
      conclusionList[rule_number_index][1] = ifThenList[rule_number_index][4];
      diagnosis = double_check (rule_number_index);
      return; 
    }
 }

 int main()
 {
    return 0;
 }