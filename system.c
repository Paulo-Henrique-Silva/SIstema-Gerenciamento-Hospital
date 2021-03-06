#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define PATIENTS_FPATH "patients.txt"
#define DOCTORS_FPATH "doctors.txt"
#define APPOINT_FPATH "appointments.txt"
#define ADM_FPATH "pwd.txt"
#define TEMP_FPATH "temp.tmp"

#define DEFAULT_PWD "2022\n"
#define MAX_PATIENTSNUM (10)
#define MAX_DOCTORSNUM (5)
#define MAX_APPOINTNUM (20)

enum menuOptions 
{
    AddAppoint_num = 1, RemoveAppoint_num, ShowAppoint_num,
    AddPatient_num, RemovePatient_num, ShowPatient_num,
    AddDoctor_num, RemoveDoctor_num, ShowDoctor_num,
    Changepwd_num, Info_num, ExitProgram_num
};

FILE *pPatients, *pDoctors, *pAppoint, *pAdm, *pTemp;

typedef struct patientsInfo
{
    char name[45], id_num[9], sex, telephone[12], age[4];
    int amountOf_appoint;
} patient;

typedef struct doctorInfo
{
    char name[45], id_num[9], age[4];
    int amountOf_appoint;
} doctor;

typedef struct appointInfo
{
    char type, date[12], time[7], patientName[45], patientId[9], doctorName[45], doctorId[9];
} appointment;

int menu(void);

void addAppoint(void);
void removeAppoint(void);
void changeAppoint(void);
void showAppoint(void);
void addPatient(void);
void removePatient(void);
void changePatient(void);
void showPatient(void);
void addDoctor(void);
void removeDoctor(void);
void changeDoctor(void);
void showDoctor(void);
void changePwd(void);
void help(void);

int login(void);
void removeExtra_chars(char *string);
int checkFile(FILE *pFile, char fPath[]);
int amountOf_lines(FILE *pFile, char fPath[]);
int isA_validId(char id[]);

int main()
{
    int operation = 0;

    do
    {
        switch(operation = menu())
        {
            case AddAppoint_num:
                addAppoint();
                break;

            case RemoveAppoint_num:
                removeAppoint();
                break;
            
            case ShowAppoint_num:
                showAppoint();
                break;
                
            case AddPatient_num:
                addPatient();
                break;

            case RemovePatient_num:
                removePatient();
                break;
            
            case ShowPatient_num:
                showPatient();
                break;

            case AddDoctor_num:
                addDoctor();
                break;

            case RemoveDoctor_num:
                removeDoctor();
                break;
            
            case ShowDoctor_num:
                showDoctor();
                break;
            
            case Changepwd_num:
                changePwd();
                break;
            
            case Info_num:
                help();
                break;
            
            case ExitProgram_num:
                printf("\nExiting...");
                break;

            default:
                printf("\nInvalid Input");
                break;
        }

        getch();
    }
    while(operation != ExitProgram_num); //shows menu options until the user types exit

    return 0;
}

//Gets the operation input as a string and returns as a integer
int menu(void)
{
    char input[1024] = {'\0'};

    system("cls");
    printf("\t\t\t       HOSPITAL MANAGEMENT SYSTEM");
    printf("\n\t\t\t--------------------------------------");

    printf("\n\n\t\t\t      [1] - Add an Appointment");
    printf("\n\t\t\t      [2] - Remove an Appointment");
    printf("\n\t\t\t      [3] - Show Appointments List");
    printf("\n\t\t\t      [4] - Add a Patient");
    printf("\n\t\t\t      [5] - Remove a Patient");
    printf("\n\t\t\t      [6] - Show Patients List");
    printf("\n\t\t\t      [7] - Add a Doctor");
    printf("\n\t\t\t      [8] - Remove a Doctor");
    printf("\n\t\t\t      [9] - Show Doctors List");
    printf("\n\t\t\t      [10] - Change Administrator Password");
    printf("\n\t\t\t      [11] - Help");
    printf("\n\t\t\t      [12] - Exit");

    printf("\n\nType the Operation: ");
    fgets(input, 1024, stdin);

    return atoi(input);
}

