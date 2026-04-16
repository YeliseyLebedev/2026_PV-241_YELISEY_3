#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QToolBar>
#include <QSpinBox>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Графический редактор - Вариант 3");
    setMinimumSize(900, 700);

    m_canvas = new Canvas(this);
    setCentralWidget(m_canvas);

    QToolBar* toolBar = addToolBar("Инструменты");

    QAction* lineAction = toolBar->addAction("Линия");
    connect(lineAction, &QAction::triggered, this, &MainWindow::onLineTool);

    QAction* rectAction = toolBar->addAction("Прямоугольник");
    connect(rectAction, &QAction::triggered, this, &MainWindow::onRectangleTool);

    QAction* ellipseAction = toolBar->addAction("Эллипс");
    connect(ellipseAction, &QAction::triggered, this, &MainWindow::onEllipseTool);

    QAction* penAction = toolBar->addAction("Ручка");
    connect(penAction, &QAction::triggered, this, &MainWindow::onPenTool);

    toolBar->addSeparator();

    QAction* colorAction = toolBar->addAction("Цвет");
    connect(colorAction, &QAction::triggered, this, &MainWindow::onColorPick);

    toolBar->addSeparator();

    QLabel* thicknessLabel = new QLabel("Толщина:", this);
    toolBar->addWidget(thicknessLabel);

    QSpinBox* thicknessSpin = new QSpinBox(this);
    thicknessSpin->setRange(1, 20);
    thicknessSpin->setValue(2);
    connect(thicknessSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onThicknessChanged);
    toolBar->addWidget(thicknessSpin);

    toolBar->addSeparator();

    QAction* clearAction = toolBar->addAction("Очистить");
    connect(clearAction, &QAction::triggered, this, &MainWindow::onClear);

    QAction* saveAction = toolBar->addAction("Сохранить");
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);

    QAction* loadAction = toolBar->addAction("Загрузить");
    connect(loadAction, &QAction::triggered, this, &MainWindow::onLoad);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLineTool()
{
    m_canvas->setCurrentTool(Canvas::ToolLine);
    statusBar()->showMessage("Линия", 2000);
}

void MainWindow::onRectangleTool()
{
    m_canvas->setCurrentTool(Canvas::ToolRectangle);
    statusBar()->showMessage("Прямоугольник", 2000);
}

void MainWindow::onEllipseTool()
{
    m_canvas->setCurrentTool(Canvas::ToolEllipse);
    statusBar()->showMessage("Эллипс", 2000);
}

void MainWindow::onPenTool()
{
    m_canvas->setCurrentTool(Canvas::ToolPen);
    statusBar()->showMessage("Ручка", 2000);
}

void MainWindow::onColorPick()
{
    QColor color = QColorDialog::getColor(m_currentColor, this, "Выберите цвет");
    if (color.isValid()) {
        m_currentColor = color;
        m_canvas->setCurrentColor(m_currentColor);
    }
}

void MainWindow::onThicknessChanged(int value)
{
    m_canvas->setCurrentThickness(value);
}

void MainWindow::onClear()
{
    m_canvas->clearShapes();
}

void MainWindow::onSave()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить", "", "*.draw");
    if (!filename.isEmpty()) {
        m_canvas->saveToFile(filename);
    }
}

void MainWindow::onLoad()
{
    QString filename = QFileDialog::getOpenFileName(this, "Загрузить", "", "*.draw");
    if (!filename.isEmpty()) {
        m_canvas->loadFromFile(filename);
    }
}