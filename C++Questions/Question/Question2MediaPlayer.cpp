/* 
Pure virtual function and inheritance

Question 2: Implement a simple media player application that can play different types of media files. The media player should support playing audio and video files. You need to design and implement the classes for this media player, incorporating various OOP concepts.

Requirements:

Create an abstract base class Media that represents a generic media file. It should have the following pure virtual functions:

virtual void play() = 0: Play the media.
virtual void pause() = 0: Pause the media.
virtual void stop() = 0: Stop the media.
virtual void displayInfo() = 0: Display information about the media (e.g., file name, duration).

Implement two derived classes: Audio and Video, which represent audio and video media files, respectively. Both classes should inherit from the Media base class.

Add appropriate member variables and functions to the Audio and Video classes to support their specific features.

Implement a MediaPlayer class that can store and manage a collection of Media objects.

The MediaPlayer class should have the following functionalities:

A function to add media files to the player.
A function to display all media files' information in the player.
A function to play a specific media file by name.
A function to pause and resume the currently playing media.
A function to stop the currently playing media.
Constraints:

Assume that the media files are represented as strings containing their file names.
For simplicity, assume that the play, pause, and stop functions in the MediaPlayer class do not handle actual 
media playback but simply display messages indicating the respective actions.

Implement a callback mechanism using function pointers or lambdas, allowing the media player to notify the user 
when playback is started, paused, or stopped.
*/



#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// ==============================
// Abstract Media class
// ==============================
class Media {
protected:
    string fileName;
    double duration; // in seconds

public:
    Media(const string& name, double dur) : fileName(name), duration(dur) {}
    virtual ~Media() {}

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void displayInfo() = 0;

    string getFileName() const { return fileName; }
};

// ==============================
// Audio class
// ==============================
class Audio : public Media {
private:
    string artist;

public:
    Audio(const string& name, double dur, const string& art)
        : Media(name, dur), artist(art) {}

    void play() override {
        cout << "Playing audio: " << fileName << " by " << artist << endl;
    }

    void pause() override {
        cout << "Audio paused: " << fileName << endl;
    }

    void stop() override {
        cout << "Audio stopped: " << fileName << endl;
    }

    void displayInfo() override {
        cout << "Audio File: " << fileName
             << ", Duration: " << duration
             << "s, Artist: " << artist << endl;
    }
};

// ==============================
// Video class
// ==============================
class Video : public Media {
private:
    string resolution;

public:
    Video(const string& name, double dur, const string& res)
        : Media(name, dur), resolution(res) {}

    void play() override {
        cout << "Playing video: " << fileName << " at " << resolution << " resolution" << endl;
    }

    void pause() override {
        cout << "Video paused: " << fileName << endl;
    }

    void stop() override {
        cout << "Video stopped: " << fileName << endl;
    }

    void displayInfo() override {
        cout << "Video File: " << fileName
             << ", Duration: " << duration
             << "s, Resolution: " << resolution << endl;
    }
};

// ==============================
// MediaPlayer class
// ==============================
class MediaPlayer {
private:
    vector<Media*> mediaCollection;
    Media* currentMedia = nullptr;

public:
    // Callbacks
    function<void(const string&)> onPlay;
    function<void(const string&)> onPause;
    function<void(const string&)> onStop;

    ~MediaPlayer() {
        for (auto m : mediaCollection)
            delete m;
    }

    void addMedia(Media* media) {
        mediaCollection.push_back(media);
    }

    void displayAllMedia() {
        for (auto m : mediaCollection)
            m->displayInfo();
    }

    void playMedia(const string& name) {
        for (auto m : mediaCollection) {
            if (m->getFileName() == name) {
                currentMedia = m;
                currentMedia->play();
                if (onPlay) onPlay(name);
                return;
            }
        }
        cout << "Media file not found: " << name << endl;
    }

    void pauseCurrent() {
        if (currentMedia) {
            currentMedia->pause();
            if (onPause) onPause(currentMedia->getFileName());
        }
    }

    void stopCurrent() {
        if (currentMedia) {
            currentMedia->stop();
            if (onStop) onStop(currentMedia->getFileName());
            currentMedia = nullptr;
        }
    }
};

// ==============================
// MAIN
// ==============================
int main() {
    MediaPlayer player;

    // Assign callbacks using lambdas
    player.onPlay = [](const string& name){ cout << "[Callback] Started playing: " << name << endl; };
    player.onPause = [](const string& name){ cout << "[Callback] Paused: " << name << endl; };
    player.onStop = [](const string& name){ cout << "[Callback] Stopped: " << name << endl; };

    // Add media
    player.addMedia(new Audio("song.mp3", 180, "Ravi"));
    player.addMedia(new Video("movie.mp4", 7200, "1080p"));

    cout << "All Media in Player:" << endl;
    player.displayAllMedia();
    cout << endl;

    // Play audio
    player.playMedia("song.mp3");
    player.pauseCurrent();
    player.stopCurrent();
    cout << endl;

    // Play video
    player.playMedia("movie.mp4");
    player.pauseCurrent();
    player.stopCurrent();

    return 0;
}
/* 
All Media in Player:
Audio File: song.mp3, Duration: 180s, Artist: Ravi
Video File: movie.mp4, Duration: 7200s, Resolution: 1080p

Playing audio: song.mp3 by Ravi
[Callback] Started playing: song.mp3
Audio paused: song.mp3
[Callback] Paused: song.mp3
Audio stopped: song.mp3
[Callback] Stopped: song.mp3

Playing video: movie.mp4 at 1080p resolution
[Callback] Started playing: movie.mp4
Video paused: movie.mp4
[Callback] Paused: movie.mp4
Video stopped: movie.mp4
[Callback] Stopped: movie.mp4
*/