void addAppoint(void)
{
    appointment newAppoint;
    patient inFile_patient;
    doctor inFile_doctor;

    int lineCounter = 0, patientNum_toSelect = 0, doctorNum_toSelect = 0;
    char input[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t ADDING AN APPOINTMENT");
    printf("\n\t\t\t--------------------------------------");

    //checks the amount of Appointments in System
    //if it returns 0, there is no need to block the program, because it is adding a new one
    if(amountOf_lines(pAppoint, APPOINT_FPATH) >= MAX_APPOINTNUM)
    {
        printf("\n\nSorry, max Amount of Appointments reached (%d)!", MAX_APPOINTNUM);
        return;
    }

    if
    (
        amountOf_lines(pPatients, PATIENTS_FPATH) == 0 || 
        amountOf_lines(pDoctors, DOCTORS_FPATH) == 0
    )
    {
        printf("\n\nSorry, it needs at least 1 Patient and 1 Doctor in System to Create an Appointment.");
        return;
    }

    printf("\n\nType the Appointment Type(F - Follow Up | N - Normal): ");
    fgets(input, 1024, stdin);
    removeExtra_chars(input);

    if((newAppoint.type = toupper(input[0])) != 'F' && newAppoint.type != 'N')
    {
        printf("\nInvalid Type Input!");
        return;
    }

    printf("\nType the Appointment Date(yyyy/mm/dd): ");
    fgets(input, sizeof(newAppoint.date), stdin);
    removeExtra_chars(strcpy(newAppoint.date, input));

    for(int i = 0; i < strlen(newAppoint.date); i++)
    {
        if //checks if it has just numbers in the string
        (
            (newAppoint.date[i] - '0' < 0 || newAppoint.date[i] - '0' > 9) && 
            newAppoint.date[i] != '/'
        )
        {
            printf("\nInvalid Date!");
            return;
        }
    }

    printf("\nType the Appointment Time(hh:mm): ");
    fgets(input, sizeof(newAppoint.time), stdin);
    removeExtra_chars(strcpy(newAppoint.time, input));

    for(int i = 0; i < strlen(newAppoint.time); i++)
    {
        if 
        (
            (newAppoint.time[i] - '0' < 0 || newAppoint.time[i] - '0' > 9) && 
            newAppoint.time[i] != ':'
        )
        {
            printf("\nInvalid Time!");
            return;
        }
    }

    system("cls");
    printf("\t\t\t\t   ADDING AN APPOINTMENT");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pPatients, PATIENTS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Patient yet :/");
        return;
    }
    
    pPatients = fopen(PATIENTS_FPATH, "r");

    while //shows patient list
    (
        fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num, 
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t\t     %d - Name: %s - Id: %s", lineCounter, inFile_patient.name, 
        inFile_patient.id_num);
    }

    fclose(pPatients);

    printf("\n\nSelect the Appointment's Patient Number: ");
    fgets(input, 1024, stdin);
    
    //gets a str and converts to an integer
    if((patientNum_toSelect = atoi(input)) < 1 || patientNum_toSelect > lineCounter)
    {
        printf("\nInvalid number Input!");
        return;
    }

    system("cls");
    printf("\t\t\t\t   ADDING AN APPOINTMENT");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pDoctors, DOCTORS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Doctor yet :/");
        return;
    }

    pDoctors = fopen(DOCTORS_FPATH, "r");
    lineCounter = 0;

    while //prints doctor list
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t\t    %d - Name: %s - Id: %s", lineCounter, inFile_doctor.name, 
        inFile_doctor.id_num);
    }

    fclose(pDoctors);

    printf("\n\nType the Appointment's Doctor Number: ");
    fgets(input, 1024, stdin);
    
    //gets a str and converts to an integer
    if((doctorNum_toSelect = atoi(input)) < 1 || doctorNum_toSelect > lineCounter)
    {
        printf("\nInvalid number Input!");
        return;
    }

