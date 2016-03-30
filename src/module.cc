#include <nan.h>
#include <node_buffer.h>

#include "crc.h"

namespace crcAsync {

NAN_MODULE_INIT(Init) {
    InitCrcTable();

    Nan::Export(target, "computeCrc", ComputeCrc);
    Nan::Export(target, "updateCrc", UpdateCrc);
    Nan::Export(target, "preCondition", PreCondition);
    Nan::Export(target, "postCondition", PostCondition);
}

NODE_MODULE(crcAsync, Init);

}
