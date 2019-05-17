#ifndef ROTOR_ELEMENT_H
#define ROTOR_ELEMENT_H

#include <iostream>

template <typename T>
class Rotor_Element
{
    int number;                  //informacja do zakodowania
    T out;                  //informacja po zakodowaniu

    Rotor_Element *next;    //wskaznik na natepny element bebenka

    public:

//-----------|Gettery|Settery|------------

    int get_number() const {return number;}
    T get_out() const {return out;}
    Rotor_Element *get_next() const {return next;}

    void set_number(int n) {number = n;}
    void set_out(T o) {out = o;}
    void set_next(Rotor_Element *n) {next = n;}

//------------|Konstruktor|-------------

    Rotor_Element(T ou, int num = 0);
};

template <typename T>
Rotor_Element<T>::Rotor_Element(T ou, int num)
:number(num), out(ou)
{next = this;}

#endif