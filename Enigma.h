#ifndef ENIGMA_H
#define ENIGMA_H

#include "Rotor.h"

template <typename T>
class Enigma
{
    string input_file;
    string help_file;
    string output_file;

    unsigned int complexity = 2;

    void copy(string from, string to);

    public:

    void menu();

    void enigma(bool decode = false);

    Enigma(string inp = "input.txt", string hlp = "help.txt", string out = "output.txt");
};

template <typename T>
void Enigma<T>::copy(string from, string to)
{
    ifstream copy_from(from);
    ofstream paste_to(to);

    char data;

    while(copy_from>>data) paste_to<<data;
}

template <typename T>
void Enigma<T>::enigma(bool decode)
{
    copy(input_file, help_file);

    if(decode)
    {
       for(unsigned int i = complexity; i > 0; i--)
        {
            Rotor<T> Rot("Settings"+to_string(i)+".txt");
            Rot.create();
            Rot.print();
            Rot.encode(decode);

            copy(output_file, help_file);
        }
    }
    else for(unsigned int i = 1; i <= complexity; i++)
    {
        Rotor<T> Rot("Settings"+to_string(i)+".txt");
        Rot.create();
        Rot.print();
        Rot.encode(decode);

        copy(output_file, help_file);
    }
}

template <typename T>
void Enigma<T>::menu()
{
    cout<<"Jak zlozone ma byc kodowanie?"<<endl;
    cin>>complexity;

    int choice;
    bool decode = false;

    cout<<"Tryb :"<<endl<<"1. Kodowanie"<<endl<<"2. Dekodowanie"<<endl;
    cin>>choice;

    switch(choice)
    {
        case 1:
            decode = false;
        break;

        case 2:
            decode = true;
        break;

        default:
            decode = false;
    }

    enigma(decode);
}

template <typename T>
Enigma<T>::Enigma(string inp, string hlp, string out)
:input_file(inp), help_file(hlp), output_file(out)
{}

#endif