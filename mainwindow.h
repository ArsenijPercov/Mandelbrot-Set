#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define COLORS 256
namespace Ui {      //start of Ui namespace
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    int getColorValue(double,double);
    int colormap_lookup(long double);
//~MainWindow();
protected:
    void paintEvent(QPaintEvent*);
    //void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    int max_hops = 1000;
    long double centerX = 0;
    long double centerY = 0;
    long double currentHeight;
    long double currentWidth;
    double scale = 1;
    QPoint mouseStart;
    int colors = COLORS;
    QColor color_map[COLORS];
};
#endif // MAINWINDOW_H
