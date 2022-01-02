const gulp = require('gulp');
const watch = require('gulp-watch');

const glob = [
    'src/server/**/*.js',
    'src/shared/**/*.js',
];

module.exports = function() {
    return watch(glob, function() {
        gulp.start('serve');
    });
};
