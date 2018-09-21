/* Linked List Line Text Editor
 * Programming Assignment 1
 * COP3530: Data Structures and Algorithms, Fall 2018
 * Asher Johnson Hogan
 *
 * The purpose of this project is to create a line text editor represented
 * by a linked list, where each line is represented by a node.
 * The user can insert, edit, and delete lines,
 * print the entire document, and search for text
 *
 * Removed several print statements including error messages
 * to conform to submission guidelines
 */


#include <iostream>
#include <vector>

using namespace std;

struct Line {
    string text;
    Line* next;
};

class Document {
private:
    Line* front; // first line
    Line* back; // last line
    int size; // number of lines
public:
    Document();
    void insertEnd(string text); // insert at end of Doc
    void insertAt(int lineNumber, string text); // insert at given line
    void deleteLine(int lineNumber); // delete given line
    void editLine(int lineNumber, string text); // edit text of given line
    void search(string text); // finds and prints line(s) of given text
    void printDoc(); // prints Document, with line numbers
    Line* findLine(int lineNumber); // returns the Line at given line number
    Line* getFront(); // returns front
    int getSize(); // returns size
    bool isEmpty(); // returns size == 0
};

// max number of characters per line
int maxLineSize = 80;

// Document used throughout the program
Document doc;

Line* Document::getFront() {
    return front;
}

int Document::getSize() {
    return size;
}

// returns whether the Document is empty
bool Document::isEmpty() {
    return (size == 0);
}

// initializes size to 0, front and back to NULL
Document::Document() {
    size = 0;
    front = back = NULL;
}

// inserts a line containing text at the end of the Document
void Document::insertEnd(string text) {
    if (text.size() > maxLineSize) {
        // cout << "Error, max line size is " << maxLineSize << endl;
        return;
    }
    Line* line = new Line();
    line->text = text;
    line->next = NULL;
    // appends the line to back
    if (!isEmpty()) {
        back->next = line;
        back = line;
    }
    // if size == 0, sets front and back to line
    else {
        front = back = line;
    }
    size++;
}

// inserts a line containing text at lineNumber
// (before the line currently at lineNumber)
void Document::insertAt(int lineNumber, string text) {
    if (lineNumber > size + 1) {
        // cout << "Error, line number too large" << endl;
        return;
    }
    if (lineNumber <= 0) {
        // cout << "Error, line number must be a positive number" << endl;
        return;
    }
    if (text.size() > maxLineSize) {
        // cout << "Error, max line size is " << maxLineSize << endl;
        return;
    }
    Line* line = new Line();
    line->text = text;
    line->next = NULL;
    // first line case
    if (lineNumber == 1) {
        line->next = front;
        front = line;
        // if also the last line, update back
        if (size == 0) {
            back = line;
        }
    }
    // last line AND NOT first line
    else if (lineNumber == size + 1) {
        back->next = line;
        back = line;
    }
    // in the middle
    else {
        Line* addAfter = findLine(lineNumber - 1);
        line->next = addAfter->next;
        addAfter->next = line;
    }
    size++;
}

// deletes the line at lineNumber
void Document::deleteLine(int lineNumber) {
    if (lineNumber > size) {
        // cout << "Error, line number too large" << endl;
        return;
    }
    if (lineNumber <= 0) {
        // cout << "Error, line number must be a positive number" << endl;
        return;
    }
    Line* prev = NULL;
    // if first line, stores the next line as the front
    if (lineNumber == 1) {
        Line* del = front;
        front = front->next;
        delete del;
    }
    // finds the previous line and sets its next to its next->next
    else {
        prev = findLine(lineNumber - 1);
        Line* del = prev->next;
        prev->next = del->next;
        delete del;
    }
    // if last line, stores prev line as back
    if (lineNumber == size) {
        back = prev;
    }
    size--;
}

// replaces line at lineNumber with text
void Document::editLine(int lineNumber, string text) {
    if (lineNumber > size) {
        // cout << "Error, line number too large" << endl;
        return;
    }
    if (lineNumber <= 0) {
        // cout << "Error, line number must be a positive number" << endl;
        return;
    }
    Line* line = findLine(lineNumber);
    line->text = text;
}

// finds each occurence of text and prints it with the line number
// if not found, prints "Not found"
void Document::search(string text) {
    Line* curr = front;
    bool found = false;
    for (int i = 1; i <= size; i++) {
        // std::string::find returns std::string::npos if not found
        if (curr->text.find(text) != string::npos) {
            cout << i << " " << curr->text << endl;
            found = true;
        }
        curr = curr->next;
    }
    if (!found) {
        cout << "not found" << endl;
    }
}

// prints the Document
void Document::printDoc() {
    Line* curr = front;
    for (int i = 1; i <= size; i++) {
        cout << i << " " << curr->text << endl;
        curr = curr->next;
    }
}

