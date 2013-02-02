var assert = require('assert'); // yeah yeah, I know I should be using a framework...
var puzzle = require('../puzzle');

var context = puzzle.context();
var distance = context.compare('./test/img/1.jpg', './test/img/2.jpg');

console.log(distance);

assert.ok(0 < distance);
assert.ok(1 > distance);

var didthrow = false;

try {
	var shouldthrow = context.compare();
} catch (err) {
	assert.ok(null !== err);
	didthrow = true;
}

assert.ok(didthrow);

console.log('OK');