//update data in files
    if(checkFile(pPatients, PATIENTS_FPATH) != 1 || checkFile(pDoctors, DOCTORS_FPATH) != 1)
    {
        printf("\n\nSorry, an Error has ocurred.");
        return;
    }

    pPatients = fopen(PATIENTS_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w"); //creates a temp file to change the patients data
    lineCounter = 0;

    while 
    (
        fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num, 
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF
    )
    {
        lineCounter++;

        //if it is the same, add an appoint and gets their name and id
        if(lineCounter == patientNum_toSelect)
        {
            fprintf(pTemp, "%s %s %c %s %s %d\n", inFile_patient.name, inFile_patient.id_num, 
            inFile_patient.sex, inFile_patient.age, inFile_patient.telephone, 
            inFile_patient.amountOf_appoint + 1);

            strcpy(newAppoint.patientName, inFile_patient.name);
            strcpy(newAppoint.patientId, inFile_patient.id_num);
        }
        else //else, just prints it
        {
            fprintf(pTemp, "%s %s %c %s %s %d\n", inFile_patient.name, inFile_patient.id_num, 
            inFile_patient.sex, inFile_patient.age, inFile_patient.telephone, 
            inFile_patient.amountOf_appoint);
        }
    }

    fclose(pPatients);
    fclose(pTemp); 

    //removes the old file and renames the new one with the updated data
    remove(PATIENTS_FPATH);
    rename(TEMP_FPATH, PATIENTS_FPATH);

//same logic
    pDoctors = fopen(DOCTORS_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w"); 
    lineCounter = 0;

    while
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF
    )
    {
        lineCounter++;

        if(lineCounter == doctorNum_toSelect)
        {
            fprintf(pTemp, "%s %s %s %d\n", inFile_doctor.name, inFile_doctor.id_num,
            inFile_doctor.age, inFile_doctor.amountOf_appoint + 1);

            strcpy(newAppoint.doctorName, inFile_doctor.name);
            strcpy(newAppoint.doctorId, inFile_doctor.id_num);
        }
        else
        {
            fprintf(pTemp, "%s %s %s %d\n", inFile_doctor.name, inFile_doctor.id_num,
            inFile_doctor.age, inFile_doctor.amountOf_appoint);
        }
    }

    fclose(pDoctors);
    fclose(pTemp); 

    remove(DOCTORS_FPATH);
    rename(TEMP_FPATH, DOCTORS_FPATH);

    //add the content to file
    //how it is adding, there is no need to block the program
    checkFile(pAppoint, APPOINT_FPATH);

    pAppoint = fopen(APPOINT_FPATH, "a");
    fprintf(pAppoint, "%c %s %s %s %s %s %s\n", newAppoint.type, newAppoint.date, 
    newAppoint.time, newAppoint.patientName, newAppoint.patientId, newAppoint.doctorName,
    newAppoint.doctorId);
    fclose(pAppoint);

    printf("\nNew Appointment Successfully Added!");
}

