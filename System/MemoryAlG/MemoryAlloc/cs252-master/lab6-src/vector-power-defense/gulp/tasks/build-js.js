const gulp = require('gulp');
const browserify = require('browserify');
const source = require('vinyl-source-stream');

module.exports = function() {
    return browserify('./src/client/js/app.js')
        .bundle()
        .pipe(source('bundle.js'))
        .pipe(gulp.dest('./public/'));
};
