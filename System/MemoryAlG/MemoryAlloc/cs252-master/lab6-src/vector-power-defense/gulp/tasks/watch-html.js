const gulp = require('gulp');
const watch = require('gulp-watch');

module.exports = function() {
    return watch('src/client/index.html', function() {
        gulp.start('build-html');
    });
};
