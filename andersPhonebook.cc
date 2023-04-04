#include <iostream>
#include <fstream>

using namespace std;

struct myBinaryTree
{
    string name;
    int myNumber;
    struct myBinaryTree *left;
    struct myBinaryTree *right;
};

static myBinaryTree *root = NULL;

static void insertMyContact(myBinaryTree *&root, string name, int phoneNumber)
{
    if (root == nullptr)
    {
        root = new myBinaryTree;
        root->name = name;
        root->myNumber = phoneNumber;
        root->left = nullptr;
        root->right = nullptr;
    }
    else
    {
        if (name < root->name)
            insertMyContact(root->left, name, phoneNumber);
        else
            insertMyContact(root->right, name, phoneNumber);
    }
}

static void addNewContact()
{

    string myName;
    int myPhoneNumber;
    cout << "Please enter you name: ";
    cin.ignore();
    getline(cin, myName);
    cout << "Please enter your phone number: ";
    cin >> myPhoneNumber;

    insertMyContact(root, myName, myPhoneNumber);
}

void printFindMyContact(myBinaryTree *root, string name)
{
    if (root == nullptr)
    {
        cout << endl;
        cout << "There's no contact with that name in your phonebook!" << endl;
        return;
    }

    if (name == root->name)
    {
        cout << "Person found!" << endl;
        cout << "Name:" << root->name << endl;
        cout << "Phone number:" << root->myNumber << endl;
        cout << endl;
        return;
    }

    if (name < root->name)
    {
        printFindMyContact(root->left, name);
    }
    else
    {
        printFindMyContact(root->right, name);
    }
}

static void searchMyContact()
{
    string findContactName;
    cout << "Please enter the name your'e searching for: ";
    cin.ignore();
    getline(cin, findContactName);

    printFindMyContact(root, findContactName);
}

void printMyContact(myBinaryTree *n)
{
    if (!root)
    {
        cout << "" << endl;
        cout << "Nothing found!" << endl;
        return;
    }

    if (n != nullptr)
    {
        printMyContact(n->left);
        cout << "Name: " << n->name << endl;
        cout << "Number: " << n->myNumber << endl;
        cout << endl;
        printMyContact(n->right);
    }
}

static int myMenu()
{

    string userChoice;
    cout << endl;
    cout << "*** MENU ***" << endl;
    cout << "" << endl;
    cout << "1. Insert contact to phonebook" << endl;
    cout << "2. Print contact in phonebook" << endl;
    cout << "3. Search contact in phonebook" << endl;
    cout << "4. Quit menu " << endl;
    cout << endl;
    cout << "Enter your prefered choice: ";
    cout << endl;
    cin >> userChoice;
    cout << "";

    if (userChoice == "1")
    {
        addNewContact();
    }
    else if (userChoice == "2")
    {
        printMyContact(root);
    }
    else if (userChoice == "3")
    {
        searchMyContact();
    }
    else if (userChoice == "4")
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        cout << "Wrong input, please try again!" << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    {

        if (argc == 2)

        {
            string filename(argv[1]);
            string line;
            ifstream input_file(filename);
            bool isName = true;
            int contactNumber;
            string name;

            if (!input_file.is_open())
            {
                cerr << "Could not open the file - '" << filename << "'" << endl;
                return EXIT_FAILURE;
            }

            while (getline(input_file, line))
            {
                if (isName && line != "")
                {
                    name = line;
                    isName = false;
                }
                else if (line != "" && isName == false)
                {
                    isName = true;
                    contactNumber = stoi(line);
                    insertMyContact(root, name, contactNumber);
                }
            }
            input_file.close();
        }
    }

    while (1)
    {
        myMenu();
    }
    return 0;
}