void removeAppoint(void)
{
    appointment inFile_appoint;
    patient inFile_patient;
    doctor inFile_doctor;

    int lineCounter = 0, appointNum_toRemove = 0;
    char input[1024] = {'\0'}, lineIn_file[1024] = {'\0'}, 
    docId_toUp[9] = {'\0'}, patientId_toUp[9] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\tREMOVING AN APPOINTMENT");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pAppoint, APPOINT_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have an Appointment yet :/");
        return;
    }

    pAppoint = fopen(APPOINT_FPATH, "r");

    while //prints appointments list
    (
        fscanf(pAppoint, "%c %s %s %s %s %s %s\n", &inFile_appoint.type, &inFile_appoint.date, 
        &inFile_appoint.time, &inFile_appoint.patientName, &inFile_appoint.patientId, 
        &inFile_appoint.doctorName, &inFile_appoint.doctorId) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t%d - Type: %c - Date and Time: %s - %s - Patient: %s - Doctor: %s", 
        lineCounter, inFile_appoint.type, inFile_appoint.date, inFile_appoint.time, 
        inFile_appoint.patientName, inFile_appoint.doctorName);
    }

    fclose(pAppoint);

    printf("\n\nType the Appointment Number to remove: ");
    fgets(input, 1024, stdin);
    
    //gets a str and converts to an integer
    if((appointNum_toRemove = atoi(input)) < 1 || appointNum_toRemove > lineCounter)
    {
        printf("\nInvalid number Input!");
        return;
    }

    if
    (
        checkFile(pAppoint, APPOINT_FPATH) != 1 || checkFile(pPatients, PATIENTS_FPATH) != 1 || 
        checkFile(pDoctors, DOCTORS_FPATH) != 1
    )
    {
        printf("\nSorry, an Error has ocurred :/");
        return;
    }

    //creates a new file to replace the old one
    pAppoint = fopen(APPOINT_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w"); 
    lineCounter = 0;

    while
    (
        fscanf(pAppoint, "%c %s %s %s %s %s %s\n", &inFile_appoint.type, &inFile_appoint.date, 
        &inFile_appoint.time, &inFile_appoint.patientName, &inFile_appoint.patientId, 
        &inFile_appoint.doctorName, &inFile_appoint.doctorId) != EOF
    )
    {
        lineCounter++;
        
        //prints the content in new file without the removed appointment
        if(lineCounter != appointNum_toRemove)
        {
            fprintf(pTemp, "%c %s %s %s %s %s %s\n", inFile_appoint.type, inFile_appoint.date, 
            inFile_appoint.time, inFile_appoint.patientName, inFile_appoint.patientId, 
            inFile_appoint.doctorName, inFile_appoint.doctorId);
        }
        else //gets the ids to update later
        {
            strcpy(patientId_toUp, inFile_appoint.patientId);
            strcpy(docId_toUp, inFile_appoint.doctorId);
        }
    }

    fclose(pAppoint);
    fclose(pTemp);

    //remove the old file and rename the new one, without that appointment
    remove(APPOINT_FPATH);
    rename(TEMP_FPATH, APPOINT_FPATH);

//update patients
    pPatients = fopen(PATIENTS_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w");

    while 
    (
        fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num, 
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF
    )
    {
        //if it is the same, subtracts the removed appointment
        if(strcmp(patientId_toUp, inFile_patient.id_num) == 0)
        {
            fprintf(pTemp, "%s %s %c %s %s %d\n", inFile_patient.name, inFile_patient.id_num, 
            inFile_patient.sex, inFile_patient.age, inFile_patient.telephone, 
            inFile_patient.amountOf_appoint - 1);
        }
        else //else, just prints it
        {
            fprintf(pTemp, "%s %s %c %s %s %d\n", inFile_patient.name, inFile_patient.id_num, 
            inFile_patient.sex, inFile_patient.age, inFile_patient.telephone, 
            inFile_patient.amountOf_appoint);
        }
    }

    fclose(pPatients);
    fclose(pTemp); 

    //removes the old file and renames the new one with the updated data
    remove(PATIENTS_FPATH);
    rename(TEMP_FPATH, PATIENTS_FPATH);

//update doctors id - same logic
    pDoctors = fopen(DOCTORS_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w"); 

    while
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF
    )
    {
        if(strcmp(docId_toUp, inFile_doctor.id_num) == 0)
        {
            fprintf(pTemp, "%s %s %s %d\n", inFile_doctor.name, inFile_doctor.id_num,
            inFile_doctor.age, inFile_doctor.amountOf_appoint - 1);
        }
        else
        {
            fprintf(pTemp, "%s %s %s %d\n", inFile_doctor.name, inFile_doctor.id_num,
            inFile_doctor.age, inFile_doctor.amountOf_appoint);
        }
    }

    fclose(pDoctors);
    fclose(pTemp); 

    remove(DOCTORS_FPATH);
    rename(TEMP_FPATH, DOCTORS_FPATH);

    printf("\nAppointment Successfully Removed!");
}

void showAppoint(void)
{
    appointment inFile_appoint;
    int lineCounter = 0;

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t   APPOINTMENTS LIST");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pAppoint, APPOINT_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have an Appointment yet :/");
        return;
    }

    pAppoint = fopen(APPOINT_FPATH, "r");

    while //prints appointments list
    (
        fscanf(pAppoint, "%c %s %s %s %s %s %s\n", &inFile_appoint.type, &inFile_appoint.date, 
        &inFile_appoint.time, &inFile_appoint.patientName, &inFile_appoint.patientId, 
        &inFile_appoint.doctorName, &inFile_appoint.doctorId) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t%d - Type: %c - Date and Time: %s - %s - Patient: %s - Doctor: %s", 
        lineCounter, inFile_appoint.type, inFile_appoint.date, inFile_appoint.time, 
        inFile_appoint.patientName, inFile_appoint.doctorName);
    }

    fclose(pAppoint);

    printf("\n\nPress anything to continue.");
}

