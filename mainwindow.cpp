//
// Created by frede on 7/9/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QBoxLayout>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

//Main window class
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Date setup
    ui->dateEdit->setDate(QDate::currentDate());

    //TODO: fix and sort out the graphing stuff issues.
    //TODO: Check if the QtCharts is properly installed.
    //TODO: the QtCharts has been added in the CMakeLists.txt
    //TODO: but getting an error, check the installing of Qt6.

    

    /*
        chartView = new QChartView();
        chartView->setRenderHint(QPainter::Antialiasing);

        ui->mainwindow_Right_GridLayout->addWidget(
            chartView,
            0,
            0
        );
    */

    /*
     * LEFT PANEL
     * Put scroll area into left grid layout
    */
    ui->mainwindow_Left_GridLayout->addWidget(
        ui->mainwindow_Left_ScrollArea,
        0,
        0
    );

    ui->mainwindow_Left_GridLayout->setRowStretch(0,1);
    ui->mainwindow_Left_GridLayout->setColumnStretch(0,1);

    /*
     * RIGHT PANEL
     * Add graph widget placeholder
     *
     * Replace this with QCustomPlot/QChartView/etc.
     */
    QTextEdit *graphPanel = new QTextEdit();
    graphPanel->setReadOnly(true);
    graphPanel->setPlaceholderText(
        "Graph panel\n\n"
        "Graph content from left panel will appear here."
    );

    ui->mainwindow_Right_GridLayout->addWidget(
        graphPanel,
        0,
        0
    );

    ui->mainwindow_Right_GridLayout->setRowStretch(0,1);
    ui->mainwindow_Right_GridLayout->setColumnStretch(0,1);

    /*
     * MAIN WINDOW LAYOUT
     */
    QVBoxLayout *mainLayout = new QVBoxLayout(ui->centralwidget);

    /*
     * Top buttons
     */
    QHBoxLayout *topLayout = new QHBoxLayout();

    topLayout->addWidget(ui->viewPushButton);
    topLayout->addWidget(ui->clearScrollBarPushButton);
    topLayout->addWidget(ui->quitPushButton);
    topLayout->addWidget(ui->dateEdit);

    topLayout->addStretch();
    mainLayout->addLayout(topLayout);

    /*
     * Main content area:
     *
     * LEFT:
     *   gridLayoutWidget
     *
     * RIGHT:
     *   gridLayoutWidget_2
     */
    QHBoxLayout *contentLayout = new QHBoxLayout();

    contentLayout->addWidget(ui->gridLayoutWidget);
    contentLayout->addWidget(ui->gridLayoutWidget_2);

    /*
     * Give more space to graph panel
     */
    contentLayout->setStretch(0,1);
    contentLayout->setStretch(1,2);

    mainLayout->addLayout(contentLayout);

    //connecting signals and slots on push button
    connect(ui->quitPushButton, &QPushButton::clicked, this, &MainWindow::on_quitPushButton_clicked);
    connect(ui->viewPushButton, &QPushButton::clicked, this, &MainWindow::on_viewPushButton_clicked);
    connect(ui->clearScrollBarPushButton, &QPushButton::clicked, this, &MainWindow::on_clearScrollBarPushButton_clicked);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::on_quitMenuBar_triggered);
    connect(ui->actionopen, &QAction::triggered, this, &MainWindow::on_openMenuBar_triggered);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_aboutMenuBar_triggered);
}

// Actions on MenuBar
void MainWindow::on_openMenuBar_triggered()
{
    qDebug() << "Open MenuBar selected";

    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        QDir::homePath(),
        tr("Text Files (*.txt);;PDF Files (*.pdf);;JPEG Files (*.jpg);;All Files (*.*)")
    );

    if (fileName.isEmpty())
        return;

    QFileInfo info(fileName);
    QString ext = info.suffix().toLower();

    if (ext == "pdf" || ext == "png")
    {
        QDesktopServices::openUrl(
            QUrl::fromLocalFile(fileName));
    } else if (ext == "txt" || ext == "asc")
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(
                this,
                tr("Error"),
                tr("Cannot open file.")
            );
            return;
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // Create text viewer
        QTextEdit *textViewer = new QTextEdit();

        textViewer->setReadOnly(true);
        textViewer->setText(content);

        // Put QTextEdit inside the scroll area
        ui->mainwindow_Left_ScrollArea->setWidget(textViewer);

        qDebug() << "TXT file loaded:" << fileName;

    }
}
void MainWindow::on_aboutMenuBar_triggered()
{
    qDebug() << "Quit MenuBar selected";

    QMessageBox::about(
        this,
        tr("About"),
        tr(
            "<h2>QtWidgets-Project</h2>"
            "<p>Version: 1.0</p>"
            "<p>Created with Qt 6.</p>"
            "<p>Author: Frederic Bonnet.</p>"
            "<p>&copy; July 2026</p>"
        )
    );
}
void MainWindow::on_quitMenuBar_triggered()
{
    qDebug() << "Quit MenuBar selected";
    close();
}

// PushButtons activators
void MainWindow::on_viewPushButton_clicked()
{
    qDebug() << "View button clicked";
    on_openMenuBar_triggered();
}
void MainWindow::on_clearScrollBarPushButton_clicked()
{
    qDebug() << "Clear ScrollBar button clicked";


    QWidget *widget = ui->mainwindow_Left_ScrollArea->takeWidget();

    if (widget)
    {
        widget->deleteLater();
    }

    /*

    QWidget *leftWidget =
    ui->mainwindow_Left_ScrollArea->takeWidget();

    if (leftWidget)
        leftWidget->deleteLater();


    if (graphPanel)
    {
        graphPanel->deleteLater();
        graphPanel = nullptr;
    }

    */
}

// Quiting and closing actions
void MainWindow::on_quitPushButton_clicked()
{
    qDebug() << "Quit button clicked, closing the application";
    close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
