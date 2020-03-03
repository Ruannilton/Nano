
#include "NanoEngine.frag.glh"

void NanoMain(){
   OutputColor = CalculateLighting(OutputColor);
   OutputColor = GammaCorrection(2.2, OutputColor);
}