void addPatient(void)
{
    patient newPatient;
    char input[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t   ADDING A PATIENT");
    printf("\n\t\t\t--------------------------------------");

    //checks the amount of Patients in System
    if(amountOf_lines(pPatients, PATIENTS_FPATH) >= MAX_PATIENTSNUM)
    {
        printf("\n\nSorry, max Amount of Patients reached (%d)!", MAX_PATIENTSNUM);
        return;
    }

    printf("\n\nType the new Patient Name: ");
    fgets(input, sizeof(newPatient.name), stdin);
    removeExtra_chars(strcpy(newPatient.name, input));

    //puts in upper case to avoid errors and
    //Checks if it has just alphabetic characters
    strupr(newPatient.name); 
    for(int i = 0; i < strlen(newPatient.name); i++)
    {
        if((newPatient.name[i] < 'A' || newPatient.name[i] > 'Z') && newPatient.name[i] != '-')
        {
            printf("\nInvalid Name!");
            return;
        }
    }

    printf("\nType the new Patient Id Number: ");
    fgets(input, sizeof(newPatient.id_num), stdin);
    removeExtra_chars(strcpy(newPatient.id_num, input));

    //checks if it has just numbers
    // "- 0" converts to an int
    for(int i = 0; i < strlen(newPatient.id_num); i++)
    {
        if
        (
            (newPatient.id_num[i] - '0' < 0 || newPatient.id_num[i] - '0' > 9) && 
            newPatient.id_num[i] != '-'
        )
        {
            printf("\nInvalid Id!");
            return;
        }
    }

    if(isA_validId(newPatient.id_num) == 0)
    {
        printf("\nThis Id number already exist!");
        return;
    }

    printf("\nType the new Patient Sex(F - Female | M - Male): ");
    fgets(input, 1024, stdin);
    removeExtra_chars(input);

    //puts in upper case and checks the first Char
    if((newPatient.sex = toupper(input[0])) != 'F' && newPatient.sex != 'M')
    {
        printf("\nInvalid Sex Input!");
        return;
    }

    printf("\nType the new Patient Age: ");
    fgets(input, 1024, stdin);
    removeExtra_chars(input);

    //checks if it is a valid age number
    if(atoi(input) <= 0) 
    {
        printf("\nInvalid Age Input!");
        return;
    }
    strcpy(newPatient.age, input);

    printf("\nType the new Patient Telephone: ");
    fgets(input, sizeof(newPatient.telephone), stdin);
    removeExtra_chars(strcpy(newPatient.telephone, input));

    //checks it it has just number
    for(int i = 0; i < strlen(newPatient.telephone); i++)
    {
        if
        (
            (newPatient.telephone[i] - '0' < 0 || newPatient.telephone[i] - '0' > 9) && 
            newPatient.telephone[i] != '-'
        )
        {
            printf("\nInvalid Telephone Number!");
            return;
        }
    }

    //it is 0, because is a new patient
    newPatient.amountOf_appoint = 0;

    //how it is adding to file, there is no need to block the program
    checkFile(pPatients, PATIENTS_FPATH);

    pPatients = fopen(PATIENTS_FPATH, "a");
    fprintf(pPatients, "%s %s %c %s %s %d\n", newPatient.name, newPatient.id_num, newPatient.sex, 
    newPatient.age, newPatient.telephone, newPatient.amountOf_appoint);
    fclose(pPatients);

    printf("\nNew Patient Successfully Added!");
}

void removePatient(void)
{
    patient inFile_patient;
    int lineCounter = 0, patientNum_toRemove = 0;
    char input[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t  REMOVING A PATIENT");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pPatients, PATIENTS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Patient yet :/");
        return;
    }

    pPatients = fopen(PATIENTS_FPATH, "r");

    while //shows patient list
    (
        fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num, 
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t   %d - Name: %s - Age: %s - Telephone: %s - Appointments Amount: %d", 
        lineCounter, inFile_patient.name, inFile_patient.age, inFile_patient.telephone, 
        inFile_patient.amountOf_appoint);
    }

    fclose(pPatients);

    printf("\n\nType the Patient Number to remove: ");
    fgets(input, 1024, stdin);
    
    //gets a str and converts to an integer
    if((patientNum_toRemove = atoi(input)) < 1 || patientNum_toRemove > lineCounter)
    {
        printf("\nInvalid number Input!");
        return;
    }

    if(checkFile(pPatients, PATIENTS_FPATH) != 1)
    {
        printf("\nSorry, an Error has ocurred :/");
        return;
    }

    //creates a new file to replace the old one
    pPatients = fopen(PATIENTS_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w"); 
    lineCounter = 0;

    while
    (   fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num, 
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        
        //prints the content in new file without the removed patient
        if(lineCounter != patientNum_toRemove)
        {
            fprintf(pTemp, "%s %s %c %s %s %d\n", inFile_patient.name, inFile_patient.id_num, 
            inFile_patient.sex, inFile_patient.age, inFile_patient.telephone, 
            inFile_patient.amountOf_appoint);
        }
        else if(inFile_patient.amountOf_appoint > 0) //you can't remove a patient with an appoint
        {
            fclose(pPatients);
            fclose(pTemp);
            remove(TEMP_FPATH);

            printf("\nSorry, it is not possible to remove this Patient.");
            printf("\nRemove all his appointments before remove him from System.");
            return;
        }
    }

    fclose(pPatients);
    fclose(pTemp);

    //remove the old file and rename the new one, without that patient
    remove(PATIENTS_FPATH);
    rename(TEMP_FPATH, PATIENTS_FPATH);

    printf("\nPatient Successfully Removed!");
}

