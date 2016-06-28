#include "frames.h"

Frames::Frames()
{
    initFrames();
}

void Frames::initFrames()
{
    dimensionSize = 32;
    frames.clear();
    frames.push_back(new QImage(dimensionSize, dimensionSize, QImage::Format_ARGB32));

    selectedFrame = 0;
}

std::vector<QImage*>::iterator Frames::first()
{
    return frames.begin();
}

std::vector<QImage*>::iterator Frames::last()
{
    return frames.end();
}

int Frames::getFrameCount()
{
    return static_cast<int>(frames.size());
}

int Frames::getCurrentFrame()
{
    return selectedFrame;
}

//inserts an image into the frames vector at the selected index plus one
void Frames::insertFrame()
{
    frames.insert(frames.begin()+selectedFrame+1, new QImage(dimensionSize, dimensionSize, QImage::Format_ARGB32));
    selectedFrame = selectedFrame + 1;
}

//sets the current frame to the given image
void Frames::setCurrentFrame(QImage* q)
{
    frames[getCurrentFrame()] = q;
}

//deletes the image from the selected frame index, sets the selected frame back by one
void Frames::deleteFrame()
{
    frames.erase(frames.begin()+selectedFrame);
    selectedFrame = selectedFrame-1;
}

//clones the current image and adds it to the frame after it
void Frames::copyFrame()
{
    frames.insert(frames.begin() + selectedFrame, new QImage(frames[selectedFrame]->copy()));
    selectedFrame = selectedFrame + 1;
}

std::vector<QImage*> Frames::getFrames()
{
    return frames;
}

QImage* Frames::getFrame(int i)
{
    return frames[i];
}

//resizes all the frames in the sprite project to the given dimension
void Frames::resizeFrames(int dim){

    dimensionSize =dim;
    for(size_t i =0;i<frames.size();i++)\
    {
        *frames[i] = frames[i]->scaled(dim, dim, Qt::KeepAspectRatio);
    }
}
