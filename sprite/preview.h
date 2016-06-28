#ifndef PREVIEW_H
#define PREVIEW_H
#include <QTimer>
using namespace std;

class Preview : public QObject
{
   Q_OBJECT

public:
   Preview();
   ~Preview();
   void updateFrames(std::vector<QImage*> frames);
   void setFPS(int fps);
private:
   QTimer* fpsTimer;
   std::vector<QImage*> framesVector;
   std::vector<QImage*>::iterator framesIter;
   int FPS;
   bool framesSet;

signals:
   void updatePreviewWindow(QImage* image);
public slots:
   void updatePreview();
};

#endif // PREVIEW_H
