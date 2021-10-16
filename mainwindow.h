#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void on_open_url(const QString& url);
        QJsonObject normalized_response(QByteArray data);
        void change_value_labels(QJsonObject data);

        QString fetch_time = NULL;

    protected slots:
        void handleNetFinished(QNetworkReply* reply);

    private slots:
        void on_get_url_button_clicked();

    private:
        Ui::MainWindow *ui;
        QNetworkAccessManager* mNetManager = NULL;
};

#endif
