#include <nan.h>

namespace crcAsync {

void InitCrcTable();

// function(buffer) -> number
NAN_METHOD(ComputeCrc);
// function(crc, buffer) -> number
NAN_METHOD(UpdateCrc);

// function() -> number
NAN_METHOD(PreCondition);
// function(crc) -> number
NAN_METHOD(PostCondition);

}
