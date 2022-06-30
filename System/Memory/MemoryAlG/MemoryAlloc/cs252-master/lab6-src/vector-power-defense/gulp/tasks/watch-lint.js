const gulp = require('gulp');
const watch = require('gulp-watch');

const glob = [
    'gulpfile.js',
    '.eslintrc.js',
    'gulp/**/*.js',
    'src/**/*.js',
];

module.exports = function() {
    return watch(glob, function() {
        gulp.start('lint');
    });
};
