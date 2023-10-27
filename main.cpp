/*Welcome to AVBIL hospital manager's source code*/
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include "./schema/date.h"
#include <random>

using namespace std;

class MedicalHistory
{ // Class used for Patient's Medical history
    char smokerStatus;
    char drugUsage;
    char disabilityStatus;
    char geneticIllness;
    char attendanceStatus;
    char intakeStatus;
    char symptoms[100];

public:
    void getHistory();
    void giveHistory();
    void init()
    { // Function used to initialize values if chart not entered
        smokerStatus = '\0';
        drugUsage = '\0';
        disabilityStatus = '\0';
        geneticIllness = '\0';
        attendanceStatus = '\0';
        intakeStatus = '\0';
        symptoms[0] = '\0';
    }
    char getGenetic() { return geneticIllness; }
    char getSmoke() { return smokerStatus; }
};
class Patient
{
    /*Main class of this program
      has a object of MedicalHistory
      Used for Patient's basic information*/
    char name[50];
    char phoneNumber[20];
    char age[4];
    char gender;
    char address[70];
    time_t registrationTime;
    time_t appointmentTime;
    int month;
    int day;
    int hour;
    int minute;
    int year;
    tm *registrationTimePointer;
    tm *appointmentTimePointer;
    char bookingTime[100];
    char visitingTime[100];
    char visitingDay[20];
    MedicalHistory medicalHistory;

public:
    void showError()
    {
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
    }
    MedicalHistory getMedicalHistory()
    {
        return medicalHistory;
    }
    void initialize()
    {
        medicalHistory.init();
    }
    void history()
    {
        medicalHistory.getHistory();
    }
    void displayMedicalHistory()
    {
        medicalHistory.giveHistory();
    }
    void setAppointmentTime();
    void enterPatientDetails();
    void displayPatientDetails();
    tm *getVisitObject() { return appointmentTimePointer; }
    char *getVisitingTime() { return visitingTime; }
    char *getVisitingDay() { return visitingDay; }
    char *getBookingTime() { return bookingTime; }
    char *getName() { return name; }
    char *getPhoneNumber() { return phoneNumber; }
    char *getAge() { return age; }
    char getGender() { return gender; }
    char *getAddress() { return address; }
    int getMonth() { return month; }
    int getDay() { return day; }
    int getHour() { return hour; }
    int getMinute() { return minute; }
    int getYear() { return year; }
};
void Patient::enterPatientDetails()
{ // Membered function used to enter Patient's details
    setAppointmentTime();
    int len;
    long temp(0);
    int check = 0;
    char *placeHolderPointer = NULL;
lb8:
    for (int j = 1; j <= 22; j++)
        cout << ' ';
    cout << "Welcome to Patient registration" << endl;
    cout << "Enter the name of the patient\n";
    cin.ignore();
    if (check >= 2)
        puts(name);
    else
        cin.getline(name, sizeof(name));
    if (!strlen(name))
    {
        cout << "Invalid input for name";
        showError();
        check = 1;
        // system("cls");
        goto lb8;
    }
    for (int i = 0; i < strlen(name); i++)
    {
        if (!(isalpha(name[i])) && !(name[i] == ' '))
        {
            cout << "Invalid input for name";
            showError();
            check = 1;
            // system("cls");
            goto lb8;
        }
    }
    cout << "Enter the age of the patient(<200)" << endl;
    cin.sync();
    if (check >= 3)
        puts(age);
    else
        cin.getline(age, sizeof(age));
    if ((strlen(age) >= 3 && age[0] >= '2') || (!strlen(age)))
        goto lb11;
    temp = strtol(age, &placeHolderPointer, 10);
    if (*placeHolderPointer)
    {
    lb11:
        cout << "Invalid input for age";
        showError();
        // system("cls");
        check = 2;
        goto lb8;
    }
    cout << "Enter the gender of the patient (M/F/O)" << endl;
    if (check >= 4)
        cout << gender << endl;
    else
        cin >> gender;
    if (!(gender == 'm' || gender == 'M' || gender == 'f' || gender == 'F' || gender == 'o' || gender == 'O'))
    {
        cout << "Invalid input for gender";
        showError();
        // system("cls");
        check = 3;
        goto lb8;
    }
    cout << "Enter the phone number of patient(<10>)\n";
    cin.ignore();
    if (check >= 5)
        puts(phoneNumber);
    else
        cin.getline(phoneNumber, sizeof(phoneNumber));
    if (!(strlen(phoneNumber) == 10) || (!strlen(phoneNumber)))
        goto lb9;
    temp = strtol(phoneNumber, &placeHolderPointer, 10);
    if (*placeHolderPointer)
    {
    lb9:
        cout << "Invalid input for phoneNumber";
        showError();
        // system("cls");
        check = 4;
        goto lb8;
    }
    cout << "Enter the address of the patient\n";
    cin.sync();
    cin.getline(address, sizeof(address));
}
void Patient ::setAppointmentTime()
{
    srand(time(0));
    char weekday[7][20] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    time(&registrationTime);
    time(&appointmentTime);
    appointmentTimePointer = localtime(&appointmentTime);
    registrationTimePointer = localtime(&registrationTime);
    if (registrationTimePointer->tm_hour > 12)
    {
        strftime(bookingTime, 100, "Date and time of registration : %d %B %Y %I:%M PM", registrationTimePointer);
    }
    else
        strftime(bookingTime, 100, "Date and time of registration : %d %B %Y %I:%M AM", registrationTimePointer);
    appointmentTimePointer->tm_year = registrationTimePointer->tm_year;
    appointmentTimePointer->tm_mday = registrationTimePointer->tm_mday;
    appointmentTimePointer->tm_mon = registrationTimePointer->tm_mon;
    appointmentTimePointer->tm_mday += (rand() % (7)) + 1;
    if (appointmentTimePointer->tm_mon == 1)
    {
        if (appointmentTimePointer->tm_mday > 28)
        {
            appointmentTimePointer->tm_mon++;
            appointmentTimePointer->tm_mday -= 28;
        }
    }
    else if (appointmentTimePointer->tm_mon == 5 || appointmentTimePointer->tm_mon == 3 || appointmentTimePointer->tm_mon == 8 || appointmentTimePointer->tm_mon == 10)
    {
        if (appointmentTimePointer->tm_mday > 30)
        {
            appointmentTimePointer->tm_mon++;
            appointmentTimePointer->tm_mday -= 30;
        }
    }
    else if (appointmentTimePointer->tm_mon == 0 || appointmentTimePointer->tm_mon == 2 || appointmentTimePointer->tm_mon == 4 || appointmentTimePointer->tm_mon == 6 || appointmentTimePointer->tm_mon == 7 || appointmentTimePointer->tm_mon == 9 || appointmentTimePointer->tm_mon == 11)
    {
        if (appointmentTimePointer->tm_mday > 31)
        {
            appointmentTimePointer->tm_mon++;
            appointmentTimePointer->tm_mday -= 31;
        }
    }
    if (appointmentTimePointer->tm_mon > 11)
    {
        appointmentTimePointer->tm_mon -= 12;
        appointmentTimePointer->tm_year++;
    }
    appointmentTimePointer->tm_hour = (rand() % (20 - 10 + 1)) + 10;
    appointmentTimePointer->tm_min = (rand() % (61));
    if (appointmentTimePointer->tm_hour > 13)
    {
        strftime(visitingTime, 100, "Time of appointment           : %d %B %I:%M PM ", appointmentTimePointer);
    }
    else
        strftime(visitingTime, 100, "Time of appointment           : %d %B %I:%M AM ", appointmentTimePointer);
    mktime(appointmentTimePointer);
    strcpy(visitingDay, weekday[appointmentTimePointer->tm_wday]);
    month = appointmentTimePointer->tm_mon;
    day = appointmentTimePointer->tm_mday;
    hour = appointmentTimePointer->tm_hour;
    minute = appointmentTimePointer->tm_min;
    year = appointmentTimePointer->tm_year;
}
void MedicalHistory ::getHistory()
{ // Function to enter Medical history of the patient
    int check(0);
lb10:
    cout << "Enter the observed symptoms" << endl;
    cin.sync();
    if (check >= 2)
        puts(symptoms);
    else
        cin.getline(symptoms, sizeof(symptoms));
    cout << endl;
    for (int i = 1; i <= 13; i++)
        cout << ' ';
    cout << "The following has to be Answered in Y(Yes) or N(no)Only\n\n";
    cout << "Has the Patient taken drugs in any point in his/her's life?(Y/N)\n(excluding prescribed medicinal drugs)" << endl;
    if (check >= 3)
        cout << drugUsage << endl;
    else
        cin >> drugUsage;
    if (!(drugUsage == 'y' || drugUsage == 'Y' || drugUsage == 'n' || drugUsage == 'N'))
    {
        cout << "Invalid input";
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
        // system("cls");
        check = 2;
        goto lb10;
    }
    cout << "Does the Patient smokes or vape?(Y/N)" << endl;
    if (check >= 4)
        cout << smokerStatus << endl;
    else
        cin >> smokerStatus;
    if (!(smokerStatus == 'y' || smokerStatus == 'Y' || smokerStatus == 'n' || smokerStatus == 'N'))
    {
        cout << "Invalid input";
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
        // system("cls");
        check = 3;
        goto lb10;
    }
    cout << "Does the patient suffer from any genetic illness?(Y/N)" << endl;
    if (check >= 5)
        cout << geneticIllness << endl;
    else
        cin >> geneticIllness;
    if (!(geneticIllness == 'y' || geneticIllness == 'Y' || geneticIllness == 'n' || geneticIllness == 'N'))
    {
        cout << "Invalid input";
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
        // system("cls");
        check = 4;
        goto lb10;
    }
    cout << "Is this the first time of the Patient's checkup here?(Y/N)" << endl;
    if (check >= 6)
        cout << attendanceStatus << endl;
    else
        cin >> attendanceStatus;
    if (!(attendanceStatus == 'y' || attendanceStatus == 'Y' || attendanceStatus == 'n' || attendanceStatus == 'N'))
    {
        cout << "Invalid input";
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
        // system("cls");
        check = 5;
        goto lb10;
    }
    cout << "Does the Patient suffer from any physical disability or ADHD?(Y/N)" << endl;
    if (check >= 7)
        cout << disabilityStatus << endl;
    else
        cin >> disabilityStatus;
    if (!(disabilityStatus == 'y' || disabilityStatus == 'Y' || disabilityStatus == 'n' || disabilityStatus == 'N'))
    {
        cout << "Invalid input";
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
        // system("cls");
        check = 6;
        goto lb10;
    }
    // system("cls");
}
void MedicalHistory ::giveHistory()
{ // Function to display Medical history
    cout << "Taken Drugs         : ";
    if (drugUsage == 'y' || drugUsage == 'Y')
        cout << "Yes\n";
    else if (drugUsage == 'n' || drugUsage == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Smokes/Vapes        : ";
    if (smokerStatus == 'y' || smokerStatus == 'Y')
        cout << "Yes\n";
    else if (smokerStatus == 'n' || smokerStatus == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Genetic illness     : ";
    if (geneticIllness == 'y' || geneticIllness == 'Y')
        cout << "Yes\n";
    else if (geneticIllness == 'n' || geneticIllness == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "First time of visit : ";
    if (attendanceStatus == 'y' || attendanceStatus == 'Y')
        cout << "Yes\n";
    else if (attendanceStatus == 'n' || attendanceStatus == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Disability/ADHD     : ";
    if (disabilityStatus == 'y' || disabilityStatus == 'Y')
        cout << "Yes\n";
    else if (disabilityStatus == 'n' || disabilityStatus == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Symptoms\n";
    if (symptoms[0] == '\0')
        cout << "N/A";
    else
        puts(symptoms);
}
void tophead()
{ // Function for Header of Program
    int i;
    for (i = 1; i <= 80; i++)
        cout << '-';
    cout << endl;
    for (i = 0; i <= 20; i++)
        cout << ' ';
    cout << "AVBIL Hospital Database Management System";
    cout << endl
         << endl;
    for (i = 1; i <= 80; i++)
        cout << '-';
    return;
}
void Patient::displayPatientDetails()
{ // Function to display basic details of the patient
    cout << "Name of the Patient : " << getName();
    cout << endl
         << "Age of the Patient  : " << getAge();
    cout << endl
         << "Phone number        : +91" << getPhoneNumber();
    if (getGender() == 'm' || getGender() == 'M')
        cout << endl
             << "Gender\t\t    : Male";
    else if (getGender() == 'f' || getGender() == 'F')
        cout << endl
             << "Gender\t\t    : Female";
    else if (getGender() == 'o' || getGender() == 'O')
        cout << endl
             << "Gender\t\t    : Other";
    cout << endl
         << "Patient's Address   : " << getAddress();
}
void searchPatientByName(Patient &patient, fstream &file, char &c)
{ // Function to Search patient by name
    char key[50];
    // system("cls");
    cout << "Enter the name of the Patient" << endl;
    int check(0);
    cin.sync();
    cin.getline(key, sizeof(key));
    file.seekg(0);
    while (file.read((char *)&patient, sizeof(patient)))
    {
        if (strcmp(patient.getName(), key) == 0)
        {
            check = 1;
            break;
        }
    }
    // system("cls");
    if (check)
    {
        cout << "Record found\n";
        if (c == 't')
        {
            cout << endl;
            cout << "Name of the Patient           : " << patient.getName();
            cout << endl;
            cout << patient.getBookingTime();
            c = 'y';
            return;
        }
        patient.displayPatientDetails();
        return;
    }
    else
    {
        cout << "Record Not found";
        c = 'n';
        return;
    }
}
int menu()
{ // Function to display and select among the available options
    char x;
    cout << "Choose an Operation" << endl;
    cout << "1-Enter a new Patient" << endl;
    cout << "2-Patient detail" << endl;
    cout << "3-Statistical Search Inquiries" << endl;
    cout << "4-Appointment status" << endl;
    cout << "5-Delete all Entries" << endl;
    cout << "0-Exit Program" << endl;
    cout << "Input : ";
    cin >> x;
    if (!(x <= '5' || x == '0'))
    {
        cout << "Invalid input";
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
        // system("cls");
        return -9;
    }
    // system("cls");
    return x;
}
int yesNoCheck(char &check)
{
    if (check == 'y' || check == 'Y' || check == 'n' || check == 'N')
        return 1;
    if (!(check == 'y' || check == 'Y' || check == 'n' || check == 'N'))
        return 0;
}
void displayError()
{
    cout << "Invalid input";
    cout << "\nPress Enter to continue";
    cin.sync();
    cin.ignore();
    return;
}
int main()
{
    char answer;
    int invalidCheck;
    time_t currentTime;
    tm *currentTimePointer;
    char formattedCurrentTime[100];
    char check;
    fstream file;
    Patient patientObject;
lb:
    tophead();
    answer = menu();
    if (answer == -9)
        goto lb;
    switch (answer)
    {
    case '1':
        char ch;
        do
        {
            patientObject.initialize();
            // system("cls");
            file.open("Patient.dat", ios ::in | ios ::app | ios ::out);
            patientObject.enterPatientDetails();
        lb2:
            cout << "Do you want to fill the Medical chart?(Y/N)" << endl;
            cin >> ch;
            invalidCheck = yesNoCheck(ch);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                goto lb2;
            }
            if (ch == 'y' || ch == 'Y')
            {
                // system("cls");
                patientObject.history();
            }
            file.write((char *)&patientObject, sizeof(patientObject));
        // system("cls");
        lb3:
            cout << "Want to Enter another Patient?(Y/N)" << endl;
            cin >> ch;
            invalidCheck = yesNoCheck(ch);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                goto lb3;
            }
            file.close();
        } while (ch == 'y' || ch == 'Y');
        // system("cls");
        goto lb;
    case '2':
        check = '\0';
        file.open("Patient.dat", ios::in);
        searchPatientByName(patientObject, file, check);
        if (!(check == 'n'))
        {
        lb4:
            cout << "\nWant to display the Medical chart too?(Y/N)\nInput : ";
            char flag;
            cin >> flag;
            invalidCheck = yesNoCheck(flag);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                cout << "Record Found\n";
                patientObject.displayPatientDetails();
                goto lb4;
            }
            if (flag == 'n' || flag == 'N')
            {
                // system("cls");
                file.close();
                goto lb;
            }
            else if (flag == 'y' || flag == 'Y')
            {
                // system("cls");
                cout << "Record Found\n";
                patientObject.displayPatientDetails();
                cout << "\n\n";
                patientObject.displayMedicalHistory();
                file.close();
            }
        }
    lb5:
        cout << endl
             << "Enter 0 for menu\n";
        cin >> ch;
        if (ch == '0')
        {
            // system("cls");
            file.close();
            goto lb;
        }
        else
        {
            displayError();
            // system("cls");
            cout << "Record Found\n";
            patientObject.displayPatientDetails();
            cout << "\n\n";
            patientObject.displayMedicalHistory();
            goto lb5;
        }
    case '4':
        check = 't';
        file.open("Patient.dat", ios::in);
        searchPatientByName(patientObject, file, check);
        if (check == 'y')
        {
            time(&currentTime);
            currentTimePointer = localtime(&currentTime);
            if (currentTimePointer->tm_hour > 13)
            {
                strftime(formattedCurrentTime, 100, "Current date and time         : %d %B %Y %I:%M PM", currentTimePointer);
            }
            else
                strftime(formattedCurrentTime, 100, "Current date and time         : %d %B %Y %I:%M AM", currentTimePointer);
            cout << endl
                 << formattedCurrentTime;
            cout << endl
                 << patientObject.getVisitingTime() << "at " << patientObject.getVisitingDay();
            int status = 0;
            if ((currentTimePointer->tm_mon) < (patientObject.getMonth()))
            {
                status = 1;
            }
            else if ((currentTimePointer->tm_mon) == (patientObject.getMonth()))
            {
                if ((currentTimePointer->tm_mday) < (patientObject.getDay()))
                {
                    status = 1;
                }
                else if ((currentTimePointer->tm_mday) == (patientObject.getDay()))
                {
                    if ((currentTimePointer->tm_hour) < (patientObject.getHour()))
                    {
                        status = 1;
                    }
                    else if ((currentTimePointer->tm_hour) == (patientObject.getHour()))
                    {
                        if ((currentTimePointer->tm_min) <= (patientObject.getMinute()))
                        {
                            status = 1;
                        }
                    }
                }
            }
            if (status)
            {
                cout << endl
                     << "Appointment Status            : In time";
            }
            else if (!status)
                cout << endl
                     << "Appointment Status            : Overdue";
        }
        cout << endl
             << "Enter 0 for menu\n";
        cin >> ch;
        if (ch == '0')
        {
            // system("cls");
            file.close();
            goto lb;
        }
    case '5':
    lb6:
        cout << "Are you sure you want to erase all the Entries?(Y/N)\n";
        cin >> ch;
        invalidCheck = yesNoCheck(ch);
        if (!invalidCheck)
        {
            displayError();
            // system("cls");
            goto lb6;
        }
        if (ch == 'y' || ch == 'Y')
        {
            remove("Patient.dat");
            // system("cls");
            cout << "All entries deleted!!!";
            cout << endl
                 << "Enter 0 for menu\n";
            cin >> ch;
            // system("cls");
            if (ch == '0')
            {
                goto lb;
            }
        }
        else
        {
            // system("cls");
            goto lb;
        }
    case '3':
        char choice;
        do
        {
            int checkAge(char *, char *, char *);
            int checkGender(char, char);
            int checkGeneticIllness(char, char);
            int checkSmokerStatus(char, char);
            int checkDate(date, date, date);
            ostringstream a, b, c;
            char check[5];
            long temp;
            char *placeHolderPointer;
            int i;
            for (i = 0; i < 5; i++)
                check[i] = '\0';
            int flag[11], counting = 0;
            for (i = 0; i < 11; i++)
                flag[i] = 0;
            char minimumAge[4], maximumAge[4];
            char geneticIll;
            char smoke;
            char sex;
            date dateUpperBound, dateLowerBound, appointmentDate;
        lb7:
            cout << "Number of patients will be displayed on the basis of the attributes selected" << endl;
            cout << "Select which attributes to include (Y/N) and enter further details if asked" << endl;
            cout << "\nInclude age? : ";
            if (flag[5] >= 2 || flag[6] >= 2)
                cout << check[0] << endl;
            else
                cin >> check[0];
            invalidCheck = yesNoCheck(check[0]);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                flag[5] = 1;
                goto lb7;
            }
            if (check[0] == 'y' || check[0] == 'Y')
            {
                placeHolderPointer = NULL;
                cin.sync();
                cout << "   ->Enter lower bound(<200) : ";
                if (flag[6] >= 3)
                    puts(minimumAge);
                else
                    cin.getline(minimumAge, sizeof(minimumAge));
                if (strlen(minimumAge) >= 3 && minimumAge[0] >= '2' || (!strlen(minimumAge)))
                    goto lb13;
                temp = strtol(minimumAge, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb13:
                    displayError();
                    // system("cls");
                    flag[6] = 2;
                    goto lb7;
                }
                cin.sync();
                cout << "   ->Enter upper bound(<200) : ";
                if (flag[6] >= 4)
                    puts(maximumAge);
                else
                    cin.getline(maximumAge, sizeof(maximumAge));
                if (strlen(maximumAge) >= 3 && maximumAge[0] >= '2' || (!strlen(maximumAge)))
                    goto lb12;
                temp = strtol(maximumAge, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb12:
                    displayError();
                    // system("cls");
                    flag[6] = 3;
                    goto lb7;
                }
                cout << endl;
            }
            flag[6] = 500;
            cout << "Include gender? : ";
            if (flag[5] >= 3 || flag[7] >= 2)
                cout << check[1] << endl;
            else
                cin >> check[1];
            invalidCheck = yesNoCheck(check[1]);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                flag[5] = 2;
                goto lb7;
            }
            if (check[1] == 'y' || check[1] == 'Y')
            {
                cout << "   ->Enter gender(M/F/O) : ";
                if (flag[7] >= 3)
                    cout << sex << endl;
                else
                    cin >> sex;
                if (!(sex == 'm' || sex == 'M' || sex == 'f' || sex == 'F' || sex == 'o' || sex == 'O'))
                {
                    displayError();
                    // system("cls");
                    flag[7] = 2;
                    goto lb7;
                }
                cout << endl;
            }
            flag[7] = 500;
            cout << "Include genetic illness criteria? : ";
            if (flag[5] >= 4 || flag[8] >= 2)
                cout << check[2] << endl;
            else
                cin >> check[2];
            invalidCheck = yesNoCheck(check[2]);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                flag[5] = 3;
                goto lb7;
            }
            if (check[2] == 'y' || check[2] == 'Y')
            {
                cout << "   ->Do they have genetic illness(Y/N)? : ";
                if (flag[8] >= 3)
                    cout << geneticIll << endl;
                else
                    cin >> geneticIll;
                invalidCheck = yesNoCheck(geneticIll);
                if (!invalidCheck)
                {
                    displayError();
                    // system("cls");
                    flag[8] = 2;
                    goto lb7;
                }
                cout << endl;
            }
            flag[8] = 500;
            cout << "Include smoker check mark? : ";
            if (flag[5] >= 5 || flag[9] >= 2)
                cout << check[3] << endl;
            else
                cin >> check[3];
            invalidCheck = yesNoCheck(check[3]);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                flag[5] = 4;
                goto lb7;
            }
            if (check[3] == 'y' || check[3] == 'Y')
            {
                cout << "   ->Do they smoke(y/n)? : ";
                if (flag[9] >= 3)
                    cout << smoke << endl;
                else
                    cin >> smoke;
                invalidCheck = yesNoCheck(smoke);
                if (!invalidCheck)
                {
                    displayError();
                    // system("cls");
                    flag[9] = 2;
                    goto lb7;
                }
                cout << endl;
            }
            flag[9] = 500;
            cout << "Include date of appointment? : ";
            if (flag[5] >= 6 || flag[10] >= 2)
                cout << check[4] << endl;
            else
                cin >> check[4];
            invalidCheck = yesNoCheck(check[4]);
            if (!invalidCheck)
            {
                displayError();
                // system("cls");
                flag[5] = 5;
                goto lb7;
            }
            if (check[4] == 'y' || check[4] == 'Y')
            {
                cout << "                          Enter the range of date\n"
                     << endl;
                cout << "Enter details of lower date" << endl;
                cout << "   ->Day of the month : ";
                cin.sync();
                if (flag[10] >= 3)
                    puts(dateLowerBound.dd);
                else
                    cin.getline(dateLowerBound.dd, sizeof(dateLowerBound.dd));
                if (strlen(dateLowerBound.dd) >= 2 && dateLowerBound.dd[0] >= '3' && dateLowerBound.dd[1] > '1' || (!strlen(dateLowerBound.dd)))
                    goto lb14;
                temp = strtol(dateLowerBound.dd, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb14:
                    displayError();
                    // system("cls");
                    flag[10] = 2;
                    goto lb7;
                }
                cout << "   ->Month : ";
                cin.sync();
                if (flag[10] >= 4)
                    puts(dateLowerBound.mm);
                else
                    cin.getline(dateLowerBound.mm, sizeof(dateLowerBound.mm));
                if (strlen(dateLowerBound.mm) >= 2 && dateLowerBound.mm[0] >= '1' && dateLowerBound.mm[1] > '2' || (!strlen(dateLowerBound.mm)))
                    goto lb15;
                temp = strtol(dateLowerBound.mm, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb15:
                    displayError();
                    // system("cls");
                    flag[10] = 3;
                    goto lb7;
                }
                cout << "   ->Year : ";
                cin.sync();
                if (flag[10] >= 5)
                    puts(dateLowerBound.yy);
                else
                    cin.getline(dateLowerBound.yy, sizeof(dateLowerBound.yy));
                if (strlen(dateLowerBound.yy) >= 5 || (!strlen(dateLowerBound.yy)))
                    goto lb16;
                temp = strtol(dateLowerBound.yy, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb16:
                    displayError();
                    // system("cls");
                    flag[10] = 4;
                    goto lb7;
                }
                cout << "Enter details of upper date" << endl;
                cout << "   ->Day of the month : ";
                cin.sync();
                if (flag[10] >= 6)
                    puts(dateUpperBound.dd);
                else
                    cin.getline(dateUpperBound.dd, sizeof(dateUpperBound.dd));
                if (strlen(dateUpperBound.dd) >= 2 && dateUpperBound.dd[0] >= '3' && dateUpperBound.dd[1] > '1' || (!strlen(dateUpperBound.dd)))
                    goto lb17;
                temp = strtol(dateUpperBound.dd, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb17:
                    displayError();
                    // system("cls");
                    flag[10] = 5;
                    goto lb7;
                }
                cout << "   ->Month : ";
                cin.sync();
                if (flag[10] >= 7)
                    puts(dateUpperBound.mm);
                else
                    cin.getline(dateUpperBound.mm, sizeof(dateUpperBound.mm));
                if (strlen(dateUpperBound.mm) >= 2 && dateUpperBound.mm[0] >= '1' && dateUpperBound.mm[1] > '2' || (!strlen(dateUpperBound.mm)))
                    goto lb18;
                temp = strtol(dateUpperBound.mm, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb18:
                    displayError();
                    // system("cls");
                    flag[10] = 6;
                    goto lb7;
                }
                cout << "   ->Year : ";
                cin.sync();
                if (flag[10] >= 8)
                    puts(dateUpperBound.yy);
                else
                    cin.getline(dateUpperBound.yy, sizeof(dateUpperBound.yy));
                if (strlen(dateUpperBound.yy) >= 5 || (!strlen(dateUpperBound.yy)))
                    goto lb19;
                temp = strtol(dateUpperBound.yy, &placeHolderPointer, 10);
                if (*placeHolderPointer)
                {
                lb19:
                    displayError();
                    // system("cls");
                    flag[10] = 7;
                    goto lb7;
                }
            }
            string op1, op2, op3;
            if ((check[0] == 'n' || check[0] == 'N') && (check[1] == 'n' || check[1] == 'N') && (check[2] == 'n' || check[2] == 'N') && (check[3] == 'n' || check[3] == 'N') && (check[4] == 'n' || check[4] == 'N'))
            {
                cout << "No parameters selected";
                goto lb1;
            }
            file.open("Patient.dat", ios::in);
            file.seekg(0);
            while (file.read((char *)&patientObject, sizeof(patientObject)))
            {
                a << patientObject.getDay();
                b << (patientObject.getMonth() + 1);
                c << (patientObject.getYear() + 1900);
                op1 = a.str();
                op2 = b.str();
                op3 = c.str();
                strcpy(appointmentDate.dd, op1.c_str());
                strcpy(appointmentDate.mm, op2.c_str());
                strcpy(appointmentDate.yy, op3.c_str());
                a.str("");
                b.str("");
                c.str("");
                if (check[0] == 'y' || check[0] == 'Y')
                    flag[0] = checkAge(patientObject.getAge(), maximumAge, minimumAge);
                else
                    flag[0] = 1;
                if (check[1] == 'y' || check[1] == 'Y')
                    flag[1] = checkGender(patientObject.getGender(), sex);
                else
                    flag[1] = 1;
                if (check[2] == 'y' || check[2] == 'Y')
                    flag[2] = checkGeneticIllness(patientObject.getMedicalHistory().getGenetic(), geneticIll);
                else
                    flag[2] = 1;
                if (check[3] == 'y' || check[3] == 'Y')
                    flag[3] = checkSmokerStatus(patientObject.getMedicalHistory().getSmoke(), smoke);
                else
                    flag[3] = 1;
                if (check[4] == 'y' || check[4] == 'Y')
                    flag[4] = checkDate(appointmentDate, dateUpperBound, dateLowerBound);
                else
                    flag[4] = 1;
                if (flag[0] && flag[1] && flag[2] && flag[3] && flag[4])
                    counting++;
            }
            file.close();
            cout << "The number of patients matching your search inquiries are : " << counting;
            counting = 0;
        lb1:
            cout << "\nWant to repeat again?(Y/N)";
            cin >> choice;
            // system("cls");
        } while (choice == 'y' || choice == 'Y');
        // system("cls");
        file.close();
        goto lb;
    case '0':
        cout << "End of Program";
        return 0;
    }
}
int checkAge(char *age, char *big, char *small)
{ // Function to check age within the given range
    stringstream e(age);
    stringstream f(small);
    stringstream g(big);
    int x, y, z;
    e >> x;
    f >> y;
    g >> z;
    if (x >= y && x <= z)
        return 1;
    return 0;
}
int checkGender(char patientObject, char gender)
{ // Function to check gender
    tolower(patientObject);
    tolower(gender);
    if (gender == patientObject)
        return 1;
    return 0;
}
int checkGeneticIllness(char objgenetic, char genetic)
{ // Function to check genetic illness
    tolower(objgenetic);
    tolower(genetic);
    if (objgenetic == genetic)
        return 1;
    return 0;
}
int checkSmokerStatus(char objsmoke, char smok)
{ // Function to check if the patient smokes
    tolower(objsmoke);
    tolower(smok);
    if (objsmoke == smok)
        return 1;
    return 0;
}
int checkDate(date objdate, date upperBound, date lowerBound)
{ // Function to check dates within the given range
    stringstream upperYearStream(upperBound.yy), upperMonthStream(upperBound.mm), upperDayStream(upperBound.dd);
    int upperYear, upperMonth, upperDay;
    upperYearStream >> upperYear;
    upperMonthStream >> upperMonth;
    upperDayStream >> upperDay;
    stringstream lowerYearStream(lowerBound.yy), lowerMonthStream(lowerBound.mm), lowerDayStream(lowerBound.dd);
    int lowerYear, lowerMonth, lowerDay;
    lowerYearStream >> lowerYear;
    lowerMonthStream >> lowerMonth;
    lowerDayStream >> lowerDay;
    stringstream appointmentYearStream(objdate.yy), appointmentMonthStream(objdate.mm), appointmentDayStream(objdate.dd);
    int appointmentYear, appointmentMonth, appointmentDay;
    appointmentYearStream >> appointmentYear;
    appointmentMonthStream >> appointmentMonth;
    appointmentDayStream >> appointmentDay;
    if (upperYear >= appointmentYear && lowerYear <= appointmentYear)
        if (upperMonth >= appointmentMonth && lowerMonth <= appointmentMonth)
            if (upperDay >= appointmentDay && lowerDay <= appointmentDay)
                return 1;
    return 0;
}
