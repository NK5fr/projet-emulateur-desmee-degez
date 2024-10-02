#include "../../header/emul/rivemul.h"

#define DEFAULT_MEMORY_SIZE 512;
#define DEFAULT_RESET_ADDR 0x0;

int main(int argc, char *argv[]) {

    if(argc < 2){
        printError();
        return 1;
    }

    int opt;
    int resetAddr = DEFAULT_RESET_ADDR;
    int memSize = DEFAULT_MEMORY_SIZE; 
    bool interactiveMode = false;

    struct option long_options[] = {
        {"help", 0, nullptr, 1},
        {"version", 0, nullptr, 'V'}
    };
    while ((opt = getopt_long(argc, argv, "r:im:hV", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'r':
                resetAddr = stoi(optarg, 0);
                break;
            case 'i':
                interactiveMode = true;
                break;
            case 'm':
                memSize = stoi(optarg);
                break;
            case 'h':
                printHelp();
                return 0;
            case 1:
                printDetailedHelp();
                return 0;
            case 'V':
                printVersion();
                return 0;
            default:
                printError();
                return 1;
        }
    }

    /*
    try{
        IEncodingInstruction instruction(0xf6405093, "OP-IMM");
        cout << instruction.getName() << endl;
    } catch (const invalid_argument& ia) {
        cout << ia.what() << endl;
    }
    */

    Processor processor(resetAddr, memSize, argv[optind]);
    if(interactiveMode){
        processor.runStepByStep();
    }else{
        processor.runContinuous();
    }

    return 0; 
}

void printHelp(){
    cout << "Rivemul is a terminal simple emulator of the RISC-V RV32I architecture" << endl;
    cout << "\nUsage: rivemul [OPTIONS] [MEMORY_SEGMENT]..." << endl;
    cout << "\nArguments:" << endl;
    cout << "   [MEMORY_SEGMENT]...   The files to load into memory. Format is file:base_addr.  If :base_addr is not provided, defaults to 0. The files and their base_addr must fit somewhere in the two memory banks" << endl;
    cout << "\nOptions:" << endl;
    cout << "   -r <RESET_ADDR>       The reset address [default: 0x0]" << endl;
    cout << "   -i                    Interactive (debug) mode" << endl;
    cout << "   -m <MEM_SIZE>         Memory size (in KB). This memory size will be split in 2 memory banks: [default: 512]" << endl;
    cout << "   -h, --help            Print help (see more with '--help')" << endl;
    cout << "   -V, --version         Print version" << endl;
}

void printDetailedHelp(){
    cout << "Rivemul is a terminal simple emulator of the RISC-V RV32I architecture" << endl;
    cout << "\nUsage: rivemul [OPTIONS] [MEMORY_SEGMENT]..." << endl;
    cout << "\nArguments:" << endl;
    cout << "   [MEMORY_SEGMENT]..." << endl;
    cout << "           The files to load into memory. Format is file:base_addr.  If :base_addr is not provided, defaults to 0. The files and their base_addr must fit somewhere in the two memory banks" << endl;
    cout << "\nOptions:" << endl;
    cout << "   -r <RESET_ADDR>" << endl;
    cout << "           The reset address" << endl;
    cout << "\n           [default: 0x0]" << endl;
    cout << "\n   -i" << endl;
    cout << "           Interactive (debug) mode" << endl;
    cout << "\n   -m <MEM_SIZE>" << endl;
    cout << "           Memory size (in KB). This memory size will be split in 2 memory banks:" << endl;
    cout << "\n           - one starting at address 0x00000000, half of the given size" << endl;
    cout << "\n           - one starting at address 0x20000000, half of the give size" << endl;
    cout << "\n           [default: 512]" << endl;
    cout << "\n   -h, --help" << endl;
    cout << "           Print help (see a summary with '-h')" << endl;
    cout << "\n   -V, --version" << endl;
    cout << "           Print version" << endl;
}

void printError(){
    cout << "rivemul [OPTIONS] [MEMORY_SEGMENT]..." << endl;
    cout << "For more information, try 'rivemul --help'." << endl;
}

void printVersion(){
    cout << "rivemul 0.1" << endl;
}