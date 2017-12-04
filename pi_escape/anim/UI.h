#ifndef PIESCAPE2_UI_H
#define PIESCAPE2_UI_H


#include <cstdint>
#include <SDL_keysym.h>
#include <memory>
#include <vector>
#include <iostream>
#include <map>

enum Event {
    LEVEL
};

class Observer;

class UIModel {
protected:
    uint64_t time;
public:
    UIModel();

    virtual ~UIModel();

    virtual void setTime(uint64_t time);

    uint64_t getTime() const;

    virtual int isDone() const = 0;
};

class UIController {
protected:
public:
    UIController();

    virtual ~UIController();

    virtual void onKey(SDLKey key) = 0;

    virtual void onExitKey() = 0;
};

class UIView {
protected:
public:
    UIView();

    virtual ~UIView();

    virtual void draw() = 0;
};

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
    Subject *subject;
public:
    virtual void notified();

    void setSubject(Subject *subject);
};

#endif //PIESCAPE2_UI_H
