var io = require('socket.io').listen(1080); 
// Отключаем вывод полного лога - пригодится в production'е
io.set('log level', 1);
// Навешиваем обработчик на подключение нового клиента
io.sockets.on('connection', function (socket) { 
	
	var ID = (socket.id).toString().substr(0, 5);
	var time = (new Date).toLocaleTimeString();
	console.log("подключение" + " " + ID);
	
	// Навешиваем обработчик на входящее сообщение
		socket.on('message', function (msg) {
		var time = (new Date).toLocaleTimeString();
		// Отсылаем сообщение остальным участникам чата
		console.log("высылаю" + " " + msg);
		socket.broadcast.json.send({msg})
	});
	// При отключении клиента - уведомляем остальных
	socket.on('disconnect', function() {
		var time = (new Date).toLocaleTimeString();
		console.log("отключение" + " " + ID);
		io.sockets.json.send({'event': 'userSplit', 'name': ID, 'time': time});
	});
});