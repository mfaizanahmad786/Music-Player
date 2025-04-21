
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    Node* front; // Points to the front of the queue
    Node* rear;  // Points to the rear of the queue
    int size;    // Tracks the size of the queue

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
        size = 0;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return size == 0;
    }

    // Add an element to the queue
    void enqueue(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
        cout << "Item added to the queue: " << value << endl;
    }

    // Remove an element from the queue
    void dequeue() {
        if (isEmpty()) {
            cout << "The queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) { // If the queue becomes empty
            rear = nullptr;
        }
        delete temp;
        size--;
        cout << "Item deleted from the queue." << endl;
    }

    // Get the element at the front of the queue
    int peek() {
        if (isEmpty()) {
            cout << "The queue is empty!" << endl;
            return -1; // Return an invalid value
        }
        return front->data;
    }

    // Get the size of the queue
    int getSize() {
        return size;
    }

    // Display the elements of the queue
    void display() {
        if (isEmpty()) {
            cout << "The queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Queue elements: ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Destructor to clean up dynamically allocated memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};


