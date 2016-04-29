/*
 * DiscoveryUPnP.h
 *
 *  Created on: Apr 29, 2016
 *      Author: pete
 */

#ifndef LIBHUE_DISCOVERYUPNP_H_
#define LIBHUE_DISCOVERYUPNP_H_

#include <QtCore>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

class QTimer;

class DiscoveryUPnP: public QUdpSocket
{
    Q_OBJECT

public:
    DiscoveryUPnP(QObject *parent);
    void findBridges();

signals:
    void error();
    void foundBridge(QHostAddress bridge);
    void noBridgesFound();

private slots:
    void onTimeout();
    void onReadyRead();

private:
    QList<QHostAddress> m_reportedBridges;
    QTimer *m_timeout;
};
#endif /* LIBHUE_DISCOVERYUPNP_H_ */
