#include <iostream>
#include <string>
using namespace std;
//we're using abstraction here

class Person
{
    // using encapsulation 
private:
    int id;
    string name;
    int age;
    string city;
public:
    
    Person()
    {
        id   = 0;
        age  = 0;
        name = "";
        city = "";
    }
    // giving parametres to teh above constructor
    Person(int i, string n, int a, string c)
    {
        id   = i;
        name = n;
        age  = a;
        city = c;
    }
    // ENCAPSULATION : Setter functions (to set private data)
    void setId(int i)      
	{ 
	id   = i;  
	}
    void setName(string n) 
	{ 
	name = n; 
	}
    void setAge(int a)     
	{ 
	age  = a; 
	}
    void setCity(string c) 
	{ 
	city = c; 
	}
    // ENCAPSULATION : Getter functions (to read private data)
    int    getId()   
	{ 
	return id;   
	}
    string getName() 
	{ 
	return name; 
	}
    int    getAge()  
	{ 
	return age;  
	}
    string getCity() 
	{ 
	return city; 
	}
    //polymorphism + abstraction
    virtual void displayInfo() = 0;
    // Virtual destructor because it's good practice
    virtual ~Person() {}
};
// using the concept of inheritance
class Criminal : public Person
{
private:
    string crimeType;
    string punishment;
    string status;      // "Arrested" or "Wanted"

public:
    //using the concept of def constructor
    Criminal() : Person()
    {
        crimeType  = "";
        punishment = "";
        status     = "";
    }
    //giving the parametres to the above constructor
    // Uses constructor chaining - calls Person constructor first
    Criminal(int id, string name, int age, string city,
             string crime, string punish, string stat)
             : Person(id, name, age, city)
    {
        crimeType  = crime;
        punishment = punish;
        status     = stat;
    }
    // Setters for Criminal-specific data
    void setCrimeType(string c)  
	{ 
	crimeType  = c; 
	}
    void setPunishment(string p) 
	{ 
	punishment = p; 
	}
    void setStatus(string s)     
	{ 
	status     = s; 
	}
    // Getters for Criminal-specific data
    string getCrimeType()  
	{ 
	return crimeType;  
	}
    string getPunishment() 
	{ 
	return punishment; 
	}
    string getStatus()     
	{ 
	return status;     
	}
    // using the concept of polymorphism again
    // Overriding the pure virtual function from Person
    void displayInfo()
    {
        cout << "--------------------------------------------" << endl;
        cout << "  Criminal ID  : " << getId()      << endl;
        cout << "  Name         : " << getName()    << endl;
        cout << "  Age          : " << getAge()     << endl;
        cout << "  City         : " << getCity()    << endl;
        cout << "  Crime Type   : " << crimeType    << endl;
        cout << "  Punishment   : " << punishment   << endl;
        cout << "  Status       : " << status       << endl;
        cout << "--------------------------------------------" << endl;
    }
};
// using the concept of inheritence again
// Officer class also inherits from Person class
// Both Criminal and Officer share Person's data via inheritance
class Officer : public Person
{
    // Additional private data specific to Officer
private:
    string badgeNumber;
    string rank;
    string department;

public:
    // CONCEPT 6: DEFAULT CONSTRUCTOR
    Officer() : Person()
    {
        badgeNumber = "";
        rank        = "";
        department  = "";
    }
    // CONCEPT 6: PARAMETERIZED CONSTRUCTOR
    Officer(int id, string name, int age, string city,
            string badge, string r, string dept)
            : Person(id, name, age, city)
    {
        badgeNumber = badge;
        rank        = r;
        department  = dept;
    }
    // Setters
    void setBadgeNumber(string b) { badgeNumber = b; }
    void setRank(string r)        { rank        = r; }
    void setDepartment(string d)  { department  = d; }
    // Getters
    string getBadgeNumber() { return badgeNumber; }
    string getRank()        { return rank;        }
    string getDepartment()  { return department;  }
    // CONCEPT 4: POLYMORPHISM
    // Same function name displayInfo() but different behavior for Officer
    void displayInfo()
    {
        cout << "--------------------------------------------" << endl;
        cout << "  Officer ID   : " << getId()      << endl;
        cout << "  Name         : " << getName()    << endl;
        cout << "  Age          : " << getAge()     << endl;
        cout << "  City         : " << getCity()    << endl;
        cout << "  Badge No.    : " << badgeNumber  << endl;
        cout << "  Rank         : " << rank         << endl;
        cout << "  Department   : " << department   << endl;
        cout << "--------------------------------------------" << endl;
    }
};
// MAIN SYSTEM CLASS
// Handles all operations: add, search, update, delete, display
class CriminalManagementSystem
{
private:
    // Arrays to store records (max 100 each)
    Criminal criminalList[100];
    Officer  officerList[100];
    int criminalCount;
    int officerCount;
public:
    // Constructor - sets up the system counter trackers
    CriminalManagementSystem()
    {
        criminalCount = 0;
        officerCount  = 0;
    }
    // CRIMINAL OPERATIONS
    void addCriminal()
    {
        if (criminalCount >= 100)
        {
            cout << "\n  System full! Cannot add more criminals." << endl;
            return;
        }
        cout << "\n  --- Add New Criminal Record ---" << endl;
        int    id, age;
        string name, city, crime, punish, stat;
        cout << "  Enter ID        : "; cin >> id;   cin.ignore();
        cout << "  Enter Name      : "; getline(cin, name);
        cout << "  Enter Age       : "; cin >> age;  cin.ignore();
        cout << "  Enter City      : "; getline(cin, city);
        cout << "  Enter Crime     : "; getline(cin, crime);
        cout << "  Enter Punishment: "; getline(cin, punish);
        cout << "  Status (Arrested/Wanted): "; getline(cin, stat);
        // Using parameterized constructor to create a Criminal object
        criminalList[criminalCount] = Criminal(id, name, age, city, crime, punish, stat);
        criminalCount++;
        cout << "\n  Record added successfully!" << endl;
    }

