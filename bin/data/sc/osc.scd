// Local network

m = NetAddr("127.0.0.1", 5612)

// Aeforia example

m.sendMsg("/aeforia", "draw");
m.sendMsg("/aeforia", "clear");
m.sendMsg("/aeforia", "setPosition", 10000, 0, 1, 1, 2, 2, 0);
m.sendMsg("/aeforia", "setPosition", 25000, 1, 0, 2, 1, 0, 2);
m.sendMsg("/aeforia", "opacity", 200);

// Aitana example

m.sendMsg("/aitana", "draw");
m.sendMsg("/aitana", "clear");
m.sendMsg("/aitana", "setPosition", 10000, 0, 1, 1, 2, 2, 0);
m.sendMsg("/aitana", "setPosition", 20000, 1, 0, 2, 1, 0, 2);
m.sendMsg("/aitana", "opacity", 200);

// Aitana example

m.sendMsg("/catelloo", "draw");
m.sendMsg("/catelloo", "clear");
m.sendMsg("/catelloo", "setPosition", 10000, 0, 1, 1, 2, 2, 0);
m.sendMsg("/catelloo", "setPosition", 20000, 1, 0, 2, 1, 0, 2);
m.sendMsg("/catelloo", "opacity", 100);

// Audio Sonification

p = ProxySpace.push(s.boot);
p.makeTempoClock(1);
p.quant = 0;

x = CSVFileReader.read("~/of_v0.10.1_linux64gcc6_release/apps/myApps/unknown-author-/bin/data/txt/aeforia.txt".standardizePath, true, true).postcs;

a = Array.fill(400, { arg i; x[i][0].split($ ) });
b = Array.fill(400, { arg i; x[i][1].split($ ) });
c = Array.fill(400, { arg i; x[i][2].split($ ) });
d = Array.fill(400, { arg i; x[i][3].split($ ) });
e = Array.fill(400, { arg i; x[i][4].split($ ) });
f = Array.fill(400, { arg i; x[i][5].split($ ) });

~pmX = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(a.flatten.asInteger, inf)), 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(b.flatten.asInteger, inf)), 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([-1, 10, 2, -1], inf)), 8),0,0.25))};

~pmY = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(c.flatten.asInteger, inf)), 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(d.flatten.asInteger, inf)), 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([-1, 12, 4, -1], inf)), 8),0,0.25))};

~pmZ = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(e.flatten.asInteger, inf)), 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(f.flatten.asInteger, inf)), 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([-1, 10, 2, -1], inf)), 8),0,0.25))};

~pmX.play
~pmY.play
~pmZ.play

~pmX.stop
~pmY.stop
~pmZ.stop

s.meter

~sinY.play
~sinX.play
~sinZ.play

s.meter


// Test Database

(
var f, g;
f = File("~/of_v0.10.1_linux64gcc6_release/apps/myApps/unknown-author-/bin/data/txt/aeforia.txt".standardizePath,"w"); // OF Directory
400.do({arg item, i; f.write(400.rand.asString++","++400.rand.asString++","++400.rand.asString++","++400.rand.asString++","++400.rand.asString++","++400.rand.asString++","++400.rand.asString++","++400.rand.asString++","++" \n")});
f.close;
)