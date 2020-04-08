/***
//// Last Build : 8_19_08
//// Compiler   : VS2019
//// Programmer : Kenneth Kho
//// Capability : Implementing a variable size record.
//// Function   : add, delete, modify, display records
***/


/////////////     Includes    /////////////

#include <cstdlib> // system()
#include <conio.h> // getch()
#include <fstream>
#include <sys\stat.h> // stat(status of a file)
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <chrono>
#include <vector>
#include <windows.h> //system.time 
using namespace std;


/////////////     Data types    /////////////

// Text Color
char normal[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '1', '5', 'm', 0 };

char color_a[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '4', '0', 'm', 0 };
char color_b[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '7', '6', 'm', 0 };
char color_c[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '1', '1', '2', 'm', 0 };
char color_d[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '1', '1', '3', 'm', 0 };
char color_e[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '7', '7', 'm', 0 };
char color_f[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '4', '1', 'm', 0 };
char color_g[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '2', '6', 'm', 0 };
char color_h[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '2', '0', 'm', 0 };
char color_i[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '1', '4', 'm', 0 };
char color_j[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '0', '8', 'm', 0 };
char color_k[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '0', '2', 'm', 0 };
char color_l[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '1', '9', '6', 'm', 0 };

char color_1[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '1', 'm', 0 };
char color_3[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '3', '3', 'm', 0 };
char color_5[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '4', '5', 'm', 0 };
char error_1[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '1', '9', '6', 'm', 0 };
char error_2[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '1', '2', '4', 'm', 0 };
char error_3[] = { 0x1b, '[', '3' ,'8', ';', '5', ';', '2', '0', '2', 'm', 0 };

int registrationID = 1000;

struct Seeker_Record // Seeker record
{
    // Declare all variables after this line
    // --- 12 FEB 2020 ---
    string first_name;
    string last_name;
    string contact_number;
    string ic_number;
    string gender;
    string dateOf_birth;
    string emergency_fullname;
    string emergency_number;
    string emergency_relationship;
    string working_pref;
    string qualification;
    string graduate_university;
    string marital_status;
    string spouse_name;
    string spouse_ic_number;
    vector<string> children_arr;
    string s;
    char email_address[40];
    int registrationID;
    int age;
    int children;
    int graduate_year;
    int day;
    int month;
    int year;
    int birthYear;
    int n;
    double working_exp;

    // Don't touch after this line
    bool deleted;
};


/////////////     Variable Declarations & Constants /////////////

#define SEEKER_FILE_NAME "Seekers.txt" // name of the database file to store Seekers informations

Seeker_Record Seeker;
char     choice; // for choice in menu
fstream* fs = NULL, * fs1 = NULL;// file streams for files : fs -> 'Seeker', fs1 -> 'temp'
bool     deletion = false; // if any record has been deleted


/////////////     Function Prototypes    /////////////

void closeFile(fstream*); // closes a file with its pointer, then deletes the file pointer
bool isFileExist(const char*); // check if a file exists
int searchRegistrationID;

// --- 26 FEB 2020 ---
void parseInt(string& a, int b, int c)
{
    stringstream geek(a.substr(b, c));
    geek >> Seeker.n;
}

void parseString(int a)
{
    stringstream ss;
    ss << a;
    Seeker.s = ss.str();
}

bool emailValidation(const std::string& email)
{
    const std::regex pattern
    ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    return std::regex_match(email, pattern);
}

bool containsNumber(const std::string& c)
{
    if (c.find('0') != std::string::npos ||
        c.find('1') != std::string::npos ||
        c.find('2') != std::string::npos ||
        c.find('3') != std::string::npos ||
        c.find('4') != std::string::npos ||
        c.find('5') != std::string::npos ||
        c.find('6') != std::string::npos ||
        c.find('7') != std::string::npos ||
        c.find('8') != std::string::npos ||
        c.find('9') != std::string::npos)
    {
        return true;
    }

    return false;
}

