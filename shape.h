#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QColor>
#include <QPainter>

class Shape
{
public:
    virtual ~Shape() = default;

    virtual void draw(QPainter* painter) const = 0;
    virtual void updateShape(const QPoint& currentPoint) = 0;

    void setStartPoint(const QPoint& point) { m_startPoint = point; }
    void setColor(const QColor& color) { m_color = color; }
    void setThickness(int thickness) { m_thickness = thickness; }

    QColor getColor() const { return m_color; }
    int getThickness() const { return m_thickness; }
    QPoint getStartPoint() const { return m_startPoint; }
    QPoint getEndPoint() const { return m_endPoint; }

protected:
    QPoint m_startPoint;
    QPoint m_endPoint;
    QColor m_color = Qt::black;
    int m_thickness = 2;
};

#endif