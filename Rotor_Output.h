#ifndef ROTOR_OUTPUT_H
#define ROTOR_OUTPUT_H

#include "Rotor_Element.h"
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class Rotor_Output
{
    
    unsigned int size = 0;                      //wielkosc bebenka
    string settings_file;                       //pliki

    Rotor_Element<T> *first;

    void add_element(T out, int num);

    public:

    int find_T(T data);
    T find_id(int id);

    void create_output();
    void rotate();

    void set_settings(string sett) {settings_file = sett;}

    Rotor_Output(string set = "Set_out1.txt");
    ~Rotor_Output();

};

template <typename T>
int Rotor_Output<T>::find_T(T data)
{
    Rotor_Element<T> *hlp = first;

    for(unsigned int i = 0; i < size; i++)
    {
        if(hlp->get_out() == data) return hlp->get_number();
        hlp = hlp->get_next();
    }
    return hlp->get_number();
}

template <typename T>
T Rotor_Output<T>::find_id(int id)
{
    Rotor_Element<T> *hlp = first;

    for(unsigned int i = 0; i < size; i++)
    {
        if(hlp->get_number() == id) return hlp->get_out();
        hlp = hlp->get_next();
    }
    return hlp->get_out();
}

template <typename T>
void Rotor_Output<T>::add_element(T out, int num)
{
    Rotor_Element<T> *new_element;
    new_element = new Rotor_Element<T>(out, num);

    if(size == 0)
    {
        first = new_element;
    }else{

        Rotor_Element<T> *nxt = first->get_next();

        first->set_next(new_element);
        if(size!=1) new_element->set_next(nxt);
        else new_element->set_next(first);
        first = new_element;
    }
    size++;
}

template <typename T>
void Rotor_Output<T>::rotate()
{
    Rotor_Element<T> *hlp = first;
    for(unsigned int i = 0; i < size; i++)
    {
        if(hlp->get_number() != (int)size) hlp->set_number(hlp->get_number() + 1);
        else hlp->set_number(1);
        hlp = hlp->get_next();
    }
}

template <typename T>
void Rotor_Output<T>::create_output()
{
    ifstream file(settings_file);
    T out_data;

    int num = 1;

    while(file>>out_data)
    {
        if(file.eof()) break;
        if(out_data == ' ' || out_data == '\n') continue;
        add_element(out_data, num);
        num++;
    }
    file.close();

    first = first->get_next();
}

template <typename T>
Rotor_Output<T>::Rotor_Output(string set)
:settings_file(set)
{
    first = NULL;
}

template <typename T>
Rotor_Output<T>::~Rotor_Output()
{
	Rotor_Element<T> *hlp = first;
	
	for(unsigned int i = 0; i < size; i++) 
	{
		first = first->get_next();
		delete hlp;
		hlp = first;
	}
}

#endif
