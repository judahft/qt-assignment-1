#include <QtDebug>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    mNetManager = new QNetworkAccessManager(this);
    connect(mNetManager, &QNetworkAccessManager::finished, this, &MainWindow::handleNetFinished);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_open_url(const QString &url) {
    mNetManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::on_get_url_button_clicked() {
    QString new_fetch_time = QDateTime::currentDateTime().toString();
    fetch_time = new_fetch_time;

    on_open_url(ui->endpoint_value_label->text());
}

QJsonObject MainWindow::normalized_response(QByteArray data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject response = doc.object();

    return response;
}

void MainWindow::change_value_labels(QJsonObject response) {
    QJsonObject rates = response["rates"].toObject();
    QString base_value = response["base"].toString();
    QString date_value = response["date"].toString();

    double btc_raw_value = rates["BTC"].toDouble();
    double eth_raw_value = rates["ETH"].toDouble();
    double ada_raw_value = rates["ADA"].toDouble();

    QString btc_value = QString::number(btc_raw_value);
    QString eth_value = QString::number(eth_raw_value);
    QString ada_value = QString::number(ada_raw_value);

    ui->btc_value_label->setText(btc_value);
    ui->eth_value_label->setText(eth_value);
    ui->ada_value_label->setText(ada_value);

    ui->date_value_label->setText(date_value);
    ui->base_value_label->setText(base_value);
    ui->last_fetched_value_label->setText(fetch_time);
}

void MainWindow::handleNetFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonObject response = normalized_response(data);
        change_value_labels(response);
    } else {
        qDebug("Network error");
    }
}
