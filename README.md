System Dependencies
-------------------

- [libpuzzle](http://www.pureftpd.org/project/libpuzzle)
- [libgd](http://www.boutell.com/gd/)

Installation
------------

	$ npm install puzzle

then...

	var puzzle = require('puzzle');
	var context = puzzle.context();	// create a context
	var distance = context.compare('./test/img/1.jpg', './test/img/2.jpg');	// compare two images

`distance` will be 0 if the images are equal, the larger the number, the more "different" the images are.
Generally, a number below .6 means they are considered similar.  See the official libpuzzle docs for details.

Build and Test
--------------

node-gyp clean configure build && node test/test.js

More
----

This is very raw.  It exposes exactly one method, there is a lot more to do.  Contributions welcome.