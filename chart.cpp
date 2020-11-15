#include "chart.h"

myChart::myChart()
{
    minData=200.1;
    maxData=799.5;
    chartSize=QSize(500,300);
    padding=30;

    numX=10;
    scaleLength=10;
    pointMax=0;
    numData=800;
}

void myChart::initData(){
    if(minData>maxData){
        return;
    }
    maxXValue=qCeil(maxData);
    minXValue=qFloor(minData);
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    stepXValue=(maxXValue-minXValue)/numX;
    data.clear();
    pointCount.clear();
    pointMax=0;
    /*添加数据*/
    for(int i=0;i<numData;i++){
        data.append((qrand() % (int)(maxData-minData))+minData);
    }
    /*初始化频数*/
    for(int i=0;i<numX;i++){
        pointCount.append(0);
    }
    /*计算频数*/
    for(int i=0;i<data.count();i++){
        pointCount[qFloor((data[i]-minData)/stepXValue)]++;
    }
    /*查找频数最大值*/
    for(int i=0;i<pointCount.count();i++){
        if(pointMax<pointCount[i])
        {
            pointMax=pointCount[i];
        }
    }
    numY=10;
    stepYValue=qCeil((double)pointMax/10);
    /*坐标轴起止点*/
    startXYAxis=QPoint(leftTopPoint.x()+padding,leftTopPoint.y()+chartSize.height()-padding);
    endXAxis=QPoint(leftTopPoint.x()+chartSize.width()-padding,leftTopPoint.y()+chartSize.height()-padding);
    endYAxis=QPoint(leftTopPoint.x()+padding,leftTopPoint.y()+padding);
    stepX=(endXAxis.x()-startXYAxis.x())/numX;
    stepY=(startXYAxis.y()-endYAxis.y())/numY;
}

void myChart::drawChart(QPainter & painter){
    painter.setBrush(QBrush(Qt::yellow));
    painter.drawRect(QRect(leftTopPoint,chartSize));
    painter.setPen(QPen(Qt::red));
    drawXAxis(painter);
    drawYAxis(painter);
    drawXScale(painter);
    drawYScale(painter);
    drawRect(painter);
}

void myChart::drawXAxis(QPainter & painter){
    painter.drawLine(startXYAxis,endXAxis);
}

void myChart::drawYAxis(QPainter& painter){
    painter.drawLine(startXYAxis,endYAxis);
}
void myChart::drawXScale(QPainter &painter){

    /*原点标注*/
    QString labelX=QString("%1").arg(minXValue);
    painter.drawText(startXYAxis.x(),startXYAxis.y()+10,labelX);

    for(int i=0;i<numX;i++){
        /*x轴刻度*/
        QPoint pStart=QPoint(startXYAxis.x()+stepX*(i+1),startXYAxis.y());
        QPoint pEnd=QPoint(startXYAxis.x()+stepX*(i+1),startXYAxis.y()-scaleLength);
        painter.drawLine(pStart,pEnd);

        /*x轴标注*/
        labelX=QString("%1").arg(minXValue+stepXValue*(i+1));
        painter.drawText(pStart.x(),pStart.y()+10,labelX);
    }
}

void myChart::drawYScale(QPainter &painter){

    /*原点标注*/
    QString labelY=QString("%1").arg(0);
    QFontMetrics fm = painter.fontMetrics();
    QSize fSize=fm.size(0,labelY);
    painter.drawText(startXYAxis.x()-fSize.width(),startXYAxis.y(),labelY);

    for(int i=0;i<numY;i++){
        /*y轴刻度*/
        QPoint pStart=QPoint(startXYAxis.x(),startXYAxis.y()-stepY*(i+1));
        QPoint pEnd=QPoint(startXYAxis.x()+scaleLength,startXYAxis.y()-stepY*(i+1));
        painter.drawLine(pStart,pEnd);

        /*y轴标注*/
        labelY=QString("%1").arg(stepYValue*(i+1));
        fSize=fm.size(0,labelY);
        painter.drawText(pStart.x()-fSize.width(),pStart.y(),labelY);
    }
}

void myChart::drawRect(QPainter& painter){
    for(int i=0;i<numX;i++){
        double height=(startXYAxis.y()-endYAxis.y())/(double)(stepYValue*10)*pointCount[i];
        QPoint pStart=QPoint(startXYAxis.x()+stepX*i,startXYAxis.y()-height);
        QPoint pEnd=QPoint(startXYAxis.x()+stepX*(i+1),startXYAxis.y()-height);
        QPoint pLBottom=QPoint(startXYAxis.x()+stepX*i,startXYAxis.y());
        QPoint pRBottom=QPoint(startXYAxis.x()+stepX*(i+1),startXYAxis.y());
        painter.drawLine(pStart,pEnd);
        painter.drawLine(pLBottom,pStart);
        painter.drawLine(pRBottom,pEnd);
        QString value=QString("%1").arg(pointCount[i]);
        painter.drawText(pStart.x()+10,pStart.y()-10,value);
//        painter.drawRect(QRect());
    }
}
