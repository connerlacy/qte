#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString m_ProjectName, m_ProjectDirectory, m_SDKPath, m_Author;

public slots:
    void slot_GenerateProject();
    void slot_SetSDKPath();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
