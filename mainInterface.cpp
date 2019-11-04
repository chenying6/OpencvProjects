#include "mainInterface.h"
#include "opencv2\opencv.hpp"
#include "qwidget.h"
#include "qfiledialog.h"
#include "QMessageBox.h"
#include <iostream>
using namespace std;
using namespace cv;
using cv::ml::EM;
//void on_mouse(int event, int x, int y, int flags, void *ustc);
Mat QImage2cvMat(QImage* image)
{
	cv::Mat mat;
	switch (image->format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image->height(), image->width(), CV_8UC4, (void*)image->bits(), image->bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image->height(), image->width(), CV_8UC3, (void*)image->bits(), image->bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(image->height(), image->width(), CV_8UC1, (void*)image->bits(), image->bytesPerLine());
		break;
	}
	return mat;
}
MainInterface::MainInterface(QWidget *parent):QWidget(parent) {
	ui = new Ui_Form;
	ui->setupUi(this);
	connect(ui->inputImage, SIGNAL(clicked()), this, SLOT(inputImage()));
	connect(ui->em, SIGNAL(clicked()), this, SLOT(calculateEM()));
	connect(ui->bayesian, SIGNAL(clicked()), this, SLOT(calculateBayesian()));
	connect(ui->kmeans, SIGNAL(clicked()), this, SLOT(calculateKMeans()));
}
void MainInterface::inputImage() {
	cout << "entering beauty......" << endl;
	
#pragma region inputImage
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("选择图像"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
		return;
	else{
		QImage* img = new QImage;
		if (!(img->load(filename))) //加载图像
		{
			QMessageBox::information(this,
				tr("打开图像失败"),
				tr("打开图像失败!"));
			delete img;
			return;
		}
		ui->originImage->setPixmap(QPixmap::fromImage(*img));
		sourceImage = QImage2cvMat(img);
	}
#pragma endregion

}
void MainInterface::calculateEM() {
	const int MAX_CLUSTERS = 5;
	Vec3b colorTab[] =
	{
		Vec3b(0, 0, 255),
		Vec3b(0, 255, 0),
		Vec3b(255, 100, 100),
		Vec3b(255, 0, 255),
		Vec3b(0, 255, 255)
	};
	cv::Mat modifiedImage;
	cv::Mat data;
	for (int i = 0; i < sourceImage.rows; i++)
		for (int j = 0; j < sourceImage.cols; j++)
		{
			Vec3b point = sourceImage.at<Vec3b>(i, j);
			Mat tmp = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
			data.push_back(tmp);
		}
	Ptr<EM> em = EM::create();
	em->setClustersNumber(3);
	em->setCovarianceMatrixType(EM::COV_MAT_SPHERICAL);
	em->setTermCriteria(TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 500, 0.1));
	em->trainEM(data, noArray(), modifiedImage, noArray());
	int n = 0;
	//显示聚类结果，不同的类别用不同的颜色显示
	for (int i = 0; i < sourceImage.rows; i++)
		for (int j = 0; j < sourceImage.cols; j++)
		{
			int clusterIdx = modifiedImage.at<int>(n);
			sourceImage.at<Vec3b>(i, j) = colorTab[clusterIdx];
			n++;
		}
	imshow("modifiedImage", sourceImage);
	waitKey(0);
}

void MainInterface::calculateBayesian() {

}

void MainInterface::calculateKMeans() {

}


MainInterface::~MainInterface() {

}


