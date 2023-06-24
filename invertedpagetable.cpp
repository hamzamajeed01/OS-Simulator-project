#include <iostream>

using namespace std;

class Node {
public:
    int processId;
    int pageNumber;
    Node *next;
};

class HashTable {
public:
    Node **table;
    int size;
    HashTable(int size) {
        this->size = size;
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = NULL;
        }
    }
    int hashFunction(int processId, int pageNumber) {
        return (processId + pageNumber) % size;
    }
    void insert(int processId, int pageNumber) {
        int index = hashFunction(processId, pageNumber);
        Node *node = new Node();
        node->processId = processId;
        node->pageNumber = pageNumber;
        node->next = NULL;
        if (table[index] == NULL) {
            table[index] = node;
        } else {
            Node *temp = table[index];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = node;
        }
    }
    void search(int processId, int pageNumber) {
        int index = hashFunction(processId, pageNumber);
        Node *temp = table[index];
        while (temp != NULL) {
            if (temp->processId == processId && temp->pageNumber == pageNumber) {
                cout << "Found at index : " << index << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Not Found !" << endl;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            Node *temp = table[i];
            while (temp != NULL) {
                cout << "(Process ID : " << temp->processId << ", Page Number :  " << temp->pageNumber << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable *hashTable = new HashTable(10); // 10 is the number of indexes in the hash table
    hashTable->insert(3, 1);
    hashTable->insert(2, 5);
    hashTable->insert(7, 2);
    hashTable->insert(4, 5);
    hashTable->insert(5, 7);
    hashTable->insert(9, 8);
    hashTable->insert(10, 3);
    hashTable->insert(1, 4);
    hashTable->insert(2, 6);
    hashTable->insert(6, 9);

    hashTable->print();
    cout << endl;

    cout << "Search for (Process ID : 2, Page Number : 6)" << endl;
    hashTable->search(2, 6);
    cout << endl;
    cout << "Search for (Process ID : 3, Page Number : 1)" << endl;
    hashTable->search(3, 1);
    cout << endl;
    cout << "Search for (Process ID : 5, Page Number : 2)" << endl;
    hashTable->search(5, 2);
    cout << endl;

   
    return 0;
}



