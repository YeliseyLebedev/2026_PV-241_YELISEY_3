#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();

    void draw(QPainter* painter) const override;
    void updateShape(const QPoint& currentPoint) override;

    void saveToStream(QDataStream& stream) const;
    void loadFromStream(QDataStream& stream);
    int getType() const { return 2; }
};

#endif