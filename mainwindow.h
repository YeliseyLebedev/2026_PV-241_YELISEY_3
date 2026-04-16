#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>

class Canvas;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onLineTool();
    void onRectangleTool();
    void onEllipseTool();
    void onPenTool();
    void onColorPick();
    void onThicknessChanged(int value);
    void onClear();
    void onSave();
    void onLoad();

private:
    Ui::MainWindow* ui;
    Canvas* m_canvas;
    QColor m_currentColor = Qt::black;
};

#endif