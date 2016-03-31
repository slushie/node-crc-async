# crc-async

Perform CRC calculations asynchronously

## Introduction

This module implements the CRC-32 function as a C++ addon for node.js.
It is designed for speed and provides both synchronous and asynchronous
methods to compute the CRC.

## Example

```js
var crcAsync = require('crc-async');
var data = new Buffer(...);

// callback-based API: one-off

crcAsync.crc(data, function(err, crc) {
  console.log('CRC-32: 0x%s', crc.toString(16));
});

// callback-based API: iterative

var initial = crcAsync.preCondition();

crcAsync.crc(chunk, initial, function(err, crc) {
  crc = crcAsync.postCondition(crc);
  console.log('CRC-32: 0x%s', crc.toString(16));
});

// one-off computation

var crc = crcAsync.computeCrc(data);
console.log('CRC-32: 0x%s', crc.toString(16));

// iterative computation

var crc = crcAsync.preCondition();
crc = crcAsync.updateCrc(crc, chunk1);
crc = crcAsync.updateCrc(crc, chunk2);
crc = crcAsync.updateCrc(crc, chunk3);
// etc...

```

## Implementation

CRC-32 is used predominantly in `.zip` files; its use has been superseded by
the CRC-32C algorithm in new applications. However, the ZIP format is a rather
old application and must continue to use the CRC-32 algorithm.

This module provides the classic CRC-32 algorithm, as well as some helper
methods to facilitate `.zip` file generation.

Notably, the ZIP specification calls for pre- and post-conditioning of the 
CRC register. The initial value for CRC computations should be all ones and
the final value should be the one's complement of the CRC-32 output.

This module performs pre- and post-conditioning of the CRC values automatically
within the `computeCrc()` method and when calling `crc()` without an initial 
value. However, methods designed to be used iteratively cannot automatically 
perform these operations. It is necessary to call `preCondition()` to retrieve 
the initial value and `postCondition(output)` to retrieve the final value.

## Acknowledgements 

The CRC-32 routines are taken directly from the [7-Zip SDK](http://www.7-zip.org/sdk.html).

The ZIP format is documented in [the ZIP APPNOTE](https://pkware.cachefly.net/webdocs/casestudies/APPNOTE.TXT).

## License

`crc-async` is Copyright 2016 Josh Leder.

This software is released under the MIT License. See the `LICENSE` file for the 
complete text of the license.
