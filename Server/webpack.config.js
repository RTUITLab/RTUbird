const path = require('path');

module.exports = {
  entry: './server.js',
  target: 'node',
  output: {
    filename: 'main.js',
    path: path.resolve(__dirname, 'deploy'),
  },
  mode: 'production'
};