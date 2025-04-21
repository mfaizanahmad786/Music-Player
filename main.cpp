#include <iostream>
#include <string>
using namespace std;

/*
This program implements a music playback system using a combination of data structures:
1. Circular Doubly Linked List (CDLL):
   - Stores the playlist as a circular list of songs.
   - Allows efficient navigation between songs (next and previous).

2. Queue (Dynamic):
   - Manages a queue of song indices to be played next.
   - Provides functionality to enqueue and dequeue songs dynamically.

3. Stack (Dynamic):
   - Maintains a history of played songs as indices.
   - Allows navigating to previously played songs.

4. Playback Class:
   - Controls playback operations such as play, pause, next song, and previous song.
   - Supports shuffle mode and a dynamic queue for prioritized playback.

Key Features:
- **CDLL** provides the core playlist functionality with constant time navigation between songs.
- **Queue** ensures that songs can be added dynamically for playback order prioritization.
- **Stack** enables easy navigation to previously played songs while maintaining playback history.
- Shuffle functionality selects a random song for playback, bypassing the usual order.
*/

struct Song {
    string title;
    string artist;
    int duration;

    Song(const string &title, const string &artist, int duration)
        : title(title), artist(artist), duration(duration) {}
};

struct Node {
    Song data;
    Node* next;
    Node* prev;
    Node(const Song& value) : data(value), next(nullptr), prev(nullptr) {}
};

class CircularDoublyLinkedList {
private:
    Node* head;
    int size;

public:
    CircularDoublyLinkedList() : head(nullptr), size(0) {}

    bool isEmpty() {
        return size == 0;
    }

    void addEnd(const Song& value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
        }
        size++;
    }

    Node* getNodeAt(int index) {
        if (isEmpty() || index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return nullptr;
        }
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp;
    }

    int getSize() {
        return size;
    }

    void display() {
        if (isEmpty()) {
            cout << "The list is empty!" << endl;
            return;
        }
        Node* temp = head;
        cout << "Playlist (Circular): ";
        do {
            cout << temp->data.title << " by " << temp->data.artist << " [" << temp->data.duration << "s] ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

class Queue {
private:
    struct QueueNode {
        int index;
        QueueNode* next;
        QueueNode(int idx) : index(idx), next(nullptr) {}
    };

    QueueNode* front;
    QueueNode* rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    bool isEmpty() {
        return size == 0;
    }

    void enqueue(int index) {
        QueueNode* newNode = new QueueNode(index);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "The queue is empty!" << endl;
            return;
        }
        QueueNode* temp = front;
        front = front->next;
        delete temp;
        size--;
        if (isEmpty()) {
            rear = nullptr;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "The queue is empty!" << endl;
            return -1;
        }
        return front->index;
    }

    void display() {
        if (isEmpty()) {
            cout << "The queue is empty!" << endl;
            return;
        }
        cout << "Queue elements: ";
        QueueNode* temp = front;
        while (temp) {
            cout << temp->index << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

class Stack {
private:
    struct StackNode {
        int index;
        StackNode* next;
        StackNode(int idx) : index(idx), next(nullptr) {}
    };

    StackNode* top;

public:
    Stack() : top(nullptr) {}

    bool isEmpty() {
        return top == nullptr;
    }

    void push(int index) {
        StackNode* newNode = new StackNode(index);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "The stack is empty!" << endl;
            return;
        }
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() {
        if (isEmpty()) {
            cout << "The stack is empty!" << endl;
            return -1;
        }
        return top->index;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};



class Playback {
private:
    CircularDoublyLinkedList& playlist;
    Node* currentSong;
    bool isPaused;
    bool isShuffled;
    Stack history;
    Queue queue;

public:
    Playback(CircularDoublyLinkedList& playlist)
        : playlist(playlist), currentSong(nullptr), isPaused(false), isShuffled(false),
          history(), queue() {}

    void play() {
        if (playlist.isEmpty()) {
            cout << "Playlist is empty!" << endl;
            return;
        }


        if (!queue.isEmpty()) {
            int index = queue.peek();
            currentSong = playlist.getNodeAt(index);
            queue.dequeue();
        }

        else if (!currentSong) {
            currentSong = playlist.getNodeAt(0);
        }

        cout << "Now Playing: " << currentSong->data.title
             << " by " << currentSong->data.artist
             << " [" << currentSong->data.duration << "s]" << endl;

        history.push(getCurrentIndex());
    }

    void nextSong() {
        if (playlist.isEmpty()) {
            cout << "Playlist is empty!" << endl;
            return;
        }


        if (!queue.isEmpty()) {
            int index = queue.peek();
            currentSong = playlist.getNodeAt(index);
            queue.dequeue();
        }

        else if (!isShuffled) {
            currentSong = currentSong->next;
        }

        else {
            int randomIndex = rand() % playlist.getSize();
            currentSong = playlist.getNodeAt(randomIndex);
        }

        play();
    }

    void previousSong() {
        if (playlist.isEmpty()) {
            cout << "Playlist is empty!" << endl;
            return;
        }
        if (history.isEmpty() || history.peek() == -1) {
            cout << "No previous song to play!" << endl;
            return;
        }

        history.pop();
        if (!history.isEmpty()) {
            int prevIndex = history.peek();
            currentSong = playlist.getNodeAt(prevIndex);
            play();
        } else {
            cout << "No previous song in history!" << endl;
        }
    }

    void addToQueue(int index) {
        if (index < 0 || index >= playlist.getSize()) {
            cout << "Invalid song index!" << endl;
            return;
        }
        queue.enqueue(index);
        cout << "Song added to the queue: " << playlist.getNodeAt(index)->data.title << endl;
    }

    int getCurrentIndex() {
        if (!currentSong) return -1;

        Node* temp = playlist.getNodeAt(0);
        int index = 0;
        while (temp != currentSong && index < playlist.getSize()) {
            temp = temp->next;
            index++;
        }
        return index;
    }

    void toggleShuffle() {
        isShuffled = !isShuffled;
        cout << "Shuffle mode " << (isShuffled ? "enabled" : "disabled") << endl;
    }
};
#include <iostream>
#include <ctime>
#include <cstdlib>

int main() {
    // Seed for random number generation (used in shuffle mode)
    srand(static_cast<unsigned>(time(0)));

    // Create and populate the playlist
    CircularDoublyLinkedList playlist;
    playlist.addEnd(Song("Song1", "Artist1", 200));
    playlist.addEnd(Song("Song2", "Artist2", 180));
    playlist.addEnd(Song("Song3", "Artist3", 210 ));
    playlist.addEnd(Song("Song4", "Artist4", 240));

    // Initialize playback
    Playback playback(playlist);

    // Test linear playback
    std::cout << "Testing Linear Playback:" << std::endl;
    playback.play();
    playback.nextSong();
    playback.nextSong();
    playback.previousSong();

    // Test queue functionality
    std::cout << "\nTesting Queue Functionality:" << std::endl;
    playback.addToQueue(1); // Add Song2 to the queue
    playback.addToQueue(3); // Add Song4 to the queue
    playback.nextSong();    // Play Song2 from the queue
    playback.nextSong();    // Play Song4 from the queue
    playback.nextSong();    // Resume linear playback from Song3

    // Test shuffle functionality
    std::cout << "\nTesting Shuffle Mode:" << std::endl;
    playback.toggleShuffle(); // Enable shuffle
    playback.nextSong();
    playback.nextSong();
    playback.toggleShuffle(); // Disable shuffle
    playback.nextSong();

    return 0;
}

