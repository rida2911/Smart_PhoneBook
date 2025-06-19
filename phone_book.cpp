#include <windows.h> //sleep and system (termical color)
#include <iostream> //input and output
#include <string>
#include <algorithm> //sort method used
#include<fstream> //file handling
#include <regex> //email validation

using namespace std;

//node to store each contact
struct Contact {
    string firstName;
    string lastName;
    string phoneNumber;
    string email;
    Contact* next; //pointer to the next node

    //constructor
    Contact(const string& fn, const string& ln, const string& phone, const string& mail)
        : firstName(fn), lastName(ln), phoneNumber(phone), email(mail), next(nullptr) {}
};

//SinglyLinkedList
class PhoneBook {
private:
    Contact* head;

public:
    PhoneBook() : head(nullptr) {}



    bool isValidPhoneNumber(const string& phoneNumber) {
        // Check if the phone number contains only digits and has a specific length
        if (phoneNumber.length() != 10) {
            return false;
        }

        for (char digit : phoneNumber) {
            if (!isdigit(digit)) {
                return false;
            }
        }

        return true;
    }

    bool isValidEmail(const std::string& email) {
        // Regular expression to validate an email address
        const std::regex pattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");
        return std::regex_match(email, pattern);
    }

    // Function to add a new contact
    void addContact(const string& fn, const string& ln, const string& phone, const string& email){
        Contact* newContact = new Contact(fn, ln, phone, email);

        // Check if a contact with the same phone number already exists
        Contact* current = head;
        Contact* duplicateContact = nullptr;
        while (current) {
            if (current->phoneNumber == phone) {
                duplicateContact = current;
                break;
            }
            current = current->next;
        }

        if (duplicateContact) {
        // A contact with the same phone number already exists
        char choice;
        cout << "A contact with the same phone number already exists. \n Do you want to merge the contacts (Y/N)? ";
        cin >> choice;
        cin.ignore();
        if (toupper(choice) == 'Y') {
            duplicateContact->firstName = fn;
            duplicateContact->lastName = ln;
            duplicateContact->email = email;
            // Do not add the new contact
            delete newContact;
            cout << "Contacts merged successfully!" << endl;
        } 
        else {
            // Do not merge, add the new contact
            if (!head) {
                head = newContact;
            } else {
                current = head;
                while (current->next) {
                    current = current->next;
                }
                current->next = newContact;
            }
            cout << "Contact added successfully!" << endl;
        }
        }
        else {
        // No duplicate contact found, add the new contact
        if (!head) {
            head = newContact;
        } 
        else{
            current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newContact;
        }
        cout << "\n";
        cout << "Contact added successfully!" << endl;
        }
        //
    }

       
    // Function to display all contacts


    void displayContacts(){
        if (!head) {
        cout << "Phone book is empty." << endl;
        return;
        }

    // Create a dynamic array to store the contacts for sorting
    int contactCount = getContactCount();
    Contact** contactArray = new Contact*[contactCount];

    Contact* current = head;
    int index = 0;
    while (current) {
        contactArray[index] = current;
        current = current->next;
        index++;
    }

    // Sort the contacts by first name
    std::sort(contactArray, contactArray + contactCount,  [](Contact* a, Contact* b){
        return a->firstName < b->firstName;
    });

    // Display sorted contacts
    cout << "Contacts in alphabetical order:" << endl;
    cout << "\n" ;

    for (int i = 0; i < contactCount; i++) {
        cout << "First Name: " << contactArray[i]->firstName << "\t\t\t\t";
        cout << "Last Name: " << contactArray[i]->lastName << endl;
        cout << "Phone Number: " << contactArray[i]->phoneNumber << "\t\t\t";
        cout << "Email: " << contactArray[i]->email << endl;
        cout << endl;
    }

    // Clean up the dynamic array
    delete[] contactArray;
    }

    //Function to delete a contact
 
