var libpuzzle = require('./build/Release/puzzle');

exports.context = function () {
	return new libpuzzle.PuzzleContextWrapper();
};