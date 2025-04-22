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
        "1. Գտնել ամենաձախ ներքևի կետը P0\n"
        "2. Սահմանել ընթացիկ կետը P = P0\n"
        "3. Կատարել մինչև P != P0:\n"
        "4.   Գտնել հաջորդ Q կետը, որը կատարում է առավելագույն աջ շրջադարձ\n"
        "5.   Յուրաքանչյուր կետ R-ի համար բազմությունում:\n"
        "6.     Եթե R-ը կատարում է ձախ շրջադարձ PQ-ից կամ ավելի հեռու է, Q = R\n"
        "7.   Ավելացնել Q-ն թաղանթին\n"
        "8.   Սահմանել P = Q\n"
        "9. Վերադարձնել թաղանթը",
        "'Jarvis'-ի ընթացքի կեղծ կոդը");
}

void MainWindow::on_grahamButton_released()
{
    emit runGraham();
    emit statusChanged("Running Graham...");
    emit setCodeText(
        "1. Գտնել P0 կետը նվազագույն y-կոորդինատով (եթե հավասար է, վերցնել ամենաձախը)\n"
        "2. Դասավորել բոլոր մյուս կետերը P0-ի հետ բևեռային անկյունով\n"
        "3. Հեռացնել նույն անկյուն ունեցող կետերը՝ պահելով ամենահեռավորը\n"
        "4. Ավելացնել P0, P[1], P[2] կետերը S պահունակի մեջ\n"
        "5. For i = 3 մինչև n-1\n"
        "6.   While ccw(next-to-top(S), top(S), P[i]) != ժամացույցի հակառակ\n"
        "7.     Հանել S-ից\n"
        "8.   Ավելացնել P[i] կետը S-ի մեջ\n"
        "9. S-ը պարունակում է ուռուցիկ թաղանթի կետերը",
        "'Graham'-ի ընթացքի կեղծ կոդը");
}

void MainWindow::on_dacButton_released()
{
    emit runDivideAndConquer();
    emit statusChanged("Running Divide & Conquer...");
    emit setCodeText(
        "1. Դասավորել կետերը x-կոորդինատով\n"
        "2. Բաժանել կետերը ձախ և աջ կիսամասերի ռեկուրսիվ կերպով\n"
        "3. Եթե 3 կետ կա՝ որոշել թաղանթը՝ հիմնվելով կողմնորոշման վրա\n"
        "4. Եթե 2 կետ կա՝ դասավորել y-կոորդինատով\n"
        "5. Եթե 1 կետ կա՝ վերադարձնել միայնակ կետը\n"
        "6. Գտնել վերին և ստորին կամուրջները ձախ և աջ թաղանթների միջև\n"
        "7. Միավորել թաղանթները՝ օգտագործելով կամուրջները, պահելով կետերը կամուրջների միջև\n"
        "8. Վերադարձնել վերջնական ուռուցիկ թաղանթը",
        "'Բաժանիր և տիրիր'-ի կեղծ կոդ");
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
