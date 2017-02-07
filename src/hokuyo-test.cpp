#include "urg_cpp/Urg_driver.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[]) {
    qrk::Urg_driver urg;

    if (!urg.open(argv[1], 115200)) {
        std::cerr << urg.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (!urg.set_scanning_parameter(urg.deg2step(-60), urg.deg2step(60), 0)) {
        std::cerr << urg.what() << std::endl;
    }

    if (!urg.start_measurement(qrk::Urg_driver::Distance, 1, 0)) {
        std::cerr << urg.what() << std::endl;
    }

    std::vector<long> myMeasurement;
    long time_stamp = 0;

    if (!urg.get_distance(myMeasurement, &time_stamp)) {
        std::cerr << urg.what() << std::endl;
    }

    urg.stop_measurement();

    urg.close();
}
