/*
 * DiscoveryUPnP.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: pete
 */

#include "DiscoveryUPnP.h"

// Discovery timeout in seconds
const unsigned int DISCOVERY_TIMEOUT = 3;

DiscoveryUPnP::DiscoveryUPnP(QObject *parent) :
    QObject(parent),
    m_timeout(new QTimer(this))
{
    quint16 port = 1900;
    unsigned int tries = 0;
    const unsigned int maxtries = 10;

    while (!bind(port++)) {
        if (++tries == maxtries) {
            QMetaObject::invokeMethod(this, "error", Qt::QueuedConnection);
            return;
        }
    }

    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

    m_timeout->setSingleShot(true);
    connect(m_timeout, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void DiscoveryUPnP::findBridges()
{
    m_timeout->stop();
    m_reportedBridges.clear();

    QString b("M-SEARCH * HTTP/1.1\r\n"
              "HOST: 239.255.255.250:1900\r\n"
              "MAN: \"ssdp:discover\"\r\n"
              "MX: %1\r\n"
              "ST: libhue:idl\r\n");
    b.arg(DISCOVERY_TIMEOUT);

//    qDebug() << "writing datagram" << b;
    m_timeout->start(DISCOVERY_TIMEOUT * 1000);
    if (writeDatagram(b.toUtf8(), QHostAddress("239.255.255.250"), 1900) < 0) {
        emit error();
    }
}

void DiscoveryUPnP::onTimeout()
{
    if (m_reportedBridges.isEmpty()) {
        emit noBridgesFound();
        // Try again...
        findBridges();
    }
}

void DiscoveryUPnP::onReadyRead()
{
    while (hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

//        qDebug() << "got datagram" << datagram;
        if (!m_reportedBridges.contains(sender)) {
            sender.setAddress(sender.toIPv4Address());
            m_reportedBridges << sender;
            emit foundBridge(sender);
        }
    }
}
