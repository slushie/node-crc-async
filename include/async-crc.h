#include <nan.h>

#include "7zCrc.h"

namespace crcAsync {

// function(buffer, cb)
// function(buffer, crc, cb)
// function(buffer, crc, postCondtion, cb)
NAN_METHOD(AsyncCrc);

class CrcWorker : public Nan::AsyncWorker {
public:
    CrcWorker(Nan::Callback *callback,
              v8::Local <v8::Object> buffer,
              UInt32 crc,
              bool post_condition);

    void Execute();
    void HandleOKCallback();

private:
    void *_data;
    size_t _length;
    UInt32 _crc;
    bool _post_condition;
};

}
