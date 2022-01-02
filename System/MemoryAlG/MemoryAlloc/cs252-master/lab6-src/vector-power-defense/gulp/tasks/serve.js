const gulp = require('gulp');
const spawn = require('child_process').spawn;
let node;

module.exports = function() {
    if (node) node.kill();
    node = spawn('node', ['src/server/index.js'], {stdio: 'inherit'});
    node.on('close', function(code) {
        if (code === 8) {
            gulp.log('Error detected, waiting for changes...');
        }
    });
};
