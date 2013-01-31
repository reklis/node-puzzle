var puzzle = require('../build/Release/puzzle');


var P = new puzzle.PuzzleContextWrapper();

var distance = P.compare('./img/1.jpg', './img/2.jpg');

console.log(distance);