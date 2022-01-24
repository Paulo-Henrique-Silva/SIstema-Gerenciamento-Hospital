#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum menuOptions 
{
    AddAppoint_num = 1, RemoveAppoint_num, ChangeAppoint_num,
    AddPatient_num, RemovePatient_num, ChangePatient_num,
    AddDoctor_num, RemoveDoctor_num, ChangeDoctor_num, 
    Info_num, ExitProgram_num
};

int menu(void);

void addAppoint(void);
void removeAppoint(void);
void changeAppoint(void);
void addPatient(void);
void removePatient(void);
void changePatient(void);
void addDoctor(void);
void removeDoctor(void);
void changeDoctor(void);
void help(void);

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
                
            case AddPatient_num:
                addPatient();
                break;

            case RemovePatient_num:
                removePatient();
                break;

            case ChangePatient_num:
                changePatient();
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
    }
    while(operation != ExitProgram_num); //shows menu options until the user types exit

    getch();
    return 0;
}

//Gets the operation input as a string and returns as a integer
int menu(void)
{
    char input[1024] = {'\0'};

    system("cls");
    printf("\t\t\t\tHOSPITAL MANAGEMENT SYSTEM");

    printf("\n\n\t\t\t\t[1] - Add an Appointment");
    printf("\n\t\t\t\t[2] - Remove an Appointment");
    printf("\n\t\t\t\t[3] - Change an Appointment data");
    printf("\n\t\t\t\t[4] - Add a Patient");
    printf("\n\t\t\t\t[5] - Remove a Patient");
    printf("\n\t\t\t\t[6] - Change a Patient data");
    printf("\n\t\t\t\t[7] - Add a Doctor");
    printf("\n\t\t\t\t[8] - Remove a Doctor");
    printf("\n\t\t\t\t[9] - Change a Doctor data");
    printf("\n\t\t\t\t[10] - Help");
    printf("\n\t\t\t\t[11] - Exit");

    printf("\n\nType the Opeeration: ");
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
void addPatient(void)
{

}
void removePatient(void)
{

}
void changePatient(void)
{

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
void help(void)
{

}