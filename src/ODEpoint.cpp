#include "ODEpoint.h"

ODEpoint::ODEpoint(double t_, const ODEpoint& P){
    t = t_;
    xvar = P.xvar;
}

double& ODEpoint::operator[](int i){
    return xvar[i];
}

void ODEpoint::SetODEpoint(double t_, std::vector<double>& v) { t = t_; xvar = v; }

ostream& operator<< (ostream& s, const ODEpoint& P) {
    s << "[ ";
    for (size_t i = 0; i < P.xvar.size(); i++) {
        s << P.xvar[i];
        if (i < P.xvar.size() - 1) {
            s << " , ";
        }
    }
    s << " ]";
    return s;
}

ODEpoint operator*(double mult, const ODEpoint& P) {
    ODEpoint Ptemp(P.t, P.xvar);
    for (size_t i = 0; i < P.xvar.size(); i++) {
        Ptemp.xvar[i] *= mult;
    }
    return Ptemp;
}

ODEpoint ODEpoint::operator+(const ODEpoint& other) const {
    ODEpoint Ptemp(t, xvar);
    for (size_t i = 0; i < xvar.size(); i++) {
        Ptemp.xvar[i] += other.xvar[i];
    }
    return Ptemp;
}