void showPatient(void)
{
    patient inFile_patient;
    int lineCounter = 0;

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t     PATIENTS LIST");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pPatients, PATIENTS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Patient yet :/");
        return;
    }

    pPatients = fopen(PATIENTS_FPATH, "r");

    while //reads each line in file and prints it
    (
        fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num,
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t%d - Name: %s - Age: %s - Telephone: %s - Appointments Amount: %d", 
        lineCounter, inFile_patient.name, inFile_patient.age, inFile_patient.telephone, 
        inFile_patient.amountOf_appoint);
    }

    fclose(pPatients);

    printf("\n\nPress anything to continue.");
}

void addDoctor(void)
{
    doctor newDoc;
    char input[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t   ADDING A DOCTOR");
    printf("\n\t\t\t--------------------------------------");

    //checks the amount of Doctors in System
    if(amountOf_lines(pDoctors, DOCTORS_FPATH) >= MAX_DOCTORSNUM)
    {
        printf("\n\nSorry, max Amount of Doctors reached (%d)!", MAX_DOCTORSNUM);
        return;
    }

    printf("\n\nType the new Doctor Name: ");
    fgets(input, sizeof(newDoc.name), stdin);
    removeExtra_chars(strcpy(newDoc.name, input));

    //Checks if it has just alphabetic characters
    strupr(newDoc.name); 
    for(int i = 0; i < strlen(newDoc.name); i++)
    {
        if((newDoc.name[i] < 'A' || newDoc.name[i] > 'Z') && newDoc.name[i] != '-')
        {
            printf("\nInvalid Name!");
            return;
        }
    }

    printf("\nType the new Doctor Id Number: ");
    fgets(input, sizeof(newDoc.id_num), stdin);
    removeExtra_chars(strcpy(newDoc.id_num, input));

    //checks if it has just numbers
    // "- 0" converts to an int
    for(int i = 0; i < strlen(newDoc.id_num); i++)
    {
        if
        (
            (newDoc.id_num[i] - '0' < 0 || newDoc.id_num[i] - '0' > 9) && 
            newDoc.id_num[i] != '-'
        )
        {
            printf("\nInvalid Id!");
            return;
        }
    }

    if(isA_validId(newDoc.id_num) == 0)
    {
        printf("\nThis Id number already exist!");
        return;
    }

    printf("\nType the new Doctor Age: ");
    fgets(input, 1024, stdin);
    removeExtra_chars(input);

    //checks if it is a valid age number
    if(atoi(input) <= 0) 
    {
        printf("\nInvalid Age Input!");
        return;
    }
    strcpy(newDoc.age, input);

    //it is 0, because is a new doctor
    newDoc.amountOf_appoint = 0;

    //add to file
    checkFile(pDoctors, DOCTORS_FPATH);

    pDoctors = fopen(DOCTORS_FPATH, "a");
    fprintf(pDoctors, "%s %s %s %d\n", newDoc.name, newDoc.id_num, newDoc.age, 
    newDoc.amountOf_appoint);
    fclose(pDoctors);

    printf("\nNew Doctor Successfully Added!");
}

void removeDoctor(void)
{
    doctor inFile_doctor;
    int lineCounter = 0, docNum_toRemove = 0;
    char input[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t  REMOVING A DOCTOR");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pDoctors, DOCTORS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Doctor yet :/");
        return;
    }

    pDoctors = fopen(DOCTORS_FPATH, "r");

    while //reads each line in file and prints doctor list
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t    %d - Name: %s - Age: %s - Appointments Amount: %d", 
        lineCounter, inFile_doctor.name, inFile_doctor.age, inFile_doctor.amountOf_appoint);
    }

    fclose(pDoctors);

    printf("\n\nType the Doctor Number to remove: ");
    fgets(input, 1024, stdin);
    
    //gets a str and converts to an integer
    if((docNum_toRemove = atoi(input)) < 1 || docNum_toRemove > lineCounter)
    {
        printf("\nInvalid number Input!");
        return;
    }

    if(checkFile(pDoctors, DOCTORS_FPATH) != 1)
    {
        printf("\nSorry, an Error has ocurred :/");
        return;
    }

    //creates a new file to replace the old one
    pDoctors = fopen(DOCTORS_FPATH, "r");
    pTemp = fopen(TEMP_FPATH, "w"); 
    lineCounter = 0;

    //reads the old file
    while
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        
        //prints the content in new file without the removed doctor
        if(lineCounter != docNum_toRemove)
        {
            fprintf(pTemp, "%s %s %s %d\n", inFile_doctor.name, inFile_doctor.id_num,
            inFile_doctor.age, inFile_doctor.amountOf_appoint);
        }
        else if(inFile_doctor.amountOf_appoint > 0)
        {
            fclose(pDoctors);
            fclose(pTemp);
            remove(TEMP_FPATH);

            printf("\nSorry, it is not possible to remove this Doctor.");
            printf("\nRemove all his appointments before remove him from System.");
            return;
        }
    }

    fclose(pDoctors);
    fclose(pTemp);

    //remove the old file and rename the new one, without that doctor
    remove(DOCTORS_FPATH);
    rename(TEMP_FPATH, DOCTORS_FPATH);

    printf("\nDoctor Successfully Removed!");
}

