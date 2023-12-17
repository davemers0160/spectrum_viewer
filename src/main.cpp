
#include "spectrum_viewer.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spectrum_viewer w;
    w.show();
    a.exec();
    if (w.mwterminate == false)
      return 0;
    else
      return -1;
}
