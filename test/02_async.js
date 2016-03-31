var chai = require('chai');
var expect = chai.expect;

var m = require('../')

var TEST_BUFFER = new Buffer('crc-async test buffer', 'utf8');
var TEST_CRC = 0x73A16EED;
var NOP = function noOp() {};

describe('async methods', function() {
  context('crc()', function() {
    it('should throw when missing arguments', function() {
      expect(function() {m.crc()}).to.throw(/Missing/);
      expect(function() {m.crc(TEST_BUFFER)}).to.throw(/Missing/);
      expect(function() {m.crc(TEST_BUFFER, NOP)}).not.to.throw();
    });

    it('should throw when the first arg is not a buffer', function() {
      expect(function() {m.crc(0, NOP)}).to.throw(/buffer/);
      expect(function() {m.crc(new Object, NOP)}).to.throw(/buffer/);
      expect(function() {m.crc(TEST_BUFFER, NOP)}).not.to.throw();
    });

    it('should throw when the last arg is not a callback', function() {
      expect(function() {m.crc(TEST_BUFFER, 0)}).to.throw(/callback/);
      expect(function() {m.crc(TEST_BUFFER, true)}).to.throw(/callback/);
      expect(function() {m.crc(TEST_BUFFER, NOP)}).not.to.throw();
    });

    it('should throw when the crc argument is not a number', function() {
      expect(function() {m.crc(TEST_BUFFER, null, NOP)}).to.throw(/number/);
      expect(function() {m.crc(TEST_BUFFER, 0, NOP)}).not.to.throw();
    });

    it('should return undefined', function() {
      expect(m.crc(TEST_BUFFER, NOP)).to.be.undefined;
    });

    it('should call the callback', function(done) {
      function callback() { done() }
      m.crc(TEST_BUFFER, callback);
    });

    it('should callback with (null, number)', function(done) {
      function callback(err, crc) {
        expect(err).to.be.null;
        expect(crc).to.be.a('number');
        done();
      }

      m.crc(TEST_BUFFER, callback);
    });

    context('when "crc" is supplied', function() {
      it('should not perform any conditioning', function(done) {
        function callback(err, crc) {
          expect(crc).not.to.equal(TEST_CRC);
          expect(m.postCondition(crc)).to.equal(TEST_CRC);
          done();
        }

        m.crc(TEST_BUFFER, m.preCondition(), callback);
      })
    });

    context('when "crc" is not supplied', function() {
      it('should automatically perform pre- and post-conditioning', function(done) {
        function callback(err, crc) {
          expect(crc).to.equal(TEST_CRC);
          done();
        }

        m.crc(TEST_BUFFER, callback);
      });
    });
  })
})
