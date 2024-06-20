#ifndef __ODESOLVER__
#define __ODESOLVER__

#include "ODEpoint.h"
#include <vector>
#include <functional>
#include <map>
#include <math.h>
#include <iostream>

/*
    Original:
        v <= 0
        dx/dt = v        [m.s-1]
        dw/dt = -g-(k/m)*(dx/dt) [m.s-2]

    Alterado para obter h>0. v>0, g>0:
        v >= 0
        dx/dt = -v        [m.s-1]
        dw/dt = g-(k/m)*(|dx/dt|) [m.s-2]
*/

class ODEsolver {
private:
    std::vector<std::function<double(ODEpoint)>> F; // Vector of ODE functions
    std::map<std::string, std::vector<ODEpoint> > MS; // Map to store solution trajectories

public:
    ODEsolver(); // Default constructor
    ODEsolver(const std::vector<std::function<double(ODEpoint)>>&); // Constructor with ODE functions
    ~ODEsolver() = default;

    void SetODEfunc(const std::vector<std::function<double(ODEpoint)>>&); //Set new functions

    // Solver methods
    const std::vector<ODEpoint>& Euler(ODEpoint, double, double);
    const std::vector<ODEpoint>& PredictorCorrector(ODEpoint, double, double);
    const std::vector<ODEpoint>& LeapFrog(ODEpoint, double, double);
    const std::vector<ODEpoint>& RK2(ODEpoint, double, double);
    const std::vector<ODEpoint>& RK4(ODEpoint, double, double);

    //auxiliars
    bool InitializeMethod(ODEpoint i, double step, double T, string type);
};

#endif