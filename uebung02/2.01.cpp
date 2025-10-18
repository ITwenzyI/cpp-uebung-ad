/*
 * File: 2
 * Author: Kilian | ItwenzyI
 * Created: 17.10.2025
 * Description: Registermaschine: berechnet n^2
 */

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<int> reg(4, 0); // R0..R3 (mehr Platz)
bool n_eingegeben = false;
int n = 0;


enum Befehle {
    LDA = 1,
    ADD = 10,
    SUB = 11,
    JMP = 20,
    JEZ = 21,
    HLT = 99
};

struct Instruction {
    Befehle op;
    std::string reg1;
    std::string reg2;
};

int main() {
    std::string pfad = "./uebung02/2_01a";

    if (!std::filesystem::exists(pfad)) {
        std::cout << "Datei existiert NICHT!" << std::endl;
        return 0;
    }

    // ---------- 1. Programm einlesen und parsen ----------
    std::ifstream in(pfad);
    std::vector<Instruction> programm;
    std::string zeile;

    while (std::getline(in, zeile)) {
        // Kommentar abschneiden
        if (zeile.find("//") != std::string::npos)
            zeile = zeile.substr(0, zeile.find("//"));
        if (zeile.empty()) continue;

        // Kommas  entfernen
        std::replace(zeile.begin(), zeile.end(), ',', ' ');

        std::istringstream iss(zeile);
        std::string opcode, op1, op2;
        iss >> opcode >> op1 >> op2;

        std::cout << opcode << " " << op1  << " " <<  op2 << std::endl;

        Befehle befehl;
        if (opcode == "LDA") befehl = LDA;
        else if (opcode == "ADD") befehl = ADD;
        else if (opcode == "SUB") befehl = SUB;
        else if (opcode == "JMP") befehl = JMP;
        else if (opcode == "JEZ") befehl = JEZ;
        else if (opcode == "HLT") befehl = HLT;
        else continue; // unbekannter Befehl

        if (!n_eingegeben) {
            std::cout << "Bitte gebe n ein!" <<  std::endl;
            std::cin >> n;
            n_eingegeben = true;
        }

        // if (zeile.find('n') != std::string::npos)
        //     zeile.replace(zeile.find('n'), 1, std::to_string(n));


        programm.push_back({befehl, op1, op2});
    }
    in.close();

    // ---------- 2. Programm ausführen ----------
    int pc = 0;
    while (pc >= 0 && pc < (int)programm.size()) {
        Instruction instr = programm[pc];
        switch (instr.op) {
            case LDA:
                if (instr.reg1 == "R1") {
                    if (instr.reg2 == "R2")
                        reg[1] = reg[2];
                    else if (instr.reg2 == "R3")
                        reg[1] = reg[3];
                    else if (instr.reg2 == "n") {
                        reg[1] = n;
                    }
                    else {
                        std::cout << instr.reg1 << " DEBUG " << instr.reg2 << std::endl;
                        reg[1] = std::stoi(instr.reg2);
                    }
                }

                else if (instr.reg1 == "R2") {
                    if (instr.reg2 == "R1")
                        reg[2] = reg[1];
                    else if (instr.reg2 == "R3")
                        reg[2] = reg[3];
                    else if (instr.reg2 == "n") {
                        reg[2] = n;
                    }
                    else {
                        std::cout << instr.reg1 << " DEBUG " << instr.reg2 << std::endl;
                        reg[2] = std::stoi(instr.reg2);
                    }
                }

                else if (instr.reg1 == "R3") {
                    if (instr.reg2 == "R1")
                        reg[3] = reg[1];
                    else if (instr.reg2 == "R2")
                        reg[3] = reg[2];
                    else if (instr.reg2 == "n") {
                        reg[3] = n;
                    }
                    else {
                        std::cout << instr.reg1 << " DEBUG " << instr.reg2 << std::endl;
                        reg[3] = std::stoi(instr.reg2);
                    }
                }
                pc++;
                break;

            case ADD:
                pc++;
                break;

            case SUB:
                pc++;
                break;

            case JMP:
                pc++;
                break;

            case JEZ:
                pc++;
                break;

            case HLT:
                if (instr.reg1 == "99")
                    std::cout << "Programm erfolgreich beendet!" << std::endl;
                else
                    std::cout << "Programm fehlerhaft beendet! Fehlercode: " << instr.reg1 << std::endl;
                pc = programm.size(); // beendet Schleife
                break;

            default:
                std::cout << "Unbekannter Befehl bei Zeile " << pc+1 << std::endl;
                pc++;
                break;
        }
    }

    std::cout << "Registerzustand:\n";
    for (size_t i = 0; i < reg.size(); ++i)
        std::cout << "R" << i << " = " << reg[i] << std::endl;

    return 0;
}
