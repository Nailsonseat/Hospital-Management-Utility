           /*Welcome to AVBIL hospital manager's source code*/
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include "date.h"

using namespace std;

class Medhistory
{ // Class used for Patient's Medical history
    char Smoker;
    char Drugs;
    char Disability;
    char genetic_illness;
    char attend;
    char intake;
    char Symptoms[100];

public:
    void gethistory();
    void givhistory();
    void init()
    { // Function used to initialize values if chart not entered
        Smoker = '\0';
        Drugs = '\0';
        Disability = '\0';
        genetic_illness = '\0';
        attend = '\0';
        intake = '\0';
        Symptoms[0] = '\0';
    }
    char getgenetic() { return genetic_illness; }
    char getsmoke() { return Smoker; }
};
class Patient
{
    /*Main class of this program
      has a object of Medhistory
      Used for Patient's basic information*/
    char Name[50];
    char Number[20];
    char age[4];
    char Gender;
    char Address[70];
    time_t reg_time;
    time_t ap_time;
    int timeof_mon;
    int timeof_day;
    int timeof_hour;
    int timeof_min;
    int timeof_year;
    tm *reg_tm;
    tm *ap_tm;
    char book_time[100];
    char visit_time[100];
    char visit_day[20];
    Medhistory extra;

public:
    void error_show()
    {
        cout << "\nPress Enter to continue";
        cin.sync();
        cin.ignore();
    }
    Medhistory getmedhistory()
    {
        return extra;
    }
    void initialize()
    {
        extra.init();
    }
    void history()
    {
        extra.gethistory();
    }
    void displaymed()
    {
        extra.givhistory();
    }
    void appoint_time();
    void appoint();
    void display();
    tm *get_visitobj() { return ap_tm; }
    char *getvisittime() { return visit_time; }
    char *getvisitday() { return visit_day; }
    char *gettime() { return book_time; }
    char *getname() { return Name; }
    char *getnum() { return Number; }
    char *getage() { return age; }
    char getgen() { return Gender; }
    char *getadr() { return Address; }
    int gettimeof_mon() { return timeof_mon; }
    int gettimeof_day() { return timeof_day; }
    int gettimeof_hour() { return timeof_hour; }
    int gettimeof_min() { return timeof_min; }
    int gettimeof_year() { return timeof_year; }
};
void Patient::appoint()
{ // Membered function used to enter Patient's details
    appoint_time();
    int len;
    long temp(0);
    int check = 0;
    char *p = NULL;
lb8:
    for (int j = 1; j <= 22; j++)
        cout << ' ';
    cout << "Welcome to Patient registration" << endl;
    cout << "Enter the name of the patient\n";
    cin.ignore();
    if (check >= 2)
        puts(Name);
    else
        cin.getline(Name, sizeof(Name));
    if (!strlen(Name))
    {
        cout << "Invalid input for name";
        error_show();
        check = 1;
        // system("cls");
        goto lb8;
    }
    for (int i = 0; i < strlen(Name); i++)
    {
        if (!(isalpha(Name[i])) && !(Name[i] == ' '))
        {
            cout << "Invalid input for name";
            error_show();
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
    temp = strtol(age, &p, 10);
    if (*p)
    {
    lb11:
        cout << "Invalid input for age";
        error_show();
        // system("cls");
        check = 2;
        goto lb8;
    }
    cout << "Enter the gender of the patient (M/F/O)" << endl;
    if (check >= 4)
        cout << Gender << endl;
    else
        cin >> Gender;
    if (!(Gender == 'm' || Gender == 'M' || Gender == 'f' || Gender == 'F' || Gender == 'o' || Gender == 'O'))
    {
        cout << "Invalid input for gender";
        error_show();
        // system("cls");
        check = 3;
        goto lb8;
    }
    cout << "Enter the phone number of patient(<10>)\n";
    cin.ignore();
    if (check >= 5)
        puts(Number);
    else
        cin.getline(Number, sizeof(Number));
    if (!(strlen(Number) == 10) || (!strlen(Number)))
        goto lb9;
    temp = strtol(Number, &p, 10);
    if (*p)
    {
    lb9:
        cout << "Invalid input for Number";
        error_show();
        // system("cls");
        check = 4;
        goto lb8;
    }
    cout << "Enter the address of the patient\n";
    cin.sync();
    cin.getline(Address, sizeof(Address));
}
void Patient ::appoint_time()
{ // Function to save registration time and assign random appointment time
    srand(time(0));
    char weekday[7][20] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    time(&reg_time);
    time(&ap_time);
    ap_tm = localtime(&ap_time);
    reg_tm = localtime(&reg_time);
    if (reg_tm->tm_hour > 12)
    {
        strftime(book_time, 100, "Date and time of registration : %d %B %Y %I:%M PM", reg_tm);
    }
    else
        strftime(book_time, 100, "Date and time of registration : %d %B %Y %I:%M AM", reg_tm);
    ap_tm->tm_year = reg_tm->tm_year;
    ap_tm->tm_mday = reg_tm->tm_mday;
    ap_tm->tm_mon = reg_tm->tm_mon;
    ap_tm->tm_mday += (rand() % (7)) + 1;
    if (ap_tm->tm_mon == 1)
    {
        if (ap_tm->tm_mday > 28)
        {
            ap_tm->tm_mon++;
            ap_tm->tm_mday -= 28;
        }
    }
    else if (ap_tm->tm_mon == 5 || ap_tm->tm_mon == 3 || ap_tm->tm_mon == 8 || ap_tm->tm_mon == 10)
    {
        if (ap_tm->tm_mday > 30)
        {
            ap_tm->tm_mon++;
            ap_tm->tm_mday -= 30;
        }
    }
    else if (ap_tm->tm_mon == 0 || ap_tm->tm_mon == 2 || ap_tm->tm_mon == 4 || ap_tm->tm_mon == 6 || ap_tm->tm_mon == 7 || ap_tm->tm_mon == 9 || ap_tm->tm_mon == 11)
    {
        if (ap_tm->tm_mday > 31)
        {
            ap_tm->tm_mon++;
            ap_tm->tm_mday -= 31;
        }
    }
    if (ap_tm->tm_mon > 11)
    {
        ap_tm->tm_mon -= 12;
        ap_tm->tm_year++;
    }
    ap_tm->tm_hour = (rand() % (20 - 10 + 1)) + 10;
    ap_tm->tm_min = (rand() % (61));
    if (ap_tm->tm_hour > 13)
    {
        strftime(visit_time, 100, "Time of appointment           : %d %B %I:%M PM ", ap_tm);
    }
    else
        strftime(visit_time, 100, "Time of appointment           : %d %B %I:%M AM ", ap_tm);
    mktime(ap_tm);
    strcpy(visit_day, weekday[ap_tm->tm_wday]);
    timeof_mon = ap_tm->tm_mon;
    timeof_day = ap_tm->tm_mday;
    timeof_hour = ap_tm->tm_hour;
    timeof_min = ap_tm->tm_min;
    timeof_year = ap_tm->tm_year;
}
void Medhistory ::gethistory()
{ // Function to enter Medical history of the patient
    int check(0);
lb10:
    cout << "Enter the observed symptoms" << endl;
    cin.sync();
    if (check >= 2)
        puts(Symptoms);
    else
        cin.getline(Symptoms, sizeof(Symptoms));
    cout << endl;
    for (int i = 1; i <= 13; i++)
        cout << ' ';
    cout << "The following has to be Answered in Y(Yes) or N(no)Only\n\n";
    cout << "Has the Patient taken drugs in any point in his/her's life?(Y/N)\n(excluding prescribed medicinal drugs)" << endl;
    if (check >= 3)
        cout << Drugs << endl;
    else
        cin >> Drugs;
    if (!(Drugs == 'y' || Drugs == 'Y' || Drugs == 'n' || Drugs == 'N'))
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
        cout << Smoker << endl;
    else
        cin >> Smoker;
    if (!(Smoker == 'y' || Smoker == 'Y' || Smoker == 'n' || Smoker == 'N'))
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
        cout << genetic_illness << endl;
    else
        cin >> genetic_illness;
    if (!(genetic_illness == 'y' || genetic_illness == 'Y' || genetic_illness == 'n' || genetic_illness == 'N'))
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
        cout << attend << endl;
    else
        cin >> attend;
    if (!(attend == 'y' || attend == 'Y' || attend == 'n' || attend == 'N'))
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
        cout << Disability << endl;
    else
        cin >> Disability;
    if (!(Disability == 'y' || Disability == 'Y' || Disability == 'n' || Disability == 'N'))
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
void Medhistory ::givhistory()
{ // Function to display Medical history
    cout << "Taken Drugs         : ";
    if (Drugs == 'y' || Drugs == 'Y')
        cout << "Yes\n";
    else if (Drugs == 'n' || Drugs == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Smokes/Vapes        : ";
    if (Smoker == 'y' || Smoker == 'Y')
        cout << "Yes\n";
    else if (Smoker == 'n' || Smoker == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Genetic illness     : ";
    if (genetic_illness == 'y' || genetic_illness == 'Y')
        cout << "Yes\n";
    else if (genetic_illness == 'n' || genetic_illness == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "First time of visit : ";
    if (attend == 'y' || attend == 'Y')
        cout << "Yes\n";
    else if (attend == 'n' || attend == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Disability/ADHD     : ";
    if (Disability == 'y' || Disability == 'Y')
        cout << "Yes\n";
    else if (Disability == 'n' || Disability == 'N')
        cout << "No\n";
    else
        cout << "N/A\n";
    cout << "Symptoms\n";
    if (Symptoms[0] == '\0')
        cout << "N/A";
    else
        puts(Symptoms);
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
void Patient::display()
{ // Function to display basic details of the patient
    cout << "Name of the Patient : " << getname();
    cout << endl
         << "Age of the Patient  : " << getage();
    cout << endl
         << "Phone number        : +91" << getnum();
    if (getgen() == 'm' || getgen() == 'M')
        cout << endl
             << "Gender\t\t    : Male";
    else if (getgen() == 'f' || getgen() == 'F')
        cout << endl
             << "Gender\t\t    : Female";
    else if (getgen() == 'o' || getgen() == 'O')
        cout << endl
             << "Gender\t\t    : Other";
    cout << endl
         << "Patient's Address   : " << getadr();
}
void Searchin(Patient &ob, fstream &f, char &c)
{ // Function to Search patient by name
    char key[50];
    // system("cls");
    cout << "Enter the name of the Patient" << endl;
    int check(0);
    cin.sync();
    cin.getline(key, sizeof(key));
    f.seekg(0);
    while (f.read((char *)&ob, sizeof(ob)))
    {
        if (strcmp(ob.getname(), key) == 0)
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
            cout << "Name of the Patient           : " << ob.getname();
            cout << endl;
            cout << ob.gettime();
            c = 'y';
            return;
        }
        ob.display();
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
int yes_no_check(char &check)
{
    if (check == 'y' || check == 'Y' || check == 'n' || check == 'N')
        return 1;
    if (!(check == 'y' || check == 'Y' || check == 'n' || check == 'N'))
        return 0;
}
void error_disp()
{
    cout << "Invalid input";
    cout << "\nPress Enter to continue";
    cin.sync();
    cin.ignore();
    return;
}
int main()
{
    char ans;
    int invalid_check;
    time_t cur_time;
    tm *cur_tm;
    char current_time[100];
    char check;
    fstream file;
    Patient obj;
lb:
    tophead();
    ans = menu();
    if (ans == -9)
        goto lb;
    switch (ans)
    {
    case '1':
        char ch;
        do
        {
            obj.initialize();
            // system("cls");
            file.open("Patient.dat", ios ::in | ios ::app | ios ::out);
            obj.appoint();
        lb2:
            cout << "Do you want to fill the Medical chart?(Y/N)" << endl;
            cin >> ch;
            invalid_check = yes_no_check(ch);
            if (!invalid_check)
            {
                error_disp();
                // system("cls");
                goto lb2;
            }
            if (ch == 'y' || ch == 'Y')
            {
                // system("cls");
                obj.history();
            }
            file.write((char *)&obj, sizeof(obj));
        // system("cls");
        lb3:
            cout << "Want to Enter another Patient?(Y/N)" << endl;
            cin >> ch;
            invalid_check = yes_no_check(ch);
            if (!invalid_check)
            {
                error_disp();
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
        Searchin(obj, file, check);
        if (!(check == 'n'))
        {
        lb4:
            cout << "\nWant to display the Medical chart too?(Y/N)\nInput : ";
            char flag;
            cin >> flag;
            invalid_check = yes_no_check(flag);
            if (!invalid_check)
            {
                error_disp();
                // system("cls");
                cout << "Record Found\n";
                obj.display();
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
                obj.display();
                cout << "\n\n";
                obj.displaymed();
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
            error_disp();
            // system("cls");
            cout << "Record Found\n";
            obj.display();
            cout << "\n\n";
            obj.displaymed();
            goto lb5;
        }
    case '4':
        check = 't';
        file.open("Patient.dat", ios::in);
        Searchin(obj, file, check);
        if (check == 'y')
        {
            time(&cur_time);
            cur_tm = localtime(&cur_time);
            if (cur_tm->tm_hour > 13)
            {
                strftime(current_time, 100, "Current date and time         : %d %B %Y %I:%M PM", cur_tm);
            }
            else
                strftime(current_time, 100, "Current date and time         : %d %B %Y %I:%M AM", cur_tm);
            cout << endl
                 << current_time;
            cout << endl
                 << obj.getvisittime() << "at " << obj.getvisitday();
            int status = 0;
            if ((cur_tm->tm_mon) < (obj.gettimeof_mon()))
            {
                status = 1;
            }
            else if ((cur_tm->tm_mon) == (obj.gettimeof_mon()))
            {
                if ((cur_tm->tm_mday) < (obj.gettimeof_day()))
                {
                    status = 1;
                }
                else if ((cur_tm->tm_mday) == (obj.gettimeof_day()))
                {
                    if ((cur_tm->tm_hour) < (obj.gettimeof_hour()))
                    {
                        status = 1;
                    }
                    else if ((cur_tm->tm_hour) == (obj.gettimeof_hour()))
                    {
                        if ((cur_tm->tm_min) <= (obj.gettimeof_min()))
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
        invalid_check = yes_no_check(ch);
        if (!invalid_check)
        {
            error_disp();
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
            int age_check(char *, char *, char *);
            int gender_check(char, char);
            int genetic_check(char, char);
            int smoke_check(char, char);
            int date_check(date, date, date);
            ostringstream a, b, c;
            char check[5];
            long temp;
            char *p;
            int i;
            for (i = 0; i < 5; i++)
                check[i] = '\0';
            int flag[11], counting = 0;
            for (i = 0; i < 11; i++)
                flag[i] = 0;
            char age_min[4], age_max[4];
            char genetic_ill;
            char smoke;
            char sex;
            date d_upper, d_lower, d_app;
        lb7:
            cout << "Number of patients will be displayed on the basis of the attributes selected" << endl;
            cout << "Select which attributes to include (Y/N) and enter further details if asked" << endl;
            cout << "\nInclude age? : ";
            if (flag[5] >= 2 || flag[6] >= 2)
                cout << check[0] << endl;
            else
                cin >> check[0];
            invalid_check = yes_no_check(check[0]);
            if (!invalid_check)
            {
                error_disp();
                // system("cls");
                flag[5] = 1;
                goto lb7;
            }
            if (check[0] == 'y' || check[0] == 'Y')
            {
                p = NULL;
                cin.sync();
                cout << "   ->Enter lower bound(<200) : ";
                if (flag[6] >= 3)
                    puts(age_min);
                else
                    cin.getline(age_min, sizeof(age_min));
                if (strlen(age_min) >= 3 && age_min[0] >= '2' || (!strlen(age_min)))
                    goto lb13;
                temp = strtol(age_min, &p, 10);
                if (*p)
                {
                lb13:
                    error_disp();
                    // system("cls");
                    flag[6] = 2;
                    goto lb7;
                }
                cin.sync();
                cout << "   ->Enter upper bound(<200) : ";
                if (flag[6] >= 4)
                    puts(age_max);
                else
                    cin.getline(age_max, sizeof(age_max));
                if (strlen(age_max) >= 3 && age_max[0] >= '2' || (!strlen(age_max)))
                    goto lb12;
                temp = strtol(age_max, &p, 10);
                if (*p)
                {
                lb12:
                    error_disp();
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
            invalid_check = yes_no_check(check[1]);
            if (!invalid_check)
            {
                error_disp();
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
                    error_disp();
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
            invalid_check = yes_no_check(check[2]);
            if (!invalid_check)
            {
                error_disp();
                // system("cls");
                flag[5] = 3;
                goto lb7;
            }
            if (check[2] == 'y' || check[2] == 'Y')
            {
                cout << "   ->Do they have genetic illness(Y/N)? : ";
                if (flag[8] >= 3)
                    cout << genetic_ill << endl;
                else
                    cin >> genetic_ill;
                invalid_check = yes_no_check(genetic_ill);
                if (!invalid_check)
                {
                    error_disp();
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
            invalid_check = yes_no_check(check[3]);
            if (!invalid_check)
            {
                error_disp();
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
                invalid_check = yes_no_check(smoke);
                if (!invalid_check)
                {
                    error_disp();
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
            invalid_check = yes_no_check(check[4]);
            if (!invalid_check)
            {
                error_disp();
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
                    puts(d_lower.dd);
                else
                    cin.getline(d_lower.dd, sizeof(d_lower.dd));
                if (strlen(d_lower.dd) >= 2 && d_lower.dd[0] >= '3' && d_lower.dd[1] > '1' || (!strlen(d_lower.dd)))
                    goto lb14;
                temp = strtol(d_lower.dd, &p, 10);
                if (*p)
                {
                lb14:
                    error_disp();
                    // system("cls");
                    flag[10] = 2;
                    goto lb7;
                }
                cout << "   ->Month : ";
                cin.sync();
                if (flag[10] >= 4)
                    puts(d_lower.mm);
                else
                    cin.getline(d_lower.mm, sizeof(d_lower.mm));
                if (strlen(d_lower.mm) >= 2 && d_lower.mm[0] >= '1' && d_lower.mm[1] > '2' || (!strlen(d_lower.mm)))
                    goto lb15;
                temp = strtol(d_lower.mm, &p, 10);
                if (*p)
                {
                lb15:
                    error_disp();
                    // system("cls");
                    flag[10] = 3;
                    goto lb7;
                }
                cout << "   ->Year : ";
                cin.sync();
                if (flag[10] >= 5)
                    puts(d_lower.yy);
                else
                    cin.getline(d_lower.yy, sizeof(d_lower.yy));
                if (strlen(d_lower.yy) >= 5 || (!strlen(d_lower.yy)))
                    goto lb16;
                temp = strtol(d_lower.yy, &p, 10);
                if (*p)
                {
                lb16:
                    error_disp();
                    // system("cls");
                    flag[10] = 4;
                    goto lb7;
                }
                cout << "Enter details of upper date" << endl;
                cout << "   ->Day of the month : ";
                cin.sync();
                if (flag[10] >= 6)
                    puts(d_upper.dd);
                else
                    cin.getline(d_upper.dd, sizeof(d_upper.dd));
                if (strlen(d_upper.dd) >= 2 && d_upper.dd[0] >= '3' && d_upper.dd[1] > '1' || (!strlen(d_upper.dd)))
                    goto lb17;
                temp = strtol(d_upper.dd, &p, 10);
                if (*p)
                {
                lb17:
                    error_disp();
                    // system("cls");
                    flag[10] = 5;
                    goto lb7;
                }
                cout << "   ->Month : ";
                cin.sync();
                if (flag[10] >= 7)
                    puts(d_upper.mm);
                else
                    cin.getline(d_upper.mm, sizeof(d_upper.mm));
                if (strlen(d_upper.mm) >= 2 && d_upper.mm[0] >= '1' && d_upper.mm[1] > '2' || (!strlen(d_upper.mm)))
                    goto lb18;
                temp = strtol(d_upper.mm, &p, 10);
                if (*p)
                {
                lb18:
                    error_disp();
                    // system("cls");
                    flag[10] = 6;
                    goto lb7;
                }
                cout << "   ->Year : ";
                cin.sync();
                if (flag[10] >= 8)
                    puts(d_upper.yy);
                else
                    cin.getline(d_upper.yy, sizeof(d_upper.yy));
                if (strlen(d_upper.yy) >= 5 || (!strlen(d_upper.yy)))
                    goto lb19;
                temp = strtol(d_upper.yy, &p, 10);
                if (*p)
                {
                lb19:
                    error_disp();
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
            while (file.read((char *)&obj, sizeof(obj)))
            {
                a << obj.gettimeof_day();
                b << (obj.gettimeof_mon() + 1);
                c << (obj.gettimeof_year() + 1900);
                op1 = a.str();
                op2 = b.str();
                op3 = c.str();
                strcpy(d_app.dd, op1.c_str());
                strcpy(d_app.mm, op2.c_str());
                strcpy(d_app.yy, op3.c_str());
                a.str("");
                b.str("");
                c.str("");
                if (check[0] == 'y' || check[0] == 'Y')
                    flag[0] = age_check(obj.getage(), age_max, age_min);
                else
                    flag[0] = 1;
                if (check[1] == 'y' || check[1] == 'Y')
                    flag[1] = gender_check(obj.getgen(), sex);
                else
                    flag[1] = 1;
                if (check[2] == 'y' || check[2] == 'Y')
                    flag[2] = genetic_check(obj.getmedhistory().getgenetic(), genetic_ill);
                else
                    flag[2] = 1;
                if (check[3] == 'y' || check[3] == 'Y')
                    flag[3] = smoke_check(obj.getmedhistory().getsmoke(), smoke);
                else
                    flag[3] = 1;
                if (check[4] == 'y' || check[4] == 'Y')
                    flag[4] = date_check(d_app, d_upper, d_lower);
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
int age_check(char *age, char *big, char *small)
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
int gender_check(char obj, char gender)
{ // Function to check gender
    tolower(obj);
    tolower(gender);
    if (gender == obj)
        return 1;
    return 0;
}
int genetic_check(char objgenetic, char genetic)
{ // Function to check genetic illness
    tolower(objgenetic);
    tolower(genetic);
    if (objgenetic == genetic)
        return 1;
    return 0;
}
int smoke_check(char objsmoke, char smok)
{ // Function to check if the patient smokes
    tolower(objsmoke);
    tolower(smok);
    if (objsmoke == smok)
        return 1;
    return 0;
}
int date_check(date objdate, date upper, date lower)
{ // Function to check dates within the given range
    stringstream a(upper.yy), b(upper.mm), c(upper.dd);
    int up_yy, up_mm, up_dd;
    a >> up_yy;
    b >> up_mm;
    c >> up_dd;
    stringstream x(lower.yy), y(lower.mm), z(lower.dd);
    int low_yy, low_mm, low_dd;
    x >> low_yy;
    y >> low_mm;
    z >> low_dd;
    stringstream e(objdate.yy), f(objdate.mm), g(objdate.dd);
    int app_yy, app_mm, app_dd;
    e >> app_yy;
    f >> app_mm;
    g >> app_dd;
    if (up_yy >= app_yy && low_yy <= app_yy)
        if (up_mm >= app_mm && low_mm <= app_mm)
            if (up_dd >= app_dd && low_dd <= app_dd)
                return 1;
    return 0;
}
