#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line();

    void draw(QPainter* painter) const override;
    void updateShape(const QPoint& currentPoint) override;

    void saveToStream(QDataStream& stream) const;
    void loadFromStream(QDataStream& stream);
    int getType() const { return 1; }
};

#endif