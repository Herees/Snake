#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer* timer;

private slots:
    void start();
    void seconds2minutes();
    void reset();
    void stop();


private:
    Ui::MainWindow *ui;
    int sec;
    int min;
};

#endif // MAINWINDOW_HH
