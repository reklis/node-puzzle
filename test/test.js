// yeah yeah, I know I should be using a framework...

var assert = require('assert');

var puzzle = require('../build/Release/puzzle');

var P = new puzzle.PuzzleContextWrapper();

var distance = P.compare('./test/img/1.jpg', './test/img/2.jpg');

console.log(distance);

assert.ok(0 < distance);
assert.ok(1 > distance);

var didthrow = false;

try {
	var shouldthrow = P.compare();
} catch (err) {
	assert.ok(null !== err);
	didthrow = true;
}

assert.ok(didthrow);