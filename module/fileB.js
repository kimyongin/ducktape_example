Duktape.modSearch = function (id) {
	print(id);
    if (id === 'foo') {
        return 'exports.hello = function() { print("Hello from foo!"); };';
    } else if (id === 'bar') {
        return 'exports.hello = function() { print("Hello from bar!"); };';
    } else {
		var res = readFile('../module/' + id + '.js');
		if (typeof res === 'string') {
			return res;
		}
	}
    throw new Error('module not found: ' + id);
};

var modfoo = require('foo');
modfoo.hello();

var modfileA = require('fileA');
modfileA.hello();