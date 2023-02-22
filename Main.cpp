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



void validate_RIBackwards (int ri, string conclusion)
{
    int rule_number_index = ri - 1;
    string truth_value;

    if (derivedGlobalConclusionList.empty() )
    {
        for (int i = 0; i < 4; i++)
        {
            if (ifThenList[rule_number_index][i] == "-1")
                return;
            
            if (ifThenList[rule_number_index][i] != "-1")
            {
                conclusion = ifThenList[rule_number_index][i];
                truth_value = ifThenKey[rule_number_index][i];

                for (int j = 0; j < VARIABLE_LIST_SIZE; j++)
                {
                    if (conclusion == variableList)
                }
            }

        }
    }
}