
#ifndef SYNTHTEST_H
#define SYNTHTEST_H
#include "Synth.h"
#include "Modules.h"
#include "ModuleExternalInput.h"


class SynthTest : public Synth
{
    public:
    ModuleConstant param[8];

    SynthTest(Input_Manager * inputManager)
    {
    
        //Define Node Objects
  ModuleWavetableOsc *moduleWavetableOsc_1 = new ModuleWavetableOsc();
  ModuleLFO *moduleLFO_1 = new ModuleLFO();
  ModuleExternalInput *pot0 = new ModuleExternalInput(0,inputManager);
  ModuleExternalInput *pot1 = new ModuleExternalInput(1,inputManager);
  ModuleExternalInput *touchosc1 = new ModuleExternalInput("/touchosc1",inputManager);
  ModuleExternalInput *touchLED1 = new ModuleExternalInput("/touchLED1",inputManager);
  ModuleExternalInput *touchosc2 = new ModuleExternalInput("/touchosc2",inputManager);
  ModuleExternalInput *touchosc3 = new ModuleExternalInput("/touchosc3",inputManager);
  ModuleExternalInput *touchosc4 = new ModuleExternalInput("/touchosc4",inputManager);

  moduleWavetableOsc_1->frequency_input=moduleLFO_1;
  moduleLFO_1->wavetable_input = pot1;
  moduleWavetableOsc_1->wavetable_input = pot0;
  moduleLFO_1->frequency_input = touchosc1;


  this->last_module = moduleWavetableOsc_1;
        
    }
};
#endif // SYNTHTEST_H    


