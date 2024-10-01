#include "../../header/emul/Processor.h"

Processor::Processor(uint32_t pc) : pc(pc) {}

Processor::Processor() : Processor(0) {}