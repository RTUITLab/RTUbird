require('dotenv').config();
const cors = require('cors');
const ios = require('socket.io-client')

const server = require('http').createServer((req, res) => {
	res.setHeader('Access-Control-Allow-Origin', '*');
	res.setHeader('Access-Control-Request-Method', '*');
	res.setHeader('Access-Control-Allow-Methods', 'OPTIONS, GET');
	res.setHeader('Access-Control-Allow-Headers', '*');
	if ( req.method === 'OPTIONS' ) {
		res.writeHead(200);
		res.end();
		return;
	}
});
const io = require('socket.io')(server, {
	path: "/server",
	serveClient: false
});

const port = 1082;
server.listen(port, () => console.log('server listening on port ' + port));

var id_ue = "";
var id_cl0 = "";
var id_cl1 = "";
let ready = { cl1: false, cl2: false }
var version = "1.0.1";
var token = 0;

const remoteURL = 'https://localhost:1070'

//var ios = require('socket.io-client');

const connection = ios.connect(remoteURL, { path: "/server" })
console.log(connection);
io.on('connect', function (socket) { //обработчик входящих подключений
	connection.send('Death');
	console.log("Test");
	socket.on('message', function (msg) { //обработчик входящих сообщений 
		connection.send(msg);
	});
	socket.on('disconnect', function () { //обработчик дисконекта
		
	});
});