    void displayAllCriminals()
    {
        cout << "\n  === All Criminal Records ===" << endl;
        if (criminalCount == 0)
        {
            cout << "  No records found." << endl;
            return;
        }
        // POLYMORPHISM in action: displayInfo() calls Criminal's version
        for (int i = 0; i < criminalCount; i++)
            criminalList[i].displayInfo();
    }

    void searchCriminalById()
    {
        int id;
        cout << "\n  Enter Criminal ID to search: ";
        cin >> id;
        for (int i = 0; i < criminalCount; i++)
        {
            if (criminalList[i].getId() == id)
            {
                cout << "\n  Record found:" << endl;
                criminalList[i].displayInfo();
                return;
            }
        }
        cout << "\n  No record found with ID " << id << endl;
    }

    void searchCriminalByName()
    {
        string name;
        cin.ignore();
        cout << "\n  Enter Name to search: ";
        getline(cin, name);

        bool found = false;
        for (int i = 0; i < criminalCount; i++)
        {
            if (criminalList[i].getName() == name)
            {
                criminalList[i].displayInfo();
                found = true;
            }
        }
        if (!found)
            cout << "\n  No record found with name: " << name << endl;
    }

    void updateCriminal()
    {
        int id;
        cout << "\n  Enter Criminal ID to update: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < criminalCount; i++)
        {
            if (criminalList[i].getId() == id)
            {
                cout << "\n  Current Record:" << endl;
                criminalList[i].displayInfo();
                cout << "\n  Enter new details:" << endl;
                string name, city, crime, punish, stat;
                int age;
                cout << "  New Name      : "; getline(cin, name);
                cout << "  New Age       : "; cin >> age; cin.ignore();
                cout << "  New City      : "; getline(cin, city);
                cout << "  New Crime     : "; getline(cin, crime);
                cout << "  New Punishment: "; getline(cin, punish);
                cout << "  New Status    : "; getline(cin, stat);
                // Using setter functions (Encapsulation)
                criminalList[i].setName(name);
                criminalList[i].setAge(age);
                criminalList[i].setCity(city);
                criminalList[i].setCrimeType(crime);
                criminalList[i].setPunishment(punish);
                criminalList[i].setStatus(stat);
                cout << "\n  Record updated successfully!" << endl;
                return;
            }
        }
        cout << "\n  No record found with ID " << id << endl;
    }

    void deleteCriminal()
    {
        int id;
        cout << "\n  Enter Criminal ID to delete: ";
        cin >> id;

        for (int i = 0; i < criminalCount; i++)
        {
            if (criminalList[i].getId() == id)
            {
                // Shift all records after this one to the left
                for (int j = i; j < criminalCount - 1; j++)
                    criminalList[j] = criminalList[j + 1];
                criminalCount--;
                cout << "\n  Record deleted successfully!" << endl;
                return;
            }
        }
        cout << "\n  No record found with ID " << id << endl;
    }
    // --------------------------------------------------------
    // OFFICER OPERATIONS
    // --------------------------------------------------------
    void addOfficer()
    {
        if (officerCount >= 100)
        {
            cout << "\n  System full! Cannot add more officers." << endl;
            return;
        }
        cout << "\n  --- Add New Officer Record ---" << endl;
        int    id, age;
        string name, city, badge, rank, dept;
        cout << "  Enter ID          : "; cin >> id;  cin.ignore();
        cout << "  Enter Name        : "; getline(cin, name);
        cout << "  Enter Age         : "; cin >> age; cin.ignore();
        cout << "  Enter City        : "; getline(cin, city);
        cout << "  Enter Badge Number: "; getline(cin, badge);
        cout << "  Enter Rank        : "; getline(cin, rank);
        cout << "  Enter Department  : "; getline(cin, dept);
        officerList[officerCount] = Officer(id, name, age, city, badge, rank, dept);
        officerCount++;
        cout << "\n  Record added successfully!" << endl;
    }

    void displayAllOfficers()
    {
        cout << "\n  === All Officer Records ===" << endl;

        if (officerCount == 0)
        {
            cout << "  No records found." << endl;
            return;
        }
        // POLYMORPHISM: same displayInfo() call, but Officer's version runs
        for (int i = 0; i < officerCount; i++)
            officerList[i].displayInfo();
    }

