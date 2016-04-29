/*
 * DiscoveryNetScan.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: pete
 */

#include "DiscoveryNetScan.h"

DiscoveryNetScan::DiscoveryNetScan(QObject *parent) : QObject(parent)
{
	m_reply = NULL;
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(ipTimeout()));
}

DiscoveryNetScan::~DiscoveryNetScan()
{
}

void DiscoveryNetScan::findBridges()
{
	QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
	foreach (const QHostAddress &address, nets) {
		if (address.name() == "eth0") {
			for (int i = 2; i < 254; i++) {
				int pos = address.toString().lastIndexOf(".");
				if (pos > 0) {
					QString toTest = address.toString().left(pos);
					toTest += QString("%1").arg(i);
					QUrl url("http://" + toTest + "/description.xml");
					qDebug() << "Testing" << url.toString();
					m_reply = m_qnam.get(QNetworkRequest(url));
				    connect(m_reply, SIGNAL(finished()), this, SLOT(ipScanFinished()));
				    connect(m_reply, SIGNAL(readyRead()), this, SLOT(ipContentReceived()));
				    connect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
				    m_timer->start(3000);
				    while (m_timer->isActive()) {
				    	QThread::msleep(500);
				    }
				}
			}
		}
	}
}

void DiscoveryNetScan::ipScanFinished()
{

}

void DiscoveryNetScan::ipContentReceived()
{
	QByteArray resp = m_reply->readAll();
}

void DiscoveryNetScan::onFinished()
{

}

void DiscoveryNetScan::ipTimeout()
{
	disconnect(m_reply, SIGNAL(finished()), this, SLOT(onFinished()));
	m_reply->abort();
}
