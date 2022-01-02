const gulp = require('gulp');
const eslint = require('gulp-eslint');

const glob = [
    'gulpfile.js',
    '.eslintrc.js',
    'gulp/**/*.js',
    'src/**/*.js',
];

module.exports = function() {
    return gulp.src(glob)
        .pipe(eslint())
        .pipe(eslint.format())
        .pipe(eslint.failAfterError());
};