void showDoctor(void)
{
    doctor inFile_doctor;
    int lineCounter = 0;

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t     DOCTORS LIST");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pDoctors, DOCTORS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Doctor yet :/");
        return;
    }

    pDoctors = fopen(DOCTORS_FPATH, "r");

    while //reads each line in file and prints it
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t%d - Name: %s - Age: %s - Appointments Amount: %d", 
        lineCounter, inFile_doctor.name, inFile_doctor.age, inFile_doctor.amountOf_appoint);
    }

    fclose(pDoctors);

    printf("\n\nPress anything to continue.");
}

void changePwd(void)
{
    char newPwd[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t   CHANGING PASSWORD");
    printf("\n\t\t\t--------------------------------------");

    printf("\n\nType the New Adm Password: ");
    fgets(newPwd, 1024, stdin);

    pAdm = fopen(ADM_FPATH, "w");
    fprintf(pAdm, "%s", newPwd);
    fclose(pAdm);

    printf("\nPassword Updated!");
}

void help(void)
{
    system("cls");
    printf("\t\t\t\t     PROGRAM INFO");
    printf("\n\t\t\t--------------------------------------");

    printf("\n\nThis program simulates a system from a Hospital.");
    printf("\n\n - You can add and remove Doctors, Patients and Appointments to the System.");
    printf("\n\n - A Doctor or a Patient cannot be removed if they have an Appointment in Schedule.");
    printf("\n\n - To create a Medical Appointment, first it needs to add a Doctor and a Patient.");
    printf("\n\n - An Appointment can be a Follow-up appointment or a Normal appointment.");
    printf("\n\n - The MAX amount of each category in system is: ");
    printf("\n * Appointments: %d", MAX_APPOINTNUM);
    printf("\n * Doctors: %d", MAX_DOCTORSNUM);
    printf("\n * Patients: %d", MAX_PATIENTSNUM);

    printf("\n\n\nThank you for downloading - Paulo");
}

//Returns 1 if the adm password it is correct,
//else returns 0
int login(void)
{
    char input[1024] = {'\0'}, pwdIn_file[1024] = {'\0'};

    //if the file does not have a pwd, it writes the default one
    if(checkFile(pAdm, ADM_FPATH) != 1)
    {
        pAdm = fopen(ADM_FPATH, "a");
        fprintf(pAdm, "%s", DEFAULT_PWD);
        fclose(pAdm);
    }

    pAdm = fopen(ADM_FPATH, "r");
    fscanf(pAdm, "%s", &pwdIn_file);
    fclose(pAdm);

    printf("\nType the Admin Password: ");
    fgets(input, 1024, stdin);

    //removes '\n' in last char
    input[strlen(input) - 1] = '\0';

    if(strcmp(pwdIn_file, input) == 0)
        return 1;
    else 
        return 0;
}

/*
Avoids a "fgets" get extra chars from the previous one and
removes the blank spaces from the string
*/
void removeExtra_chars(char *string)
{
    //removes extra chars
    if(strchr(string, '\n') == NULL)
    {
        char extra;

        while((extra = fgetc(stdin)) != '\n' && extra != EOF);
    } 

    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == ' ')
            string[i] = '-';
    }

    //removes the '\n' in last char
    string[strlen(string) - 1] = '\0';
}

