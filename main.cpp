 #include <QApplication>
 #include "mainwindow.h"
#include "fileReader.h"


 int main(int argc, char *argv[])
 {
//     FileReader f("test.txt");

//     vector<double> temp = f.getValues();
//     std::cerr << temp.size();

//     for ( int i = 0; i < temp.size() ; ++i ) {
//         std::cerr << temp[i] << std::endl;
//     }
     QApplication a(argc, argv);
     MainWindow w;
     w.show();

     return a.exec();
 }
