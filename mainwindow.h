#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:    
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    vector< vector<int> > leerArchivo(QString filePath);

private slots:   
    void on_bttCancelar_clicked();
    void on_bttArchivo_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
