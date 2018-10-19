

#include<iostream>
#include<conio.h>
#include <chrono>
using namespace std;
#include <xsensdeviceapi.h> // The Xsens device API header
//#include "xsdevicedetector.h"
#include<map>
#include "Config.h"
#include "DeviceContainer.h"
typedef std::map<XsDevice *, XsPortInfo const *> DeviceInfo;
typedef DeviceInfo::iterator DeviceInfoIterator;

typedef vector<DeviceContainer*> ListOfGPS;
typedef ListOfGPS::iterator GPSIterator;

int main(int argc, char** argv)
{
	DeviceInfo gpsDevices;
	ListOfGPS gpsList;
	GPSIterator itr;
	DeviceInfoIterator pos;
	cout << "Application for testing GPS. " << "Version:" << VERSION_MAJOR << "." << VERSION_MINOR << endl;
	XsControl* control;
	control = XsControl::construct();
	assert(control != 0);
	cout << "XsControl object constructed" << std::endl;
	// Scan for connected devices
	std::cout << "Scanning for devices..." << std::endl;
	XsPortInfoArray portInfoArray = XsScanner::scanPorts();
	size_t deviceCounter = 0;
	
	XsDevice* detectedDevice;
	for (XsPortInfoArray::const_iterator portInfoIter = portInfoArray.begin(); portInfoIter != portInfoArray.end(); ++portInfoIter) {
		++deviceCounter;
		if (!control->openPort(portInfoIter->portName(), portInfoIter->baudrate())) {
			throw runtime_error("Error opening port " + portInfoIter->portName().toStdString());
		}
		XsPortInfo const portInfo = *portInfoIter;
		detectedDevice = control->device(portInfoIter->deviceId());
		gpsDevices.insert(DeviceInfo::value_type(detectedDevice, &portInfo));
		DeviceContainer dc = DeviceContainer(detectedDevice, &portInfo, 10);
		gpsList.push_back(&dc);
		cout << "All the devices detected are configured" << endl;
	}
	XsString fName = "gps.txt";
	XsFile f;
	
	f.createText(fName,TRUE);

	for (itr = gpsList.begin(); itr != gpsList.end(); itr++) {
		XsDeviceCallbackHandler m_CallBackHandler(5);
		(*itr)->addCallback();
		(*itr)->gotoMeasurement();

		cout << "Device set for measurement." << endl;
	}
	//XsDeviceCallbackHandler m_CallBackHandler(5);
	//detectedDevice->addCallbackHandler(&m_CallBackHandler);
	//detectedDevice->gotoMeasurement();

	//while (!_kbhit())
	//{
	//	if (m_CallBackHandler.numberOfPacketsInBuffer() > 0)
	//	{
	//		//int64_t stamp = std::chrono::duration_cast<std::chrono::duration<int64_t, std::micro>>(std::chrono::steady_clock::now().time_since_epoch()).count();
	//		// Retrieve a packet
	//		XsDataPacket packet = m_CallBackHandler.popOldestPacket();

	//		// Get the quaternion data
	//		XsQuaternion quaternion = packet.orientationQuaternion();
	//		XsCalibratedData cal = packet.calibratedData();
	//		XsVector gps = packet.positionLLA();
	//		cout << gps[0] << "," << gps[1] << "," << gps[2] << ";" << std::endl;
	//	}
	//}


	for (itr = gpsList.begin(); itr != gpsList.end(); itr++) {
		
		while (!_kbhit())
		{
			if ((*itr)->packetAvailable())
			{
			//	int64_t stamp = std::chrono::duration_cast<std::chrono::duration<int64_t, std::micro>>(std::chrono::steady_clock::now().time_since_epoch()).count();
				// Retrieve a packet
				XsDataPacket packet = (*itr)->popOldestPacket();

				// Get the quaternion data
				XsQuaternion quaternion = packet.orientationQuaternion();
				XsCalibratedData cal = packet.calibratedData();
				XsVector gps = packet.positionLLA();
				cout << gps[0] << "," << gps[1] << "," << gps[2] << ";" << std::endl;
			}
		}
	}
	/*for (DeviceContainer *gps : gpsList) {
		gps->gotoMeasurement();

	}*/

	cout << "Press [ENTER] to continue." << std::endl; std::cin.get();
	return 0;
}