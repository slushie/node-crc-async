var chai = require('chai');
var expect = chai.expect;

var m = require('../')

var TEST_BUFFER = new Buffer('crc-async test buffer', 'utf8');
var TEST_CRC = 0x73A16EED;

describe('sync methods', function() {
  context('preCondition()', function() {
    it('should return a number', function() {
      expect(m.preCondition()).to.be.a('number');
    });
  });

  context('postCondition()', function() {
    it('should throw when missing an argument', function() {
      expect(function() {m.postCondition()}).to.throw(/Missing/);
    });

    it('should throw when its arg is not a number', function() {
      expect(function() {m.postCondition('string')}).to.throw(/number/);
      expect(function() {m.postCondition(1)}).not.to.throw();
    });

    it('should return a number', function() {
      expect(m.postCondition(1)).to.be.a('number');
    });

    it('should return the ones complement of the pre-condition', function() {
      var pre = m.preCondition();
      expect(m.postCondition(pre)).to.equal(~pre);
    });
  });

  context('computeCrc()', function() {
    it('should throw when missing an argument', function() {
      expect(function() {m.computeCrc()}).to.throw(/Missing/);
    });

    it('should throw when its arg is not a buffer', function() {
      expect(function() {m.computeCrc('string')}).to.throw(/buffer/);
      expect(function() {m.computeCrc(new Object)}).to.throw(/buffer/);
      expect(function() {m.computeCrc(new Buffer(0))}).not.to.throw();
    });

    it('should return a number', function() {
      expect(m.computeCrc(TEST_BUFFER)).to.be.a('number');
    });

    it('should compute the CRC-32 across a given buffer', function() {
      expect(m.computeCrc(TEST_BUFFER)).to.equal(TEST_CRC);
    });
  });

  context('updateCrc()', function() {
    it('should throw when missing arguments', function() {
      expect(function() {m.updateCrc()}).to.throw(/Missing/);
      expect(function() {m.updateCrc(0)}).to.throw(/Missing/);
      expect(function() {m.updateCrc(TEST_BUFFER, 0)}).not.to.throw();
    });

    it('should throw when the first arg is not a buffer', function() {
      expect(function() {m.updateCrc(0, 0)}).to.throw(/buffer/);
      expect(function() {m.updateCrc(new Object, 0)}).to.throw(/buffer/);
      expect(function() {m.updateCrc(TEST_BUFFER, 0)}).not.to.throw();
    });

    it('should throw when the second arg is not a number', function() {
      expect(function() {m.updateCrc(TEST_BUFFER, 'string')}).to.throw(/number/);
      expect(function() {m.updateCrc(TEST_BUFFER, 0)}).not.to.throw();
    });

    it('should return a number', function() {
      expect(m.updateCrc(TEST_BUFFER, 0)).to.be.a('number');
    });

    it('should compute the CRC-32 iteratively', function() {
      var first = TEST_BUFFER.slice(0, 2),
          second = TEST_BUFFER.slice(2);

      var crc = m.preCondition();
      crc = m.updateCrc(first, crc);
      crc = m.updateCrc(second, crc);

      expect(m.postCondition(crc)).to.equal(TEST_CRC);
    });
  });
})
