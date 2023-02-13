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
    // Instantiate the Clause Variable List
    // rule 1
    clauseVarList[0] = "Sick";
    clauseVarList[1] = "";
    clauseVarList[2] = "";
    clauseVarList[3] = "";
    // rule 2
    clauseVarList[4] = "Sick";
    clauseVarList[5] = "";
    clauseVarList[6] = "";
    clauseVarList[7] = "";
    // rule 3
    clauseVarList[8] = "Irregular Breathing";
    clauseVarList[9] = "";
    clauseVarList[10] = "";
    clauseVarList[11] = "";
    // rule 4
    clauseVarList[12] = "Irregular Breathing";
    clauseVarList[13] = "Cognitive Problems";
    clauseVarList[14] = "Eye Problems";
    clauseVarList[15] = "";
    // rule 5
    clauseVarList[16] = "Irregular Breathing";
    clauseVarList[17] = "Cognitive Problems";
    clauseVarList[18] = "Eye Problems";
    clauseVarList[19] = "";
    // rule 6
    clauseVarList[20] = "Irregular Breathing";
    clauseVarList[21] = "Cognitive Problems";
    clauseVarList[22] = "Muscle Pain";
    clauseVarList[23] = "";
    // rule 7
    clauseVarList[24] = "Irregular Breathing";
    clauseVarList[25] = "Cognitive Problems";
    clauseVarList[26] = "Muscle Pain";
    clauseVarList[27] = "";
    // rule 8
    clauseVarList[28] = "Irregular Breathing";
    clauseVarList[29] = "Muscle Pain";
    clauseVarList[30] = "";
    clauseVarList[31] = "";
    // rule 9
    clauseVarList[32] = "Irregular Breathing";
    clauseVarList[33] = "Muscle Pain";
    clauseVarList[34] = "";
    clauseVarList[35] = "";
    // rule 10
    clauseVarList[36] = "Irregular Breathing";
    clauseVarList[37] = "Muscle Pain";
    clauseVarList[38] = "";
    clauseVarList[39] = "";
    // rule 11
    clauseVarList[40] = "Irregular Breathing";
    clauseVarList[41] = "Muscle Pain";
    clauseVarList[42] = "";
    clauseVarList[43] = "";
    // rule 12
    clauseVarList[44] = "Irregular Breathing";
    clauseVarList[45] = "Muscle Pain";
    clauseVarList[46] = "";
    clauseVarList[47] = "";

    
}
