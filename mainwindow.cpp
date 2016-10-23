#include "mainwindow.h"


MainWindow::MainWindow()
{
    setObjectName("MainWindow");
    setWindowTitle("Qt Main Window Example");
    readSettings();

    createMenu();
    createTable();
    createTable_2();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
        writeSettings();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        readFile(fileName);
}

void MainWindow::zoom(QTableWidgetItem *Item)
{
    QString line = Item->text();
    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%5").arg((line.at(0))));
    table_2->setItem(0,0,newItem);
    line.remove(0,1);
    QTableWidgetItem *newsItem = new QTableWidgetItem(tr("%5").arg((line)));
    table_2->setItem(0,1,newsItem);
    table_2->resizeColumnToContents(1);
}

void MainWindow::readFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    int i=0;
    table->setRowCount(10);
    while(!in.atEnd()){
        i++;
        QString line = in.readLine();
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%5").arg((line)));
        table->setItem(i, 0, newItem);
    }
    table->resizeColumnsToContents();
}

void MainWindow::createTable_2()
{
    table_2 = new QTableWidget(1,3,this);
    table_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_2->setGeometry(0,320,500,80);
    table_2->horizontalHeader()->setDefaultSectionSize(20);
    table_2->verticalHeader()->setDefaultSectionSize(60);
}

void MainWindow::createTable()
{
    table = new QTableWidget(1,1,this);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setGeometry(0,20,500,200);
    table->horizontalHeader()->setDefaultSectionSize(20);
    table->verticalHeader()->setDefaultSectionSize(20);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%5").arg((1)*(1)));
    table->setItem(0, 0, newItem);
    QModelIndex Index;
    connect(table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)) , this,SLOT(zoom(QTableWidgetItem*)));
}

void MainWindow::createMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *newAct = new QAction(tr("&New"), this);
    fileMenu->addAction(newAct);

    QAction *openAct = new QAction(tr("&Open"), this);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

}


void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}
