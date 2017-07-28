/*


Emily Lam, November 2016
*/

//var keypress = require('keypress');
var dotenv = require('dotenv').config();
var requestParticle = require('request');
//var Particle = require('particle-api-js');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var host = 'https://api.particle.io/v1/devices/',
    deviceID = process.env.DEVICEID,
    func1 = 'forbackward',
    func2 = 'leftright',
    accessToken = process.env.ACCESSTOKEN;
var urlParticle1 = host + deviceID + '/' + func1 + '?access_token=' + accessToken;
var urlParticle2 = host + deviceID + '/' + func2 + '?access_token=' + accessToken;

app.get('/', function(req, res){
  res.sendFile(__dirname + '/remotesteering.html');
});

io.on('connection', function(socket) {
  console.log('a user connected');
  socket.on('disconnect', function() {
    console.log('user disconnected');
  });
});

io.on('connection', function(socket) {
  socket.on('command', function(msg) {
    console.log('command: ' + msg);
    if (msg == 'forward' || msg == "back") {
      requestParticle(urlParticle1, {method: 'POST', json: {mes: msg}}, callbackParticle);
    }
    else if (msg == "left" || msg == "right") {
      requestParticle(urlParticle2, {method: 'POST', json: {mes: msg}}, callbackParticle);
    }
  });
});

// Callback function to print error if post to Particle Cloud fails
function callbackParticle(error, response, body) {
  if (error) {
    console.log(error);
  }
}

http.listen(3000, function() {
  console.log('listening on *:3000');
});

/*// make `process.stdin` begin emitting "keypress" events
keypress(process.stdin);

// listen for the "keypress" event
process.stdin.on('keypress', function (ch, key) {
  //console.log('got "keypress"', key);
  if (key && key.name == 'up') {
    console.log(key.name);
  }
  else if (key && key.name == 'down') {
    console.log(key.name);
  }
  else if (key && key.name == 'right') {
    console.log(key.name);
  }
  else if (key && key.name == 'left') {
    console.log(key.name);
  }
  else if (key && key.ctrl && key.name == 'c') {
    process.stdin.pause();
  }
});

process.stdin.setRawMode(true);
process.stdin.resume();*/
