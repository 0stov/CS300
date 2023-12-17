// Proj2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



using namespace std;

//A class to hold the class information
struct eClass {
    string shortName;
    string longName;
    vector<string> prereq;// because # of prereqs is unknown. we need an elastic variable.

    eClass() {
        shortName = "";
    }
    eClass(string short_in, string long_in, vector<string> prereq_in) {
        shortName = short_in;
        longName = long_in;
        prereq = prereq_in;

    }
};

class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        eClass className;
        Node* next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a class
        Node(eClass name) {
            className = name;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(eClass className);
    void PrintList();
    void Remove(string shortName);
    eClass Search(string shortName);
    int Size();
};
LinkedList::LinkedList() {
    // FIXME (1): Initialize housekeeping variables
    //set head and tail equal to null
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList() {
    // start at the head
    Node* current = head;
    Node* temp;

    // loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // hang on to current node
        current = current->next; // make current the next node
        delete temp; // delete the orphan node
    }
}
/**
 * Append a new class to the end of the list
 */
void LinkedList::Append(eClass className) {
    //Create new node
    Node* new_node = new Node(className);

    //if there is nothing at the head...
    if (head == nullptr) {
        // new node becomes the head and the tail
        head = new_node;
        tail = new_node;

    }

    //else 
    else {
        // make current tail node point to the new node
        tail->next = new_node;
        // and tail becomes the new node
        tail = new_node;
        //increase size count
        size++;
    }
}
void LinkedList::PrintList() {
    // start at the head
    Node* curr_node = head;
    //cout << "SIZE: " << size << endl;

    // while loop over each node looking for a match
    while (curr_node != nullptr) {
        //output current bidID, title, amount and fund
        cout << curr_node->className.shortName << ", " << curr_node->className.longName;
        for (string i : curr_node->className.prereq) {
            cout << ", " << i;
        }
        cout << endl;

        //set current equal to next
        curr_node = curr_node->next;
    }
}

eClass LinkedList::Search(string classSearch) {
    Node* curr_node = head;
    // special case if matching node is the head
    if (head->className.shortName == classSearch) {
        return curr_node->className;
    }

    // start at the head of the list

    // keep searching until end reached with while loop (next != nullptr
    while (curr_node->next != nullptr) {
        // if the current node matches, return it
        if (curr_node->className.shortName == classSearch) {
            return curr_node->className;
        }

        // else current node is equal to next node
        curr_node = curr_node->next;
    }


    //not found
    return eClass();

}
int main()
{
    std::ifstream myfile;
    fstream fin;
    //line stores an entire line as a string
        //temp will store the users search string later
    string line, temp;
    cout << "Input fileName : ";
    cin.clear();

    cin >> temp;
    //temp = "ABCU_Advising_Program_Input.csv";
    LinkedList classList;

    fin.open(temp, ios::in);

    int choice = 0;
    while (choice != 9) {
        cin.clear();
        cout << "Menu:" << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List.  " << endl;
        cout << "3. Print Course. " << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        //temp variables to create an eClass temp variable
        string short_in;
        string long_in;
        vector<string> prereq;
        
        //a vector array to store the entries in each line of input.
        vector<string> row;
        
        
        //helps parse incoming lines from the csv?
        stringstream ss(line);


        if (choice == 1) {
            cout << "You selected Load Data Structure." << endl;

            //this works by converting each line in the string vector
            // then it takes the first two entries as class names and puts the rest in a 'prerequisite' vector.


            //while theres still lines in the file.
            while (getline(fin, line, '\n')) {

                stringstream ss(line);

                //cout << "LINE: " << line << endl;
                //store the entries, seperated by comma, in a vector
                while (getline(ss, line, ',')) {
                    row.push_back(line);
                }

                short_in = row.at(0);
                long_in = row.at(1);

                //put the rest of the line in a prereq vector
                for (int i = 2; i < row.size(); i++) {
                    prereq.push_back(row.at(i));
                    cout << "    ADDING PREREQ: " << row.at(i) << endl;
                }


                cout << "ADDING " << short_in;
                cout << ", " << long_in << ", " << prereq.size() << " prerequisites found" << endl;

                eClass class_to_add = eClass(short_in, long_in, prereq);
                classList.Append(class_to_add);

                row.clear();
                prereq.clear();
                cout << endl;
            }
        }
        else if (choice == 2) {

            //basically use PrintAll()
            cout << endl << endl;
            cout << "You selected Print Course List." << endl; 
            cout << endl;
            classList.PrintList();
            cout << endl;
            continue;
        }

        else if (choice == 3) {
            cout << "What course would you like to know about? :";
            cin >> temp;
            eClass search_result = classList.Search(temp);

            //was the search successfull?
            if (search_result.shortName == "") {
                cout << "Class not found";
                continue;
            }

            //if yes, ouput the search findings.
            cout << search_result.shortName << ", " << search_result.longName << endl;

            cout << "Prerequisites: ";
            for (int i = 0; i < search_result.prereq.size(); i++) {
                cout << search_result.prereq.at(i);

                //should we add a comma between prereq?
                if (i - search_result.prereq.size() > 1) {
                    cout << ", ";
                }
            }
            cout << endl;
            continue;
        }
        //exit choice.
        else if (choice == 9) {
            continue;
        }
        //if the code made it this far, the user gave an invalid input.
        cout << choice << " is not a valid option. Please try again." << endl;



            
    
    }
    cout << "Exiting..";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
