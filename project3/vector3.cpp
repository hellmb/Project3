#include <iostream>
#include <cmath>
#include "vector3.h"

using namespace std;

// empty vector
vector3::vector3(){
    zeros();
}
void vector3::zeros(){
    comp[0] = 0.0;
    comp[1] = 0.0;
    comp[2] = 0.0;
}

// member functions definitions -> goes into .cpp file
vector3::vector3(double x, double y, double z){
    comp[0] = x;
    comp[1] = y;
    comp[2] = z;
}

vector3 &vector3::operator+=(double rhs){
    comp[0] += rhs;
    comp[1] += rhs;
    comp[2] += rhs;
    return *this;
}

vector3 &vector3::operator+=(vector3 rhs){
    comp[0] += rhs[0];
    comp[1] += rhs[1];
    comp[2] += rhs[2];
    return *this;
}

vector3 &vector3::operator*=(double rhs){
    comp[0] *= rhs;
    comp[1] *= rhs;
    comp[2] *= rhs;
    return *this;
}

vector3 &vector3::operator*=(vector3 rhs){
    comp[0] *= rhs[0];
    comp[1] *= rhs[1];
    comp[2] *= rhs[2];
    return *this;
}

vector3 &vector3::operator/=(double rhs){
    comp[0] /= rhs;
    comp[1] /= rhs;
    comp[2] /= rhs;
    return *this;
}

vector3 &vector3::operator/=(vector3 rhs){
    comp[0] /= rhs[0];
    comp[1] /= rhs[1];
    comp[2] /= rhs[2];
    return *this;
}

vector3 &vector3::operator-=(double rhs){
    comp[0] -= rhs;
    comp[1] -= rhs;
    comp[2] -= rhs;
    return *this;
}

vector3 &vector3::operator-=(vector3 rhs){
    comp[0] -= rhs[0];
    comp[1] -= rhs[1];
    comp[2] -= rhs[2];
    return *this;
}

double vector3::length_squared(){
    return comp[0] * comp[0] + comp[1] * comp[1] + comp[2] * comp[2];
}

double vector3::length(){
    return sqrt(length_squared());
}

void vector3::print()
{
    // Will print matlab syntax vector. Output will be like: [2.09, 5.3, 9.1];
    cout << "[" << comp[0] << ", " << comp[1] << ", " << comp[2] << "]" << endl;
}

void vector3::print(string name)
{
    // Will print matlab syntax vector with a name. Output will be like: A = [2.09, 5.3, 9.1];
    cout << name << " = ";
    print();
}

vector3 vector3::cross(vector3 otherVector)
{
    return vector3(y()*otherVector.z()-z()*otherVector.y(), z()*otherVector.x()-x()*otherVector.z(), x()*otherVector.y()-y()*otherVector.x());
}

double vector3::dot(vector3 otherVector)
{
    return otherVector[0]*comp[0] + otherVector[1]*comp[1] + otherVector[2]*comp[2];
}

void vector3::normalize()
{
    double length = this->length();
    if(length > 0) {
        comp[0] /= length;
        comp[1] /= length;
        comp[2] /= length;
    }
}

vector3 vector3::normalized()
{
    vector3 newVector = *this;
    newVector.normalize();
    return newVector;
}
