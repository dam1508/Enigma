#ifndef ROTOR_H
#define ROTOR_H

#include "Rotor_Output.h"

template <typename T>
class Rotor
{
    string input_settings_file;
    string output_settings_file;

    T *input;
    Rotor_Output<T> output;

    int size;

    void set_input();
    void set_output();

    public:

    T translate(T input, bool decode = false);

    void create(string in, string ou);
    void rotation();

    int get_size() const {return size;}

    Rotor(string inpset = "Set_in1.txt", string outset = "Set_out1.txt");
    ~Rotor();
};

template <typename T>
void Rotor<T>::set_input()
{
    ifstream file(input_settings_file);

    size = 0;
    T data;

    while(file>>data) size++;

    input = new T[size];

    file.close();

    file.open(input_settings_file);

    for(int i = 0; i<size; i++)
    {
        file>>data;
        input[i] = data;
    }

    file.close();
}

template <typename T>
void Rotor<T>::set_output()
{
    output.set_settings(output_settings_file);
    output.create_output();
}

template <typename T>
void Rotor<T>::create(string in, string ou)
{
    input_settings_file = in;
    output_settings_file = ou;
    set_input();
    set_output();
}

template <typename T>
void Rotor<T>::rotation()
{
    output.rotate();
}

template <typename T>
T Rotor<T>::translate(T inp, bool decode)
{
    int id = 1;

    if(decode)
    {
        return input[output.find_T(inp)-1];
    }
    else for(int i = 0; i<size ; i++)
    {
        if(input[i] == inp) break;
        id++;
    }
    return output.find_id(id);
}

template <typename T>
Rotor<T>::Rotor(string inset, string outset)
:input_settings_file(inset), output_settings_file(outset)
{}

template <typename T>
Rotor<T>::~Rotor()
{
    delete [] input;
}

#endif