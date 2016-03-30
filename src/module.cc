#include <nan.h>
#include <node_buffer.h>

#include <cmath>

#include "7zCrc.h"

namespace crcp {

NAN_METHOD(ComputeCrc) {
    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    char *data = node::Buffer::Data(info[1]);
    size_t len = node::Buffer::Length(info[1]);
    UInt32 crc = CrcCalc(data, len);

    info.GetReturnValue().Set(crc);
}

NAN_METHOD(UpdateCrc) {
    if (info.Length() < 2) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (! info[0]->IsNumber()) {
        Nan::ThrowTypeError("First argument must be a number");
    }

    char *data = node::Buffer::Data(info[1]);
    size_t len = node::Buffer::Length(info[1]);

    UInt32 previous = std::floor(info[0]->NumberValue());

    UInt32 crc = CrcUpdate(previous, data, len);

    info.GetReturnValue().Set(crc);
}


NAN_METHOD(PreCondition) {
    info.GetReturnValue().Set(CRC_INIT_VAL);
}

NAN_METHOD(PostCondition) {
    if (info.Length() < 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (! info[0]->IsNumber()) {
        Nan::ThrowTypeError("First argument must be a number");
    }

    UInt32 value = std::floor(info[0]->NumberValue());

    info.GetReturnValue().Set(CRC_GET_DIGEST(value));
}

NAN_MODULE_INIT(Init) {
    CrcGenerateTable();

    Nan::Export(target, "computeCrc", ComputeCrc);
    Nan::Export(target, "updateCrc", UpdateCrc);
    Nan::Export(target, "preCondition", PreCondition);
    Nan::Export(target, "postCondition", PostCondition);
}

NODE_MODULE(crcp, Init);

}
