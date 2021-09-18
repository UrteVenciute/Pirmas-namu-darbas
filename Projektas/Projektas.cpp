// Projektas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


struct duomenys {
    std::string Vardas, Pavarde;
    std::vector<int> nd = { 0 };
    int egz;
    float galut = 0;
};

void count_median(std::vector<int> pazymiai) //galutinio balo medianos skaičiavimas
{
    int counter = 0;
    for (int i = 0; i < pazymiai.size(); i++)
    {
        if (pazymiai[i] != 0)
        {
            counter++;
        }
        if (pazymiai[i] == -1)
        {
            pazymiai[i] = 0;
            counter--;
            break;
        }
    }
    if (counter % 2 == 0)
    {
        std::cout << float(((pazymiai[counter / 2 - 1]) + (pazymiai[(counter / 2)])) / 2.0);
    }
    else
    {
        std::cout << pazymiai[(counter / 2)];
    }
    std::cout << std::endl;
}

int generate_random_mark() //generuojami skaičiai atsitiktinai
{
    srand(time(NULL));
    return rand() % 10 + 1;
}

void automated_marks_input(duomenys Eil[], int i, int pazymiu_skaicius) //automatiškai įvedami skaičiai
{
    Eil[i].egz = generate_random_mark();
    for (int x = 0; x < pazymiu_skaicius; x++)
    {
        Eil[i].nd.push_back(generate_random_mark());
    }
    Eil[i].galut = Eil[i].galut / pazymiu_skaicius;
    Eil[i].galut = Eil[i].galut * 0.4 + 0.6 * Eil[i].egz;
}

void input_by_hand(duomenys Eil[], int i) //suvedami studento rezultatai ranka
{
    int temp;
    do {
        std::cout << "Iveskite studento egzamino bala:\n";
        std::cin >> Eil[i].egz;
    } while (Eil[i].egz < 0 || Eil[i].egz > 10);
    std::cout << "Iveskite studento pazymius (kai baigsite, iveskite -1 ):";
    int counter = 0;
    do {
        std::cin >> temp;
        Eil[i].nd.push_back(temp);
        if (Eil[i].nd.at(counter) != -1) { Eil[i].galut = Eil[i].galut + (float)Eil[i].nd.at(counter); }
        counter++;
    } while (Eil[i].nd.at(counter) != -1);
    counter--;
    Eil[i].galut = Eil[i].galut / counter;
    Eil[i].galut = Eil[i].galut * 0.4 + 0.6 * Eil[i].egz;
}
bool has_digit(std::string s)
{
    return (s.find_first_of("0123456789") != std::string::npos);
}

void name_input(duomenys Eil[], int i) //suvedami studentų vardai ir pavardės
{
    std::cout << "Iveskite studento nr. " << i + 1 << " duomenis:\n";
    do {
        std::cout << "Iveskite studento nr. " << i + 1 << " Vardas:\n";
        std::cin >> Eil[i].Vardas;
    } while (Eil[i].Vardas.length() < 0 || Eil[i].Vardas.length() > 30 || has_digit(Eil[i].Vardas));
    do {
        std::cout << "Iveskite studento nr. " << i + 1 << " Pavarde:\n";
        std::cin >> Eil[i].Pavarde;
    } while (Eil[i].Pavarde.length() < 0 && Eil[i].Pavarde.length() > 30 || has_digit(Eil[i].Pavarde));
    std::cout << std::endl;
}


void print_student(duomenys Eil[], int studentu_sk) //atspausdina rezultatus
{
    std::cout << "\n\n";
    std::cout << std::setw(20) << std::left << "Vardas"
        << std::setw(20) << std::left << "Pavarde"
        << std::setw(18) << std::left << "Galutinis(vid.)/"
        << std::left << "Galutinis(med.)\n"
        << "--------------------------------------------------------------------------\n";
    for (int i = 0; i < studentu_sk; i++)
    {
        std::cout << std::setw(20) << std::left << Eil[i].Vardas
            << std::setw(20) << std::left << Eil[i].Pavarde
            << std::setw(18) << std::left << Eil[i].galut;
        count_median(Eil[i].nd);
    }
    std::cout << "\n\n";
}

int main()
{
    std::cout << "\n\n\n\n\n";
    int studentu_sk;
    std::string temp;
    do
    {
        std::cout << "Iveskite studentu kieki:\n";
        std::cin >> studentu_sk;
    } while (int(studentu_sk) < 0 || int(studentu_sk) > 256);
    duomenys Eil[25];
    //std::vector<duomenys> Eil_vect;
    do
    {
        std::cout << "Norint automatisko duomenu generavimo - RASYKITE \"R\"\n Norint suvesti duomenis - RASYKITE \"P\"\n";
        std::cin >> temp;
        if (temp != "r" && temp != "R" && temp != "p" && temp != "P") { std::cout << "netinkamas simbolis\n"; }
    } while (temp != "r" && temp != "R" && temp != "p" && temp != "P");
    for (int i = 0; i < studentu_sk; i++)
    {
        name_input(Eil, i);
        if (temp == "p" || temp == "P") { input_by_hand(Eil, i); }
        else { automated_marks_input(Eil, i, 5); }
    }
    print_student(Eil, studentu_sk);
    system("pause");
    return 0;
}
