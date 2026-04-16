#include "rectangle.h"
#include <QPen>

Rectangle::Rectangle() {}

void Rectangle::draw(QPainter* painter) const
{
    QPen pen(m_color);
    pen.setWidth(m_thickness);
    painter->setPen(pen);
    QRect rect(m_startPoint, m_endPoint);
    painter->drawRect(rect);
}

void Rectangle::updateShape(const QPoint& currentPoint)
{
    m_endPoint = currentPoint;
}

void Rectangle::saveToStream(QDataStream& stream) const
{
    stream << m_startPoint << m_endPoint << m_color << m_thickness;
}

void Rectangle::loadFromStream(QDataStream& stream)
{
    stream >> m_startPoint >> m_endPoint >> m_color >> m_thickness;
}