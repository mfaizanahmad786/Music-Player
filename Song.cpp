
#include "Song.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
struct Song {
    string title;
    string artist;
    int duration;

    Song(const string &title, const string &artist, int duration)
        : title(title),
          artist(artist),
          duration(duration) {
    }
};

struct Playback {
    vector<Song> playlist;
    int currentSong;
    bool isPaused;
    bool isShuffled;
    stack<int> history;
    queue<int> queue;


    Playback(const vector<Song> &playlist)
        : playlist(playlist),
          currentSong(0),
            isPaused(false),
            isShuffled(false){
    }

    void play() {
        if(playlist.empty()) {
            cout<<"Playlist is Empty";
            return;
        }
        if(!queue.empty()) {
            currentSong = queue.front();
            queue.pop();
        }
        if(isPaused) {
            cout<<"Resuming...";
            isPaused = false;

        }else {
            cout << "Now Playing: " << playlist[currentSong].title
                  << " by " << playlist[currentSong].artist
                  << " [" << playlist[currentSong].duration << "s]" << endl;
        }
        if(currentSong!=history.top() || history.empty()) {
            history.push(currentSong);
        }
    }

    void pause() {
        if(playlist.empty() || isPaused) {
            cout<<"Nothng to pause";
        }else {
            cout<<"Playlist Paused";
            isPaused = true;
        }
    }

    void nextSong() {
        if(playlist.empty()) {
            cout<<"Playlist is Empty";
            return;
        }
        if(!queue.empty()) {
            currentSong = queue.front();
            queue.pop();
        }
        else if(isShuffled) {
            int randomSong = rand()%playlist.size();
            currentSong = randomSong;
        }else {
            currentSong = (currentSong+1) % playlist.size();
        }
        play();
    }

    void previousSong() {
        if(playlist.empty()) {
            cout<<"Playlist is Empty";
            return;
        }
        if(history.size()<=1) {
            cout<<"No Previous song to play";
            return;
        }
        history.pop();
        currentSong = history.top();
        play();
    }

    void toggleShuffle() {
        isShuffled = !isShuffled;
        cout<<"Shuffle Mode "<<(isShuffled ? "Enabled":"Disabled");
    }

    void addToQueue(int index) {
        if(index < 0 || index >= playlist.size()) {
            cout<<"Invalid Song";
            return;
        }
        queue.push(index);
        cout<<"Added To Queue";
    }

    void removeFromQueue() {
        if(queue.empty()) {
            cout<<"The Queue is Empty";
            return;
        }
        int removedSong = queue.front();
        queue.pop();
        cout<<"Song removed from queue "<<playlist[removedSong].title;
    }
};
