#pragma once
#include <xsensdeviceapi.h>
#include <iostream>
#include <list>

class DeviceContainer : public XsCallback
{
private:
	//XsDevice * m_device;
	const XsPortInfo* m_portInfo;
	mutable XsMutex m_mutex;
	size_t m_maxNumberOfPacketsInBuffer;
	size_t m_numberOfPacketsInBuffer;
	std::list<XsDataPacket> m_packetBuffer;
public:
	XsDevice * m_device;
	DeviceContainer(size_t);
	~DeviceContainer();
	DeviceContainer(XsDevice* device, const XsPortInfo* portInfo, size_t);
	void onLiveDataAvailable(XsDevice*, const XsDataPacket* packet);
	XsDataPacket popOldestPacket();
	bool configure();
	bool gotoMeasurement();
};

