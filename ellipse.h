#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();

    void draw(QPainter* painter) const override;
    void updateShape(const QPoint& currentPoint) override;

    void saveToStream(QDataStream& stream) const;
    void loadFromStream(QDataStream& stream);
    int getType() const { return 3; }
};

#endif