var puzzle = require('../build/Release/puzzle');


var P = new puzzle.PuzzleContextWrapper();

var distance = P.compare('./test/img/1.jpg', './test/img/2.jpg');

console.log(distance);