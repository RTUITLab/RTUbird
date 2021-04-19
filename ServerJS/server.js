var io = require('socket.io').listen(1080);
io.set('log level', 1);
io.origins('*');
var id_ue = "";
var id_cl0 = "";
var id_cl1 = "";
var version = "1.0.1";
var token = 0;
io.sockets.on('connection', function (socket) { //обработчик входящих подключений
	socket.on('message', function (msg) { //обработчик входящих сообщений 
		

		var ArrayOfData = msg.split(";");
		if (ArrayOfData[0] == "X") { //сообщение анрил подключился
			let ID = (socket.id).toString();
			id_ue = ID;
			console.log("подключился анрил" + " " + id_ue);
			
			if(ArrayOfData[1]!=version)
			{
				console.log("версия проверку не прошла");
				io.sockets.connected[socket.id].disconnect();
			}
			else
			{
				console.log("версия проверку прошла");
			}
			
		}
		if (ArrayOfData[0] == "4") { //пришел хэш-токен для последующей проверки клиента

			token = Number(ArrayOfData[1]);
			console.log("получен токен" + " " + token);
		}
		else if (ArrayOfData[0] == "5") { //хэш-токен от клиента пришел на проверку
			ArrayOfData[1] = ArrayOfData[1].replace(/^#/, '');
			console.log("хэш на проверку пришел" + " " + ArrayOfData[1]);
			if (ArrayOfData[1] != String(token)) {
				socket.send("dis");
				console.log("хэш проверку не прошел");
				io.sockets.connected[socket.id].disconnect();
			}
		}
		else { //бродкаст сообщений через сервер
			var vrem = String(msg);
			console.log("высылаю" + " " + vrem);
			socket.broadcast.emit("message", vrem);
		}


		if (msg == "0") { //подключился клиент, уведомим анрил
			if (id_cl0 == "") {
				let ID = (socket.id).toString();
				id_cl0 = ID;
				socket.send("00");
				console.log("подключился клиент 0" + " " + id_cl0);
			}
			else if (id_cl1 == "") {
				var ID = (socket.id).toString();
				id_cl1 = ID;
				socket.send("01");
				console.log("подключился клиент 1" + " " + id_cl1);
			}
		}

	});
	socket.on('disconnect', function () { //обработчик дисконекта
		let ID = (socket.id).toString();
		if (ID == id_ue) {
			console.log("отключение анрила" + " " + ID);
			id_ue = "";
			token = 0;
		}
		if (ID == id_cl0) {
			console.log("отключение клиента 0" + " " + ID);
			id_cl0 = "";
			socket.broadcast.emit("message", "2;0");
		}
		if (ID == id_cl1) {
			console.log("отключение клиента 1" + " " + ID);
			id_cl1 = "";
			socket.broadcast.emit("message", "2;1");
		}
	});
});