/////////////     Main    /////////////
int main()
{
    chrono::steady_clock sc;
    auto start = sc.now();

    ifstream input;
    input.open("id.txt"), ios::in;
    input >> registrationID;
    ofstream output;

    SYSTEMTIME It;
    GetLocalTime(&It);
    Seeker.day = (It.wDay);
    Seeker.month = (It.wMonth);
    Seeker.year = (It.wYear);

    while (true)
    {
        do ////// Menu //////
        {
            system("cls"); // clear screen
        loopaddcase:
            cout << normal << "\n\t\t Welcome to JS Company!            ";
            cout << "\n   Sign up now and we will contact you once there";
            cout << "\n   are jobs available based on your requirements!\n";
            cout << "\n\t\t" << color_a << "< Job " << color_b << "See" << color_c << "ker" << color_d << "s Da" << color_e << "tab" << color_f << "ase >" << normal << "\n\n";
            cout << "    " << color_g << "(1)\t\tAdd     a new Record" << normal << endl;
            cout << "    " << color_h << "(2)\t\tSearch an existing Record" << normal << endl;
            cout << "    " << color_i << "(3)\t\tModify an existing Record" << normal << endl;
            cout << "    " << color_j << "(4)\t\tDelete an existing Record" << normal << endl;
            cout << "    " << color_k << "(5)\t\tDisplay Records" << normal << endl;
            cout << "    " << color_l << "(6)\t\tExit " << normal << "\n\n";
            cout << "    Select    : " << flush;
            choice = _getch();
        } while (choice < '1' || choice > '6'); // while we have no good(between 1 and 5), show menu again

        system("cls");

        // to modify, delete or display records, database file should exist, then we have some records           
        if (choice == '3' || choice == '4' || choice == '5')
        {
            if (!isFileExist(SEEKER_FILE_NAME)) // if database file doesn't exist
            {
                cout << "\n Database file ('" << SEEKER_FILE_NAME << "') doesn't exist, then there are no records." << endl;
                system("pause");
                continue; // show the menu again
            }
        }

        switch (choice)
        {
            int recs_num; // number of records before the record for modifying(deletion)
            int id;

        case '1': ////// Add Record //////

            cout << "\n                " << color_g << "< Add a new record > " << normal;
            cout << "\n   Enter the following informations for the new record : " << endl;

            // --- 26 FEB 2020 ---
            cout << color_5 << "\n               < Seeker Information > " << normal << endl;

            Seeker.registrationID = ++registrationID;
            cout << "\n   Registration ID             : " << Seeker.registrationID;
            if (output.open("id.txt"), ios::out)
            {
                output << registrationID;
            }
            else cout << "  The file is empty.";
            output.close();

            int selector;

            cout << "\n   First Name                  : ";
            getline(cin, Seeker.first_name);

            while (containsNumber(Seeker.first_name))
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid first name! " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John                    " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   First Name                  : ";
                getline(cin, Seeker.first_name);
            }
            Seeker.first_name[0] = toupper(Seeker.first_name[0]);

            cout << "   Last Name                   : ";
            getline(cin, Seeker.last_name);

            while (containsNumber(Seeker.last_name))
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid last name!  " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "Collins                 " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Last Name                   : ";
                getline(cin, Seeker.last_name);
            }
            Seeker.last_name[0] = toupper(Seeker.last_name[0]);

            cout << "   IC Number                   : ";
            cin >> Seeker.ic_number;


            while (Seeker.ic_number.find_first_of("1234567890") == string::npos || Seeker.ic_number.length() != 12)
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid IC Number!  " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "011231016703            " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   IC Number                   : ";
                cin >> Seeker.ic_number;
            }

            parseInt(Seeker.ic_number, 11, 1);

            if (Seeker.n % 2 == 0)
            {
                Seeker.gender = "Female";
            }
            else
            {
                Seeker.gender = "Male";
            }

            parseInt(Seeker.ic_number, 0, 2);

            if (Seeker.n > 20)
            {
                Seeker.birthYear = 1900 + Seeker.n;
                Seeker.age = Seeker.year - Seeker.birthYear;
            }
            else
            {
                Seeker.birthYear = 2000 + Seeker.n;
                Seeker.age = Seeker.year - Seeker.birthYear;
            }

            parseString(Seeker.birthYear);
            Seeker.dateOf_birth = Seeker.ic_number.substr(4, 2) + "/" + Seeker.ic_number.substr(2, 2) + "/" + Seeker.s;

            cout << "   Contact Number              : ";
            cin >> Seeker.contact_number;



            while (Seeker.contact_number.find_first_of("1234567890") == string::npos || (Seeker.contact_number.length() != 10 && Seeker.contact_number.length() != 11))
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid number!     " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "0123456789              " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Contact Number              : ";
                cin >> Seeker.contact_number;
            }

            cout << "   Email Address               : ";
            cin >> Seeker.email_address;


            while (emailValidation(Seeker.email_address) != true)
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid email!      " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "john@example.com        " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Email Address               : ";
                cin >> Seeker.email_address;

            }

            cout << "\n       --------------------------------------------------";
            cout << "\n       |                 Marital Status                 |";
            cout << "\n       --------------------------------------------------" << endl;
            cout << "\n   '1'                         : Single";
            cout << "\n   '2'                         : Married";
            cout << "\n   '3'                         : Divorced";
            cout << "\n   Select                      : ";
            cin >> selector;

            do
            {
                switch (selector)
                {
                case 1: Seeker.marital_status = "Single";
                    break;
                case 2: Seeker.marital_status = "Married";
                    break;
                case 3: Seeker.marital_status = "Divorced";
                    break;
                default:
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << "   Select                      : ";
                    cin >> selector;
                    break;
                }
            } while (selector != 1 && selector != 2 && selector != 3);


            // Number of children
            if (selector == 2)
            {
                system("cls");
                cout << color_g << "\n                < Add a new record > " << normal;
                cout << "\n   Enter the following informations for the new record : " << endl;

                cout << color_5 << "\n               < Seeker Information > " << normal << endl;

                cout << "\n   Registration ID             : " << Seeker.registrationID << endl;

                cout << "   Spouse's Full Name          : ";
                cin.get();
                getline(cin, Seeker.spouse_name);

                while (containsNumber(Seeker.spouse_name))
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid full name!  " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John Collins            " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << "   Spouse's Full Name          : ";
                    cin.get();
                    getline(cin, Seeker.spouse_name);
                }
                Seeker.first_name[0] = toupper(Seeker.first_name[0]);

                cout << "   IC Number                   : ";
                cin >> Seeker.spouse_ic_number;

                while (Seeker.spouse_ic_number.find_first_of("1234567890") == string::npos || Seeker.spouse_ic_number.length() != 12)
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid IC Number!  " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "011231016703            " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << "   IC Number                   : ";
                    cin >> Seeker.spouse_ic_number;
                }

                cout << "   Number of Children          : ";
                cin >> Seeker.children;



                // Add spouse name & children
                if (Seeker.children != 0)
                {
                    for (int i = 0; i < Seeker.children; i++)
                    {
                        string message, child;

                        switch (i)
                        {
                        case 0:
                            message = "st Child's Full Name       : ";
                            cout << "   " << i + 1 << message;
                            break;
                        case 1:
                            message = "nd Child's Full Name       : ";
                            cout << "   " << i + 1 << message;
                            break;
                        case 2:
                            message = "rd Child's Full Name       : ";
                            cout << "   " << i + 1 << message;
                            break;
                        default:
                            message = "th Child's Full Name       : ";
                            cout << "   " << i + 1 << message;
                            break;
                        }

                        getline(cin, child);
                        while (containsNumber(child))
                        {
                            cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                            cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid first name! " << error_2 << "*****" << endl;
                            cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John                    " << error_2 << "*****" << endl;
                            cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                            cout << "   " << i + 1 << message;

                            getline(cin, child);
                        }
                        child[0] = toupper(child[0]);
                        Seeker.children_arr.push_back(child);
                    }
                }
            }

            system("cls");

            cout << color_g << "\n                < Add a new record > " << normal;
            cout << "\n   Enter the following informations for the new record : " << endl;

            cout << color_3 << "\n          < Emergency Contact Information > " << normal << endl;

            cout << "\n   Registration ID             : " << Seeker.registrationID;

            cout << "\n   Full Name                   : ";
            cin.get();
            getline(cin, Seeker.emergency_fullname);

            while (containsNumber(Seeker.emergency_fullname))
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid full name!  " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John Collins            " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Full Name                   : ";
                cin.get();
                getline(cin, Seeker.emergency_fullname);
            }

            cout << "   Contact Number              : ";
            cin >> Seeker.emergency_number;



            while (Seeker.emergency_number.find_first_of("1234567890") == string::npos || (Seeker.emergency_number.length() != 10 && Seeker.emergency_number.length() != 11))
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid number   !  " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "0123456789              " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Contact Number              : ";
                cin >> Seeker.emergency_number;
            }

            cout << "\n       --------------------------------------------------";
            cout << "\n       |                  Relationship                  |";
            cout << "\n       --------------------------------------------------" << endl;
            cout << "\n   '1'                         : Parent/Guardian";
            cout << "\n   '2'                         : Partner";
            cout << "\n   '3'                         : Sibling";
            cout << "\n   '4'                         : Relative";
            cout << "\n   '5'                         : Friend";
            cout << "\n   Select                      : ";
            cin >> selector;

            do
            {
                switch (selector)
                {
                case 1:
                    Seeker.emergency_relationship = "Parent/Guardian";
                    break;
                case 2:
                    Seeker.emergency_relationship = "Partner";
                    break;
                case 3:
                    Seeker.emergency_relationship = "Sibling";
                    break;
                case 4:
                    Seeker.emergency_relationship = "Relative";
                    break;
                case 5:
                    Seeker.emergency_relationship = "Friend";
                    break;
                default:
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << "   Select                      : ";
                    cin >> selector;
                    break;
                }
            } while (selector < 1 || selector > 5);

            system("cls");
            cout << color_g << "\n                < Add a new record > " << normal;
            cout << "\n   Enter the following informations for the new record : " << endl;

            cout << color_1 << "\n                    < Job Resume > " << normal << endl;

            cout << "\n   Registration ID             : " << Seeker.registrationID;

            cout << "\n   Working Experience (years)  : ";
            cin >> Seeker.working_exp;

            cout << "\n       --------------------------------------------------";
            cout << "\n       |               Working Preference               |";
            cout << "\n       --------------------------------------------------" << endl;
            cout << "\n   '1'                         : Part-time";
            cout << "\n   '2'                         : Full-time";
            cout << "\n   '3'                         : Both";
            cout << "\n   Select                      : ";
            cin >> selector;

            do
            {
                switch (selector)
                {
                case 1: Seeker.working_pref = "Part-time";
                    break;
                case 2: Seeker.working_pref = "Full-time";
                    break;
                case 3: Seeker.working_pref = "Part-time & Full-time";
                    break;
                default:
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << "   Select                      : ";
                    cin >> selector;
                    break;
                }
            } while (selector != 1 && selector != 2 && selector != 3);

            // Ask for which year user graduated
            cout << "\n   Year of Graduation          : ";
            cin >> Seeker.graduate_year;

            while (Seeker.graduate_year >= Seeker.year)
            {
                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid year!       " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "2010                    " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Year of Graduation          : ";
                cin >> Seeker.graduate_year;
            }

            // Use Malaysia's qualification levels
            cout << "\n       --------------------------------------------------";
            cout << "\n       |         Highest Academic Qualification         |";
            cout << "\n       --------------------------------------------------" << endl;
            cout << "\n   '1'                         : Certificate";
            cout << "\n   '2'                         : Diploma";
            cout << "\n   '3'                         : Bachelor's Degree";
            cout << "\n   '4'                         : Master's Degree";
            cout << "\n   '5'                         : Doctoral Degree";
            cout << "\n   Select                      : ";
            cin >> selector;

            do
            {
                switch (selector)
                {
                case 1:
                    Seeker.qualification = "Certificate";
                    break;
                case 2:
                    Seeker.qualification = "Diploma";
                    break;
                case 3:
                    Seeker.qualification = "Bachelor's Degree";
                    break;
                case 4:
                    Seeker.qualification = "Master's Degree";
                    break;
                case 5:
                    Seeker.qualification = "Doctoral Degree";
                default:
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << "   Select                      : ";
                    cin >> selector;
                    break;
                }
            } while (selector < 1 || selector > 5);

            // State which university
            cout << "\n   Graduating University       : ";
            cin.get();
            getline(cin, Seeker.graduate_university);

            while (Seeker.graduate_university.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos || containsNumber(Seeker.graduate_university))
            {

                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid university! " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "Sunway University       " << error_2 << "*****" << endl;
                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                cout << "   Graduating University       : ";
                cin.get();
                getline(cin, Seeker.graduate_university);
            }

            system("cls");

            cout << color_a << "\n    ----------------------- < Confirmation > -----------------------" << normal;
            cout << "\n    Registration ID                : " << Seeker.registrationID;
            cout << "\n    Registration Date              : " << Seeker.day << '/' << Seeker.month << '/' << Seeker.year;
            cout << color_5 << "\n    -------------------- < Seeker Information > --------------------" << normal;
            cout << "\n    First Name                     : " << Seeker.first_name;
            cout << "\n    Last Name                      : " << Seeker.last_name;
            cout << "\n    IC Number                      : " << Seeker.ic_number;
            cout << "\n    Gender                         : " << Seeker.gender;
            cout << "\n    Age                            : " << Seeker.age;
            cout << "\n    Date of Birth                  : " << Seeker.dateOf_birth;
            cout << "\n    Contact Number                 : " << Seeker.contact_number;
            cout << "\n    Email Address                  : " << Seeker.email_address;
            cout << "\n    Marital Status                 : " << Seeker.marital_status;
            if (Seeker.marital_status == "Married")
            {
                cout << "\n    Spouse's Full Name             : " << Seeker.spouse_name;
                cout << "\n    Spouse's IC Number             : " << Seeker.spouse_ic_number;
                if (Seeker.children != 0)
                {
                    cout << "\n    Children                       : " << Seeker.children;
                    for (int i = 0; i < Seeker.children; i++)
                    {
                        cout << "\n\t\t\t\t  " << i + 1 << ") " << Seeker.children_arr[i];
                    }
                }
            }
            cout << color_3 << "\n    --------------- < Emergency Contact Information > ---------------" << normal;
            cout << "\n    Full Name                      : " << Seeker.emergency_fullname;
            cout << "\n    Contact Number                 : " << Seeker.emergency_number;
            cout << "\n    Relationship                   : " << Seeker.emergency_relationship;
            cout << color_1 << "\n    ---------------------- < Job Information > ----------------------" << normal;
            cout << "\n    Working Experience             : " << Seeker.working_exp << " year(s)";
            cout << "\n    Working Preference             : " << Seeker.working_pref;
            cout << "\n    Year of Graduation             : " << Seeker.graduate_year;
            cout << "\n    Highest Academic Qualification : " << Seeker.qualification;
            cout << "\n    Graduating University          : " << Seeker.graduate_university << endl;
            {
                auto end = sc.now();
                auto time_span = static_cast<chrono::duration<double>>(end - start);
                cout << "\n    Time Elapsed                   : " << time_span.count() << " seconds.." << endl;
            }

            // Don't touch after this line

            Seeker.deleted = 0;

            fs = new fstream(SEEKER_FILE_NAME, ios::out | ios::app | ios::binary);

            if (!fs)
            {
                cout << "\n    Can't open or create " << SEEKER_FILE_NAME << " file" << endl;
                system("pause");
                break;
            }

            cout << "\n    Do you want to save this record? (1=Yes 2=No 3=Save and Add): ";

            char confirm;

        loopadd:
            cin >> confirm;
            cin.ignore();

            if (confirm == '1')
            {
                fs->write((char*)&Seeker, sizeof(Seeker));
                closeFile(fs);
                break;
            }
            if (confirm == '2')
            {
                cout << error_1 << "Record not added." << normal << endl;
                system("pause");
                break;
            }
            if (confirm == '3')
            {
                fs->write((char*)&Seeker, sizeof(Seeker));
                closeFile(fs);

                goto loopaddcase;
            }
            else
            {
                cout << "\n\n   Invalid input! Please enter (1=Yes 2=No 3=Save and Add) To Confirm Add Record.";
                cout << "\n\n   Do you want to add this record? (1=Yes 2=No 3=Save and Add): ";

                goto loopadd;
            }

        case '2': ////// Search Record //////

            // --- 3 MARCH 2020 ---

            cout << color_h << "\n                    < Search for Record > " << normal;
            cout << "\n        Enter Registration ID to search for record.. " << endl;
            cout << "\n   Registration ID                : ";
            cin >> searchRegistrationID;
            cin.ignore();

            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << SEEKER_FILE_NAME << "' file" << endl;
                system("pause");

                break;
            }

            recs_num = -1;

            while (fs->read((char*)&Seeker, sizeof(Seeker)))
            {
                recs_num++;

                if (Seeker.registrationID == searchRegistrationID && !Seeker.deleted)
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
            {
                cout << error_1 << "\n                          < Error > " << normal;
                cout << error_2 << "\n    The entered Registration ID doesn't exist in saved records.\n" << normal << endl;
                closeFile(fs);
                system("pause");
                system("cls");
                goto loopaddcase;
                break;
            }

            fs->seekp(sizeof(Seeker) * recs_num, ios::beg); // go to the first of the record to be modified
            fs->read((char*)&Seeker, sizeof(Seeker));

            if (!Seeker.deleted)
            {
                system("cls");

                cout << color_a << "\n    ----------------------- < Record Found > -----------------------" << normal;
                cout << "\n    Registration ID                : " << Seeker.registrationID;
                cout << "\n    Registration Date              : " << Seeker.day << '/' << Seeker.month << '/' << Seeker.year;
                cout << color_5 << "\n    -------------------- < Seeker Information > --------------------" << normal;
                cout << "\n    First Name                     : " << Seeker.first_name;
                cout << "\n    Last Name                      : " << Seeker.last_name;
                cout << "\n    IC Number                      : " << Seeker.ic_number;
                cout << "\n    Gender                         : " << Seeker.gender;
                cout << "\n    Age                            : " << Seeker.age;
                cout << "\n    Date of Birth                  : " << Seeker.dateOf_birth;
                cout << "\n    Contact Number                 : " << Seeker.contact_number;
                cout << "\n    Email Address                  : " << Seeker.email_address;
                cout << "\n    Marital Status                 : " << Seeker.marital_status;
                if (Seeker.marital_status == "Married")
                {
                    cout << "\n    Spouse's Full Name             : " << Seeker.spouse_name;
                    cout << "\n    Spouse's IC Number             : " << Seeker.spouse_ic_number << endl;
                    if (Seeker.children != 0)
                    {
                        cout << "    Children                       : " << Seeker.children << endl;
                        for (int i = 0; i < Seeker.children; i++)
                        {
                            cout << "\t\t\t\t  " << i + 1 << ") " << Seeker.children_arr[i] << endl;
                        }
                    }
                }
                else { cout << "\n"; }
                cout << color_3 << "    --------------- < Emergency Contact Information > ---------------" << normal;
                cout << "\n    Full Name                      : " << Seeker.emergency_fullname;
                cout << "\n    Contact Number                 : " << Seeker.emergency_number;
                cout << "\n    Relationship                   : " << Seeker.emergency_relationship;
                cout << color_1 << "\n    ---------------------- < Job Information > ----------------------" << normal;
                cout << "\n    Working Experience             : " << Seeker.working_exp << " year(s)";
                cout << "\n    Working Preference             : " << Seeker.working_pref;
                cout << "\n    Year of Graduation             : " << Seeker.graduate_year;
                cout << "\n    Highest Academic Qualification : " << Seeker.qualification;
                cout << "\n    Graduating University          : " << Seeker.graduate_university << endl;
            }

            cout << "\n    To return to menu, ";
            system("pause");
            system("cls");
            goto loopaddcase;
            closeFile(fs);

            break;

        case '3': ////// Modify Record //////

            cout << color_i << "\n                    < Modifying an existing record > " << normal;
            cout << "\n         Enter Registration ID to update specific information.. " << endl;

            cout << "\n    Registration ID                   : ";
            cin >> searchRegistrationID;
            cin.ignore();

            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::out | ios::binary);

            if (!fs)
            {
                cout << "\nCan't open or create" << SEEKER_FILE_NAME << "file" << endl;

                system("pause");
                break;
            }

            recs_num = -1;
            while (fs->read((char*)&Seeker, sizeof(Seeker)))
            {
                recs_num++;

                if (searchRegistrationID == Seeker.registrationID && !Seeker.deleted)
                    /*if user deleted an driver then added another one
                    with the same ID in the same instance of program runs,delected driver is still there, then we should go through
                    all the file*/
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)   
            {
                cout << error_1 << "\n                          < Error > " << normal;
                cout << error_2 << "\n      The entered Registration ID doesn't exist in file.\n" << normal << endl;
                closeFile(fs);
                system("pause");
                system("cls");
                goto loopaddcase;
                break;
            }

        UpdateList:

            system("cls");

            cout << color_i << "\n                    < Modify an existing record > " << normal;
            cout << "\n              Enter an existing information to update..";
            cout << "\n             Enter '0' to stop modifying and save record" << endl;
            cout << "\n    Registration ID                    : " << Seeker.registrationID;
            cout << "\n    Registration Date                  : " << Seeker.day << '/' << Seeker.month << '/' << Seeker.year;
            cout << color_5 << "\n    -------------------- < Seeker Information > --------------------" << normal;
            cout << "\n    A: First Name                      : " << Seeker.first_name;
            cout << "\n    B: Last Name                       : " << Seeker.last_name;
            cout << "\n    C: IC Number                       : " << Seeker.ic_number;
            cout << "\n    D: Contact Number                  : " << Seeker.contact_number;
            cout << "\n    E: Email Address                   : " << Seeker.email_address;
            cout << "\n    F: Marital Status                  : " << Seeker.marital_status;
            if (Seeker.marital_status == "Married")
            {
                cout << "\n    G: Spouse's Full Name              : " << Seeker.spouse_name;
                cout << "\n    H: Spouse's IC Number              : " << Seeker.spouse_ic_number;
                if (Seeker.children != 0)
                {
                    cout << "\n        Children                       : " << Seeker.children;
                    for (int i = 0; i < Seeker.children; i++)
                    {
                        cout << "\n\t\t\t\t  " << i + 1 << ") " << Seeker.children_arr[i];
                    }
                }
            }
            cout << color_3 << "\n    --------------- < Emergency Contact Information > ---------------" << normal;
            cout << "\n    I: Full Name                       : " << Seeker.emergency_fullname;
            cout << "\n    J: Contact Number                  : " << Seeker.emergency_number;
            cout << "\n    K: Relationship                    : " << Seeker.emergency_relationship;
            cout << color_1 << "\n    ---------------------- < Job Information > ----------------------" << normal;
            cout << "\n    L: Working Experience              : " << Seeker.working_exp << " year(s)";
            cout << "\n    M: Working Preference              : " << Seeker.working_pref;
            cout << "\n    N: Year of Graduation              : " << Seeker.graduate_year;
            cout << "\n    O: Highest Academic Qualification  : " << Seeker.qualification;
            cout << "\n    P: Graduating University           : " << Seeker.graduate_university << endl;
            cout << "\n    Select                             : ";

            char choice;
            cin >> choice;

            if (choice == '0')
            {
                goto update;
            }

            switch (choice)
            {
            case 'A':

                cout << color_a << "\n   *" << normal << " First Name                : ";

                getline(cin, Seeker.first_name);

                while (containsNumber(Seeker.first_name))
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid first name! " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John                    " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "   *" << normal << " First Name                : ";

                    getline(cin, Seeker.first_name);
                }
                Seeker.first_name[0] = toupper(Seeker.first_name[0]);

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'B':

                cout << color_a << "\n   *" << normal << " Last Name                 : ";
                getline(cin, Seeker.last_name);

                while (containsNumber(Seeker.last_name))
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid last name!  " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "Collins                 " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " Last Name                : ";
                    getline(cin, Seeker.last_name);
                }
                Seeker.last_name[0] = toupper(Seeker.last_name[0]);

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'C':

                cout << color_a << "\n    *" << normal << " IC Number                : ";
                cin >> Seeker.ic_number;



                while (Seeker.ic_number.find_first_of("1234567890") == string::npos || Seeker.ic_number.length() != 12)
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid IC Number!  " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "011231016703            " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " IC Number                : ";
                    cin >> Seeker.ic_number;
                }

                parseInt(Seeker.ic_number, 11, 1);

                if (Seeker.n % 2 == 0)
                {
                    Seeker.gender = "Female";
                }
                else
                {
                    Seeker.gender = "Male";
                }

                parseInt(Seeker.ic_number, 0, 2);

                if (Seeker.n > 20)
                {
                    Seeker.birthYear = 1900 + Seeker.n;
                    Seeker.age = Seeker.year - Seeker.birthYear;
                }
                else
                {
                    Seeker.birthYear = 2000 + Seeker.n;
                    Seeker.age = Seeker.year - Seeker.birthYear;
                }

                parseString(Seeker.birthYear);
                Seeker.dateOf_birth = Seeker.ic_number.substr(4, 2) + "/" + Seeker.ic_number.substr(2, 2) + "/" + Seeker.s;

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'D':

                cout << color_a << "\n    *" << normal << " Contact Number           : ";
                cin >> Seeker.contact_number;



                while (Seeker.contact_number.find_first_of("1234567890") == string::npos || (Seeker.contact_number.length() != 10 && Seeker.contact_number.length() != 11))
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid number!     " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "0123456789              " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " Contact Number           : ";
                    cin >> Seeker.contact_number;
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'E':

                cout << color_a << "\n    *" << normal << " Email Address            : ";
                cin >> Seeker.email_address;


                while (emailValidation(Seeker.email_address) != true)
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid email!      " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "john@example.com        " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " Email Address            : ";
                    cin >> Seeker.email_address;

                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'F':

                cout << "\n       --------------------------------------------------";
                cout << "\n       |                 Marital Status                 |";
                cout << "\n       --------------------------------------------------" << endl;
                cout << "\n   '1'                         : Single";
                cout << "\n   '2'                         : Married";
                cout << "\n   '3'                         : Divorced";
                cout << color_a << "\n    *" << normal << " Select                   : ";
                cin >> selector;

                do
                {
                    switch (selector)
                    {
                    case 1: Seeker.marital_status = "Single";
                        break;
                    case 2: Seeker.marital_status = "Married";
                        break;
                    case 3: Seeker.marital_status = "Divorced";
                        break;
                    default:
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cout << color_a << "    *" << normal << " Select                   : ";
                        cin >> selector;
                        break;
                    }
                } while (selector != 1 && selector != 2 && selector != 3);


                // Number of children
                if (selector == 2)
                {
                    cout << color_a << "\n    *" << normal << " Spouse's Full Name       : ";
                    cin.get();
                    getline(cin, Seeker.spouse_name);

                    while (containsNumber(Seeker.spouse_name))
                    {
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid full name!  " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John Collins            " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cout << color_a << "    *" << normal << " Spouse's Full Name       : ";
                        cin.get();
                        getline(cin, Seeker.spouse_name);
                    }
                    Seeker.spouse_name[0] = toupper(Seeker.spouse_name[0]);

                    cout << color_a << "    *" << normal << " Number of Children          : ";
                    cin >> Seeker.children;



                    // Add spouse name & children
                    if (Seeker.children != 0)
                    {
                        for (int i = 0; i < Seeker.children; i++)
                        {
                            string message;
                            switch (i)
                            {
                            case 0:
                                message = "st Child's Full Name       : ";
                                cout << "      " << i + 1 << message;
                                break;
                            case 1:
                                message = "nd Child's Full Name       : ";
                                cout << "      " << i + 1 << message;
                                break;
                            case 2:
                                message = "rd Child's Full Name       : ";
                                cout << "      " << i + 1 << message;
                                break;
                            default:
                                message = "th Child's Full Name       : ";
                                cout << "      " << i + 1 << message;
                                break;
                            }
                            string child;
                            getline(cin, child);
                            while (containsNumber(child))
                            {
                                cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                                cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid first name! " << error_2 << "*****" << endl;
                                cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John                    " << error_2 << "*****" << endl;
                                cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                                cout << "   " << i + 1 << message;
                                getline(cin, child);
                            }
                            child[0] = toupper(child[0]);
                            Seeker.children_arr.push_back(child);
                        }
                    }
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'G':

                if (Seeker.marital_status == "Married")
                {
                    cout << color_a << "\n    *" << normal << " Spouse's Full Name       : ";
                    cin.get();
                    getline(cin, Seeker.spouse_name);

                    while (containsNumber(Seeker.spouse_name))
                    {
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid full name!  " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John Collins            " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cout << color_a << "    *" << normal << " Spouse's Full Name       : ";
                        cin.get();
                        getline(cin, Seeker.spouse_name);
                    }
                    Seeker.spouse_name[0] = toupper(Seeker.spouse_name[0]);
                }
                else
                {
                    cout << "\n    " << error_1 << "No information recorded to modify." << normal << endl;
                }
                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'H':

                if (Seeker.marital_status == "Married")
                {
                    cout << color_a << "\n    *" << normal << " Spouse's IC Number       : ";
                    cin >> Seeker.spouse_ic_number;

                    while (Seeker.spouse_ic_number.find_first_of("1234567890") == string::npos || Seeker.spouse_ic_number.length() != 12)
                    {
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid IC Number!  " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "011231016703            " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cin >> Seeker.spouse_ic_number;
                        cout << color_a << "    *" << normal << " Spouse's IC Number       : ";
                    }
                }
                else
                {
                    cout << "\n    " << error_1 << "No information recorded to modify." << normal << endl;
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;


            case 'I':

                cout << color_a << "\n    *" << normal << " Full Name                : ";
                cin.get();
                getline(cin, Seeker.emergency_fullname);

                while (containsNumber(Seeker.emergency_fullname))
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid full name!  " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "John Collins            " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " Full Name                : ";
                    cin.get();
                    getline(cin, Seeker.emergency_fullname);
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'J':

                cout << color_a << "\n    *" << normal << " Contact Number           : ";
                cin >> Seeker.emergency_number;

                while (Seeker.emergency_number.find_first_of("1234567890") == string::npos || (Seeker.emergency_number.length() != 10 && Seeker.emergency_number.length() != 11))
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid number   !  " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "0123456789              " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " Contact Number           : ";
                    cin >> Seeker.emergency_number;
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'K':

                cout << "\n       --------------------------------------------------";
                cout << "\n       |                  Relationship                  |";
                cout << "\n       --------------------------------------------------" << endl;
                cout << "\n   '1'                         : Parent/Guardian";
                cout << "\n   '2'                         : Partner";
                cout << "\n   '3'                         : Sibling";
                cout << "\n   '4'                         : Relative";
                cout << "\n   '5'                         : Friend";
                cout << color_a << "\n    *" << normal << " Select                   : ";
                cin >> selector;

                do
                {
                    switch (selector)
                    {
                    case 1:
                        Seeker.emergency_relationship = "Parent/Guardian";
                        break;
                    case 2:
                        Seeker.emergency_relationship = "Partner";
                        break;
                    case 3:
                        Seeker.emergency_relationship = "Sibling";
                        break;
                    case 4:
                        Seeker.emergency_relationship = "Relative";
                        break;
                    case 5:
                        Seeker.emergency_relationship = "Friend";
                        break;
                    default:
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cout << color_a << "    *" << normal << " Select                   : ";
                        cin >> selector;
                        break;
                    }
                } while (selector < 1 || selector > 5);

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'L':

                cout << color_a << "\n    *" << normal << " Working Experience (years): ";
                cin >> Seeker.working_exp;

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'M':

                cout << "\n       --------------------------------------------------";
                cout << "\n       |               Working Preference               |";
                cout << "\n       --------------------------------------------------" << endl;
                cout << "\n   '1'                         : Part-time";
                cout << "\n   '2'                         : Full-time";
                cout << "\n   '3'                         : Both";
                cout << color_a << "\n    *" << normal << " Select                   : ";
                cin >> selector;

                do
                {
                    switch (selector)
                    {
                    case 1: Seeker.working_pref = "Part-time";
                        break;
                    case 2: Seeker.working_pref = "Full-time";
                        break;
                    case 3: Seeker.working_pref = "Part-time & Full-time";
                        break;
                    default:
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cout << color_a << "\n    *" << normal << " Select                   : ";
                        cin >> selector;
                        break;
                    }
                } while (selector != 1 && selector != 2 && selector != 3);

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'N':

                // Ask for which year user graduated
                cout << color_a << "\n    *" << normal << " Year of Graduation       : ";
                cin >> Seeker.graduate_year;

                while (Seeker.graduate_year >= Seeker.year)
                {
                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid year!       " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "2010                    " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "\n    *" << normal << " Year of Graduation       : ";
                    cin >> Seeker.graduate_year;
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'O':

                // Use Malaysia's qualification levels
                cout << "\n       --------------------------------------------------";
                cout << "\n       |         Highest Academic Qualification         |";
                cout << "\n       --------------------------------------------------" << endl;
                cout << "\n   '1'                         : Certificate";
                cout << "\n   '2'                         : Diploma";
                cout << "\n   '3'                         : Bachelor's Degree";
                cout << "\n   '4'                         : Master's Degree";
                cout << "\n   '5'                         : Doctoral Degree";
                cout << color_a << "\n    *" << normal << " Select                   : ";
                cin >> selector;

                do
                {
                    switch (selector)
                    {
                    case 1:
                        Seeker.qualification = "Certificate";
                        break;
                    case 2:
                        Seeker.qualification = "Diploma";
                        break;
                    case 3:
                        Seeker.qualification = "Bachelor's Degree";
                        break;
                    case 4:
                        Seeker.qualification = "Master's Degree";
                        break;
                    case 5:
                        Seeker.qualification = "Doctoral Degree";
                    default:
                        cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Invalid option! Please select a valid option!   " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "1                       " << error_2 << "*****" << endl;
                        cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                        cout << color_a << "    *" << normal << " Select                   : ";
                        cin >> selector;
                        break;
                    }
                } while (selector < 1 || selector > 5);

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            case 'P':

                // State which university
                cout << color_a << "\n    *" << normal << " Graduating University    : ";
                cin.get();
                getline(cin, Seeker.graduate_university);

                while (Seeker.graduate_university.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos || containsNumber(Seeker.graduate_university))
                {

                    cout << "   " << error_2 << "------------------------------^----------------------------" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Invalid input! Please enter a valid university! " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "*****" << error_1 << " Example               : " << error_3 << "Sunway University       " << error_2 << "*****" << endl;
                    cout << "   " << error_2 << "-----------------------------------------------------------" << normal << endl;
                    cout << color_a << "    *" << normal << " Graduating University    : ";
                    cin.get();
                    getline(cin, Seeker.graduate_university);
                }

                cout << "To continue modifying, ";
                system("pause");
                system("cls");
                goto UpdateList;
                break;

            update:

                fs->seekp(sizeof(Seeker) * recs_num, ios::beg); // go to the first of the record to be modified     
                fs->write((char*)&Seeker, sizeof(Seeker));

                closeFile(fs);
                cout << color_a << "\n    Record saved and updated." << normal << endl;
                system("pause");
                system("cls");
                goto loopaddcase;
                break;

            default:

                goto UpdateList;
                break;

            }//end(update) switch

        case '4': ////// Delete Record //////

            system("cls");

            cout << color_j << "\n                    < Delete an existing record > " << normal;
            cout << "\n              Enter an existing information to update.." << endl;
            cout << "\n    Registration ID                   : ";
            cin >> id;

            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::out | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << SEEKER_FILE_NAME << "' file." << endl;
                system("pause");
                break;
            }

            recs_num = -1;

            while (fs->read((char*)&Seeker, sizeof(Seeker)))
            {
                recs_num++;

                if (Seeker.registrationID == id && !Seeker.deleted) // if user deleted an Seeker then added another one with the same ID in the same instance of program runs, deleted Seeker is still there, then we should go through all the file
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
            {
                cout << error_1 << "\n The entered Registration ID doesn't exist in database file." << normal << endl;
                closeFile(fs);
                system("pause");
                break;
            }

            Seeker.deleted = 1;

            fs->seekp(sizeof(Seeker) * recs_num, ios::beg);
            fs->write((char*)&Seeker, sizeof(Seeker));

            closeFile(fs);

            deletion = true; // we have some deleted records

            cout << color_a << "\n    Record successfully deleted.\n" << normal << endl;
            system("pause");

            break;


        case '5': // Display Records

            cout << color_k << "\n                       < Display all Records >" << normal << endl;

            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << SEEKER_FILE_NAME << "' file." << endl;
                system("pause");
                break;
            }

            while (fs->read((char*)&Seeker, sizeof(Seeker))) // display records
            {
                if (!Seeker.deleted)
                {
                    cout << color_a << "\n    ----------------------- < Seeker Record > -----------------------" << normal;
                    cout << "\n    Registration ID                : " << Seeker.registrationID;
                    cout << "\n    Registration Date              : " << Seeker.day << '/' << Seeker.month << '/' << Seeker.year;
                    cout << color_5 << "\n    -------------------- < Seeker Information > --------------------" << normal;
                    cout << "\n    First Name                     : " << Seeker.first_name;
                    cout << "\n    Last Name                      : " << Seeker.last_name;
                    cout << "\n    IC Number                      : " << Seeker.ic_number;
                    cout << "\n    Gender                         : " << Seeker.gender;
                    cout << "\n    Age                            : " << Seeker.age;
                    cout << "\n    Date of Birth                  : " << Seeker.dateOf_birth;
                    cout << "\n    Contact Number                 : " << Seeker.contact_number;
                    cout << "\n    Email Address                  : " << Seeker.email_address;
                    cout << "\n    Marital Status                 : " << Seeker.marital_status;
                    if (Seeker.marital_status == "Married")
                    {
                        cout << "\n    Spouse's Full Name             : " << Seeker.spouse_name;
                        cout << "\n    Spouse's IC Number             : " << Seeker.spouse_ic_number << endl;
                        if (Seeker.children != 0)
                        {
                            cout << "    Children                       : " << Seeker.children << endl;
                            for (int i = 0; i < Seeker.children; i++)
                            {
                                cout << "\t\t\t\t " << i + 1 << ") " << Seeker.children_arr[i] << endl;
                            }
                        }
                    }
                    cout << color_3 << "    --------------- < Emergency Contact Information > ---------------" << normal;
                    cout << "\n    Full Name                      : " << Seeker.emergency_fullname;
                    cout << "\n    Contact Number                 : " << Seeker.emergency_number;
                    cout << "\n    Relationship                   : " << Seeker.emergency_relationship;
                    cout << color_1 << "\n    ---------------------- < Job Information > ----------------------" << normal;
                    cout << "\n    Working Experience             : " << Seeker.working_exp << " year(s)";
                    cout << "\n    Working Preference             : " << Seeker.working_pref;
                    cout << "\n    Year of Graduation             : " << Seeker.graduate_year;
                    cout << "\n    Highest Academic Qualification : " << Seeker.qualification;
                    cout << "\n    Graduating University          : " << Seeker.graduate_university << endl;
                }
                cout << color_k << "\n    *****************************************************************" << normal << endl;
            }

            cout << "\n To return to menu, ";
            system("pause");
            system("cls");
            closeFile(fs);
            goto loopaddcase;
            break;

        case '6': // Exit

            if (deletion) // if there is any deletion, then update database file (create a new temp file that doesn't have deleted records, then remove the old database file and rename temp file to database file name)
            {
                cout << "\n Updating '" << SEEKER_FILE_NAME << "' File..." << endl;

                fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::binary);
                if (!fs)
                {
                    cout << "\n Can't open '" << SEEKER_FILE_NAME << "' file, then Updating is incomplete." << endl;
                    system("pause");

                    system("cls");
                    return 1;
                }

                fs1 = new fstream("temp", ios::out | ios::binary);
                if (!fs1)
                {
                    cout << "\n Can't create temp file, then Updating is incomplete." << endl;
                    system("pause");

                    closeFile(fs);
                    system("cls");
                    return 1;
                }

                // write nondeleted records to the temp file
                while (fs->read((char*)&Seeker, sizeof(Seeker)))
                    if (!Seeker.deleted)
                        fs1->write((char*)&Seeker, sizeof(Seeker));

                closeFile(fs);
                closeFile(fs1);

                if (remove(SEEKER_FILE_NAME) == -1) // if there is an error
                {
                    cout << "\n Can't delete '" << SEEKER_FILE_NAME << "' file, then Updating is incomplete." << endl;
                    system("pause");

                    system("cls");
                    return 1;
                }


                struct stat st; // to check size of the temp file
                int res = stat("temp", &st);

                if (st.st_size == 0) // if all of records are deleted then the temp file size is zero
                    remove("temp"); // we have no records, then no database file is needed, just delete the temp file
                else
                    if (rename("temp", SEEKER_FILE_NAME))
                    {
                        cout << "\n Can't rename temp file, then Updating is incomplete." << endl;
                        system("pause");

                        system("cls");
                        return 1;
                    }

                cout << "\n Updating database file completed." << endl;
                system("pause");
            }

            system("cls");
            return 0;
            break;

        } // end 'switch'
    } // end 'while'

    return 0;

} // end 'main()'


    /////////////     Function Definitions    /////////////

void closeFile(fstream* fs)
{
    fs->close(); // close the file
    delete fs;
    fs = NULL;
}


bool isFileExist(const char* file_name)
{
    struct stat st; // to check status of file
    int res = stat(file_name, &st);
    return (res == 0); // if file exists     
}