// iterates through the list to find the line at the requested index
Line* Document::findLine(int lineNumber) {
    if (lineNumber > size)
        return NULL;
    Line* curr = front;
    for (int i = 1; i < lineNumber; i++) {
        curr = curr->next;
    }
    return curr;
}

// separates a string into individual tokens,
// where tokens are separated by a space in the string
// anything contained in quotes is considered one token
vector<string> getTokens(string input) {
    vector<string> tokens;
    string currToken = "";
    bool inQuotes = false;
    // loops through each character
    for (int i = 0; i < input.size(); i++) {
        // toggles inQuotes so tokens contained in quotes aren't separated
        if (input.at(i) == '\"') {
            currToken += input.at(i);
            inQuotes = !inQuotes;
        }
        else if (input.at(i) != ' ' || inQuotes) {
            currToken += input.at(i);
        }
        // curr char is ' ', so currToken is pushed to tokens and reset
        else {
            if (currToken != "")
                tokens.push_back(currToken);
            currToken = "";
        }
    }
    if (currToken != "") {
        tokens.push_back(currToken);
    }
    return tokens;
}

// checks to see if a string is contained in quotes
bool isQuote(string input) {
    return (input.at(0) == '\"' && input.at(input.size() - 1) == '\"');
}

// checks to see if a string input is numerical
// used in input parsing
bool isNum(string input) {
    try {
        int temp = stoi(input);
    }
    catch(invalid_argument& e){
        return false;
    }
    return true;
}

/*
insertEnd "text" -- insert given text at the end of the document
insert 3 "text" --insert given text at the line indicated by index given
delete 3 --- delete line at index given
edit 3 "text" --- replace the line at the index given with the given text
print -- print the entire document, with line numbers
search "text" -- print the line number and line that contains the given text
                 print "not found" if it is not found
quit - quit/exit the program
*/

// runs the menu, gets input from user and runs appropriate command
// returns 1 to continue program, 0 to quit
// executed inside a while loop, so it runs until it returns 0
int menu() {

    // get input from cin
    string input;
    getline(cin, input);
    // parses the input into individual tokens, stored in a vector
    vector<string> tokens = getTokens(input);

    // checks for proper syntax; if syntax doesn't match exactly,
    // prints an error statement with correct syntax for each command
    // then executes the matching command
    string command = tokens.at(0);
    if (command == "insertEnd") {
        if (tokens.size() != 2 || !isQuote(tokens.at(1))) {
            // cout << "Error, syntax for insertEnd is insertEnd \"text\"" << endl;
            return 1;
        }
        string text = tokens.at(1);
        doc.insertEnd(text.substr(1, text.size() - 2));
    }
    else if (command == "insert") {
        if (tokens.size() != 3  || !isNum(tokens.at(1)) || !isQuote(tokens.at(2))) {
            // cout << "Error, syntax for insert is insert line# \"text\"" << endl;
            return 1;
        }
        string text = tokens.at(2);
        doc.insertAt(stoi(tokens.at(1)), text.substr(1, text.size() - 2));
    }
    else if (command == "delete") {
        if (tokens.size() != 2 || !isNum(tokens.at(1))) {
            // cout << "Error, syntax for delete is delete line#" << endl;
            return 1;
        }
        doc.deleteLine(stoi(tokens.at(1)));
    }
    else if (command == "edit") {
        if (tokens.size() != 3  || !isNum(tokens.at(1)) || !isQuote(tokens.at(2))) {
            // cout << "Error, syntax for edit is edit line# \"text\"" << endl;
            return 1;
        }
        string text = tokens.at(2);
        doc.editLine(stoi(tokens.at(1)), text.substr(1, text.size() - 2));
    }
    else if (command == "print") {
        doc.printDoc();
    }
    else if (command == "search") {
        if (tokens.size() != 2 || !isQuote(tokens.at(1))) {
            // cout << "Error, syntax for search is search \"text\"" << endl;
            return 1;
        }
        string text = tokens.at(1);
        doc.search(text.substr(1, text.size() - 2));
    }
    else if (command == "quit") {
        return 0;
    }
    else if (command == "commands") {
        cout << "Valid commands:\n"
             << "insertEnd \"text\" -- insert given text at the end of the document\n"
             << "insert 3 \"text\" -- insert given text at the line indicated by index given\n"
             << "delete 3 -- delete line at index given\n"
             << "edit 3 \"text\" -- replace the line at the index given with the given text\n"
             << "print -- print the entire document, with line numbers\n"
             << "search \"text\" -- print the line number and line that contains the given text\n"
             << "quit -- quit/exit the program\n"
             << "commands -- list valid commands" << endl;
    }
    else {
        // cout << "Error, invalid command. To list valid commands, type \"commands\"" << endl;
    }
    return 1;
}


int main(int argc, const char * argv[]) {
    // cout << "Welcome!" << endl;

    // menu() returns 0 when quit is called
    while (menu()) {
        // loops menu
    }

    return 0;
}
