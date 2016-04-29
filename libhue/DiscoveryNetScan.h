/*
 * DiscoveryNetScan.h
 *
 *  Created on: Apr 29, 2016
 *      Author: pete
 */

#ifndef LIBHUE_DISCOVERYNETSCAN_H_
#define LIBHUE_DISCOVERYNETSCAN_H_

#include <QtCore>
#include <QtNetwork>

class DiscoveryNetScan : public QObject {
    Q_OBJECT
public:
    DiscoveryNetScan(QObject *parent = 0);
    virtual ~DiscoveryNetScan();
    void findBridges();

signals:
    void error();
    void foundBridge(QHostAddress bridge);
    void noBridgesFound();

private slots:
    void onTimeout();
    void onReadyRead();
    void ipScanFinished();
    void ipContentReceived();
    void onFinished();
    void ipTimeout();

private:
    QList<QHostAddress> m_reportedBridges;
    QNetworkAccessManager m_qnam;
    QMutex m_wait;
    QTimer *m_timer;
    QNetworkReply *m_reply;
};

#endif /* LIBHUE_DISCOVERYNETSCAN_H_ */
