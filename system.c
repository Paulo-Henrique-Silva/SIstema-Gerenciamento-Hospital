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

enum menuOptions 
{
    AddAppoint_num = 1, RemoveAppoint_num, ChangeAppoint_num, ShowAppoint_num,
    AddPatient_num, RemovePatient_num, ChangePatient_num, ShowPatient_num,
    AddDoctor_num, RemoveDoctor_num, ChangeDoctor_num, ShowDoctor_num,
    Changepwd, Info_num, ExitProgram_num
};

FILE *pPatients, *pDoctors, *pAppoint, *pAdm, *pTemp;

typedef struct patientsInfo
{
    char name[45], id_num[9], sex, telephone[12], age[4];
} patient;

typedef struct doctorInfo
{
    char name[45], id_num[9], age[4];
} doctor;

typedef struct appointInfo
{
    char type[2], date[10], time[6], patientName[45], DoctorName[45];
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

            case ChangeAppoint_num:
                changeAppoint();
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

            case ChangePatient_num:
                changePatient();
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

            case ChangeDoctor_num:
                changeDoctor();
                break;
            
            case ShowDoctor_num:
                showDoctor();
                break;
            
            case Changepwd:
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
    printf("\t\t\t\tHOSPITAL MANAGEMENT SYSTEM");
    printf("\n\t\t\t--------------------------------------");

    printf("\n\n\t\t\t\t[1] - Add an Appointment");
    printf("\n\t\t\t\t[2] - Remove an Appointment");
    printf("\n\t\t\t\t[3] - Change an Appointment data");
    printf("\n\t\t\t\t[4] - Show Appointments List");
    printf("\n\t\t\t\t[5] - Add a Patient");
    printf("\n\t\t\t\t[6] - Remove a Patient");
    printf("\n\t\t\t\t[7] - Change a Patient data");
    printf("\n\t\t\t\t[8] - Show Patients List");
    printf("\n\t\t\t\t[9] - Add a Doctor");
    printf("\n\t\t\t\t[10] - Remove a Doctor");
    printf("\n\t\t\t\t[11] - Change a Doctor data");
    printf("\n\t\t\t\t[12] - Show Doctors List");
    printf("\n\t\t\t\t[13] - Change Administrator Password");
    printf("\n\t\t\t\t[14] - Help");
    printf("\n\t\t\t\t[15] - Exit");

    printf("\n\nType the Operation: ");
    fgets(input, 1024, stdin);

    return atoi(input);
}

void addAppoint(void)
{

}

void removeAppoint(void)
{

}

void changeAppoint(void)
{

}

void showAppoint(void)
{

}

void addPatient(void)
{
    char input[1024] = {'\0'};
    patient new;

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t   ADDING A PATIENT");
    printf("\n\t\t\t--------------------------------------");

    printf("\n\nType the new Patient Name: ");
    fgets(input, sizeof(new.name), stdin);
    removeExtra_chars(strcpy(new.name, input));

    //puts in upper case to avoid errors and
    //Checks if it has just alphabetic characters
    strupr(new.name); 
    for(int i = 0; i < strlen(new.name); i++)
    {
        if((new.name[i] < 'A' || new.name[i] > 'Z') && new.name[i] != '-')
        {
            printf("\nInvalid Name!");
            return;
        }
    }

    printf("\nType the new Patient Id: ");
    fgets(input, sizeof(new.id_num), stdin);
    removeExtra_chars(strcpy(new.id_num, input));

    //checks if it has just numbers
    // "- 0" converts to an int
    for(int i = 0; i < strlen(new.id_num); i++)
    {
        if((new.id_num[i] - '0' < 0 || new.id_num[i] - '0' > 9) && new.id_num[i] != '-')
        {
            printf("\nInvalid Id!");
            return;
        }
    }

    printf("\nType the new Patient Sex(F - Female | M - Male): ");
    fgets(input, 1024, stdin);
    removeExtra_chars(input);
    if((new.sex = toupper(input[0])) != 'F' && new.sex != 'M')
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
    strcpy(new.age, input);

    printf("\nType the new Patient Telephone: ");
    fgets(input, sizeof(new.telephone), stdin);
    removeExtra_chars(strcpy(new.telephone, input));

    //checks it it has just number
    for(int i = 0; i < strlen(new.telephone); i++)
    {
        if((new.telephone[i] - '0' < 0 || new.telephone[i] - '0' > 9) && new.telephone[i] != '-')
        {
            printf("\nInvalid Telephone Number!");
            return;
        }
    }

    //how it is adding to file, there is no need to block the program
    checkFile(pPatients, PATIENTS_FPATH);

    pPatients = fopen(PATIENTS_FPATH, "a");
    fprintf(pPatients, "%s %s %c %s %s\n", new.name, new.id_num, new.sex, 
    new.age, new.telephone);
    fclose(pPatients);

    printf("\nNew Patient Successfully Added!");
}

void removePatient(void)
{
    patient inFile;
    int lineCounter = 0, patientNum_toRemove = 0;
    char input[1024] = {'\0'};

    if(login() == 0)
    {
        printf("\nIncorrect Password!");
        return;
    }

    system("cls");
    printf("\t\t\t\t    REMOVING A PATIENT");
    printf("\n\t\t\t--------------------------------------");

    if(checkFile(pPatients, PATIENTS_FPATH) != 1)
    {
        printf("\n\nSorry, it seems it does not have a Patient yet :/");
        return;
    }

    pPatients = fopen(PATIENTS_FPATH, "r");

    while //shows patient list
    (
        fscanf(pPatients, "%s %s %c %s %s\n", &inFile.name, &inFile.id_num, &inFile.sex, 
        &inFile.age, &inFile.telephone) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t    %d - Name: %s - Age: %s - Telephone: %s", lineCounter, inFile.name, 
        inFile.age, inFile.telephone);
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

    while //reads the old file
    (
        fscanf(pPatients, "%s %s %c %s %s\n", &inFile.name, &inFile.id_num, &inFile.sex, 
        &inFile.age, &inFile.telephone) != EOF
    )
    {
        lineCounter++;
        
        //prints the content in new file without the removed patient
        if(lineCounter != patientNum_toRemove)
        {
            fprintf(pTemp, "%s %s %c %s %s\n", inFile.name, inFile.id_num, inFile.sex, 
            inFile.age, inFile.telephone);
        }
    }

    fclose(pPatients);
    fclose(pTemp);

    //remove the old file and rename the new one, without that patient
    remove(PATIENTS_FPATH);
    rename(TEMP_FPATH, PATIENTS_FPATH);

    printf("\nPatient Successfully Removed!");
}

void changePatient(void)
{

}

void showPatient(void)
{
    int lineCounter = 0;
    patient inFile;

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
        fscanf(pPatients, "%s %s %c %s %s\n", &inFile.name, &inFile.id_num, &inFile.sex, 
        &inFile.age, &inFile.telephone) != EOF
    )
    {
        lineCounter++;
        printf("\n\n\t\t    %d - Name: %s - Age: %s - Telephone: %s", lineCounter, inFile.name, 
        inFile.age, inFile.telephone);
    }

    fclose(pPatients);

    printf("\n\nPress anything to continue.");
}

void addDoctor(void)
{

}

void removeDoctor(void)
{

}

void changeDoctor(void)
{

}

void showDoctor(void)
{
    
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