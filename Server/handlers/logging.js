const fs = require('fs');

const logging = (req, res) => {
    console.log(`[${new Date().toISOString()}] ${req.method} ${req.url} [${res.statusCode}]`);
};

module.exports = logging;
