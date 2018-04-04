#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfaz.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //Poner una imagen de fondo
    QPixmap fondo("../Images/fondo.jpg");
    fondo = fondo.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, fondo);
    this->setPalette(palette);
    this->setFixedSize(QSize(536, 374));

    //configuracion ComboBox busqueda informada
    ui->cbbInf->setEditable(false);
    QStringList lista = (QStringList()<<"Avara"<<"A*");
    ui->cbbInf->addItems(lista);

    //configuracion ComboBox busqueda no informada
    ui->cbbNoInf->setEditable(false);
    QStringList lista2 = (QStringList()<<"Amplitud"<<"Costo Uniforme"<<"Profundidad evitando ciclos");
    ui->cbbNoInf->addItems(lista2);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_bttCancelar_clicked() {
    this->close();
}

void MainWindow::on_bttArchivo_clicked() {    
    QString filtro = "Text File (*.txt)";
    QString path;
    path = QFileDialog::getOpenFileName(this, "Seleccione un archivo", QDir::homePath(), filtro);

    Interfaz *interfazMario = new Interfaz(path);

    bool noInfChecked = ui->rbtNoInf->isChecked();
    bool infChecked = ui->rbtInf->isChecked();

    if(noInfChecked) {        
        if(path.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
        } else {
            QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);            
            //interfazMario->leerArchivo(path);
            interfazMario->show();
            this->hide();
        }
    } else if (infChecked) {        
        if(path.length() == 0) {
            QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
        } else {
            QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);            
            interfazMario->show();
            this->hide();
        }
    }
}
