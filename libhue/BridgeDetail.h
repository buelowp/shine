/*
 * BridgeDetail.h
 *
 *  Created on: Apr 29, 2016
 *      Author: pete
 */

#ifndef LIBHUE_BRIDGEDETAIL_H_
#define LIBHUE_BRIDGEDETAIL_H_

#include <QtCore>
#include <QtXml>

class BridgeDetail {
public:
	BridgeDetail();
	virtual ~BridgeDetail();

	bool parse(QIODevice&);

private:

};

#endif /* LIBHUE_BRIDGEDETAIL_H_ */
