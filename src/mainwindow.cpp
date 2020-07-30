#include "include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , showMode(false)
{
  ui->setupUi(this);
  connect(&showTimer, &QTimer::timeout, this, &MainWindow::updateImage);

  //cv::Mat img1 = cv::imread(".//satellite.png");
  //cv::Mat img2 = cv::imread(".//earth02.png");

  ASImage = new QImage(".//satellite.png");
  earthImage = new QImage(".//earth02.png");

  if(ASImage->isNull() || earthImage->isNull())
  {
    qDebug() << "read image error!!!";
  }
  else
  {
    showTimer.start(10);
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::updateImage()
{
  this->update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
  int winWidth = this->frameGeometry().width();
  int winHeight = this->frameGeometry().height();
  QPoint centerPoint(winWidth/2, winHeight/2);
  static QPoint ASCenterPoint(0, (winHeight/2)-(ASImage->height()/2));
  //绘制黑色背景
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::black);
  painter.drawRect(rect());

  if(showMode)
  {
    //painter.setPen(QPen(Qt::blue, 4));
    //painter.drawEllipse(centerPoint.x()-winWidth*0.75/2,
    //                    centerPoint.y()-winHeight*0.75/2,
    //                    winWidth*0.75,winHeight*0.75);
    //绘制地球图片
    painter.setPen(Qt::NoPen);
    painter.drawImage(QPoint((winWidth/2)-(earthImage->width()/2),
                             (winHeight/2)-(earthImage->height()/2)),
                      *earthImage);

    painter.setPen(QPen(Qt::blue, 4));
    static float row = 0.0;
    int ex = winWidth*0.75*0.5*cos(row) + centerPoint.x();
    int ey = winHeight*0.75*0.5*sin(row) + centerPoint.y();
    //painter.drawEllipse(ex-25, ey-25, 50, 50);
    painter.drawImage(QPoint(ex-(ASImage->width()/2),
                             ey-(ASImage->height()/2)), *ASImage);
    row+=0.01;
    if(row > 6.2831852)
    {
      row = 0;
    }
    //QMatrix matrix;
    //matrix.rotate(90.0);
    //QImage earthShowImage = earthImage->transformed(matrix, Qt::FastTransformation);
  }
  else
  {
    //绘制卫星图片
    painter.drawImage(ASCenterPoint, *ASImage);
    ASCenterPoint.setX(ASCenterPoint.x()+5);
    if(ASCenterPoint.x() > winWidth)
    {
      ASCenterPoint.setX(0);
    }
  }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
  if(e->key() == Qt::Key_Escape)
  {
    QApplication* app;
    app->exit(0);
  }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
  if(e->button() == Qt::RightButton)
  {
    showMode = !showMode;
  }
}

