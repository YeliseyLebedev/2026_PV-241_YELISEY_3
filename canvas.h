#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVector>
#include "smartptr.h"
#include "shape.h"

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget* parent = nullptr);

    enum Tool { ToolLine, ToolRectangle, ToolEllipse, ToolPen };

    void setCurrentTool(Tool tool);
    void setCurrentColor(const QColor& color);
    void setCurrentThickness(int thickness);
    void clearShapes();

    bool saveToFile(const QString& filename);
    bool loadFromFile(const QString& filename);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QVector<SmartPtr<Shape>> m_shapes;
    SmartPtr<Shape> m_currentShape;
    Tool m_currentTool = ToolLine;
    QColor m_currentColor = Qt::black;
    int m_currentThickness = 2;
    bool m_isDrawing = false;
};

#endif