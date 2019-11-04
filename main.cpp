#include "mainInterface.h"
#include <qapplication.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	cout << "OpenCV machine Learning widgets" << endl;
	MainInterface mainInterface;
	mainInterface.show();

	return app.exec();
}