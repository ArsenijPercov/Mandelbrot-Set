#include "mainwindow.h"
#include <complex>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <math.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui (new Ui::MainWindow)
{

    ui->setupUi(this);
    currentWidth = 4;
    currentHeight = 4;
    for (int i = 0;i< colors;i++)
    {
        color_map[0].setRgb(i*256%colors,i*256%colors,i*256/colors);
    }
}

int MainWindow::getColorValue(double ptX, double ptY)
{

    long double transX = currentWidth*(ptX/width()-0.5)+centerX;
    long double transY = currentHeight*(ptY/height()-0.5)+centerY;
    int hops = 0;
    long double y = 0;
    long double x = 0;
    long double xz = 0;
    long double yz = 0;
    long double w = 0;
    while((xz+yz <= 4) && (hops<=max_hops))
    {
        y = 2*x*y + transY;
        x = xz - yz + transX;
        xz = x*x;
        yz = y*y;
        hops++;
    }
    //qDebug()<<hops;
    if (hops < max_hops)
    {
        long double logz = log(xz+yz)/2;
        long double nu = log(logz/log(2))/log(2);
        hops = hops +1 - nu;
        return colormap_lookup(nu);
    }
    else {
        return 0;
    }
}
int MainWindow::colormap_lookup(long double nu)
{
    return (int)(nu*colors)%colors;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter oPainter(this);
    oPainter.setRenderHint(QPainter::Antialiasing);

    QPen oPen;
    int nColorValue = 0;

    for (int x = 0; x < width(); ++x)
    {
        for (int y=0; y < height();++y)
        {
            nColorValue = getColorValue(static_cast<double>(x),static_cast<double>(y));
            oPen.setColor(QColor((nColorValue),nColorValue,nColorValue));
            oPainter.setPen(oPen);
            oPainter.drawPoint(x,y);
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        centerX += (long double)(event->x()- (width()/2))/width()*currentWidth ;
        centerY += (long double)(event->y() - (height()/2))/height()*currentHeight;
        //qDebug()<<event->x()<<event->y()<<width()<<height()<<centerX<<centerY;
        scale = 2*scale;
        if (scale<=1)
        {
            scale = 2;
        }
        currentWidth /= scale;
        currentHeight /= scale;
        //qDebug()<<currentWidth<<currentHeight;
        update();

    }
    if (event->button() == Qt::RightButton)
    {
        centerX += (double)(event->x()- (width()/2))/width()*currentWidth ;
        centerY += (double)(event->y() - (height()/2))/height()*currentHeight;
        //qDebug()<<event->x()<<event->y()<<width()<<height()<<centerX<<centerY;
        currentWidth *= scale;
        currentHeight *= scale;
        scale = scale/2;
        //qDebug()<<currentWidth<<currentHeight;
        update();

    }
}
