/* 
Pure virtual function and inheritance

Question 2: Implement a simple media player application that can play different types of media files. 
The media player should support playing audio and video files. 
You need to design and implement the classes for this media player, incorporating various OOP concepts.

Requirements:
Create an abstract base class Media that represents a generic media file. It should have the following pure virtual functions:

virtual void play() = 0: Play the media.
virtual void pause() = 0: Pause the media.
virtual void stop() = 0: Stop the media.
virtual void displayInfo() = 0: Display information about the media (e.g., file name, duration).

Implement two derived classes: Audio and Video, which represent audio and video media files, respectively. 
Both classes should inherit from the Media base class.

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
For simplicity, assume that the play, pause, and stop functions in the MediaPlayer class do not handle actual media playback 
but simply display messages indicating the respective actions.
Implement a callback mechanism using function pointers or lambdas, allowing the media player to notify the user 
when playback is started, paused, or stopped.
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
using namespace std;

/* ============================================================
   ABSTRACT BASE CLASS — MEDIA
============================================================ */
class Media {
  protected:
    string fileName;
    double duration; // in seconds

  public:
    Media(string name, double dur) : fileName(name), duration(dur) {}

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void displayInfo() = 0;

    string getName() const { return fileName; }

    virtual ~Media() {}
};

/* ============================================================
   DERIVED CLASS — AUDIO
============================================================ */
class Audio : public Media {
  private:
    string artist;
    string format;

  public:
    Audio(string name, double dur, string art, string fmt)
        : Media(name, dur), artist(art), format(fmt) {}

    void play() override {
        cout << "Playing audio: " << fileName << endl;
    }

    void pause() override {
        cout << "Audio paused: " << fileName << endl;
    }

    void stop() override {
        cout << "Audio stopped: " << fileName << endl;
    }

    void displayInfo() override {
        cout << "[Audio] File: " << fileName
             << ", Duration: " << duration << " secs"
             << ", Artist: " << artist
             << ", Format: " << format << endl;
    }
};

/* ============================================================
   DERIVED CLASS — VIDEO
============================================================ */
class Video : public Media {
  private:
    string resolution;
    string format;

  public:
    Video(string name, double dur, string res, string fmt)
        : Media(name, dur), resolution(res), format(fmt) {}

    void play() override {
        cout << "Playing video: " << fileName << endl;
    }

    void pause() override {
        cout << "Video paused: " << fileName << endl;
    }

    void stop() override {
        cout << "Video stopped: " << fileName << endl;
    }

    void displayInfo() override {
        cout << "[Video] File: " << fileName
             << ", Duration: " << duration << " secs"
             << ", Resolution: " << resolution
             << ", Format: " << format << endl;
    }
};

/* ============================================================
   MEDIA PLAYER — MANAGES MEDIA FILES + CALLBACKS
============================================================ */
class MediaPlayer {
  private:
    vector<unique_ptr<Media>> mediaList;
    Media* currentMedia = nullptr;
    bool isPaused = false;

    // Callback functions
    function<void(const string&)> onPlay;
    function<void(const string&)> onPause;
    function<void(const string&)> onStop;

  public:
    // Register callback handlers
    void setCallbacks(
        function<void(const string&)> playCb,
        function<void(const string&)> pauseCb,
        function<void(const string&)> stopCb
    ) {
        onPlay = playCb;
        onPause = pauseCb;
        onStop = stopCb;
    }

    // Add media to player
    void addMedia(unique_ptr<Media> m) {
        mediaList.push_back(move(m));
    }

    // Display all media info
    void displayAll() const {
        cout << "\nAll Media Files:\n";
        for (const auto& m : mediaList)
            m->displayInfo();
        cout << endl;
    }

    // Play a media file by name
    void playMedia(const string& name) {
        for (auto& m : mediaList) {
            if (m->getName() == name) {
                currentMedia = m.get();
                currentMedia->play();
                if (onPlay) onPlay(name);
                isPaused = false;
                return;
            }
        }
        cout << "Media '" << name << "' not found.\n";
    }

    // Pause current media
    void pauseMedia() {
        if (currentMedia && !isPaused) {
            currentMedia->pause();
            if (onPause) onPause(currentMedia->getName());
            isPaused = true;
        }
    }

    // Resume if paused
    void resumeMedia() {
        if (currentMedia && isPaused) {
            cout << "Resuming: " << currentMedia->getName() << endl;
            if (onPlay) onPlay(currentMedia->getName());
            isPaused = false;
        }
    }

    // Stop current media
    void stopMedia() {
        if (currentMedia) {
            currentMedia->stop();
            if (onStop) onStop(currentMedia->getName());
            currentMedia = nullptr;
            isPaused = false;
        }
    }
};

/* ============================================================
   MAIN — DEMO PROGRAM
============================================================ */
int main() {
    MediaPlayer player;

    // Register callback notifications
    player.setCallbacks(
        [](const string& name) { cout << "[Callback] Started: " << name << endl; },
        [](const string& name) { cout << "[Callback] Paused: " << name << endl; },
        [](const string& name) { cout << "[Callback] Stopped: " << name << endl; }
    );

    // Add media files
    player.addMedia(make_unique<Audio>("song1.mp3", 210, "Arijit", "mp3"));
    player.addMedia(make_unique<Video>("movie1.mp4", 7200, "1080p", "mp4"));
    player.addMedia(make_unique<Audio>("song2.wav", 180, "Sonu Nigam", "wav"));

    player.displayAll();

    // Play media
    player.playMedia("song1.mp3");
    player.pauseMedia();
    player.resumeMedia();
    player.stopMedia();
    
    cout << endl;

    player.playMedia("movie1.mp4");
    player.stopMedia();

    return 0;
}
/*

All Media Files:
[Audio] File: song1.mp3, Duration: 210 secs, Artist: Arijit, Format: mp3
[Video] File: movie1.mp4, Duration: 7200 secs, Resolution: 1080p, Format: mp4
[Audio] File: song2.wav, Duration: 180 secs, Artist: Sonu Nigam, Format: wav

Playing audio: song1.mp3
[Callback] Started: song1.mp3
Audio paused: song1.mp3
[Callback] Paused: song1.mp3
Resuming: song1.mp3
[Callback] Started: song1.mp3
Audio stopped: song1.mp3
[Callback] Stopped: song1.mp3

Playing video: movie1.mp4
[Callback] Started: movie1.mp4
Video stopped: movie1.mp4
[Callback] Stopped: movie1.mp4
*/