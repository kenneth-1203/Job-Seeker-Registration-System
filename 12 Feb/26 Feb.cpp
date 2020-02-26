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
using namespace std;


/////////////     Data types    /////////////



struct Seeker_Record // Seeker record
{
    // Declare all variables after this line
    // --- 12 FEB 2020 ---
    string first_name;
    string last_name;
    string ic_number;
    string contact_number;
    string emergency_number;
    string email_address;
    string dateOf_birth;
    string dob;
    string marital_status;
    string working_pref;
    string qualification;
    string gender;
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


/////////////     Main    /////////////
int main()
{
    while (true)
    {
        do ////// Menu //////
        {
            system("cls"); // clear screen

            cout << "\n    < Seekers Database > \n\n";
            cout << "(1) Add     a new Record \n";
            cout << "(2) Search an existing Record\n";
            cout << "(3) Modify an existing Record\n";
            cout << "(4) Delete an existing Record \n";
            cout << "(5) Display Records \n";
            cout << "(6) Exit \n\n";
            cout << " Enter a choice (1-5) : " << flush;
            choice = _getch();
        } while (choice < '1' || choice > '5'); // while we have no good(between 1 and 5), show menu again

        system("cls");

        // to modify, delete or display records, database file should exist, then we have some records           
        if (choice == '2' || choice == '3' || choice == '4')
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

            cout << "\n\t\t < Entering a new record > ";
            cout << "\n   Enter the following informations for the new record : " << endl;

            // --- 26 FEB 2020 ---
            int selector;

            cout << "\n   First Name                  : ";
            cin >> Seeker.first_name;
            
            cin.get();

            while (Seeker.first_name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
            {
                cout << "   ------------------------------^----------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid first name! *****" << endl;
                cout << "   ***** Example:    George                              *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   First Name                  : ";
                getline(cin, Seeker.first_name);
            }
            Seeker.first_name[0] = toupper(Seeker.first_name[0]);
            
            cout << "   Last Name                   : ";
            cin >> Seeker.last_name;

            cin.get();

            while (Seeker.last_name.find_first_of("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == string::npos)
            {
                cout << "   ------------------------------^----------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid last name!  *****" << endl;
                cout << "   ***** Example:    Washington                          *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   Last Name                  : ";
                getline(cin, Seeker.last_name);
            }
            Seeker.last_name[0] = toupper(Seeker.last_name[0]);

            cout << "   IC Number                   : ";
            cin >> Seeker.ic_number;

            cin.get();

            while (Seeker.ic_number.find_first_of("1234567890") == string::npos || Seeker.ic_number.length() != 12)
            {
                cout << "   ------------------------------^----------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid IC number!  *****" << endl;
                cout << "   ***** Example:    012049056709                        *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   IC Number                   : ";
                getline(cin, Seeker.ic_number);
            }
                    
            cout << "\n   -----------------------------------------------------------";
            cout << "\n   |                      Date of Birth                      |";
            cout << "\n   -----------------------------------------------------------" << endl;
            cout << "\n   Day (DD)                    : ";
            cin >> Seeker.dob;

            while (Seeker.dob.find_first_of("1234567890") == string::npos || Seeker.dob.length() != 2)
            {
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid day!        *****" << endl;
                cout << "   ***** Example:    31                                  *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   Day (DD)                    : ";
                cin >> Seeker.dob;
            }
            Seeker.dateOf_birth.append(Seeker.dob + "/");

            cout << "   Month (MM)                  : ";
            cin >> Seeker.dob;

            while (Seeker.dob.find_first_of("1234567890") == string::npos || Seeker.dob.length() != 2)
            {
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid month!      *****" << endl;
                cout << "   ***** Example:    12                                  *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   Month (MM)                  : ";
                cin >> Seeker.dob;
            }
            Seeker.dateOf_birth.append(Seeker.dob + "/");

            cout << "   Year (YYYY)                 : ";
            cin >> Seeker.dob;

            while (Seeker.dob.find_first_of("1234567890") == string::npos || Seeker.dob.length() != 4)
            {
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid year!       *****" << endl;
                cout << "   ***** Example:    1995                                *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   Year (YYYY)                 : ";
                cin >> Seeker.dob;
            }
            Seeker.dateOf_birth.append(Seeker.dob);

            cout << "\n   -----------------------------------------------------------";
            cout << "\n   |                         Gender                          |";
            cout << "\n   -----------------------------------------------------------" << endl;
            cout << "\n   '1'   : Male";
            cout << "\n   '2'   : Female";
            cout << "\n   Select: ";
            cin >> selector;

            do {
                switch (selector)
                {
                case 1: Seeker.gender = "Male";
                    break;
                case 2: Seeker.gender = "Female";
                    break;
                default:
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   ***** Invalid option! Please select a valid option!   *****" << endl;
                    cout << "   ***** Example:    1                                   *****" << endl;
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   Select: ";
                    cin >> selector;
                    break;
                }
            } while (selector != 1 && selector != 2);

            cout << "   Contact Number              : ";
            cin >> Seeker.contact_number;

            while (Seeker.contact_number.find_first_of("1234567890") == string::npos || (Seeker.contact_number.length() != 10 && Seeker.contact_number.length() != 11))
            {
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid number!     *****" << endl;
                cout << "   ***** Example:    0123456789                          *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   Contact Number              : ";
                cin >> Seeker.contact_number;
            }

            cout << "   Emergency Contact Number    : ";
            cin >> Seeker.emergency_number;

            while (Seeker.emergency_number.find_first_of("1234567890") == string::npos || (Seeker.emergency_number.length() != 10 && Seeker.emergency_number.length() != 11))
            {
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   ***** Invalid input! Please enter a valid number!     *****" << endl;
                cout << "   ***** Example:    0123456789                          *****" << endl;
                cout << "   -----------------------------------------------------------" << endl;
                cout << "   Emergency Contact Number    : ";
                cin >> Seeker.emergency_number;
            }

            cout << "   Email Address               : ";
            cin >> Seeker.email_address;

            cout << "   Working Experience (years)  : ";
            cin >> Seeker.working_exp;

            cout << "\n   -----------------------------------------------------------";
            cout << "\n   |                     Marital Status                      |";
            cout << "\n   -----------------------------------------------------------" << endl;
            cout << "\n   '1'   : Single";
            cout << "\n   '2'   : Married";
            cout << "\n   Select: ";
            cin >> selector;

            do {
                switch (selector)
                {
                case 1: Seeker.marital_status = "Single";
                    break;
                case 2: Seeker.marital_status = "Married";
                    break;
                default: 
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   ***** Invalid option! Please select a valid option!   *****" << endl;
                    cout << "   ***** Example:    1                                   *****" << endl;
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   Select: ";
                    cin >> selector;
                    break;
                }
            } while (selector != 1 && selector != 2);

            cout << "\n   -----------------------------------------------------------";
            cout << "\n   |                   Working Preference                    |";
            cout << "\n   -----------------------------------------------------------" << endl;
            cout << "\n   '1'   : Part-time";
            cout << "\n   '2'   : Full-time";
            cout << "\n   '3'   : Both";
            cout << "\n   Select: ";
            cin >> selector;

            do {
                switch (selector)
                {
                case 1: Seeker.working_pref = "Part-time";
                    break;
                case 2: Seeker.working_pref = "Full-time";
                    break;
                case 3: Seeker.working_pref = "Both";
                    break;
                default: 
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   ***** Invalid option! Please select a valid option!   *****" << endl;
                    cout << "   ***** Example:    1                                   *****" << endl;
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   Select: ";
                    cin >> selector;
                    break;
                }
            } while (selector != 1 && selector != 2 && selector != 3);

            cout << "\n   -----------------------------------------------------------";
            cout << "\n   |              Academic Qualification Level               |";
            cout << "\n   -----------------------------------------------------------" << endl;
            cout << "\n   '1':    Higher Certificate";
            cout << "\n   '2':    National Diploma";
            cout << "\n   '3':    Bachelor's Degree";
            cout << "\n   '4':    Honours Degree";
            cout << "\n   Select : ";
            cin >> selector;

            do {
                switch (selector)
                {
                case 1: Seeker.qualification = "Higher Certificate";
                    break;
                case 2: Seeker.qualification = "National Diploma";
                    break;
                case 3: Seeker.qualification = "Bachelor's Degree";
                    break;
                case 4: Seeker.qualification = "Honours Degree";
                    break;
                default: 
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   ***** Invalid option! Please select a valid option!   *****" << endl;
                    cout << "   ***** Example:    1                                   *****" << endl;
                    cout << "   -----------------------------------------------------------" << endl;
                    cout << "   Select: ";
                    cin >> selector;
                    break;
                }
            } while (selector < 1 || selector > 4);

            // Don't touch after this line
            Seeker.deleted = 0;

            fs = new fstream(SEEKER_FILE_NAME, ios::out | ios::app | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << SEEKER_FILE_NAME << "' file" << endl;
                system("pause");
                break;
            }

            fs->write((char*)&Seeker, sizeof(Seeker));

            closeFile(fs);

            cout << "\n Record added." << endl;
            system("pause");

            break;
/*
        case '2': ////// Modify Record //////

            cout << "\n Enter Seeker ID, that you want modify its informatin : ";
            cin >> id;

            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::out | ios::binary);

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

                if (Seeker.ID == id && !Seeker.deleted)
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
            {
                cout << "\n Your specified Seeker doesn't exist in file." << endl;
                closeFile(fs);
                system("pause");
                break;
            }


            cout << "\n   Enter new informations for this record : ";
            cout << "\n\n PAY_TYPE ( SALARIED : 0, HOURLY : 1 ) : ";
            cin >> Seeker.PAY_TYPE;

            cout << "\n ID : ";
            cin >> Seeker.ID;
            cout << "\n AGE : ";
            cin >> Seeker.AGE;
            cout << "\n DEPT (one character) : ";
            cin >> Seeker.DEPT;

            if (Seeker.PAY_TYPE == SALARIED)
            {
                cout << "\n MONTHLY_RATE : ";
                cin >> Seeker.MONTHLY_RATE;
                cout << "\n START_DATE : ";
                cin >> Seeker.START_DATE;
            }

            if (Seeker.PAY_TYPE == HOURLY)
            {
                cout << "\n RATE_PER_HOUR : ";
                cin >> Seeker.RATE_PER_HOUR;
                cout << "\n REG_HOURS : ";
                cin >> Seeker.REG_HOURS;
                cout << "\n OVERTIME_HOURS : ";
                cin >> Seeker.OVERTIME_HOURS;
            }


            fs->seekp(sizeof(Seeker) * recs_num, ios::beg); // go to the first of the record to be modified
            fs->write((char*)&Seeker, sizeof(Seeker));

            closeFile(fs);

            cout << "\n Record is modified." << endl;
            system("pause");

            break;


        case '3': ////// Delete Record //////

            cout << "\n Enter Seeker's ID, for deletion : ";
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

                if (Seeker.ID == id && !Seeker.deleted) // if user deleted an Seeker then added another one with the same ID in the same instance of program runs, deleted Seeker is still there, then we should go through all the file
                    break;
            }

            if (fs->eof()) // if (the record is not in the file || it's there but it's deleted)
            {
                cout << "\n Your specified Seeker doesn't exist in database file." << endl;
                closeFile(fs);
                system("pause");
                break;
            }

            Seeker.deleted = 1;

            fs->seekp(sizeof(Seeker) * recs_num, ios::beg);
            fs->write((char*)&Seeker, sizeof(Seeker));

            closeFile(fs);

            deletion = true; // we have some deleted records

            cout << "\n Record is deleted." << endl;
            system("pause");

            break;


        case '4': // Display Records

              ////// Print Salaried records...
            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << SEEKER_FILE_NAME << "' file." << endl;
                system("pause");
                break;
            }

            // display column titles
            cout << "\n\t\t < Salaried >\n\n";
            cout << "ID\tAGE\tDEPT\tMONTHLY_RATE\tSTART_DATE\n"
                << "-------------------------------------------------- \n";

            while (fs->read((char*)&Seeker, sizeof(Seeker))) // display records
            {
                if (Seeker.PAY_TYPE == SALARIED && !Seeker.deleted)
                {
                    cout << Seeker.ID << '\t';
                    cout << Seeker.AGE << '\t';
                    cout << Seeker.DEPT << '\t';
                    cout << Seeker.MONTHLY_RATE << "\t\t";
                    cout << Seeker.START_DATE << '\n';
                }
            }

            cout << "\n To see Hourly records, "; system("pause");

            closeFile(fs);

            ////// Print Hourly records...                 
            system("cls");

            fs = new fstream(SEEKER_FILE_NAME, ios::in | ios::binary);

            if (!fs)
            {
                cout << "\n Can't open or create '" << SEEKER_FILE_NAME << "' file." << endl;
                system("pause");
                break;
            }

            cout << "\n\t\t\t < Hourly > \n\n";
            cout << "ID\tAGE\tDEPT\tRATE_PER_HOUR\tREG_HOURS\tOVERTIME_HOURS\n"
                << "---------------------------------------------------------------------- \n";

            while (fs->read((char*)&Seeker, sizeof(Seeker_Record)))
            {
                if (Seeker.PAY_TYPE == HOURLY && !Seeker.deleted)
                {
                    cout << Seeker.ID << '\t';
                    cout << Seeker.AGE << '\t';
                    cout << Seeker.DEPT << '\t';
                    cout << Seeker.RATE_PER_HOUR << "\t\t";
                    cout << Seeker.REG_HOURS << "\t\t";
                    cout << Seeker.OVERTIME_HOURS << '\n';
                }
            }

            cout << "\n To see menu, "; system("pause");

            closeFile(fs);

            break;
*/

        case '5': // Exit

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