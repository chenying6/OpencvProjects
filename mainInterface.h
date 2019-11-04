#ifndef MainInterface_H
#define MainInterface_H
#include "ui_mainInterface.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
namespace ui {
	class MainInterface:public Ui_Form {};
}
class MainInterface : public QWidget {
	Q_OBJECT
public:
	MainInterface(QWidget *parent = 0);
	virtual ~MainInterface();

private slots:
	void inputImage();
	void calculateEM();
	void calculateBayesian();
	void calculateKMeans();


private:
	Ui_Form *ui;
	cv::Mat sourceImage;
};

#endif // !MainInterface_H