    void deleteContact() {
    if (!head) {
        cout << "Phone book is empty. No contacts to delete." << endl;
        return;
    }

    string searchKey;
    int choice;

    cout << "How do you want to search for the contact to delete?" << endl;
    cout << "1. By name" << endl;
    cout << "2. By phone number" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  // Clear newline character from previous input

    if (choice == 1) {
        // Delete by name
        cout << "Enter the first name of the contact you want to delete: ";
        getline(cin, searchKey);
        // cin.ignore();  // Clear newline character from previous input

        Contact* current = head;
        bool found = false;
        int contactNumber = 1; // To display contact number

        while (current) {
            if (current->firstName == searchKey) {
                found = true;
                cout << "Contact " << contactNumber << ":" << endl;
                cout << "Name: " << current->firstName << " " << current->lastName << endl;
                cout << "Phone number: " << current->phoneNumber << endl;
                cout << "Email: " << current -> email << endl;
                cout << "\n";
                contactNumber++;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No contacts with the specified name found." << endl;
        } else {
            // Ask the user to choose which contact to delete by contact number
            int contactToDelete;
            cout << "Enter the number of the contact you want to delete: ";
            cin >> contactToDelete;
            cin.ignore();  // Clear newline character from previous input

            // Find the chosen contact to delete and perform deletion
            current = head;
            Contact* prev = nullptr;
            int currentContactNumber = 1;

            while (current) {
                if (current->firstName == searchKey) {
                    if (currentContactNumber == contactToDelete) {
                        if (prev) {
                            prev->next = current->next;
                        } else {
                            head = current->next;
                        }
                        delete current;
                        cout << "Contact " << contactToDelete << " has been deleted." << endl;
                        break;
                    }
                    currentContactNumber++;
                }
                prev = current;
                current = current->next;
            }
        }
    } else if (choice == 2) {
        // Delete by phone number
        cout << "Enter the phone number of the contact you want to delete: ";
        getline(cin, searchKey);
        // cin.ignore();  // Clear newline character from previous input

        Contact* prev = nullptr;
        Contact* current = head;
        bool found = false;

        while (current) {
            if (current->phoneNumber == searchKey) {
                found = true;
                cout << "Contact found: " << current->firstName << " " << current->lastName << endl;
                cout << "Phone number: " << current->phoneNumber << endl;
                cout << "Email: " << current -> email << endl;
                break;
            }
            prev = current;
            current = current->next;
        }

        if (!found) {
            cout << "Contact not found." << endl;
        } else {
            // Confirm with the user if they want to delete the contact
            cout << "Do you want to delete this contact? (Y/N): ";
            char confirmDelete;
            cin >> confirmDelete;
            cin.ignore();  // Clear newline character from previous input

            if (tolower(confirmDelete) == 'y') {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                cout << "Contact has been deleted." << endl;
            } else {
                cout << "Contact has not been deleted." << endl;
            }
        }
        cout << "Contact deleted successfully !" << endl;
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}


    // Function to update a contact

    void updateContact() {
    if (!head) {
        cout << "Phone book is empty. No contacts to update." << endl;
        return;
    }

    string searchKey;
    int choice;

    cout << "How do you want to search for the contact to update?" << endl;
    cout << "1. By name" << endl;
    cout << "2. By phone number" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  // Clear newline character from previous input

    if (choice == 1) {
        // Update by name
        cout << "Enter the first name of the contact you want to update: ";
        getline(cin, searchKey);
        // cin.ignore();  // Clear newline character from previous input
        Contact* current = head;
        bool found = false;
        int contactNumber = 1; // To display contact number

        while (current) {
            if (current->firstName == searchKey) {
                found = true;
                cout << "Contact " << contactNumber << ":" << endl;
                cout << "Name: " << current->firstName << " " << current->lastName << endl;
                cout << "Phone number: " << current->phoneNumber << endl;
                cout << "Email: " << current->email << endl;
                cout << "\n" ;
                contactNumber++;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No contacts with the specified name found." << endl;
        } else {
            // Ask the user to choose which contact to update by contact number
            int contactToUpdate;
            cout << "Select the contact you want to update: ";
            cin >> contactToUpdate;
            cin.ignore();  // Clear newline character from previous input

            // Find the chosen contact to update and perform updating
            current = head;
            int currentContactNumber = 1;

            while (current) {
                if (current->firstName == searchKey) {
                    if (currentContactNumber == contactToUpdate) {
                        cout << "Contact selected. What would you like to update?" << endl;
                        cout << "1. Update the name" << endl;
                        cout << "2. Update the phone number" << endl;
                        cout << "3. Update the email" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        cin.ignore();  // Clear newline character from previous input

                        string newFirstName, newLastName;
                        string newPhoneNumber;
                        string newEmail;

                        switch (choice) {
                            case 1:
                                // Update the name
                                cout << "New First Name: ";
                                getline(cin, newFirstName);
                                // cin.ignore();
                                cout << "New Last Name: ";
                                getline(cin, newLastName);
                                // cin.ignore();

                                // Update the contact's information
                                current->firstName = newFirstName;
                                current->lastName = newLastName;
                                cout << "Contact updated successfully!" << endl;
                                break;
                            case 2:
                                // Update the phone number
                                cout << "New Phone Number: ";
                                getline(cin, newPhoneNumber);
                                // cin.ignore();

                                // Implement the code to update the phone number
                                current->phoneNumber = newPhoneNumber;
                                cout << "Contact updated successfully!" << endl;
                                break;
                            case 3:
                                // Update the email
                                cout << "New Email: ";
                                getline(cin, newEmail);
                                // cin.ignore();

                                // Implement the code to update the email
                                current->email = newEmail;
                                cout << "Contact updated successfully!" << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                        break;
                    }
                    currentContactNumber++;
                }
                current = current->next;
            }
        }
    } else if (choice == 2) {
        // Update by phone number
        cout << "Enter the phone number of the contact you want to update: ";
        getline(cin, searchKey);
        cin.ignore();  // Clear newline character from previous input
        Contact* current = head;
        bool found = false;

        while (current) {
            if (current->phoneNumber == searchKey) {
                found = true;
                cout << "Contact found. What would you like to update?" << endl;
                cout << current -> firstName << current ->lastName <<endl;
                cout << "Phone Number: " << current -> phoneNumber << endl;
                cout << "Email; " << current ->email <<endl;
                cout << "1. Update the name" << endl;
                cout << "2. Update the phone number" << endl;
                cout << "3. Update the email" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();  // Clear newline character from previous input

                string newFirstName, newLastName;
                string newPhoneNumber;
                string newEmail;

                switch (choice) {
                    case 1:
                        // Update the name
                        cout << "New First Name: ";
                        getline(cin, newFirstName);
                        // cin.ignore();
                        cout << "New Last Name: ";
                        getline(cin, newLastName);
                        // cin.ignore();

                        // Update the contact's information
                        current->firstName = newFirstName;
                        current->lastName = newLastName;
                        cout << "Contact updated successfully!" << endl;
                        break;
                    case 2:
                        // Update the phone number
                        cout << "New Phone Number: ";
                        getline(cin, newPhoneNumber);
                        // cin.ignore();
                        while(!isValidPhoneNumber(newPhoneNumber)){
                            getline(cin, newPhoneNumber);
                        }

                        // Implement the code to update the phone number
                        current->phoneNumber = newPhoneNumber;
                        cout << "Contact updated successfully!" << endl;
                        break;
                    case 3:
                        // Update the email
                        cout << "New Email: ";
                        getline(cin, newEmail);
                        // cin.ignore();
                        while (!isValidEmail(newEmail)){
                            getline(cin, newEmail);
                        }

                        // Implement the code to update the email
                        current->email = newEmail;
                        cout << "Contact updated successfully!" << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }
            current = current->next;
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}

    int getContactCount(){
        int count = 0;
        Contact* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        
        return count;
    }

    // Function to search for a contact
    void searchContact(){
    if (!head) {
        cout << "Phone book is empty. No contacts to search." << endl;
        return;
    }

    string searchKey;
    int choice;

    cout << "How do you want to search for the contact?" << endl;
    cout << "1. By name" << endl;
    cout << "2. By email" << endl;
    cout << "3. By phone number" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();  // Clear newline character from previous input

    if (choice == 1) {
        // Search by name
        cout << "Enter the first name of the contact you want to search for: ";
        getline(cin, searchKey);
        // cin.ignore();  // Clear newline character from previous input
        Contact* current = head;
        bool found = false;

        while (current) {
            if (current->firstName == searchKey) {
                found = true;
                // cout << "Contact is found !! ";
                cout << "\n";
                cout << "Contact details are:" << endl;
                cout << "First Name: " << current->firstName << endl;
                cout << "Last Name: " << current->lastName << endl;
                cout << "Phone Number: " << current->phoneNumber << endl;
                cout << "Email: " << current->email << endl;
                // break;
                cout << "\n";
            }
            current = current->next;
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    } else if (choice == 2) {
        // Search by email
        cout << "Enter the email of the contact you want to search for: ";
        getline(cin, searchKey);
        cin.ignore();  // Clear newline character from previous input
        Contact* current = head;
        bool found = false;

        while (current) {
            if (current->email == searchKey) {
                found = true;
                // cout << "Contact is found !! ";
                cout << "\n";
                cout << "Contact details are :" << endl;
                cout << "First Name: " << current->firstName << endl;
                cout << "Last Name: " << current->lastName << endl;
                cout << "Phone Number: " << current->phoneNumber << endl;
                cout << "Email: " << current->email << endl;
                cout << "\n";
            }
            current = current->next;
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    } else if (choice == 3) {
        // Search by phone number
        cout << "Enter the phone number of the contact you want to search for: ";
        getline(cin, searchKey);
        cin.ignore();  // Clear newline character from previous input
        Contact* current = head;
        bool found = false;

        while (current) {
            if (current->phoneNumber == searchKey) {
                found = true;
                // cout << "Contact is found !! ";
                cout << "\n";
                cout << "Contact details are :" << endl;
                cout << "First Name: " << current->firstName << endl;
                cout << "Last Name: " << current->lastName << endl;
                cout << "Phone Number: " << current->phoneNumber << endl;
                cout << "Email: " << current->email << endl;
                cout << "\n";
                // break;
            }
            current = current->next;
        }

        if (!found) {
            cout << "Contact not found." << endl;
        }
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}


    // Function to delete all contacts
    void deleteAllContacts(){
        if (!head){
            cout << "Phone book is empty. No contacts to delete." << endl;
            return;
        }
        while (head){
        Contact* current = head;
        head = head->next;
        delete current;
        }
        cout << "All contacts have been deleted." << endl;
    }


    // Destructor to free memory
    ~PhoneBook() {
        while (head) {
            Contact* current = head;
            head = head->next;
            delete current;
        }
    }

};


// Implement the member functions of PhoneBook
int main() {

    system("Color 9C");
    cout<<"\n\n\n\n\n\n\n\n\n";
	cout<<"\t\t\t\t\t\t----------------------------\n";
	cout<<"\t\t\t\t\t\t----------------------------\n";
	cout<<"\t\t\t\t\t\tSMART PHONE BOOK by RIDA\n";
	cout<<"\t\t\t\t\t\t----------------------------\n\n";
	cout<<"\t\t\t\t\tLoading ";
	char x = 219;
	for(int i=0; i<30; i++)
	{
		cout<<x;
		if(i<10)
		Sleep(250);
		if(i>=10 && i<20)
		Sleep(100);
		if(i>=20)
		Sleep(50);
	}
	system("cls");
    PhoneBook phoneBook;
    int choice;

    do {
        
        system("Color 5F");
        cout<<"\n\n\n\n\n";
	    cout<<"\t\t\t\t\t--------------------------------------------\n";
	    cout<<"\t\t\t\t\t--------------------------------------------\n";
	    cout<<"\t\t\t\t\t|               PHONE BOOK                 |\n";
	    cout<<"\t\t\t\t\t--------------------------------------------\n";
	    cout<<"\t\t\t\t\t|                                          |\n";
	    cout<<"\t\t\t\t\t|       [1]  Add a new Contact             |\n";
	    cout<<"\t\t\t\t\t|       [2]  Diplay All Contacts           |\n";
	    cout<<"\t\t\t\t\t|       [3]  Delete a contact              |\n";
	    cout<<"\t\t\t\t\t|       [4]  Update a contact              |\n";
	    cout<<"\t\t\t\t\t|       [5]  Number of Contacts            |\n";
	    cout<<"\t\t\t\t\t|       [6]  Search                        |\n";
	    cout<<"\t\t\t\t\t|       [7]  Delete All  Contacts          |\n";
	    cout<<"\t\t\t\t\t--------------------------------------------\n";
	    cout<<"\t\t\t\t\t|       [8]  Exit                          |\n";
	    cout<<"\t\t\t\t\t--------------------------------------------\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string firstName, lastName, phoneNumber, eMail;
        int count;
        switch (int(choice)) {
            case 1:
                // Add a new contact
                cout << "Enter the following details: " << endl;
                
                cout << "\n Enter the first name : " << endl;
                getline(cin, firstName);
                // cin.ignore();
                cout << "Enter the last name : " << endl;
                getline(cin, lastName);
                // cin.ignore();
                cout << "Enter the phone number :" << endl;
                getline(cin, phoneNumber);
                // cin.ignore();
                while (!phoneBook.isValidPhoneNumber(phoneNumber)){
                    cout << "Invalid phone number. Please enter a 10-digit numeric phone number." << endl;
                    getline(cin, phoneNumber);
                    // cin.ignore();
                }
                cout << "Enter the mail :" << endl;
                getline(cin, eMail);
                // cin.ignore();
                while (!phoneBook.isValidEmail(eMail)){
                    cout << "Invalid Email Address. Please enter a valid email address." << endl;
                    getline(cin, eMail);
                    // cin.ignore();
                }
                phoneBook.addContact(firstName, lastName, phoneNumber, eMail);
                break;
            case 2:
                // Display all contacts
                phoneBook.displayContacts();
                break;
            case 3:
                // Delete a contact
                phoneBook.deleteContact();
                break;
            case 4:
                // Update a contact
                phoneBook.updateContact();
                break;
            case 5:
                // Number of contacts
                count = phoneBook.getContactCount();
                cout << "Number of contacts: " << count << endl;
                break;
            case 6:
                // Search
                phoneBook.searchContact();
                break;
            case 7:
                // Delete all contacts
                phoneBook.deleteAllContacts();
                break;
            case 8:
                // Exit the program
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 8);

    return 0;
}