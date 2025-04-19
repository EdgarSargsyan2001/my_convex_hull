#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(generatePoints()), ui->drawWidget, SLOT(generatePoints()));
    connect(this, SIGNAL(runJarvis()), ui->drawWidget, SLOT(runJarvis()));
    connect(this, SIGNAL(runGraham()), ui->drawWidget, SLOT(runGraham()));
    connect(this, SIGNAL(runDivideAndConquer()), ui->drawWidget, SLOT(runDivideAndConquer()));
    connect(this, SIGNAL(clearAll()), ui->drawWidget, SLOT(clearAll()));
    connect(this, SIGNAL(stop()), ui->drawWidget, SLOT(stopAllAlgorithms()));
    connect(this, SIGNAL(pointsCountChanged(int)), ui->drawWidget, SLOT(onPointsCountChanged(int)));
    connect(this, SIGNAL(speedChanged(int)), ui->drawWidget, SLOT(onSpeedChanged(int)));
    connect(this, SIGNAL(statusChanged(const QString &)), ui->statusLabel, SLOT(setText(const QString &)));
    connect(this, SIGNAL(setCodeText(const QString &, const QString &)), this, SLOT(onSetCodeText(const QString &, const QString &)));
    connect(this, SIGNAL(highlightCodeLine(int)), this, SLOT(onHighlightCodeLine(int)));
    connect(ui->drawWidget, SIGNAL(highlightLine(int)), this, SIGNAL(highlightCodeLine(int))); // Connect highlightLine

    ui->pointsValueLabel->setText(QString::number(ui->pointsSlider->value()));
    ui->speedValueLabel->setText(QString::number(ui->speedSlider->value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_released()
{
    emit generatePoints();
    emit statusChanged("Points generated");
}

void MainWindow::on_jarvisButton_released()
{
    emit runJarvis();
    emit statusChanged("Running Jarvis...");
    emit setCodeText(
        "1. Find the leftmost bottom point P0\n"
        "2. Set current point P = P0\n"
        "3. Do while P != P0:\n"
        "4.   Find next point Q that makes maximum right turn\n"
        "5.   For each point R in set:\n"
        "6.     If R makes left turn from PQ or is collinear and farther, Q = R\n"
        "7.   Add Q to hull\n"
        "8.   Set P = Q\n"
        "9. Return hull",
        "Jarvis March Pseudocode");
}

void MainWindow::on_grahamButton_released()
{
    emit runGraham();
    emit statusChanged("Running Graham...");
    emit setCodeText(
        "1. Find point P0 with minimum y-coordinate (if tie, take leftmost)\n"
        "2. Sort all other points by polar angle with P0\n"
        "3. Remove points with same angle keeping farthest one\n"
        "4. Push P0, P[1], P[2] into stack S\n"
        "5. For i = 3 to n-1\n"
        "6.   While ccw(next-to-top(S), top(S), P[i]) != counterclockwise\n"
        "7.     Pop from S\n"
        "8.   Push P[i] into S\n"
        "9. S contains the convex hull points",
        "Graham's Scan Pseudocode");
}

void MainWindow::on_dacButton_released()
{
    emit runDivideAndConquer();
    emit statusChanged("Running Divide & Conquer...");
    emit setCodeText(
        "1. Sort points by x-coordinate\n"
        "2. Divide points into left and right halves recursively\n"
        "3. If 3 points: determine hull based on orientation\n"
        "4. If 2 points: order by y-coordinate\n"
        "5. If 1 point: return single point\n"
        "6. Find upper and lower bridges between left and right hulls\n"
        "7. Merge hulls using bridges, keeping points between bridges\n"
        "8. Return final convex hull",
        "Divide and Conquer Pseudocode");
}

void MainWindow::on_clearButton_released()
{
    emit clearAll();
    emit statusChanged("Cleared");
    emit setCodeText("", "Algorithm Pseudocode");
}

void MainWindow::on_stopButton_released()
{
    emit stop();
    emit statusChanged("Stopped");
}

void MainWindow::on_pointsSlider_valueChanged(int value)
{
    emit pointsCountChanged(value);
    ui->pointsValueLabel->setText(QString::number(value));
}

void MainWindow::on_speedSlider_valueChanged(int value)
{
    emit speedChanged(value);
    ui->speedValueLabel->setText(QString::number(value));
}

void MainWindow::onSetCodeText(const QString &code, const QString &title)
{
    ui->codeDisplay->setPlainText(code);
    ui->codeTitleLabel->setText(title);
}

void MainWindow::onHighlightCodeLine(int line)
{
    line++;
    QTextCursor cursor = ui->codeDisplay->textCursor();
    cursor.movePosition(QTextCursor::Start);
    for (int i = 0; i < line - 1; i++)
    { // line - 1 because pseudocode starts at 1
        cursor.movePosition(QTextCursor::Down);
    }
    cursor.select(QTextCursor::LineUnderCursor);
    ui->codeDisplay->setTextCursor(cursor);
    ui->codeDisplay->ensureCursorVisible();
}
