#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const string namesList = "names.txt";

class DoublyLinkedList {
 private:
  struct Node {
    string name;
    Node* prev;
    Node* next;
    Node(string val, Node* p = nullptr, Node* n = nullptr) {
      name = val;
      prev = p;
      next = n;
    }
  };

  Node* head;
  Node* tail;

 public:
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  void insert_after(string name, int position) {
    if (position < 0) {
      cout << "Position must be >= 0." << endl;
      return;
    }

    Node* newNode = new Node(name);
    if (!head) {
      head = tail = newNode;
      return;
    }

    Node* temp = head;
    for (int i = 0; i < position && temp; ++i) temp = temp->next;

    if (!temp) {
      cout << "Position exceeds list size. Node not inserted.\n";
      delete newNode;
      return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next)
      temp->next->prev = newNode;
    else
      tail = newNode;
    temp->next = newNode;
  }

  void delete_val(string name) {
    if (!head) return;

    Node* temp = head;

    while (temp && temp->name != name) temp = temp->next;

    if (!temp) return;

    if (temp->prev)
      temp->prev->next = temp->next;
    else
      head = temp->next;

    if (temp->next)
      temp->next->prev = temp->prev;
    else
      tail = temp->prev;

    delete temp;
  }

  void delete_pos(int pos) {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    if (pos == 1) {
      pop_front();
      return;
    }

    Node* temp = head;

    for (int i = 1; i < pos; i++) {
      if (!temp) {
        cout << "Position doesn't exist." << endl;
        return;
      } else
        temp = temp->next;
    }
    if (!temp) {
      cout << "Position doesn't exist." << endl;
      return;
    }

    if (!temp->next) {
      pop_back();
      return;
    }

    Node* tempPrev = temp->prev;
    tempPrev->next = temp->next;
    temp->next->prev = tempPrev;
    delete temp;
  }

  void push_back(string name) {
    Node* newNode = new Node(name);
    if (!tail)
      head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  void push_front(string name) {
    Node* newNode = new Node(name);
    if (!head)
      head = tail = newNode;
    else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  void pop_front() {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    Node* temp = head;

    if (head->next) {
      head = head->next;
      head->prev = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  void pop_back() {
    if (!tail) {
      cout << "List is empty." << endl;
      return;
    }
    Node* temp = tail;

    if (tail->prev) {
      tail = tail->prev;
      tail->next = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  ~DoublyLinkedList() {
    while (head) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }
  void print() {
    Node* current = head;
    if (!current) {
      cout << "The line is empty." << endl;
      return;
    }
    cout << "   Resulting line:" << endl;
    while (current) {
      cout << "     " << current->name << endl;
      current = current->next;
    }
  }

  void print_reverse() {
    Node* current = tail;
    if (!current) {
      cout << "List is empty." << endl;
      return;
    }
    while (current) {
      cout << current->name << "        ";
      current = current->prev;
    }
    cout << endl;
  }
};

// func to read names file
vector<string> readNamesFromFile(const string& namesFile) {
  vector<string> names;
  ifstream file(namesFile);

  if (!file.is_open()) {
    cout << "Error: Could not open file '" << namesFile
         << "'. Please check the file and try again.\n";
    return names;
  }

  string line;
  while (getline(file, line)) {
    if (!line.empty()) {
      names.push_back(line);
    }
  }

  file.close();
  return names;
}

// func to randomize names used
string getRandomName(const vector<string>& names) {
  int num = rand() % names.size();
  return names[num];
}

int main() {
  srand(time(0));

  vector<string> names = readNamesFromFile(namesList);
  if (names.empty()) {
    return 1;
  }

  DoublyLinkedList list;

  // When store first opens, we will randomize 5 names from the list as
  // customers that entered the store when it first opened (or minute 1)
  cout << "Store opens:" << endl;
  for (int i = 0; i < 5; ++i) {
    string name = getRandomName(names);
    cout << "   " << name << " joins the line" << endl;
    list.push_back(name);
  }
  list.print();

  // Minute 2-20
  for (int min = 2; min <= 20; ++min) {
    cout << "Time step #" << min << ":" << endl;
    int prob = rand() % 100 + 1;  // returns random number 1-100

    if (prob <= 40) {
      cout << "";
    }
  }

  return 0;
}