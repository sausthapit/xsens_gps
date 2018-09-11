

#include<iostream>
#include<conio.h>
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
	
	
	for (XsPortInfoArray::const_iterator portInfoIter = portInfoArray.begin(); portInfoIter != portInfoArray.end(); ++portInfoIter){
		++deviceCounter;
		if (!control->openPort(portInfoIter->portName(), portInfoIter->baudrate())){
			throw runtime_error("Error opening port "+ portInfoIter->portName().toStdString());
		}
		XsPortInfo const portInfo = *portInfoIter;
		XsDevice* detectedDevice = control->device(portInfoIter->deviceId());
		gpsDevices.insert(DeviceInfo::value_type(detectedDevice,  &portInfo));
		DeviceContainer dc = DeviceContainer(detectedDevice, &portInfo,10);
		gpsList.push_back(&dc);
		cout << "All the devices detected are configured" << endl;
	}
	for (itr = gpsList.begin(); itr != gpsList.end(); itr++) {
		(*itr)->gotoMeasurement();
	}
	for (itr = gpsList.begin(); itr != gpsList.end(); itr++) {
		
		//while (!_kbhit())
		//{
		//	if ((*itr)->m_device->packetAvailable())
		//	{
		//		int64_t stamp = std::chrono::duration_cast<std::chrono::duration<int64_t, std::micro>>(std::chrono::steady_clock::now().time_since_epoch()).count();
		//		// Retrieve a packet
		//		XsDataPacket packet = callback.getNextPacket();

		//		// Get the quaternion data
		//		XsQuaternion quaternion = packet.orientationQuaternion();
		//		XsCalibratedData cal = packet.calibratedData();
		//		XsVector gps = packet.positionLLA();
		//	}
		//}
	}
	/*for (DeviceContainer *gps : gpsList) {
		gps->gotoMeasurement();

	}*/
	
	cout << "Press [ENTER] to continue." << std::endl; std::cin.get();
	return 0;
}