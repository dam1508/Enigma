#ifndef ROTOR_H
#define ROTOR_H

#include "Rotor_Element.h"
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class Rotor
{
    Rotor_Element<T> *first;
    unsigned int size = 0;                      //wielkosc bebenka
    string settings_file;                       //pliki
    string input_file;
    string help_file;
    string output_file;

    bool find(T data, bool decode = false);
    void add_element(T inp, T out);

    T translate(T input, bool decode = false);

    public:

    void create();
    void encode(bool decode = false);
    void print();

    Rotor(string set = "Settings I.txt", string inp = "input.txt", string hlp = "help.txt", string out = "output.txt");

};

template <typename T>
bool Rotor<T>::find(T data, bool decode)
{
    for(unsigned int i = 0; i < size; i++)
    {
        if(decode && first->get_out() == data) return true;
        else if(!decode && first->get_inp() == data) return true;
        else first = first->get_next();
    }
    cout<<"Can't find "<<data<<endl;
    return false;
}

template <typename T>
void Rotor<T>::add_element(T inp, T out)
{
    Rotor_Element<T> *new_element;
    new_element = new Rotor_Element<T>(inp, out);

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
void Rotor<T>::create()
{
    ifstream file(settings_file);
    T inp_data;
    T out_data;

    while(file>>inp_data)
    {
        if(file.eof()) break;
        if(inp_data == ' ' || inp_data == '\n') continue;

        while(file>>out_data)
        {
            if(out_data == ' ' || out_data == '\n') continue;
            else break ;
        }
        add_element(inp_data, out_data);
    }
    file.close();
}

template <typename T>
void Rotor<T>::print()
{
    Rotor_Element<T> *tmp = first;

    cout<<"Instrukcja: "<<endl;

    for(unsigned int i = 0; i < size ; i++)
    {
        cout<<tmp->get_inp()<<"->"<<tmp->get_out()<<"  ";
        tmp = tmp->get_next();
    }
    cout<<endl;
}

template <typename T>
T Rotor<T>::translate(T input, bool decode)
{
    if(find(input, decode))
    {
        if(decode) return first->get_inp();
        else return first->get_out();
    }else return input;
}

template <typename T>
void Rotor<T>::encode(bool decode)
{
    ifstream inpfile(help_file);
    ofstream outfile(output_file);

    T help;

    while(inpfile>>help)
    {
        if(inpfile.eof()) break;
        else
        {
            outfile<<translate(help, decode);
        }
    }
    inpfile.close();
    outfile.close();
}

template <typename T>
Rotor<T>::Rotor(string set, string inp, string hlp, string out)
:settings_file(set), input_file(inp), help_file(hlp), output_file(out)
{
    first = NULL;
}

#endif