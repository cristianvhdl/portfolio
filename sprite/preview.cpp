#include "preview.h"
#include <iostream>

Preview::Preview()
{
   // Initialize FPS and timer.
   FPS = 12;
   fpsTimer = new QTimer(this);
   fpsTimer->start(1000 / FPS);
   // Connect timer timeout() to slot updatePreview()
   QObject::connect(fpsTimer, SIGNAL(timeout()), this, SLOT(updatePreview()));
   framesSet = false;
}

Preview::~Preview()
{

}

// Provides preview with an iterator of frames to display.
void Preview::updateFrames(std::vector<QImage*> frames)
{
   // Update preview frames from frames class.
   framesVector = frames;
   framesIter = framesVector.begin();
   // Frames have been initially initialized.
   framesSet = true;
}

//sets the fps that the preview runs at
void Preview::setFPS(int fps)
{
   // Stop timer, update FPS, and start timer once more.
   fpsTimer->stop();
   FPS = fps;
   fpsTimer->start(1000 / FPS);
}

//updates the preview
void Preview::updatePreview()
{
   // Do not run until frames have been provided.
   if (framesSet)
   {
       // Get current QImage to display and increment iterator to next frame.
       QImage* abs = *framesIter;
       framesIter++;

       // Once iterator reaches end, start back at beginning.
       if (framesIter == framesVector.end())
       {
           // Reset iterator.
           framesIter = framesVector.begin();
       }
       // Send signal to update GUI with next QImage to display.
       emit updatePreviewWindow(abs);
   }
}