    void searchOfficerById()
    {
        int id;
        cout << "\n  Enter Officer ID to search: ";
        cin >> id;

        for (int i = 0; i < officerCount; i++)
        {
            if (officerList[i].getId() == id)
            {
                cout << "\n  Record found:" << endl;
                officerList[i].displayInfo();
                return;
            }
        }
        cout << "\n  No record found with ID " << id << endl;
    }

    void updateOfficer()
    {
        int id;
        cout << "\n  Enter Officer ID to update: ";
        cin >> id;
        cin.ignore();

        for (int i = 0; i < officerCount; i++)
        {
            if (officerList[i].getId() == id)
            {
                cout << "\n  Current Record:" << endl;
                officerList[i].displayInfo();
                cout << "\n  Enter new details:" << endl;
                string name, city, badge, rank, dept;
                int age;

                cout << "  New Name        : "; 
				getline(cin, name);
                cout << "  New Age         : "; 
				cin >> age; cin.ignore();
                cout << "  New City        : "; 
				getline(cin, city);
                cout << "  New Badge Number: "; 
				getline(cin, badge);
                cout << "  New Rank        : "; 
				getline(cin, rank);
                cout << "  New Department  : "; 
				getline(cin, dept);
                officerList[i].setName(name);
                officerList[i].setAge(age);
                officerList[i].setCity(city);
                officerList[i].setBadgeNumber(badge);
                officerList[i].setRank(rank);
                officerList[i].setDepartment(dept);
                cout << "\n  Record updated successfully!" << endl;
                return;
            }
        }
        cout << "\n  No record found with ID " << id << endl;
    }

    void deleteOfficer()
    {
        int id;
        cout << "\n  Enter Officer ID to delete: ";
        cin >> id;

        for (int i = 0; i < officerCount; i++)
        {
            if (officerList[i].getId() == id)
            {
                for (int j = i; j < officerCount - 1; j++)
                    officerList[j] = officerList[j + 1];

                officerCount--;
                cout << "\n  Record deleted successfully!" << endl;
                return;
            }
        }
        cout << "\n  No record found with ID " << id << endl;
    }
    // --------------------------------------------------------
    // MENUS
    // --------------------------------------------------------
    void criminalMenu()
    {
        int choice;
        do
        {
            cout << "\n  =============================" << endl;
            cout << "   CRIMINAL RECORDS MENU"         << endl;
            cout << "  =============================" << endl;
            cout << "  1. Add Criminal"                << endl;
            cout << "  2. Display All Criminals"       << endl;
            cout << "  3. Search by ID"                << endl;
            cout << "  4. Search by Name"              << endl;
            cout << "  5. Update Criminal"             << endl;
            cout << "  6. Delete Criminal"             << endl;
            cout << "  0. Back"                        << endl;
            cout << "  =============================" << endl;
            cout << "  Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1: addCriminal();          break;
                case 2: displayAllCriminals();  break;
                case 3: searchCriminalById();   break;
                case 4: searchCriminalByName(); break;
                case 5: updateCriminal();       break;
                case 6: deleteCriminal();       break;
                case 0: break;
                default: cout << "\n  Invalid choice!" << endl;
            }

        } while (choice != 0);
    }

    void officerMenu()
    {
        int choice;
        do
        {
            cout << "\n  =============================" << endl;
            cout << "   OFFICER RECORDS MENU"          << endl;
            cout << "  =============================" << endl;
            cout << "  1. Add Officer"                 << endl;
            cout << "  2. Display All Officers"        << endl;
            cout << "  3. Search by ID"                << endl;
            cout << "  4. Update Officer"              << endl;
            cout << "  5. Delete Officer"              << endl;
            cout << "  0. Back"                        << endl;
            cout << "  =============================" << endl;
            cout << "  Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1: addOfficer();         break;
                case 2: displayAllOfficers(); break;
                case 3: searchOfficerById();  break;
                case 4: updateOfficer();      break;
                case 5: deleteOfficer();      break;
                case 0: break;
                default: cout << "\n  Invalid choice!" << endl;
            }
        } while (choice != 0);
    }

    void mainMenu()
    {
        int choice;
        do
        {
            cout << "\n  =============================" << endl;
            cout << "   CRIMINAL MANAGEMENT SYSTEM"    << endl;
            cout << "  =============================" << endl;
            cout << "  1. Criminal Records"            << endl;
            cout << "  2. Officer Records"             << endl;
            cout << "  0. Exit"                        << endl;
            cout << "  =============================" << endl;
            cout << "  Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1: criminalMenu(); break;
                case 2: officerMenu();  break;
                case 0: cout << "\n  Goodbye!" << endl; break;
                default: cout << "\n  Invalid choice!" << endl;
            }
        } while (choice != 0);
    }
};
// MAIN FUNCTION
int main()
{
    // Creating an object of the system class
    CriminalManagementSystem system;
    // Running the main menu
    system.mainMenu();
    return 0;
}
