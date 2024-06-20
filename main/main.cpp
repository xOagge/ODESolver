#include "ODEsolver.h"
#include <vector>
using namespace std;

#include "PlotsMaker.h"
#include "TGraph.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TSystem.h"
#include <cmath>

//histograms
#include <TH1F.h>
#include <TStyle.h>

int main() {
    //preguiçade criar método que adicione aceleração a todos os elementos de MS 
    const double g = 9.806;
    const double L = 30;
    const double k = 1.6;
    const double M = 20.0;
    const double w = 0.5;
    const double pi = 3.14159;
    const double b = 0.01;

    /*
    do/dt = w           [rad.s-1]
    dw/dt = -g/L sin(o) [rad.s-2]
    */

    std::vector<std::function<double(ODEpoint)>> HarmonicOscilator = {
        [](ODEpoint P)->double { return P.X()[1]; }, 
        [w](ODEpoint P)->double {return -w*w*P.X()[0]; }
    };

    std::vector<std::function<double(ODEpoint)>> DampedOscilator = {
        [](ODEpoint P)->double { return P.X()[1]; }, 
        [k,M,b](ODEpoint P)->double {return -b*P.X()[1] -k/M * P.X()[0]; } //dv/dt
    };

    std::vector<std::function<double(ODEpoint)>> DampedFall = {
        [    ](ODEpoint P)->double { return -P.X()[1] /* dx/dt */ ; }, 
        [g, k, M](ODEpoint P)->double {return g - (k / M) * P.X()[1]  /* dv/dt */; },
    };

    std::vector<std::function<double(ODEpoint)>> FreeFall = {
        [    ](ODEpoint P)->double { return -P.X()[1] /* dx/dt */ ; }, 
        [g, k, M](ODEpoint P)->double {return g;  /* dv/dt */; },
    };
    
    // Create an instance of ODEsolver
    ODEsolver S(DampedFall);
    
    // Set the initial conditions for the ODE
    ODEpoint I(/*tempo*/0, {/*altura*/ 10000 , /*velocidade*/0});

    // Use the RK4 method to solve the ODE
    vector<ODEpoint> V1 = S.RK4(I, 0.1, 400);

    // Prepare data for plotting
    vector<double> vt, vy, vvel, vacel;
    for (int i = 0; i < V1.size(); i++) {
        vt.push_back(V1[i].T());
        vy.push_back(V1[i].X()[0]);
        vvel.push_back(V1[i].X()[1]);

        //cout << "{ " << vt[i] << " , " << vy[i] << " , " << vvel[i] << " }";
    }

    // Create TGraph objects for plotting
    TGraph G1(vt.size(), vt.data(), vy.data());
    TGraph G2(vt.size(), vt.data(), vvel.data());
    TGraph G3(vy.size(), vy.data(), vvel.data());
    TGraph G4(vy.size(), vy.data(), vacel.data());

    PlotsMaker Plot;
    Plot.Draw(vt, vy, "h(t).pdf", "h(t)", "time", "height");
    Plot.Draw(vt, vvel, "v(t).pdf", "v(t)", "time", "velocity");
    Plot.Draw(vy, vvel, "v(x).pdf", "v(x)", "time", "velocity");


    
}