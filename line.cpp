#include "line.h"
#include <QPen>

Line::Line() {}

void Line::draw(QPainter* painter) const
{
    QPen pen(m_color);
    pen.setWidth(m_thickness);
    painter->setPen(pen);
    painter->drawLine(m_startPoint, m_endPoint);
}

void Line::updateShape(const QPoint& currentPoint)
{
    m_endPoint = currentPoint;
}

void Line::saveToStream(QDataStream& stream) const
{
    stream << m_startPoint << m_endPoint << m_color << m_thickness;
}

void Line::loadFromStream(QDataStream& stream)
{
    stream >> m_startPoint >> m_endPoint >> m_color >> m_thickness;
}