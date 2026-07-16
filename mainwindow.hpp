//
// Created by frede on 7/9/2026.
//

#ifndef QTWIDGETS_PROJECT_MAINWINDOW_HPP
#define QTWIDGETS_PROJECT_MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QBarSeries>
#include <QtCharts/QBarSet>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Constructors
    explicit MainWindow(QWidget* parent = nullptr);
    //Button actions
    void on_viewPushButton_clicked();
    void on_clearScrollBarPushButton_clicked();
    void on_quitPushButton_clicked();
    //MenuBar actions
    void on_openMenuBar_triggered();
    void on_quitMenuBar_triggered();
    //Help menu bar functions
    void on_aboutMenuBar_triggered();
    ~MainWindow() override;

    QWidget *graphPanel;
    QChartView *chartView = nullptr;

private:
    Ui::MainWindow* ui;
};


#endif //QTWIDGETS_PROJECT_MAINWINDOW_HPP
