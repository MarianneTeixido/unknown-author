// Local network

m = NetAddr("127.0.0.1", 5612)

// Aeforia example

m.sendMsg("/aeforia", "draw");
m.sendMsg("/aeforia", "clear");
m.sendMsg("/aeforia", "setTransition", 10000, 0, 1, 1, 2, 2, 0);
m.sendMsg("/aeforia", "setTransition", 25000, 1, 0, 2, 1, 0, 2);
m.sendMsg("/aeforia", "opacity", 5000, 0, 200);
m.sendMsg("/aeforia", "opacity", 2000, 255, 0);
m.sendMsg("/aeforia", "scale", 4);


// Aitana example

m.sendMsg("/aitana", "draw");
m.sendMsg("/aitana", "clear");
m.sendMsg("/aitana", "setTransition", 10000, 0, 1, 1, 2, 2, 0);
m.sendMsg("/aitana", "setTransition", 20000, 1, 0, 2, 1, 0, 2);
m.sendMsg("/aitana", "opacity", 10000, 0, 255);
m.sendMsg("/aitana", "opacity", 10000, 255, 0);
m.sendMsg("/aitana", "scale", 1);


// Catelloo example

m.sendMsg("/catelloo", "draw");
m.sendMsg("/catelloo", "clear");
m.sendMsg("/catelloo", "setTransition", 10000, 0, 1, 1, 2, 2, 0);
m.sendMsg("/catelloo", "setTransition", 20000, 1, 0, 2, 1, 0, 2);
m.sendMsg("/catelloo", "opacity", 10000, 0, 255);
m.sendMsg("/catelloo", "opacity", 10000, 255, 0);
m.sendMsg("/catelloo", "scale", 1);

// Audio Sonification

p = ProxySpace.push(s.boot);
p.makeTempoClock(1);
p.quant = 0;

~outS = {DelayC.ar(~out.ar*1, 0.01, 0.0006*0.75) * EnvFollow.ar(~out.ar*1, 1 - (0.0006 * SampleRate.ir).reciprocal).max(0.174377).reciprocal *0.45!2}; // para las otras rolas está a 0.2
~outD = {GVerb.ar(BPF.ar(~out, Array.geom(8, 50, 1.5), 1/4).sum, 120, 5.85, 0.41, 0.19, 15, -3.dbamp, -5.dbamp, -5.dbamp, 120, 1) * 0.5}
~outM = {Limiter.ar(~outS + ~outD)};
~outM.play;
~outM.stop

x = CSVFileReader.read("~/of_v0.10.1_linux64gcc6_release/apps/myApps/unknown-author-/bin/data/txt/aeforia.txt".standardizePath, true, true).postcs;

a = Array.fill(400, { arg i; x[i][0].split($ ) });
b = Array.fill(400, { arg i; x[i][1].split($ ) });
c = Array.fill(400, { arg i; x[i][2].split($ ) });
d = Array.fill(400, { arg i; x[i][3].split($ ) });
e = Array.fill(400, { arg i; x[i][4].split($ ) });
f = Array.fill(400, { arg i; x[i][5].split($ ) });
g = Array.fill(400, { arg i; x[i][6].split($ ) });
h = Array.fill(400, { arg i; x[i][7].split($ ) });

// Sound


Tdef(\x, { loop { m.sendMsg("/aeforia", "opacity", 8000, 20, 200); 8.wait; m.sendMsg("/aeforia", "opacity", 8000, 200, 20); 8.wait;} }); // oldSchool Live Coding

Tdef(\y, { loop { m.sendMsg("/aitana", "opacity", 4000, 200, 20); 8.wait; m.sendMsg("/aitana", "opacity", 4000, 20, 200); 8.wait;} }); // oldSchool Live Coding

Tdef(\x).stop;
Tdef(\x).play;

Tdef(\y).play;

~pmX = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(a.flatten.asInteger, inf)) * [1, 1.01], 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(b.flatten.asInteger*2, inf))* [1, 1.01], 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([0.1, 1, 14, 0.1], inf)), 32),0,0.125/4))};

~pmY = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(c.flatten.asInteger, inf)) * [1, 1.02], 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(d.flatten.asInteger, inf))* [1, 1.02], 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([0.1, 1, 14, 0.1], inf)), 8),0,0.125/4))};

~pmZ = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(e.flatten.asInteger, inf))* [1, 1.03], 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(f.flatten.asInteger, inf))* [1, 1.03], 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([0.1, 1, 14, 0.1], inf)), 8),0,0.125/4))};

~pm4 = {Pan2.ar(PMOsc.ar(Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(g.flatten.asInteger, inf))* [1, 1.04], 0),Lag.kr(Demand.kr(Impulse.kr(~tempo*0.125), 0, Dseq(h.flatten.asInteger, inf))* [1, 1.04], 0), Lag.kr(Demand.kr(Impulse.kr(~tempo*0.5), 0, Dseq([0.1, 1, 14, 0.1], inf)), 8),0,0.125/4))};

~out = (~pmX + ~pmY + ~pmZ + ~pm4) * 2
~out.play
s.meter

~pmX.play;
~pmY.play;
~pmZ.play;
~pm4.play;

~pmX.stop;
~pmY.stop;
~pmZ.stop;

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