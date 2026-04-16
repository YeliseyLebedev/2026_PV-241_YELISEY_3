#ifndef PENTOOL_H
#define PENTOOL_H

#include "shape.h"
#include <QVector>

class PenTool : public Shape
{
public:
    PenTool();

    void draw(QPainter* painter) const override;
    void updateShape(const QPoint& currentPoint) override;

    void addPoint(const QPoint& point);

    void saveToStream(QDataStream& stream) const;
    void loadFromStream(QDataStream& stream);
    int getType() const { return 4; }

private:
    QVector<QPoint> m_points;
};

#endif