require('dotenv').config();

// Set up HTTP server
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

let connectedWithServer = false;
let connectedWithGame = false;

// Set up WS client
const clientIo = require('socket.io-client');
const client = clientIo.connect(process.env.WS_SERVER, {
	reconnect: true,
	path: '/server'
});

client.on('connect', () => { 
	connectedWithServer = true;
    console.log('Connected to ' + process.env.WS_SERVER);
});

client.on('disconnect', (reason) => {
	connectedWithServer = false;

	console.log('Client disconnected');
	console.log(`Reason: ${reason}`);
});

// Set up WS server
const io = require('socket.io')(server, {
	path: "/server",
	serveClient: false
});

io.on('connect', (socket) => {
	connectedWithGame = true;

	socket.on('message', (msg) => {
		if (connectedWithServer === true) {
			client.send(msg);
		} else {
			console.log(`Can't send message to server. Not connected`);
		}
	});
	socket.on('disconnect', () => {
		console.log('Disconnected from ' + process.env.WS_SERVER);

		connectedWithGame = false;
	});
});

// Run server
const port = process.env.WS_PORT || 1080;
server.listen(port, () => console.log('Server listening on port ' + port));
