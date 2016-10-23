#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QHeaderView>
#include <QString>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    void readFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    void readSettings();
    void writeSettings();
    void createMenu();
    void createTable();
    void createTable_2();
    QTableWidget *table, *table_2;

private slots:
    void open();
    void zoom(QTableWidgetItem *Item);
};

#endif // MAINWINDOW_H
