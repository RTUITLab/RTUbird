var io = require('socket.io').listen(1080); 
// Отключаем вывод полного лога - пригодится в production'е
io.set('log level', 1);
// Навешиваем обработчик на подключение нового клиента
var id_ue = "";
var id_cl0 = "";
var id_cl1 = "";
io.sockets.on('connection', function (socket) { 
	if(id_ue ==""){
		var ID = (socket.id).toString().substr(0, 5);
		id_ue = ID;
		console.log("подключился анрил" + " " + id_ue);
	}
	else if(id_cl0 ==""){
		var ID = (socket.id).toString().substr(0, 5);
		id_cl0 = ID;
		console.log("подключился клиент 0" + " " + id_cl0);	
	}
		else if(id_cl1 ==""){
		var ID = (socket.id).toString().substr(0, 5);
		id_cl1 = ID;
		console.log("подключился клиент 1" + " " + id_cl1);	
		}
	
	// Навешиваем обработчик на входящее сообщение
	socket.on('message', function (msg) {
		// Отсылаем сообщение остальным участникам чата
		console.log("высылаю" + " " + msg);
		
	});
	// При отключении клиента - уведомляем остальных
	socket.on('disconnect', function() {
		var time = (new Date).toLocaleTimeString();
		if(ID == id_ue){
		console.log("отключение анрила" + " " + ID);
        id_ue = "";		
		}
		if(ID == id_cl0){
		console.log("отключение клиента 0" + " " + ID);
        id_cl0 = "";
        msg="2;0";
        socket.broadcast.json.send({msg});	
		}
		if(ID == id_cl1){
		console.log("отключение клиента 1" + " " + ID);
        id_cl1 = "";
		msg="2;1";
        socket.broadcast.json.send({msg});			
		}
	});
});


