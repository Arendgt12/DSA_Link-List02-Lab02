//Jael Johnson
//CMPS2131 Lab-01
// Lab 2: Singly Linked List for Username/Password storage

// Goal: Implement a simple credential store using a singly linked list

// Instructions:
// 1) Search for "TODO" and implement each function.
// 2) Build & run:   g++ -std=c++17 -O2 -Wall linked_lists.cpp -o lab && ./lab
// 3) Do not change function signatures

// NOTE: In the real world, NEVER store plaintext passwords.


// ADD HEADER FILES HERE
#include <iostream>
using namespace std;
// -----------------------------
// Data Model
// -----------------------------
struct User {
    string username;
    string password; 
    string role;
    User* next;
    
    User(string u, string p, string r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};

// Default argument specified here (Declaration)
bool insertUser(User*& head, const string& username, const string& password, const string& role = "viewer");
User* findUser(User* head, const string& username);
bool authenticate(User* head, const string& username, const string& password);
bool removeFront(User*& head);
bool removeByUsername(User*& head, const string& username);
void clearList(User*& head);
size_t size(User* head);
void printUsers(User* head);
bool authorize(User* head, const string& username, const string& action);


int main() {
 User* head = nullptr;
   
   // 1. Insert Users
   cout << "Inserting users..." << endl;
   insertUser(head, "Solo", "T1m3@&Password!", "admin");
   insertUser(head, "Andre", "Z@ni+2023", "editor");
   insertUser(head, "Nadia", "SecreT$&Pa55");
   insertUser(head, "Carris", "M@G!C12");
   insertUser(head, "Ajoni", "A1234Password!", "editor");
   insertUser(head, "Henry", "H3nRy$2024");
   insertUser(head, "Keira", "P@ssw0rDKeira!");
   insertUser(head, "Cailen", "Ca!len$17");
   insertUser(head, "Jair", "J@ir@1234");

   // 2. Print All Users
   cout << "All users in the list:" << endl;
   printUsers(head);

   // 3. Find Users
   cout << "Finding 'Andre' in the list:" << endl;
   User* foundUser = findUser(head, "Andre");
   if (foundUser) {
       cout << "Found user: " << foundUser->username << " (Role: " << foundUser->role << ")" << endl;
   } else {
       cout << "User 'Andre' not found." << endl;
   }

   cout << "Finding 'Alice' in the list:" << endl;
   foundUser = findUser(head, "Alice");
   if (foundUser) {
       cout << "Found user: " << foundUser->username << endl;
   } else {
       cout << "User 'Alice' not found." << endl;
   }

   // 4. Authorize Users
   cout << "Authorization Tests:" << endl;
   
   // Admin (Solo) attempts actions
   cout << "Solo (admin) 'edit': "
        << (authorize(head, "Solo", "edit") ? "Allowed" : "Denied") << endl;
   cout << "Solo (admin) 'delete': "
        << (authorize(head, "Solo", "delete") ? "Allowed" : "Denied") << endl;

   // Editor (Andre) attempts actions
   cout << "Andre (editor) 'create': "
        << (authorize(head, "Andre", "create") ? "Allowed" : "Denied") << endl;
   cout << "Andre (editor) 'delete': "
        << (authorize(head, "Andre", "delete") ? "Allowed" : "Denied") << endl;

   // Viewer (Nadia) attempts actions
   cout << "Nadia (viewer) 'view': "
        << (authorize(head, "Nadia", "view") ? "Allowed" : "Denied") << endl;
   cout << "Nadia (viewer) 'edit': "
        << (authorize(head, "Nadia", "edit") ? "Allowed" : "Denied") << endl;
   
   // Non-existent user
   cout << "Bob 'view': "
        << (authorize(head, "Bob", "view") ? "Allowed" : "Denied") << endl;
   
   cout << "List after tests:" << endl;
   printUsers(head);
   
   // FIX: Added clearList to deallocate memory and prevent leaks
   clearList(head);
   
   return 0;
}


// -----------------------------
// Core API — implement these
// -----------------------------

// Inserts a new (username, password) at the END of the list.
// If username already exists, do NOT insert a duplicate; return false.
// Otherwise insert and return true.
// FIX: Default argument removed here to prevent compilation error
bool insertUser(User*& head, const string& username, const string& password, const string& role) {
    if (findUser(head, username)) return false;

    // The User constructor handles the default role if not provided by the caller
    User* newUser = new User(username, password, role);

    if (!head) {
        head = newUser;
        return true;
    }

    User* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newUser;
    return true;
}


// Returns pointer to the node with matching username; otherwise nullptr.
User* findUser(User* head, const string& username) {
   User* current = head;


   while(current) {
       if(current->username == username) return current;
       current = current->next;
   }
  
   return nullptr;
}


// Returns true if (username, password) matches an existing node; false otherwise.
bool authenticate(User* head, const string& username, const string& password) {
   User* current = head;


   while(current) {
       if(current->username == username && current->password == password) {
          return true;
       }
       current = current->next;
   }
 
   return false;
}


// Deletes the FIRST node (head) and updates head. No-op if list is empty.
// Return true if a node was deleted, false otherwise.
bool removeFront(User*& head) {
   if (!head) return false; 

   User* temp = head;       
   head = head->next;       
   delete temp;            
   return true;  
}


// Deletes the node with matching username (first match only).
// Return true if a node was found & deleted; false if not found.
bool removeByUsername(User*& head, const string& username) {
  if (!head) return false; 

   if (head->username == username) {
       return removeFront(head); 
   }

   User* current = head;
   while (current->next) {
       if (current->next->username == username) {
           User* temp = current->next;
           current->next = temp->next; 
           delete temp;                
           return true;                
       }
       current = current->next;
   }

   return false; 
  
}


// Deletes ALL nodes and sets head=nullptr. 
void clearList(User*& head) {
   while (head) {
       User* temp = head;   
       head = head->next;   
       delete temp;         
   }
  
}


// Returns number of nodes.
size_t size(User* head) {
 size_t count = 0;
   User* current = head;
  
   while (current) {
       count++;
       current = current->next;
   }
  
   return count;
}

// Prints usernames in order, separated by " -> " then " -> NULL".
// Example: alice -> bob -> charlie -> NULL
void printUsers(User* head) {
   User* current = head;
  
   while (current) {
       cout << current->username;
       if (current->next) {
           cout << " -> ";
       }
       current = current->next;
   }
   cout << " -> NULL" << endl;
}

bool authorize(User* head, const string& username, const string& action) {
    User* user = findUser(head, username);
    if (!user) return false;

    if (user->role == "admin") {
        return true;
    } else if (user->role == "editor") {
        return (action == "view" || action == "edit" || action == "create");
    } else if (user->role == "viewer") {
        return (action == "view");
    }

    return false;
}