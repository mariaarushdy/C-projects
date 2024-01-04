#include "libFile.h" // Including the header file

// Initializing variables

int arrOfids[MAX_Patient]; // Array to hold removed Patient IDs

int ReservationArr[MAX_SLOTS];
 AdminPW = 1234;
// Struct and typedef definition from the header file
typedef Patient *nodeptr;
nodeptr root = NULL; // Root of the linked list
int id_cnt = 0; // Counter for generating Patient IDs
nodeptr getPatient(){
    int x;
    printf("please enter the Patient id to edit it : ");
    scanf("%d", &x);
    if (root == NULL) return NULL;
    if(!arrOfids[x]) {
        printf("invalid id\n");
        return NULL;
    }
    nodeptr cur = root;
    while (cur != NULL) {
        if (cur->id == x) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
// slots
void slots(int x){
     switch(x){
        case 0 : printf("2pm to 2:30pm");break;
        case 1 : printf("2:30pm to 3pm");break;
        case 2 : printf("3pm to 3:30pm");break;
        case 3 : printf("4pm to 4:30pm");break;
        case 4 : printf("4:30pm to 5pm");break;
    }
}
//reserve slot for a patient
void ReserveSlot() {
    nodeptr cur = getPatient();

    // Check if the patient has already reserved a slot
    if (cur->reserve >=0 && cur->reserve <MAX_SLOTS) {
        printf("Patient with ID %d has already reserved a slot (Slot %d).\n", cur->id, cur->reserve + 1);
        return;
    }

    int x;
    printf("Enter the slot number you want to reserve (1 to %d): ", MAX_SLOTS);
    scanf("%d", &x);

    while (x < 1 || x > MAX_SLOTS || ReservationArr[x - 1] == 1) {
        if (x < 1 || x > MAX_SLOTS) {
            printf("Invalid slot number. Please enter a number between 1 and %d: ", MAX_SLOTS);
        } else {
            printf("Slot already reserved. Please pick another: ");
        }
        scanf("%d", &x);
    }

    cur->reserve = x - 1;
    ReservationArr[x - 1] = 1;
    printf("Slot %d reserved successfully for patient with ID %d.\n", x, cur->id);
}


// cancel reservation
void cancleRes(){
    nodeptr cur = getPatient();
    ReservationArr[cur->reserve] = 0;
    cur->reserve = -1;
}
// Function to input Patient information
void PatientInfo(Patient* x) {
    printf("please enter Patient name : ");
    scanf("%s", x->name);
    printf("please enter Patient age : ");
    scanf("%d", &x->age);
    printf("please enter Patient gender 1 if female 0 of male: ");
    scanf("%d", &x->gender);
    while(x->gender !=1 && x->gender != 0){
        printf("\n1 if female 0 of male: ");
        scanf("%d", &x->gender);
    }
    printf("please enter patient id between 0 and 1e5-1 : ");
    int y; scanf("%d",&y);
    while(arrOfids[y]){
        printf("invalid id number\n");
        scanf("%d",&y);
    }
    arrOfids[y] = 1;
    x->id = y;
}

// Function to add a Patient to the Clinic
void addPatient() {
    Patient *newPatient = (Patient *)malloc(sizeof(Patient));
    if (newPatient == NULL) {
        printf("memory allocation error\n");
        return;
    }
    newPatient->next = NULL;
    PatientInfo(newPatient); // Input Patient information
    if (root == NULL) {
        root = newPatient;
    } else {
        nodeptr end = root;
        while (end->next != NULL) {
            end = end->next;
        }
        end->next = newPatient;
    }
}


// Function to display Patients in the Clinic
void ViewPatient() {
    nodeptr cur = getPatient();
    printf("--------------------------------------------------------\n");
    printf("|Patient name : %s\t | Patient age : %d\t | gender : %d | Patient id : %d | ", cur->name, cur->age, cur->gender , cur->id);
    if(cur->reserve >= 0 && cur->reserve < MAX_SLOTS && ReservationArr[cur->reserve] ==1) {
        printf("Slot: ");
        slots(cur->reserve);
        printf("\n");
    }
    else printf("Patient did not pick an appointment\n");
    printf("--------------------------------------------------------\n");
}

// view reservation slots available
void viweRes() {
    nodeptr cur = root;
    while (cur != NULL) {
        if (cur->reserve >= 0 && cur->reserve < MAX_SLOTS && ReservationArr[cur->reserve] ==1) {
            slots(cur->reserve);
            printf(" - id : %d\n", cur->id);
        }
        cur = cur->next;
    }
}
// Function to edit a Patient recored
void EditPatient() {
    nodeptr cur = getPatient();
    printf("please enter Patient name : ");
    scanf("%s", cur->name);
    printf("please enter Patient age : ");
    scanf("%d", &cur->age);
    printf("please enter Patient gender 1 if female 0 of male: ");
    scanf("%d", &cur->gender);
}

// Function to deallocate memory for the linked list
void deallocate() {
    nodeptr current = root;
    while (current != NULL) {
        nodeptr next = current->next;
        free(current);
        current = next;
    }
    root = NULL;
}
//admin menu
void AdminMode(){
    while(1){
    printf("enter number \n1 - Add new patient record.\n2 - Edit patient record.\n3- Reserve a slot with the doctor.\n4 - Cancel reservation.\n5 - exit.\n ");
    int x; scanf("%d",&x);
    switch(x){
    case 1: addPatient();break;
    case 2: EditPatient();break;
    case 3: ReserveSlot();break;
    case 4: cancleRes();break;
    case 5: return;
    default : printf("invalid choice\n");
    }
    }
}
int IsAdmin(){
    printf("please enter your pw : ");
    int tryes = 3;
    int x;
    while(tryes--){
        scanf("%d",&x);
        if(x==AdminPW) return 1;
        else printf("incorrect pw %d trials left\n",tryes);
        printf("please enter your pw : ");
    }
    return 0;
}
void UserMode(){
     while(1){
    printf("enter number \n1 - View patient record\n2 - View patient reservation.  \n3 - exit.\n ");
    int x; scanf("%d",&x);
    switch(x){
    case 1: ViewPatient();break;
    case 2: viweRes();break;
    case 3: return;
    default : printf("invalid choice\n");
    }
     }
}
// init

// Function to display the menu and handle user input
void menu() {
    memset(arrOfids , 0,sizeof arrOfids);
    while (1) {
        printf("\twelcome\n1-admin mode.\n2-user mode\n3-exit.\n");
        int x;
        scanf("%d", &x);
        switch (x) {
            case 1:
                if(IsAdmin()) AdminMode();
                else exit(0);
                break;
            case 2:
                UserMode();
                break;
            case 3 : deallocate(); exit(0);
            default:
                printf("please choose number from 1 to 6");
        }
    }
}


