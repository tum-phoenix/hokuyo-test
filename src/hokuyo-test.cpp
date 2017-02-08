#include "urg_cpp/Urg_driver.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: hokuyo-test <DEVICE_PATH>\n"
                  << "  Example: hokuyo-test /dev/ttyACM0" << std::endl;
        return EXIT_FAILURE;
    }

    qrk::Urg_driver urg;

    if (!urg.open(argv[1], 115200)) {
        std::cerr << urg.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (!urg.set_scanning_parameter(urg.deg2step(-60), urg.deg2step(60), 0)) {
        std::cerr << urg.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (!urg.start_measurement(qrk::Urg_driver::Distance, 1, 0)) {
        std::cerr << urg.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<long> myMeasurement;
    long time_stamp = 0;

    if (!urg.get_distance(myMeasurement, &time_stamp)) {
        std::cerr << urg.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (myMeasurement.size() == 0) {
        std::cerr << "Measurement is empty" << std::endl;
        return EXIT_FAILURE;
    }

    urg.stop_measurement();

    urg.close();

    return EXIT_SUCCESS;
}
