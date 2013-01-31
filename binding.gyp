{
	"targets": [
		{
			"target_name": "puzzle",
			"sources": [ "puzzle.cc" ],
			"link_settings": {
				"libraries": [
					"/opt/local/lib/libgd.dylib",
					"/opt/local/lib/libpuzzle.dylib"
				],
			},
		}
	]
}
