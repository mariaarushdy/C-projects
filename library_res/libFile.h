#ifndef LIB_H
#define LIB_H

// Include necessary standard libraries or other headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Declare your struct and typedefs
typedef struct Patient {
    int id;
    char name[30];
    int age;
    int gender;
    int reserve;
    struct Patient* next;

} Patient;

typedef Patient* nodeptr;
int AdminPW;

//init

// Declare your function prototypes
nodeptr getPatient();
void slots(int x);
void ReserveSlot();
void cancleRes();
void PatientInfo(Patient* x);
void addPatient();
void ViewPatient();
void viweRes();
void EditPatient();
void deallocate();
void AdminMode();
int IsAdmin();
void UserMode();
void menu();


#define MAX_Patient 10000

#define MAX_SLOTS 5

#endif // LIB_H
