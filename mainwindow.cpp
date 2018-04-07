#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfaz.h"
#include "busqueda.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

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

vector< vector<int> > MainWindow::leerArchivo(QString filePath) {
    QStringList lista, lista2;
    vector< vector<int> > listaArchivo;
    vector< int > listaFilasColumnas;
    int filas, columnas;
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Not open";
    }
    QTextStream in(&file);

    QString mfile = in.readAll();
    lista = mfile.split("\n");
    filas = lista.length(); //número de filas para el tablero

    QString aux = lista.first();
    lista2 = aux.split(" ");
    columnas = lista2.length(); //número de columnas para el tablero
    listaArchivo.assign(filas, vector<int>(columnas));

    for (int i = 0; i < filas; i++) {
        QStringList listaAux;
        QString cadenaAux;
        cadenaAux = lista.at(i);
        listaAux = cadenaAux.split(" ");

        for (int j = 0; j < columnas; j++) {
            QString first = listaAux.at(j);
            listaArchivo[i][j] = first.toInt();
        }
    }

    file.close();

    return listaArchivo;
}

void MainWindow::on_bttCancelar_clicked() {
    this->close();
}

void MainWindow::on_bttArchivo_clicked() {    
    QString filtro = "Text File (*.txt)";
    QString path;
    path = QFileDialog::getOpenFileName(this, "Seleccione un archivo", QDir::homePath(), filtro);
    vector< vector<int> > tablero = leerArchivo(path);

    int filas = tablero.size();
    int columnas = tablero[0].size();
    int xInicial;
    int yInicial;
    int xFinal;
    int yFinal;

    for (int i = 0; (unsigned) i < filas; i++) {
        for (int j = 0; (unsigned) j < columnas; j++) {
            if (tablero[i][j] == 2){
                xInicial = i;
                yInicial = j;
            } else if (tablero[i][j] == 5) {
                xFinal = i;
                yFinal = j;
            }
        }
    }

    busqueda buscar(filas, columnas, tablero, xInicial, yInicial, xFinal, yFinal);

    vector< pair< pair<int,int> ,int > > camino;

    bool noInfChecked = ui->rbtNoInf->isChecked();
    bool infChecked = ui->rbtInf->isChecked();

    QString textoCbbInf = ui->cbbInf->currentText();
    QString textoCbbNoInf = ui->cbbNoInf->currentText();

    if(noInfChecked) {        
        if(textoCbbNoInf == "Amplitud") {
            if(path.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);
                QTime myTimer;
                myTimer.start();
                camino = buscar.amplitud();                
                Interfaz *interfazMario = new Interfaz(camino, tablero);
                interfazMario->show();
                //int tiempoTotal = myTimer.elapsed();
                QMessageBox::information(NULL, tr("Amplitud"),
                                         tr("Nodos expandidos: ")+QString::number(buscar.nodosExpandidos)
                                         +tr("\n")+tr("Profundidad del árbol: ")+QString::number(buscar.profundidadDelArbol)
                                         +tr("\n")+tr("Tiempo de cómputo: ")+QString::number(buscar.tiempoTotal));
            }
        } else if(textoCbbNoInf == "Costo Uniforme") {
            if(path.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);
                QTime myTimer;
                myTimer.start();
                camino = buscar.costoUniforme();
                Interfaz *interfazMario = new Interfaz(camino, tablero);
                interfazMario->show();
                int tiempoTotal = myTimer.elapsed();
                QMessageBox::information(NULL, tr("Costo Uniforme"),
                                         tr("Nodos expandidos: ")+QString::number(buscar.nodosExpandidos)
                                         +tr("\n")+tr("Profundidad del árbol: ")+QString::number(buscar.profundidadDelArbol)
                                         +tr("\n")+tr("Tiempo de cómputo: ")+QString::number(buscar.tiempoTotal));
            }
        } else if(textoCbbNoInf == "Profundidad evitando ciclos") {
            if(path.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);
                QTime myTimer;
                myTimer.start();
                camino = buscar.profundidad();
                Interfaz *interfazMario = new Interfaz(camino, tablero);
                interfazMario->show();
                int tiempoTotal = myTimer.elapsed();
                QMessageBox::information(NULL, tr("Profundidad evitando ciclos"),
                                         tr("Nodos expandidos: ")+QString::number(buscar.nodosExpandidos)
                                         +tr("\n")+tr("Profundidad del árbol: ")+QString::number(buscar.profundidadDelArbol)
                                         +tr("\n")+tr("Tiempo de cómputo: ")+QString::number(buscar.tiempoTotal));
            }
        }
    } else if (infChecked) {
        if (textoCbbInf == "Avara") {
            if(path.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);
                QTime myTimer;
                myTimer.start();
                camino = buscar.avara();
                Interfaz *interfazMario = new Interfaz(camino, tablero);
                interfazMario->show();
                int tiempoTotal = myTimer.elapsed();
                QMessageBox::information(NULL, tr("Profundidad evitando ciclos"),
                                         tr("Nodos expandidos: ")+QString::number(buscar.nodosExpandidos)
                                         +tr("\n")+tr("Profundidad del árbol: ")+QString::number(buscar.profundidadDelArbol)
                                         +tr("\n")+tr("Tiempo de cómputo: ")+QString::number(buscar.tiempoTotal));
            }
        } else if (textoCbbInf == "A*") {
            if(path.length() == 0) {
                QMessageBox::information(NULL, tr("Path"), tr("No se seleccionó ningún archivo"));
            } else {
                QMessageBox::information(NULL, tr("Path"), tr("Se seleccionó ") + path);
                QTime myTimer;
                myTimer.start();
                camino = buscar.aEstrella();
                Interfaz *interfazMario = new Interfaz(camino, tablero);
                interfazMario->show();
                int tiempoTotal = myTimer.elapsed();
                QMessageBox::information(NULL, tr("Profundidad evitando ciclos"),
                                         tr("Nodos expandidos: ")+QString::number(buscar.nodosExpandidos)
                                         +tr("\n")+tr("Profundidad del árbol: ")+QString::number(buscar.profundidadDelArbol)
                                         +tr("\n")+tr("Tiempo de cómputo: ")+QString::number(buscar.tiempoTotal));
            }
        }
    }
}
