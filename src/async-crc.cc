#include "async-crc.h"

namespace crcAsync {

NAN_METHOD(AsyncCrc) {
    size_t argc = info.Length();
    v8::Local <v8::Object> buffer;
    Nan::Callback *callback;
    UInt32 crc = CRC_INIT_VAL;
    bool post_condition = true;

    if (argc < 2) {
        Nan::ThrowTypeError("Missing arguments");
        return;
    }

    if (! node::Buffer::HasInstance(info[0])) {
        Nan::ThrowTypeError("First argument must be a buffer");
        return;
    }

    if (! info[argc-1]->IsFunction()) {
        Nan::ThrowTypeError("Last argument must be a callback");
        return;
    }

    if (argc > 2) {
        if (! info[1]->IsNumber()) {
            Nan::ThrowTypeError("Second argument must be a number, if supplied");
            return;
        }

        crc = info[1]->NumberValue();
        post_condition = false;
    }

    buffer = info[0]->ToObject();
    callback = new Nan::Callback(info[argc-1].As <v8::Function> ());

    Nan::AsyncQueueWorker(new CrcWorker(callback, buffer, crc, post_condition));

    info.GetReturnValue().SetUndefined();
}

CrcWorker::CrcWorker(Nan::Callback *callback,
                     v8::Local<v8::Object> buffer,
                     UInt32 crc,
                     bool post_condition)
    : AsyncWorker(callback)
    , _data(node::Buffer::Data(buffer))
    , _length(node::Buffer::Length(buffer))
    , _crc(crc)
    , _post_condition(post_condition)
{
    SaveToPersistent("buffer", buffer);
}

void CrcWorker::Execute()
{
    UInt32 crc = CrcUpdate(_crc, _data, _length);

    if (_post_condition) {
        _crc = CRC_GET_DIGEST(crc);
    }
    else {
        _crc = crc;
    }
}

void CrcWorker::HandleOKCallback()
{
    Nan::HandleScope scope;
    v8::Local <v8::Value> args[] = {
        Nan::Null(),
        Nan::New <v8::Number> (_crc)
    };

    callback->Call(2, args);
}

}
