#include "CS4345_Project1.h"
#include <algorithm>

using namespace std;
// Constructor
Patient::Patient(int initial_capacity) : capacity(initial_capacity), used(0), current_index(0)
{
    if (capacity < 1)
        capacity = DEFAULT_CAPACITY;
    symptoms = new string[capacity];
}
// Deconstructor
Patient::~Patient() { delete [] symptoms };
// Copy constructor
Patient::Patient(const Patient& src)
    : capacity(src.capacity), used(src.used), current_index(srs.current_index)
{
    symptoms = new string[capacity];
    copy (source.symptoms, source.symptoms + used, symptoms)
}
// Resize function to dynamically increase if more symptoms are needed 
void Patient::resize(int new_capacity)
{
    if (new_capacity < used)
        new_capacity = used;
    if (new_capacity < 1)
        new_capacity = 1;
    capacity = new_capacity;
    string *newSymptoms = new string[capacity];
    copy (symptoms, symptoms + used, newSymptoms)
    delete [] symptoms;
    symptoms = newSymptoms;
    newSymptoms = nullptr;
}
// Returns the number of symptoms the patient has
int Patient::size() const { return used; }
// Returns true if the patient has the symptom, else fasle
bool Patient::contains(string symptom) const
{
    for (int i = 0; i < used; ++i)
    {
        if(symptom == symptoms[i])
            return true;
    }
    return false;
}
// Checks if the patient already contains the symptoms.
// Checks if the symptoms[] is at capacity, if so dynamically adds 3 more
// Appends the symptom and moves the current_index to the end of the symptoms[] array
bool Patient::addSymptom(string symptom)
{
    if ( contains(symptom) == true )
        return false;
    if ( capacity == used)
        this -> resize(capacity + 3);
    
    symptoms[used] = symptom;
    used++;
    current_index++;
    return true;
}