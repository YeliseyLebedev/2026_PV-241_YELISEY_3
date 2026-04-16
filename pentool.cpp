#include "pentool.h"
#include <QPen>

PenTool::PenTool() {}

void PenTool::draw(QPainter* painter) const
{
    if (m_points.size() < 2) return;

    QPen pen(m_color);
    pen.setWidth(m_thickness);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);

    for (int i = 0; i < m_points.size() - 1; ++i) {
        painter->drawLine(m_points[i], m_points[i + 1]);
    }
}

void PenTool::updateShape(const QPoint& currentPoint)
{
    m_points.append(currentPoint);
    m_endPoint = currentPoint;
}

void PenTool::addPoint(const QPoint& point)
{
    m_points.append(point);
    if (m_points.size() == 1) {
        m_startPoint = point;
    }
    m_endPoint = point;
}

void PenTool::saveToStream(QDataStream& stream) const
{
    stream << m_points << m_color << m_thickness;
}

void PenTool::loadFromStream(QDataStream& stream)
{
    stream >> m_points >> m_color >> m_thickness;
    if (!m_points.isEmpty()) {
        m_startPoint = m_points.first();
        m_endPoint = m_points.last();
    }
}