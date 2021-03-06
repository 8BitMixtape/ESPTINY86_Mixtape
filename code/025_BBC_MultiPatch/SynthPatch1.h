

#ifndef SynthPatch1_H
#define SynthPatch1_H
#include "Synth.h"
#include "Modules.h"
//#include "ModuleExternalInput.h"


class SynthPatch1 : public Synth
{
  public:
    ModuleConstant param[8];

    SynthPatch1()
    {
        //Define Node Objects
  ModuleWavetableOsc *moduleWavetableOsc_1 = new ModuleWavetableOsc();

  moduleWavetableOsc_1->frequency_input= &param[0];
  moduleWavetableOsc_1->wavetable_input= &param[1];


  this->last_module = moduleWavetableOsc_1;

    }
};
#endif // SynthPatch1_H    

/* 

This is espnode86 stuff do not edit

--BEGINESPNODEPATCH--
djIuMS4xCm5ldHdvcmsvYWRkLXBhdGNoIHNhZDQgcm9vdApwYXRjaC9vcGVuIHNhZDQKcGF0Y2gvYWRkLW5vZGUgc2FkNCB6bDlzIGVzcG5vZGUvbm9kZWxpc3QgRXNwbm9kZSUyMFBhbGV0dGUKbm9kZS90dXJuLW9uIHpsOXMKcGF0Y2gvYWRkLW5vZGUgc2FkNCB6
M2NoIGlucHV0L211bHRpcGxleGVyIE11bHRpcGxleGVyCm5vZGUvdHVybi1vbiB6M2NoCm5vZGUvYWRkLW91dGxldCB6M2NoIDY0cncgZXNwbm9kZS9zdHJpbmcgUG90MSBQb3QxCm5vZGUvYWRkLW91dGxldCB6M2NoIHI4M2sgZXNwbm9kZS9zdHJpbmcgUG90MiBQ
b3QyCm5vZGUvYWRkLW91dGxldCB6M2NoIGhoZ3MgZXNwbm9kZS9zdHJpbmcgUG90MyBQb3QzCm5vZGUvYWRkLW91dGxldCB6M2NoIGY1czEgZXNwbm9kZS9zdHJpbmcgUG90NCBQb3Q0Cm5vZGUvYWRkLW91dGxldCB6M2NoIDc1M3EgZXNwbm9kZS9zdHJpbmcgUG90
NSBQb3Q1Cm5vZGUvYWRkLW91dGxldCB6M2NoIGtjNmIgZXNwbm9kZS9zdHJpbmcgUG90NiBQb3Q2Cm5vZGUvYWRkLW91dGxldCB6M2NoIGg5MWQgZXNwbm9kZS9zdHJpbmcgUG90NyBQb3Q3Cm5vZGUvYWRkLW91dGxldCB6M2NoIHQzcmEgZXNwbm9kZS9zdHJpbmcg
UG90OCBQb3Q4CnBhdGNoL2FkZC1ub2RlIHNhZDQgOXZoayB3YXZlL29zY2lsbGF0b3IgT3NjaWxsYXRvcgpub2RlL3R1cm4tb24gOXZoawpub2RlL2FkZC1pbmxldCA5dmhrIGJid3MgZXNwbm9kZS9zdHJpbmcgZnJlcXVlbmN5X2lucHV0IGZyZXF1ZW5jeV9pbnB1
dApub2RlL2FkZC1pbmxldCA5dmhrIHJkaWggZXNwbm9kZS9zdHJpbmcgd2F2ZXRhYmxlX2lucHV0IHdhdmV0YWJsZV9pbnB1dApub2RlL2FkZC1vdXRsZXQgOXZoayBwNXRlIGVzcG5vZGUvc3RyaW5nIE91dCBPdXQKcGF0Y2gvYWRkLW5vZGUgc2FkNCBpODg1IG91
dHB1dC9kYWMgQXVkaW8lMjBEQUMKbm9kZS90dXJuLW9uIGk4ODUKbm9kZS9hZGQtaW5sZXQgaTg4NSBqNzFiIGVzcG5vZGUvc3RyaW5nIGF1ZGlvX2lucHV0IGF1ZGlvX2lucHV0Cm5vZGUvbW92ZSB6bDlzIDMwIDIwCm5vZGUvbW92ZSB6M2NoIDMzMiAxNDkKbm9k
ZS9tb3ZlIDl2aGsgNjA4IDEyMQpub2RlL21vdmUgaTg4NSA5MTEgMTI0Cm91dGxldC9jb25uZWN0IDY0cncgYmJ3cyBmc2hqCm91dGxldC9jb25uZWN0IHI4M2sgcmRpaCB1MjZvCm91dGxldC9jb25uZWN0IHA1dGUgajcxYiB6eXdhCm5vZGUvdXBkYXRlLWlubGV0
IDl2aGsgYmJ3cyBmcmVxdWVuY3lfaW5wdXQgMApub2RlL3VwZGF0ZS1pbmxldCA5dmhrIHJkaWggd2F2ZXRhYmxlX2lucHV0IDA=
--ENDESPNODEPATCH--

*/

