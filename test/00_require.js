var chai = require('chai');
var expect = chai.expect;

describe('require()', function() {
  it('should not throw errors', function() {
    expect(function() { require('../') }).not.to.throw();
  })
})
