#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateImage();

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
private:
    Ui::MainWindow *ui;
    bool showMode;
    QTimer showTimer;
    QImage* ASImage;
    QImage* earthImage;
};
#endif // MAINWINDOW_H