/*
Checks the file situation. Returns:
-1 - If the file does not exist and creates it
0 - if it is empty
1 - If it is filled
*/
int checkFile(FILE *pFile, char fPath[])
{
    char buffer[1024] = {'\0'}, firstLine[1024] = {'\0'};

    pFile = fopen(fPath, "r");
    fgets(buffer, 1024, pFile);
    fclose(pFile);

    if(pFile == NULL) 
    {   
        pFile = fopen(fPath, "w");
        fclose(pFile);

        return -1;
    }
    else if(strcmp(buffer, "\0") == 0)  
        return 0;
    else 
        return 1;
}

//Returns the amount of line in a file.
//It will return 0, if the file does not exist or is empty
int amountOf_lines(FILE *pFile, char fPath[])
{
    int amount = 0;
    char buffer[1024] = {'\0'};

    pFile = fopen(fPath, "r");
    while(fgets(buffer, 1024, pFile) != NULL)
        amount++;
    fclose(pFile);

    return amount;
}

/*
Returns 1, if the id is valid, otherwise will return 0. 
- Doctors and Patients have ids.
- A Doctor cannot have a same id of a Patient and vice-versa

Checks the files before use it
*/
int isA_validId(char id[])
{
    doctor inFile_doctor;
    patient inFile_patient;

    pDoctors = fopen(DOCTORS_FPATH, "r");
    pPatients = fopen(PATIENTS_FPATH, "r");

    while //reads the files
    (
        fscanf(pDoctors, "%s %s %s %d\n", &inFile_doctor.name, &inFile_doctor.id_num,
        &inFile_doctor.age, &inFile_doctor.amountOf_appoint) != EOF &&
        
        fscanf(pPatients, "%s %s %c %s %s %d\n", &inFile_patient.name, &inFile_patient.id_num, 
        &inFile_patient.sex, &inFile_patient.age, &inFile_patient.telephone, 
        &inFile_patient.amountOf_appoint) != EOF 
    )
    {
        if(strcmp(inFile_doctor.id_num, id) == 0 || strcmp(inFile_patient.id_num, id) == 0)
        {
            fclose(pDoctors);
            fclose(pPatients);
            return 0;
        }
    }

    fclose(pDoctors);
    fclose(pPatients);
    return 1;
}