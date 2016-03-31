#include "crc.h"
#include "7zCrc.h"

#include <cmath>

namespace crcAsync {

void InitCrcTable() {
    CrcGenerateTable();
}

NAN_METHOD(ComputeCrc) {
    if (info.Length() < 1) {
        Nan::ThrowTypeError("Missing arguments");
        return;
    }

    if (! node::Buffer::HasInstance(info[0])) {
        Nan::ThrowTypeError("First argument must be a buffer");
        return;
    }

    char *data = node::Buffer::Data(info[0]);
    size_t len = node::Buffer::Length(info[0]);
    UInt32 crc = CrcCalc(data, len);

    info.GetReturnValue().Set(crc);
}

NAN_METHOD(UpdateCrc) {
    if (info.Length() < 2) {
        Nan::ThrowTypeError("Missing arguments");
        return;
    }

    if (! node::Buffer::HasInstance(info[0])) {
        Nan::ThrowTypeError("First argument must be a buffer");
        return;
    }

    if (! info[1]->IsNumber()) {
        Nan::ThrowTypeError("Second argument must be a number");
        return;
    }

    char *data = node::Buffer::Data(info[0]);
    size_t len = node::Buffer::Length(info[0]);

    UInt32 previous = std::floor(info[1]->NumberValue());

    UInt32 crc = CrcUpdate(previous, data, len);

    info.GetReturnValue().Set(crc);
}


NAN_METHOD(PreCondition) {
    info.GetReturnValue().Set(CRC_INIT_VAL);
}

NAN_METHOD(PostCondition) {
    if (info.Length() < 1) {
        Nan::ThrowTypeError("Missing arguments");
        return;
    }

    if (! info[0]->IsNumber()) {
        Nan::ThrowTypeError("First argument must be a number");
        return;
    }

    UInt32 value = std::floor(info[0]->NumberValue());

    info.GetReturnValue().Set(CRC_GET_DIGEST(value));
}
}
