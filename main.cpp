#include "sound_processor/convertion_manager.h"

int main(int argc, char* argv[]) {
    TConvertionManager ConvertionManager(argc, argv);
    ConvertionManager.ConvertByConfig();

    return 0;
}