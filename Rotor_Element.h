#ifndef ROTOR_ELEMENT_H
#define ROTOR_ELEMENT_H

#include <iostream>

template <typename T>
class Rotor_Element
{
    T inp;                  //informacja do zakodowania
    T out;                  //informacja po zakodowaniu

    Rotor_Element *next;    //wskaznik na natepny element bebenka

    public:

//-----------|Gettery|Settery|------------

    T get_inp() const {return inp;}
    T get_out() const {return out;}
    Rotor_Element *get_next() const {return next;}

    void set_inp(T i) {inp = i;}
    void set_out(T o) {out = o;}
    void set_next(Rotor_Element *n) {next = n;}

//------------|Konstruktor|-------------

    Rotor_Element(T in, T ou);
};

template <typename T>
Rotor_Element<T>::Rotor_Element(T in, T ou)
:inp(in), out(ou)
{next = this;}

#endif