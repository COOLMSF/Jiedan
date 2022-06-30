const gulp = require('gulp');

module.exports = function() {
    gulp.src('./src/client/index.html')
        .pipe(gulp.dest('./public'));
};
