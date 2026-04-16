#include "ellipse.h"
#include <QPen>

Ellipse::Ellipse() {}

void Ellipse::draw(QPainter* painter) const
{
    QPen pen(m_color);
    pen.setWidth(m_thickness);
    painter->setPen(pen);
    QRect rect(m_startPoint, m_endPoint);
    painter->drawEllipse(rect);
}

void Ellipse::updateShape(const QPoint& currentPoint)
{
    m_endPoint = currentPoint;
}

void Ellipse::saveToStream(QDataStream& stream) const
{
    stream << m_startPoint << m_endPoint << m_color << m_thickness;
}

void Ellipse::loadFromStream(QDataStream& stream)
{
    stream >> m_startPoint >> m_endPoint >> m_color >> m_thickness;
}