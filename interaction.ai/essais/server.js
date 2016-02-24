var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

app.get('/snap.svg-min.js', function(req, res){
  res.sendFile(__dirname + '/libs/snap.svg-min.js');
});

app.get('/vis.js', function(req, res){
  res.sendFile(__dirname + '/libs/vis.js');
});

app.get('/vis.css', function(req, res){
  res.sendFile(__dirname + '/style/vis.css');
});

app.get('/animation_test.svg', function(req, res){
  res.sendFile(__dirname + '/animation_test.svg');
});

app.get('/circle.png', function(req, res){
  res.sendFile(__dirname + '/assets/graphics/circle.png');
});

app.get('/triangle.png', function(req, res){
  res.sendFile(__dirname + '/assets/graphics/triangle.png');
});

app.get('/triangle3d.png', function(req, res){
  res.sendFile(__dirname + '/assets/graphics/triangle3d.png');
});

io.on('connection', function(socket){
  socket.on('graphUDR', function(msg){
	console.log('Graph update requested');
//    io.emit('graphUD', fs.readFileSync('graph.DOT', 'utf8'));
  });
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
