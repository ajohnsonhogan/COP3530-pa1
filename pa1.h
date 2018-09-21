// condensed into pa1.cpp for file submission

#include <string>

using namespace std;

#ifndef pa3_h
#define pa3_h

struct Line {
    string text;
    Line* next;
};

class Document {
private:
    Line* front;
    Line* back;
    int size;
public:
    Document();
    void insertEnd(string text);
    void insertAt(int lineNumber, string text);
    void deleteLine(int lineNumber);
    void editLine(int lineNumber, string text);
    void search(string text);
    void printDoc();
    Line* findLine(int lineNumber);
    Line* getFront();
    int getSize();
    bool isEmpty();
};

#endif /* pa1_h */
