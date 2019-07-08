#include <thread>

#include "camera_cap.h"
#include "utility.h"

int main(int argc, char const *argv[])
{
    if(UserInput(argc, argv) == "crop"){
        CamCap *cap = new CamCap(CamCap::kCapCrop);
        std::thread thrd(&CamCap::run, cap);
        thrd.join();
    }
    return 0;
}
