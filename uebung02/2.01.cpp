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

std::vector<int> reg(3, 0); // R0..R3 (R2=Result)
bool n_eingegeben = false; // Damit n nur 1x eingegeben wird und nicht jedesmal wenn n wo steht
int n = 0; // Globale Variable n, wird im Code immer genutzt wenn, n in der Instruction steht


// Enum für alle Befehle, da später switch() genutzt wird!
enum Befehle {
    LDA,
    ADD,
    SUB,
    JMP,
    JEZ,
    HLT
};

// Struktur für jede Instruction weil später ein Vektor wo jede Instruktion gespeichert wird
struct Instruction {
    Befehle op;
    std::string reg1;
    std::string reg2;
};

int main() {
    // Pfad für Registermaschinenprogramm
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

        // String stream um alles in verschiedene Variablen für Instruction zu laden
        std::istringstream iss(zeile);
        std::string opcode, op1, op2;
        iss >> opcode >> op1 >> op2;


        // String zu enum umwandeln
        Befehle befehl;
        if (opcode == "LDA") befehl = LDA;
        else if (opcode == "ADD") befehl = ADD;
        else if (opcode == "SUB") befehl = SUB;
        else if (opcode == "JMP") befehl = JMP;
        else if (opcode == "JEZ") befehl = JEZ;
        else if (opcode == "HLT") befehl = HLT;
        else continue; // unbekannter Befehl


        // Eingabe von n und n_eingegeben auf true, damit eben nur 1x n gefordert wird
        if (!n_eingegeben) {
            std::cout << "Bitte gebe n ein!" <<  std::endl;
            std::cin >> n;
            n_eingegeben = true;
        }

        // Print von jeder Instruction, sieht man nochmal alles genau bevor es in Programm gepushed wird.
        std::cout << opcode << " " << op1  << " " <<  op2 << std::endl;

        // Laden der Befehle in Programm, was ein vector<Instruction> ist!
        programm.push_back({befehl, op1, op2});
    }
    in.close();

    // ---------- 2. Programm ausführen ----------
    // PC = Programm Counter, um zu wissen in welcher Zeile man ist
    int pc = 0;

    // Schleife läuft solange, bis letzte Zeile erreicht wird!
    while (pc >= 0 && pc < static_cast<int>(programm.size()) ) {

        // Variable, die jedesmal die eine Zeile vom Programm annimmt, in welcher Zeile man gerade ist
        Instruction instr = programm[pc];
        std::cout <<" DEBUG PC VALUE BEFORE SWITCH "<< pc << std::endl;

        switch (instr.op) {

            // Load Value Case
            case LDA:
                //std::cout << instr.reg1 << " DEBUG LDA ALLGEMEIN " << instr.reg2 << std::endl;
                if (instr.reg1 == "R1") {
                    //std::cout << instr.reg1 << " DEBUG LDA R1 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R2")
                        reg[1] = reg[2];
                    else if (instr.reg2 == "R3")
                        reg[1] = reg[3];
                    else if (instr.reg2 == "n") {
                        reg[1] = n;
                    }
                    // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                    else {
                        reg[1] = std::stoi(instr.reg2);
                    }
                }

                else if (instr.reg1 == "R2") {
                    //std::cout << instr.reg1 << " DEBUG LDA R2 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R1")
                        reg[2] = reg[1];
                    else if (instr.reg2 == "R3")
                        reg[2] = reg[3];
                    else if (instr.reg2 == "n") {
                        reg[2] = n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[2] = std::stoi(instr.reg2);
                    }
                }

                else if (instr.reg1 == "R3") {
                    //std::cout << instr.reg1 << " DEBUG LDA R3 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R1")
                        reg[3] = reg[1];
                    else if (instr.reg2 == "R2")
                        reg[3] = reg[2];
                    else if (instr.reg2 == "n") {
                        reg[3] = n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[3] = std::stoi(instr.reg2);
                    }
                }
                // pc++ weil wir in die nächste Zeile wollen
                pc++;
                break;



            case ADD:
                //std::cout << instr.reg1 << " DEBUG ADD ALLGEMEIN " << instr.reg2 << std::endl;
                if (instr.reg1 == "R1") {
                    //std::cout << instr.reg1 << " DEBUG ADD R1 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R2") {
                        reg[1] = reg[1] + reg[2];
                    }
                    else if (instr.reg2 == "R3") {
                        reg[1] = reg[1] + reg[3];
                    }
                    else if (instr.reg2 == "n") {
                        reg[1] = reg[1] + n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[1] = reg[1] + std::stoi(instr.reg2);
                    }

                }

                else if (instr.reg1 == "R2") {
                    //std::cout << instr.reg1 << " DEBUG ADD R2" << instr.reg2 << std::endl;
                    if (instr.reg2 == "R1") {
                        reg[2] = reg[2] + reg[1];
                    }
                    else if (instr.reg2 == "R3") {
                        reg[2] = reg[2] + reg[3];
                    }
                    else if (instr.reg2 == "n") {
                        reg[2] = reg[2] + n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[2] = reg[2] + std::stoi(instr.reg2);
                    }

                }

                else if (instr.reg1 == "R3") {
                    //std::cout << instr.reg1 << " DEBUG ADD R3 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R1") {
                        reg[3] = reg[3] + reg[1];
                    }
                    else if (instr.reg2 == "R2") {
                        reg[3] = reg[3] + reg[2];
                    }
                    else if (instr.reg2 == "n") {
                        reg[3] = reg[3] + n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[3] = reg[3] + std::stoi(instr.reg2);
                    }

                }
                // Wieder pc++ um in nächste Zeile zu kommen
                pc++;
                break;




            case SUB:
                //std::cout << instr.reg1 << " DEBUG SUB ALLGEMEIN " << instr.reg2 << std::endl;
                if (instr.reg1 == "R1") {
                    if (instr.reg2 == "R2") {
                        reg[1] = reg[1] - reg[2];
                    }
                    else if (instr.reg2 == "R3") {
                        reg[1] = reg[1] - reg[3];
                    }
                    else if (instr.reg2 == "n") {
                        reg[1] = reg[1] - n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[1] = reg[1] - std::stoi(instr.reg2);
                    }

                }

                else if (instr.reg1 == "R2") {
                    //std::cout << instr.reg1 << " DEBUG SUB R2 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R1") {
                        reg[2] = reg[2] - reg[1];
                    }
                    else if (instr.reg2 == "R3") {
                        reg[2] = reg[2] - reg[3];
                    }
                    else if (instr.reg2 == "n") {
                        reg[2] = reg[2] - n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[2] = reg[2] - std::stoi(instr.reg2);
                    }

                }

                else if (instr.reg1 == "R3") {
                    //std::cout << instr.reg1 << " DEBUG SUB R3 " << instr.reg2 << std::endl;
                    if (instr.reg2 == "R1") {
                        reg[3] = reg[3] - reg[1];
                    }
                    else if (instr.reg2 == "R2") {
                        reg[3] = reg[3] - reg[2];
                    }
                    else if (instr.reg2 == "n") {
                        reg[3] = reg[3] - n;
                    }
                    else {
                        // Else ist, wenn nur eine Zahl steht und dann einfach String zu int umwandeln
                        reg[3] = reg[3] - std::stoi(instr.reg2);
                    }

                }
                // pc++ für nächste Zeile
                pc++;
                break;





            case JMP:
                //std::cout << instr.reg1 << " DEBUG JMP " << instr.reg2 << std::endl;
                // -1 weil Vektor bei 0 beginnt aber Zeilen bei 1 :)
                pc = std::stoi(instr.reg1) - 1;
                break;





            case JEZ:
                //std::cout << instr.reg1 << " DEBUG JEZ ALLGEMEIN " << instr.reg2 << std::endl;

                // Hier wird geprüft, ob das Register, was an erster Stelle steht, den Wert 0 hat.
                // Wenn true, dann wird pc auf den Wert gesetzt in welche Zeile man springen will.
                // Wenn false, dann einfach pc++ weil nächste Zeile

                if (instr.reg1 == "R1") {
                    //std::cout << instr.reg1 << " DEBUG JEZ R1 " << instr.reg2 << std::endl;
                    if (reg[1] == 0) {
                        pc = std::stoi(instr.reg2);
                    }
                    else {
                        pc++;
                    }
                }

                else if (instr.reg1 == "R2") {
                    //std::cout << instr.reg1 << " DEBUG JEZ R2 " << instr.reg2 << std::endl;
                    if (reg[2] == 0) {
                        pc = std::stoi(instr.reg2);
                    }
                    else {
                        pc++;
                    }
                }

                else if (instr.reg1 == "R3") {
                    //std::cout << instr.reg1 << " DEBUG JEZ R3 " << instr.reg2 << std::endl;
                    if (reg[3] == 0) {
                        pc = std::stoi(instr.reg2);
                    }
                    else {
                        pc++;
                    }
                }
                break;





            case HLT:
                // 99 ist wie return 0; Also erfolgreich beendet. Sonst beendet mit Fehler Code!

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

    // Ausgabe der Register um zu checken ob es geklappt hat!
    std::cout << "Registerzustand:\n";
    for (size_t i = 1; i <= reg.size(); ++i)
        std::cout << "R" << i << " = " << reg[i] << std::endl;

    return 0;
}