/* 

This is espnode86 stuff do not edit

--BEGINESPNODEPATCH--
djIuMS4xCm5ldHdvcmsvYWRkLXBhdGNoIHNhZDQgcm9vdApwYXRjaC9vcGVuIHNhZDQKcGF0Y2gvYWRkLW5vZGUgc2FkNCB6MTRjIGVzcG5vZGUvbm9kZWxpc3QgTm9kZSUyMFBhbGxldGUKbm9kZS90dXJuLW9uIHoxNGMKcGF0Y2gvYWRkLW5vZGUgc2FkNCB0YzZ3
IHdhdmUvb3NjaWxsYXRvciBPc2NpbGxhdG9yCm5vZGUvdHVybi1vbiB0YzZ3Cm5vZGUvYWRkLWlubGV0IHRjNncgZGxkdiBlc3Bub2RlL3N0cmluZyBmcmVxdWVuY3lfaW5wdXQgZnJlcXVlbmN5X2lucHV0Cm5vZGUvYWRkLWlubGV0IHRjNncgNHk2dSBlc3Bub2Rl
L3N0cmluZyB3YXZldGFibGVfaW5wdXQgd2F2ZXRhYmxlX2lucHV0Cm5vZGUvYWRkLW91dGxldCB0YzZ3IHo3MW8gZXNwbm9kZS9zdHJpbmcgT3V0IE91dApwYXRjaC9hZGQtbm9kZSBzYWQ0IDd3dG4gb3V0cHV0L2RhYyBBdWRpbyUyMERBQwpub2RlL3R1cm4tb24g
N3d0bgpub2RlL2FkZC1pbmxldCA3d3RuIHNoMjIgZXNwbm9kZS9zdHJpbmcgYXVkaW9faW5wdXQgYXVkaW9faW5wdXQKcGF0Y2gvYWRkLW5vZGUgc2FkNCB2ZnZnIHdhdmUvbGZvIExGJTIwT3NjaWxsYXRvcgpub2RlL3R1cm4tb24gdmZ2Zwpub2RlL2FkZC1pbmxl
dCB2ZnZnIHF4b3QgZXNwbm9kZS9zdHJpbmcgZnJlcXVlbmN5X2lucHV0IGZyZXF1ZW5jeV9pbnB1dApub2RlL2FkZC1pbmxldCB2ZnZnIGRqbGggZXNwbm9kZS9zdHJpbmcgd2F2ZXRhYmxlX2lucHV0IHdhdmV0YWJsZV9pbnB1dApub2RlL2FkZC1vdXRsZXQgdmZ2
ZyB3OTdxIGVzcG5vZGUvc3RyaW5nIE91dCBPdXQKcGF0Y2gvYWRkLW5vZGUgc2FkNCA2cnBhIGlucHV0L3BvdGVudGlvbWV0ZXIgUG90ZW50aW8lMjB+JTIwSW5wdXQKbm9kZS90dXJuLW9uIDZycGEKbm9kZS9hZGQtaW5sZXQgNnJwYSBxeWtoIGVzcG5vZGUvc3Ry
aW5nIHNhbXBsZSBzYW1wbGUKbm9kZS9hZGQtb3V0bGV0IDZycGEgMjZlcSBlc3Bub2RlL3N0cmluZyBvdXQgb3V0CnBhdGNoL2FkZC1ub2RlIHNhZDQgMXE1NSBpbnB1dC9wb3RlbnRpb21ldGVyIFBvdGVudGlvJTIwfiUyMElucHV0Cm5vZGUvdHVybi1vbiAxcTU1
Cm5vZGUvYWRkLWlubGV0IDFxNTUgMndvaCBlc3Bub2RlL3N0cmluZyBzYW1wbGUgc2FtcGxlCm5vZGUvYWRkLW91dGxldCAxcTU1IHBoMWcgZXNwbm9kZS9zdHJpbmcgb3V0IG91dApwYXRjaC9hZGQtbm9kZSBzYWQ0IHI5aDMgaW5wdXQvb3NjIE9TQyUyMH4lMjBJ
bnB1dApub2RlL3R1cm4tb24gcjloMwpub2RlL2FkZC1pbmxldCByOWgzIGhjYzcgZXNwbm9kZS9zdHJpbmcgc2FtcGxlIHNhbXBsZQpub2RlL2FkZC1vdXRsZXQgcjloMyBzYm8wIGVzcG5vZGUvc3RyaW5nIG91dCBvdXQKcGF0Y2gvYWRkLW5vZGUgc2FkNCBkNjhy
IGlucHV0L29zYyBPU0MlMjB+JTIwSW5wdXQKbm9kZS90dXJuLW9uIGQ2OHIKbm9kZS9hZGQtaW5sZXQgZDY4ciA1dGR1IGVzcG5vZGUvc3RyaW5nIHNhbXBsZSBzYW1wbGUKbm9kZS9hZGQtb3V0bGV0IGQ2OHIgYXl2YSBlc3Bub2RlL3N0cmluZyBvdXQgb3V0CnBh
dGNoL2FkZC1ub2RlIHNhZDQgdnhtOSBpbnB1dC9vc2MgT1NDJTIwfiUyMElucHV0Cm5vZGUvdHVybi1vbiB2eG05Cm5vZGUvYWRkLWlubGV0IHZ4bTkgc2Z5eSBlc3Bub2RlL3N0cmluZyBzYW1wbGUgc2FtcGxlCm5vZGUvYWRkLW91dGxldCB2eG05IGZsNzEgZXNw
bm9kZS9zdHJpbmcgb3V0IG91dApwYXRjaC9hZGQtbm9kZSBzYWQ0IGV1NG8gaW5wdXQvb3NjIE9TQyUyMH4lMjBJbnB1dApub2RlL3R1cm4tb24gZXU0bwpub2RlL2FkZC1pbmxldCBldTRvIHRlbzAgZXNwbm9kZS9zdHJpbmcgc2FtcGxlIHNhbXBsZQpub2RlL2Fk
ZC1vdXRsZXQgZXU0byA4ZWxpIGVzcG5vZGUvc3RyaW5nIG91dCBvdXQKcGF0Y2gvYWRkLW5vZGUgc2FkNCBxMXJuIGlucHV0L29zYyBPU0MlMjB+JTIwSW5wdXQKbm9kZS90dXJuLW9uIHExcm4Kbm9kZS9hZGQtaW5sZXQgcTFybiAxcDJ0IGVzcG5vZGUvc3RyaW5n
IHNhbXBsZSBzYW1wbGUKbm9kZS9hZGQtb3V0bGV0IHExcm4gNWN0NSBlc3Bub2RlL3N0cmluZyBvdXQgb3V0Cm5vZGUvbW92ZSB6MTRjIDMwIDIwCm5vZGUvbW92ZSB0YzZ3IDk0OCA1OApub2RlL21vdmUgN3d0biAxMTYwIDcwCm5vZGUvbW92ZSB2ZnZnIDY3NiA3
Ngpub2RlL21vdmUgNnJwYSA3NDMgMjEyCm5vZGUvbW92ZSAxcTU1IDQwMCAyMTIKbm9kZS9tb3ZlIHI5aDMgMzY0IDMwCm5vZGUvbW92ZSBkNjhyIDQwOSAzNjgKbm9kZS9tb3ZlIHZ4bTkgNzc1IDQ3Mgpub2RlL21vdmUgZXU0byA0MjIgNTI0Cm5vZGUvbW92ZSBx
MXJuIDc3NiAzMzcKb3V0bGV0L2Nvbm5lY3Qgdzk3cSBkbGR2IDRxc3QKb3V0bGV0L2Nvbm5lY3QgcGgxZyBkamxoIGhkajUKb3V0bGV0L2Nvbm5lY3QgejcxbyBzaDIyIDc0MjAKb3V0bGV0L2Nvbm5lY3QgMjZlcSA0eTZ1IHdjODQKb3V0bGV0L2Nvbm5lY3Qgc2Jv
MCBxeG90IHNleTcKbm9kZS91cGRhdGUtaW5sZXQgNnJwYSBxeWtoIHNhbXBsZSAwCm5vZGUvdXBkYXRlLWlubGV0IDFxNTUgMndvaCBzYW1wbGUgMQpub2RlL3VwZGF0ZS1pbmxldCByOWgzIGhjYzcgc2FtcGxlIHRvdWNob3NjMQpub2RlL3VwZGF0ZS1pbmxldCBk
NjhyIDV0ZHUgc2FtcGxlIHRvdWNoTEVEMQpub2RlL3VwZGF0ZS1pbmxldCB2eG05IHNmeXkgc2FtcGxlIHRvdWNob3NjMwpub2RlL3VwZGF0ZS1pbmxldCBldTRvIHRlbzAgc2FtcGxlIHRvdWNob3NjMgpub2RlL3VwZGF0ZS1pbmxldCBxMXJuIDFwMnQgc2FtcGxl
IHRvdWNob3NjNA==
--ENDESPNODEPATCH--

*/
