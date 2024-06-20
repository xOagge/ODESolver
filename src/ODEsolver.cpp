
#include "ODEsolver.h"

//by default the system runs this system
ODEsolver::ODEsolver() {
    const double g = 9.806;
    const double k = 1.6;
    const double M = 20.0;  


    F = {
        [    ](ODEpoint P)->double { return -P.X()[1] /* dx/dt */ ; }, 
        [g, k, M](ODEpoint P)->double {return g - (k / M) * P.X()[1]  /* dv/dt */; },
    };
}

ODEsolver::ODEsolver(const std::vector<std::function<double(ODEpoint)>>& G) { F = G; }

void ODEsolver::SetODEfunc(const std::vector<std::function<double(ODEpoint)>>& G) { F = G; }

const std::vector<ODEpoint>& ODEsolver::Euler(ODEpoint i, double step, double T) {
    // If it can't be initialized then make no change to the map
    if (!InitializeMethod(i, step, T, "euler")) {
        return MS["euler"];
    }

    // Apply the Euler method to the last point in map until a defined time
    while (MS["euler"].back().T() < T) {
        ODEpoint i1 = MS["euler"].back();
        // Declare and initialize inext directly, using temp_point inline
        ODEpoint inext(i1.T() + step, i1 + step * ODEpoint(0, { F[0](i1), F[1](i1) }));
        MS["euler"].push_back(inext);
    }
    return MS["euler"];
}
 
//steps um novo usando Euler, e um seguinte ainda usando step da média do inicial+novo
//aproveita-se de que o valor de Euler vai ficando cada vez maior do que devia, entao desce os valores usando média com o valor anterior
const std::vector<ODEpoint>& ODEsolver::PredictorCorrector(ODEpoint i, double step, double T) {
    //if it cant be initialized then make no change to the mapo
    if(!InitializeMethod(i, step, T, "trapezoidal")){return MS["trapezoidal"];}

    while (MS["trapezoidal"].back().T() < T) {
        ODEpoint i1 = MS["trapezoidal"].back();
        //novo valor temporário usando Euler
        ODEpoint i2(i1.T() + step, i1 + step * ODEpoint(0, { F[0](i1), F[1](i1) }));
        //cria um novo valor que vai ser o seguinte, utilizando a média valor+step_valor_temporario
        ODEpoint inext(i1.T() + step, i1 + step * 0.5 * (ODEpoint(0, { F[0](i1), F[1](i1) }) + ODEpoint(0, { F[0](i2), F[1](i2) }) ));
        MS["trapezoidal"].push_back(inext);
    }
    return MS["trapezoidal"];
}

const std::vector<ODEpoint>& ODEsolver::LeapFrog(ODEpoint i, double step, double T) {
    //if it cant be initialized then make no change to the mapo
    if(!InitializeMethod(i, step, T, "leapfrog")){return MS["leapfrog"];}

    while (MS["leapfrog"].back().T() < T) {
        //ultimo valor
        ODEpoint i1 = MS["leapfrog"].back();
        // i2 = {T + dt,  {dt * w1 + dt * dt* (1/2) * (dw1/dt), w1}}  =  {T + dt, {o1 + dt * w1 + (1/2) * dt * dw1, w1}} = {T + dt, {o1 + dt * w1 + (1/2) * dt * dw1, w1}}
        ODEpoint i2(i1.T() + step, i1 + ODEpoint(0, { step * (i1.X()[1] + step * 0.5 * F[1](i1)), 0 }));
        //inext = {T + dt, {o1 + dt * w1 + (1/2) * dt * dw1, w1 +  (1/2)*(dw1 + dw2)}}
        ODEpoint inext(i1.T() + step, i2 + ODEpoint(0, { 0, step * 0.5 * (F[1](i1) + F[1](i2)) }));
        MS["leapfrog"].push_back(inext);
    }

    return MS["leapfrog"];
}
//ODEpoint inext(i1.T() + step, {i1.X()[0] + step * i1.X()[1] + 0.5 * step * step * F[1](i1), i1.X()[1] + * step * (F[1](i1)+ F[1](i2))});


const std::vector<ODEpoint>& ODEsolver::RK2(ODEpoint i, double step, double T) {
    //if it cant be initialized then make no change to the mapo
    if(!InitializeMethod(i, step, T, "RK2")){return MS["RK2"];}

    while (MS["RK2"].back().T() < T) {
        ODEpoint i1 = MS["RK2"].back();
        ODEpoint k1(0, { step * F[0](i1), step * F[1](i1) }); //{0,{do1, dw1}}

        ODEpoint i_0(i1.T() + step, i1 + k1);  // {T+dt, {o1 + do1, w1 + dw1}}
        ODEpoint k2(0, { step * F[0](i_0), step * F[1](i_0) });  //{0, {d(o1 + do1), d(w1 + dw1)}}

        ODEpoint inext(i_0.T(), i1 + 0.5 * (k1 + k2));  //{T+dt, {o1 + 0.5*(do1 + d(o1 + do1) , w1 + 0.5*(dw1 + d(w1 + dw1)}}
        MS["RK2"].push_back(inext);
    }

    return MS["RK2"];
}

const std::vector<ODEpoint>& ODEsolver::RK4(ODEpoint i, double step, double T) {
    //if it cant be initialized then make no change to the mapo
    if(!InitializeMethod(i, step, T, "RK4")){return MS["RK4"];}

    while (MS["RK4"].back().T() < T) {
        ODEpoint i1 = MS["RK4"].back(); // {T, {o1,w1}}
        ODEpoint k1(0, { step * F[0](i1), step * F[1](i1) });  // {0, {do1, dw1}}

        ODEpoint i2(i1.T() + 0.5 * step, i1 + 0.5 * k1); // {T + 0.5*dt , {o1 + 0.5*do1, w1 + 0.5*dw1}}
        ODEpoint k2(0, { step * F[0](i2), step * F[1](i2) }); // {0, {d(o1 + 0.5*do1) , d(w1 + 0.5*dw1)}}

        ODEpoint i3(i1.T() + 0.5 * step, i1 + 0.5 * k2); // {T + 0.5*dt , {o1 +0.5*d(o1 + 0.5*do1), w1 +0.5*d(w1 + 0.5*dw1)}}
        ODEpoint k3(0, { step * F[0](i3), step * F[1](i3) });// {0, {d(o1 +0.5*d(o1 + 0.5*do1)) , d(w1 +0.5*d(w1 + 0.5*dw1))}}

        ODEpoint i4(i1.T() + step, i1 + k3);  //  { T + dt, {o1 + d(o1 +0.5*d(o1 + 0.5*do1)) , w1 + d(w1 +0.5*d(w1 + 0.5*dw1)) }}
        ODEpoint k4(0, { step * F[0](i4), step * F[1](i4) }); // {0, { d(o1 + d(o1 +0.5*d(o1 + 0.5*do1))) , d(w1 + d(w1 +0.5*d(w1 + 0.5*dw1)))}}

        ODEpoint inext(i4.T(), i1 + 1. / 6. * (k1 + 2 * k2 + 2 * k3 + k4));
        MS["RK4"].push_back(inext);
    }

    return MS["RK4"];
}

bool ODEsolver::InitializeMethod(ODEpoint i, double step, double T, string type){
    //limit the cases where the while loop will be infinite
    if((T<=i.T() && step>0) || (T>=i.T() && step<0) || step == 0 ){return false;}

    //clean map and set the initial point
    MS[type].clear();
    MS[type].push_back(i);
    return true;
}