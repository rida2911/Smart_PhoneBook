# Smart Phone Book Application

The **Phone Book Application** is a simple C++ program that allows users to manage a digital phone book. Users can add, display, update, search, and delete contacts within the phone book. This project is designed to help users organize and maintain a list of contacts with their personal information, such as names, phone numbers, and email addresses.

![smartphonebook](https://github.com/user-attachments/assets/77406826-564a-445d-9fca-3a893339aab7)


## Features
![smartphonebookoutput](https://github.com/user-attachments/assets/132e7ee6-44c7-453d-bd22-d1bbaf6e304e)


 
## Features

- **Add a New Contact**  
  Add a contact with first name, last name, phone number, and email. Duplicate detection is supported, and users can choose to merge existing entries.

- **Display All Contacts**  
  Displays all saved contacts sorted alphabetically by first name for easy viewing.

- **Delete a Contact**  
  Delete a contact either by first name or phone number with flexible search options.

- **Update a Contact**  
  Modify contact details such as name, phone number, or email. Input validation is included to ensure correctness.

- **Search for a Contact**  
  Search by first name, email address, or phone number. Matching results are displayed with complete details.

- **Number of Contacts**  
  Shows the total count of contacts stored in the phone book.

- **Delete All Contacts**  
  Quickly clear all saved contacts from memory in a single operation.

## Quick Fixes
- Phone and email validation  
- Handles spacing in inputs  
- Detects and merges duplicates  
- Error-proof and user-friendly  
- Colored terminal UI with centered layout  
- Fully Windows-compatible (`windows.h` used for styling and delay)


## Getting Started

To use the Phone Book Application, you can follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/KhyatiSatija/Smart_PhoneBook.git
   ```

2. Compile the source code using a C++ compiler:

   ```bash
   g++ phone_book.cpp -o phone_book
   ```

3. Run the program:

   ```bash
   ./phone_book
   ```

4. Follow the on-screen menu to interact with the phone book.
