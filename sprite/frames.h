#ifndef FRAMES_H
#define FRAMES_H
#include <vector>
#include <QImage>
#include <QColor>
#include <QMovie>

class Frames
{
public:
    // constructor
    Frames();

    // initialize helper for constructing, editing, saving, etc
    void initFrames ();

    //copy current frame and paste into next frame
    void copyFrame();

    // insert and delete frames
    void insertFrame();
    void deleteFrame();

    // set frame
    void setCurrentFrame(QImage*);

    //getters & setters
    QImage* getFrame(int);
    int getFrameCount();
    int getCurrentFrame();

    // helper methods
    void resizeFrames(int);

    // frames iterator
    std::vector<QImage*>::iterator first();
    std::vector<QImage*>::iterator last();

    // vector of frames forms a sprite
    std::vector<QImage*> frames;
    int selectedFrame;

    std::vector<QImage*> getFrames();
    void exportAsGIF();

private:

    // helpful getters
    void selectCurrentFrame();
    void getImageSize();

    int dimensionSize;
};

#endif // FRAMES_H
