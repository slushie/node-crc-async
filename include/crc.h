#include <nan.h>

namespace crcAsync {

void InitCrcTable();

// function(buffer) -> number
NAN_METHOD(ComputeCrc);
// function(buffer, crc) -> number
NAN_METHOD(UpdateCrc);

// function() -> number
NAN_METHOD(PreCondition);
// function(crc) -> number
NAN_METHOD(PostCondition);

}
