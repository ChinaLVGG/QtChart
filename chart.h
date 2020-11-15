#ifndef CHART_H
#define CHART_H

#include <QList>
#include <QPoint>
#include <QSize>
#include <QPainter>
#include <QTime>
#include <QBrush>
#include <QDebug>
#include <QFontMetrics>
#include "qmath.h"
class myChart
{
public:
    myChart();
public:
    QPoint leftTopPoint;
    QSize chartSize;
    int minXValue;
    int maxXValue;
    double minData;
    double maxData;
    int numX;//条形统计图条数
    QList<int> pointCount;//每条的频数

    int pointMax;//最大频数
    int numY;//纵轴标注数量
    int scaleLength;//刻度长度
    QList <double> data;//数据
    int padding;//
    int stepXValue;//x标注间数据的间隔
    int stepYValue;//y标注间数据的间隔
    double stepX;//x标注间像素的间隔
    double stepY;//y标注间像素的间隔
    QPoint startXYAxis;//坐标原点
    QPoint endXAxis;
    QPoint endYAxis;
    int numData;//数据数量
public:
    void initData();
    void drawChart(QPainter &);
    void drawXAxis(QPainter &);
    void drawYAxis(QPainter &);
    void drawXScale(QPainter &);
    void drawYScale(QPainter &);
    void drawRect(QPainter &);
};

#endif // CHART_H
