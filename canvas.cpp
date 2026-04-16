#include "canvas.h"
#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "pentool.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QDataStream>

Canvas::Canvas(QWidget* parent) : QWidget(parent)
{
    setMinimumSize(800, 600);
    setStyleSheet("background-color: white;");
}

void Canvas::setCurrentTool(Tool tool)
{
    m_currentTool = tool;
}

void Canvas::setCurrentColor(const QColor& color)
{
    m_currentColor = color;
}

void Canvas::setCurrentThickness(int thickness)
{
    m_currentThickness = thickness;
}

void Canvas::clearShapes()
{
    m_shapes.clear();
    update();
}

void Canvas::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    for (const auto& shape : m_shapes) {
        if (shape.get()) {
            shape->draw(&painter);
        }
    }

    if (m_currentShape.get()) {
        m_currentShape->draw(&painter);
    }
}

void Canvas::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;

        Shape* newShape = nullptr;
        switch (m_currentTool) {
            case ToolLine:
                newShape = new Line();
                break;
            case ToolRectangle:
                newShape = new Rectangle();
                break;
            case ToolEllipse:
                newShape = new Ellipse();
                break;
            case ToolPen:
                newShape = new PenTool();
                break;
        }

        m_currentShape = SmartPtr<Shape>(newShape);
        m_currentShape->setStartPoint(event->pos());
        m_currentShape->setColor(m_currentColor);
        m_currentShape->setThickness(m_currentThickness);
        m_currentShape->updateShape(event->pos());
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isDrawing && m_currentShape.get()) {
        if (m_currentTool == ToolPen) {
            PenTool* pen = dynamic_cast<PenTool*>(m_currentShape.get());
            if (pen) {
                pen->addPoint(event->pos());
            }
        } else {
            m_currentShape->updateShape(event->pos());
        }
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing && m_currentShape.get()) {
        if (m_currentTool != ToolPen) {
            m_currentShape->updateShape(event->pos());
        }
        m_shapes.append(std::move(m_currentShape));
        m_isDrawing = false;
        update();
    }
}

bool Canvas::saveToFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream stream(&file);
    stream << (qint32)m_shapes.size();

    for (const auto& shape : m_shapes) {
        if (!shape.get()) continue;

        if (dynamic_cast<Line*>(shape.get())) {
            stream << (qint32)1;
            dynamic_cast<Line*>(shape.get())->saveToStream(stream);
        } else if (dynamic_cast<Rectangle*>(shape.get())) {
            stream << (qint32)2;
            dynamic_cast<Rectangle*>(shape.get())->saveToStream(stream);
        } else if (dynamic_cast<Ellipse*>(shape.get())) {
            stream << (qint32)3;
            dynamic_cast<Ellipse*>(shape.get())->saveToStream(stream);
        } else if (dynamic_cast<PenTool*>(shape.get())) {
            stream << (qint32)4;
            dynamic_cast<PenTool*>(shape.get())->saveToStream(stream);
        }
    }

    file.close();
    return true;
}

bool Canvas::loadFromFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    clearShapes();

    QDataStream stream(&file);
    qint32 shapeCount;
    stream >> shapeCount;

    for (int i = 0; i < shapeCount; ++i) {
        qint32 type;
        stream >> type;

        switch (type) {
            case 1: {
                Line* line = new Line();
                line->loadFromStream(stream);
                m_shapes.append(SmartPtr<Shape>(line));
                break;
            }
            case 2: {
                Rectangle* rect = new Rectangle();
                rect->loadFromStream(stream);
                m_shapes.append(SmartPtr<Shape>(rect));
                break;
            }
            case 3: {
                Ellipse* ellipse = new Ellipse();
                ellipse->loadFromStream(stream);
                m_shapes.append(SmartPtr<Shape>(ellipse));
                break;
            }
            case 4: {
                PenTool* pen = new PenTool();
                pen->loadFromStream(stream);
                m_shapes.append(SmartPtr<Shape>(pen));
                break;
            }
        }
    }

    file.close();
    update();
    return true;
}