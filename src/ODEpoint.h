#ifndef __ODEPOINT__
#define __ODEPOINT__

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
Represents a point in time of a physical object, containing time of occurence
and variables of the system
*/
class ODEpoint{
    private:
        double t; //time
        vector<double> xvar; //variables 
        

    public:
        ODEpoint() : t(-1), xvar() {;}
        ODEpoint(double t_, const std::vector<double>& v) : t(t_), xvar(v) {;}
        //used in defining new ODEpoint that is the result of operations of other ODEpoints
        ODEpoint(double t_, const ODEpoint& P);

        double& operator[](int); // xvar[i]
    
        void SetODEpoint(double t_, std::vector<double>& v);

        double& T() { return t;} // accessor to time
        vector<double>& X() { return xvar; } // accessor to variables

        friend ostream& operator<< (ostream&, const ODEpoint&); // beautiful print of xvar
        friend ODEpoint operator*(double, const ODEpoint&); // multiply by scalar
        ODEpoint operator+(const ODEpoint&) const; // add two ODEpoints
};



#endif

//CLASSE XVAR QUE JÁ NAO PODEMOS USAR
// class Xvar {
//     protected:
//         std::vector<double> x;

//     public:
//         Xvar() = default;
//         Xvar(int);
//         Xvar(std::vector<double>);
//         Xvar(const std::initializer_list<double>&);

//         Xvar(const Xvar&); //??

//         Xvar& operator=(const Xvar&);
//         Xvar operator+(const Xvar&);

//         double& operator[](int);

//         friend Xvar operator*(double, const Xvar&); //whats a friend? i aint got any
//         friend std::ostream& operator<< (std::ostream&, const Xvar&); //HOHOHO

//         const std::vector<double>& X() { return x; };
// };
// std::ostream& operator<< (std::ostream& s, const Xvar& P) {
//     s << "[ ";
//     for (int i=0; i<P.x.size()-1; i++) { s << P.x[i] << " , "; }
//     s << P.x.back() << " ]";
//     return s; 
// }

// Xvar operator* (double mult, const Xvar& P) {
//     Xvar Ptemp(P);
//     for (int i=0; i  < P.x.size(); i++) { Ptemp.x[i] = P.x[i] * mult; }
//     return Ptemp;
// }
// Xvar::Xvar(int inputInt) { x.resize(2); x[0] = inputInt; x[1] = 0; }
// Xvar::Xvar(std::vector<double> inputVector) { x = inputVector;}
// Xvar::Xvar(const std::initializer_list<double>& inputList) { x.insert(x.end(), inputList.begin(), inputList.end()); }
// Xvar::Xvar(const Xvar& xVar) { x = xVar.x; }

// Xvar& Xvar::operator=(const Xvar& xVar) { x = xVar.x; return *this; }

// Xvar Xvar::operator+(const Xvar& xVar) {
//     Xvar xVar2(x);
//     for (int i = 0; i < x.size(); i++) { xVar2[i] = x[i] + xVar.x[i]; }
//     return xVar2;
// }

// double& Xvar::operator[](int i) { return x[i]; }