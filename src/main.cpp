// This code is based on the xda_cpp example provided by xsens.
// Created by saurav on 26/07/18.
//
//Generic
#include <iostream>
#include <iomanip>


// Include files for the xsens api
#include <xsensdeviceapi.h>
#include "xsdevicedetector.h"


//Include files for log4cpp (logger similar to log4j)
#include "log4cpp/Category.hh"
#include "log4cpp/FileAppender.hh"


int main(int argc, char **argv) {

    log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
    appender1->setLayout(new log4cpp::BasicLayout());
    log4cpp::Category &rootLog = log4cpp::Category::getRoot();
    rootLog.setPriority(log4cpp::Priority::WARN);
    rootLog.addAppender(appender1);
    rootLog.info("Log4cpp is initialised");

    // Create XsControl
    XsControl *control = XsControl::construct();
    assert(control != 0);
    rootLog.info("XsControl object is constructed. Scanning ports for available devices");

    // Create device detector
    XsDemo::XsDeviceDetector deviceDetector(*control);

    // Scan for and open devices
    rootLog << log4cpp::Priority::INFO << "Detecting devices...\n" << std::string(79, '-') << "\n";
    if (!deviceDetector.detectAndOpenDevices()) {
        rootLog << log4cpp::Priority::ERROR << "An error occured while detecting devices. Aborting.\n";
//        waitForKeyPress();
        return EXIT_FAILURE;
    }
    if (deviceDetector.detectedDevices().empty()) {
        rootLog << log4cpp::Priority::ERROR << "No devices found. Aborting.\n";
//        waitForKeyPress();
        return EXIT_FAILURE;
    }


}