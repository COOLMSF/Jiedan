const gulp = require('./gulp')([
    'build-html',
    'build-js',
    'watch-html',
    'watch-js',
    'watch-serve',
    'serve',
    'lint',
    'watch-lint',
]);

gulp.task('build', ['build-html', 'build-js']);
gulp.task('watch', ['watch-html', 'watch-js']);

gulp.task('default', ['build', 'watch', 'serve', 'watch-serve']);
