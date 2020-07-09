var express = require('express');
var app = express();
var path = require('path');

var http = require('http').createServer(app);
var io = require('socket.io')(http);

const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')
const port = new SerialPort("/dev/cu.usbmodemHIDF1", {
  baudRate: 115200
})

const parser = new Readline()
port.pipe(parser)

// parser.on('data', line => console.log(`> ${line}`))
parser.on('data', function(line){
  console.log(line);
});


const PORT = process.env.PORT || 5000

app.use(express.static(path.join(__dirname, '/public')));

app.get('/', function(req, res) {
  res.sendFile(path.join(__dirname, '/public/index.html'));
});

http.listen(PORT, () => console.log(`Listening on ${ PORT }`));

//socket.io
// io.on('connection', function(socket) {
//   socket.on('createEvents', function(data) {
//     console.log("fdsa");
//     socket.broadcast.emit('createEventsBroadcast', {
//       eventdata: data.eventdata,
//       startTime: data.startTime
//     });
//   });
//     socket.on('startpiece', function(data) {
//       socket.broadcast.emit('startpiecebroadcast', {});
//     });
// });
