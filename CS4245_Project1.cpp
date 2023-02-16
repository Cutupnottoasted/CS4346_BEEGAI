#include "CS4345_Project1.h"
#include <algorithm>

using namespace std;

void search_con (double var)
{
    // searches through the conclusion list
    for (int i = 0; i < conclusionList.size(); i++)
    {
        // finds the corresponding rule number
        if (var == (i + 1))
            int ri = static_cast<int>(var);
        rule_to_clause(ri);
    }   
}
// rule_to_clause (int ri):
// Converts ri to clause variable list number, cvi using the formula:
// cvi = 4 * (ri - 1) + 1 *numbers are seq. 1,2,3..
// check if cvi in variable list is instantiated
// if not, then ask with update_VL(cvi)
void rule_to_clause (int ri)
{
    // conversion
    int cvi = 4 * (ri - 1) + 1;
    
    // if the cvi matches the variable name and the variable isn't instantiated
    // call update  _vl(cvi);
    update_vl(cvi);
    
}

void update_vl (int cvi)
{ 
    
    // alligns to conclusionList
    int index = cvi - 1;
    // checks the cvi stack for variables to instantiate
    for (index; index < index + 4; index++)
    {
        // if clauseVarList[index] is invalid then there are no more variables to read
        if (clauseVarList[index] == "")
            break;
        // if variable in the clauseVarList is valid then check if it is instantiated
        if (clauseVarList[index] != "")
        {
            // a loop to compare clauseVarList[index] with all the variables in variableList[]
            for (int i = 0; i < 10; i++)
            {
                // if they match and it isn't instantiated then call process(cvi)
                if (clauseVarList[index] == variableList[i][0])
                {
                    if (variableList[i][1] == "0")
                    {
                        process(cvi);
                        break; // breaks the for loop to find a new variable in clauseVarList
                    }
                    else
                        break; // the variable is instantiated already
                }
            }
        }
    }
    // check the ifThenList[] for any if variables to instantiate
    for (int i = 0; i < 4; i++)
    {
        // if the string is not valid then no more ifs in the ifThenList[]
        if (ifThenList[index][i] == "0")
            break;
        // if the string is valid then check if instantiated 
        if (ifThenList[index][i] != "0")
        {
            for (int j = 0; j < 12; j++)
            {
                if (ifThenList[index][i] == variableList[j][0] && variableList[j][1] == "0" )
                {
                    process(cvi);
                    break;
                }
            }
        }
    }
}

void process (int cvi)
{
    string response;
    cout << "Does the patient feel/have " << variableList[cvi - 1][0] << "? (Reply Yes or No)" << endl;
    while (cin >> response)
    {
        if (response = "Yes" || response == "yes")
        {
            variableList[cvi - 1][1] = "1";
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

// validate_ri (int ri, string conclusion):
// check if the variables in the 'if' clause of the rules
// are satisfied. if yes then assign conclusion of rule (yes or no)
// to the string 'conclusion' otherwise no value is assigned.
void validate_ri (int ri, string conclusion)
{

}