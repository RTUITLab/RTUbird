const fs = require('fs');

const staticHandler = (req, res) => {
    let filePath = __dirname + '/' + (process.env.STATIC_LOCATION || 'static') + req.url;

    if (req.url === '/') {
        filePath += 'index.html';
    }

    try {
        fs.accessSync(filePath, fs.constants.R_OK);
        if(fs.lstatSync(filePath).isDirectory()){
            res.statusCode = 404;
            res.end("Resourse not found!");
        }
        else{
            fs.createReadStream(filePath).pipe(res);
        }
    } catch (e) {
        console.log(e);
        res.statusCode = 404;
        res.end("Resourse not found!");
    }
};

module.exports = staticHandler;
