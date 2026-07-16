

// Put the scroll area into the grid layout
ui->mainwindow_Left_GridLayout->addWidget(
    ui->mainwindow_Left_ScrollArea,
    0,
    0,
    1,
    1
);

// Optional: make scroll area expand
ui->mainwindow_Left_GridLayout->setRowStretch(0, 1);
ui->mainwindow_Left_GridLayout->setColumnStretch(0, 1);


//Insert the layout here:
QVBoxLayout *mainLayout = new QVBoxLayout( ui->centralwidget);
QHBoxLayout *topLayout = new QHBoxLayout;


topLayout->addWidget(ui->viewPushButton);
topLayout->addWidget(ui->quitPushButton);
topLayout->addWidget(ui->dateEdit);

mainLayout->addLayout(topLayout);

//mainLayout->addWidget(ui->mainwindow_Left_ScrollArea);

// Add the grid layout widget containing the scroll area
mainLayout->addWidget(ui->gridLayoutWidget);

//mainLayout->setStretch(0, 0);
//mainLayout->setStretch(1, 1);


// Optional: make scroll area expand when window resizes
//mainLayout->setStretch(0, 0);  // top controls keep their size
//mainLayout->setStretch(1, 1);  // scroll area expands







#include <qmainwindow.h>

QPushButton button("Hello world!", nullptr);
button.resize(200, 100);
button.show();

QMainWindow main_window;

main_window.setWindowTitle("QtWidgets-Project");
main_window.resize(300, 200);
main_window.show();



QString fileName = QFileDialog::getOpenFileName(
    this,
    tr("Open File"),
    "",
    tr("All Files (*.*)")
);

if (fileName.isEmpty())
    return;

QFile file(fileName);

if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
{
    qDebug() << "Cannot open file:" << fileName;
    return;
}

QByteArray data = file.readAll();

qDebug() << "Opened file:" << fileName;
qDebug() << data;

file.close();

