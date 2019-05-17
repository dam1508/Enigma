#ifndef ENIGMA_H
#define ENIGMA_H

#include "Rotor.h"

template <typename T>
class Enigma
{
    string input_file;
    string help_file;
    string output_file;

    void copy(string from, string to);

    int number_of_changes = 0;
    void change_coding();

    Rotor<T> R1;
    Rotor<T> R2;

    public:

    void menu();

    void enigma(bool decode = false);

    Enigma(string inp = "input.txt", string out = "output.txt", int chngs = 0);
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
void Enigma<T>::change_coding()
{
    R1.rotation();
    if(number_of_changes % R1.get_size() == R1.get_size() - 1) R2.rotation();

    number_of_changes++;
}

template <typename T>
void Enigma<T>::enigma(bool decode)
{
    copy(input_file, help_file);

    ifstream inpfile(input_file);
    ofstream outfile(output_file);

    T data;

    R1.create("Set_in1.txt", "Set_out1.txt");
    R2.create("Set_in2.txt", "Set_out2.txt");

    if(decode)
    {
       while(inpfile>>data)
       {    
            outfile<<R1.translate(R2.translate(data, decode), decode);
            change_coding();
       }
    }
    else while(inpfile>>data)
    {
        outfile<<R2.translate(R1.translate(data));
        change_coding();
    }
    inpfile.close();
    outfile.close();
}

template <typename T>
void Enigma<T>::menu()
{
    int choice;
    bool decode = false;

    system("clear");
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
Enigma<T>::Enigma(string inp, string out, int chngs)
:input_file(inp), output_file(out), number_of_changes(chngs)
{}

#endif