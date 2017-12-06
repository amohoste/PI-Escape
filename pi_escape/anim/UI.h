#ifndef PIESCAPE2_UI_H
#define PIESCAPE2_UI_H


#include <cstdint>
#include <SDL_keysym.h>
#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include "FontManager.h"

enum Event {
    LEVEL, SELECTION, INPUT
};

class UIView;

class Observer;

class Listener;

class Subject;

class Subject {
private:
    std::map<Event, std::vector<Observer *>> observers;

protected:

    void notify(Event e);

public:

    void registerObserver(Event e, Observer *o);

};


class Observer {
protected:
public:
    virtual void notified();
};


class Observable {
protected:
    vector<Listener *> listeners;
public:
    void addListener(Listener *listener);

    void fireInvalidationEvent();
};

class Listener {
private:
    Observable *model{};
public:
    virtual void invalidated() = 0;
};

class UIModel : public Observable {
protected:
    uint64_t time;

    bool done;

public:
    UIModel();

    virtual ~UIModel();


    void setTime(uint64_t time);

    uint64_t getTime() const;

    int isDone() const;

    void setDone(bool done); //is alles klaar?
};

class UIController : public Observer{
protected:
public:
    UIController();

    virtual ~UIController();

    virtual void onKey(SDLKey key) = 0;

    virtual void onExitKey() = 0;
};

class UIView : public Listener {
protected:
    FontManager *fontManager;
public:
    void setFontManager(FontManager *fm);

    UIView();

    virtual ~UIView();

    virtual void draw() = 0;
};


#endif //PIESCAPE2_UI_H
