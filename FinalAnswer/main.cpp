
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <chrono>
#include "piece.hpp"
#include "solution.hpp"
#include "Singleton.hpp"
#include "data.hpp"
#include "termcolor.hpp"
#include "args.h"

using namespace std;
using namespace args;

list<Piece>* generatePieceArray(list<Piece> *aPiece) {
     list<Piece> *_aPiece = new list<Piece>;

    for(auto & oPiece : *aPiece)
    {
        _aPiece->insert(_aPiece->end(),oPiece);
        Piece rotatedPiece = oPiece.rotate();
        _aPiece->insert(_aPiece->end(),rotatedPiece);
        rotatedPiece = oPiece.rotate().rotate();
        _aPiece->insert(_aPiece->end(),rotatedPiece);
        rotatedPiece = oPiece.rotate().rotate().rotate();
        _aPiece->insert(_aPiece->end(),rotatedPiece);
    }

    return _aPiece;
 }

bool compareLeftUp(int flag, const Piece &oCurrentPiece, const Piece &oCheckPiece) {

 
    switch (flag) {
        case 1: // left
            
            if (oCheckPiece.getColors()[0] != oCurrentPiece.getColors()[1] || oCheckPiece.getColors()[3] != oCurrentPiece.getColors()[2]) {
                return false;
            }
            break;
        case 2: // up
            
            if (oCheckPiece.getColors()[0] != oCurrentPiece.getColors()[3] || oCheckPiece.getColors()[1] != oCurrentPiece.getColors()[2]) {
                return false;
            }
            break;
    }
    return true;
}


void removePieces(list<Piece> *aNewAvailablePiece, const Piece &oElement) {

    list<Piece>::iterator it = aNewAvailablePiece->begin();
    while (it != aNewAvailablePiece->end())
    {
        if (it->getId() == oElement.getId()) {
            aNewAvailablePiece->erase(it++);
        } else {
            ++it;
        }
    }
}

void cleanupAvailablePieces(list<Piece> *aNewAvailablePiece, const vector<Piece> *aSolution){

    for(auto & elem : *aSolution)
    {
        removePieces(aNewAvailablePiece, elem);
    }
}

void findNextPiece(vector<Piece> *aCurrentSolution, list<Piece> *aAvailablePieces) {
    vector<Piece> aPossibleMatches;
    Singleton::GetInstance()->incNumIterations();
    long ROW_SIZE = Singleton::GetInstance()->getRowSize();

    // found solution
    if (aCurrentSolution->size() == (int)Singleton::GetInstance()->getNumPieces())  {
        
        Singleton::GetInstance()->addSolution(new Solution(aCurrentSolution));
         return;
    
    } else if (aCurrentSolution->size() == 0) {
        aPossibleMatches.push_back(Singleton::GetInstance()->getPossibleMatch());

    } else {
        // if first row then just check left
        int iNewIndex = (int)aCurrentSolution->size();
        int iCurrentPieceIndex = (int)aCurrentSolution->size() -1;
   
        if (iNewIndex <= ROW_SIZE -1) {
            for(auto & oAvailablePiece : *aAvailablePieces) {
                if (compareLeftUp(1, aCurrentSolution->at(iCurrentPieceIndex), oAvailablePiece)) {
                    aPossibleMatches.push_back(oAvailablePiece);
                }
            }
        } else if (iNewIndex % ROW_SIZE == 0) {
            for(auto & oAvailablePiece : *aAvailablePieces) {
               if (compareLeftUp(2, aCurrentSolution->at(iNewIndex - ROW_SIZE), oAvailablePiece)) {
                    aPossibleMatches.push_back(oAvailablePiece);
                }
            }
        } else {
            for(auto & oAvailablePiece : *aAvailablePieces) {
                if (!compareLeftUp(1, aCurrentSolution->at(iCurrentPieceIndex), oAvailablePiece)) {
                    continue;
                }
               else if (!compareLeftUp(2, aCurrentSolution->at(iNewIndex - ROW_SIZE), oAvailablePiece)) {
                    continue;
                }
                aPossibleMatches.push_back(oAvailablePiece);
            }
        }
    }
    
    for(auto & oPossibleMatch : aPossibleMatches) {

        vector<Piece> aNewSolution;
        
        copy(aCurrentSolution->begin(), aCurrentSolution->end(), back_inserter(aNewSolution));
        aNewSolution.emplace_back(oPossibleMatch);

        list<Piece> aNewAvailablePiece;
        copy(aAvailablePieces->begin(), aAvailablePieces->end(), back_inserter(aNewAvailablePiece));
        cleanupAvailablePieces(&aNewAvailablePiece, &aNewSolution);
       
        findNextPiece(&aNewSolution, &aNewAvailablePiece);
    }
}


bool isEqual(const std::vector<Piece> &first, const std::vector<Piece> &second)
{
    if (first.size() != second.size()) {
        return false;
    }

    for (auto p1 : first) {
        for (auto p2 : second) {
            if (p1.getId() != p2.getId()) {
                return false;
            }
        }
    }
        return true;
}

void startRecursion(vector<Piece> &arrSolution, list<Piece> &arrPieces, Piece possibleMatch) {
    Singleton::GetInstance()->setPossibleMatch(possibleMatch);
    findNextPiece(&arrSolution, &arrPieces);
}

  void ClearScreen()
    {
    int n;
    for (n = 0; n < 10; ++n)
      printf( "\n\n\n\n\n\n\n\n\n\n" );
    }

void line() {
cout << termcolor::blue << "------------------------------------------------------------" << termcolor::reset << endl;
}

void colorField(const string sC)  {
    if ( sC == "B" ) cout << termcolor::on_blue << termcolor::white  << " " << sC << " " <<termcolor::reset;
    else if ( sC == "G" ) cout << termcolor::on_bright_green << termcolor::grey << " " << sC << " " << termcolor::reset;
    else if ( sC == "K" ) cout << termcolor::on_grey << termcolor::white << " " << sC << " " << termcolor::reset;
    else if ( sC == "N" ) cout << termcolor::on_color<94> << termcolor::white << " " << sC << " " << termcolor::reset;
    else if ( sC == "O" ) cout << termcolor::on_red << termcolor::white  << " " << sC << " " << termcolor::reset;
    else if ( sC == "P" ) cout << termcolor::on_bright_magenta << termcolor::grey  << " " << sC << " " << termcolor::reset;
    else if ( sC == "R" ) cout << termcolor::on_bright_red << termcolor::white  << " " << sC << " " << termcolor::reset;
    else if ( sC == "Y" ) cout << termcolor::on_bright_yellow << termcolor::grey << " " << sC << " " << termcolor::reset;
    else cout << sC << " ";
}

vector<string> readFileToVector(const string& filename)
{
    ifstream source;
    source.open(filename);
    vector<string> lines;
    string line;
    while (getline(source, line))
    {
        lines.push_back(line);
    }
    return lines;
}
    
void makeUnique(vector<Solution> *solutions, map<string,Solution>* solmap) {
    vector<Solution>::iterator it;
    for ( it = solutions->begin(); it != solutions->end(); ++it ) {
        it->prepareOutput();
        solmap->insert( pair<string,Solution>(it->getId(),*it) );
    }
}


int main(int argc, char** argv) {
    
    bool multithreading = false;
    bool uqSolution = false;
    bool verbose = false;

    ArgParser parser("The final answer to the Colors problem.\nThere is no known faster solution than this tool.\n\nUsage: FinalAnswer [--multithreading] [--uqSolution] [--file <FILENAME>].\nThe default settings are: singletherading and all solutions.", "2.0");

    parser.flag("multithreading");
    parser.flag("uqSolution");
    parser.flag("verbose");
    parser.option("file","data.txt");

    parser.parse(argc, argv);
    
    if (parser.found("multithreading")) {
        multithreading = true;
    }
    if (parser.found("uqSolution")) {
        uqSolution = true;
    }
    if (parser.found("verbose")) {
        verbose = true;
    }
    string sFileName = (parser.value("file"));
    
    list<Piece> arrPieces;
    vector<string> inputData = readFileToVector(sFileName);
    for (auto line : inputData ) {
        arrPieces.push_back(Piece(line));
    }
    
    ClearScreen();
    
    line();
    cout << "The final answer to the Colors problem.\nThere is no known faster solution than this tool." << endl;
    line();

    cout << "parameter values:";
    parser.print();
    line();
    
    cout << "Data is loading... " << endl;
    arrPieces = readData(arrPieces);

    cout << "Initialization is being done..." << endl;
    Singleton::GetInstance()->setNumPieces(arrPieces.size());
    arrPieces = *(generatePieceArray(&arrPieces));
    vector<Piece> arrSolution;
    vector<Solution> aSolutions = vector<Solution>();
    Singleton::GetInstance()->setAllSolution(&aSolutions);
    vector<Piece> aPossibleMatches;
    copy(arrPieces.begin(), arrPieces.end(), back_inserter(aPossibleMatches));
    
    cout << "Computing the solutions..." << endl;
     
    auto begin = std::chrono::high_resolution_clock::now();
    
    
    // multithreading
    if ( multithreading ) {
        vector<thread> threads;
        for (int i = 0; i < aPossibleMatches.size(); i++) {
            threads.push_back(thread(startRecursion, ref(arrSolution), ref(arrPieces), aPossibleMatches[i]));
        }
        for (auto &th : threads) {
            th.join();
        }
    } else {
    // single threading
        for (int i = 0; i < aPossibleMatches.size(); i++) {
            startRecursion(arrSolution, arrPieces, aPossibleMatches[i]);
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
  
    line();
    cout << termcolor::reset << "...finished calculation" << endl;
    line();

    map<string,Solution>* solmap = new map<string,Solution>;
    makeUnique(Singleton::GetInstance()->getAllSolution(), solmap);

    if ( verbose ) {
//        vector<Solution> *solutions = Singleton::GetInstance()->getAllSolution();
        vector<Solution> uniqueSolutions = vector<Solution>();

        vector<Solution>* vP;
        if ( uqSolution ) {
            vP = &uniqueSolutions;
        } else {
            vP = Singleton::GetInstance()->getAllSolution();
        }
        for ( auto solution : *vP ) {
            for (auto p : solution.getPieces()) {
                p.print();
            }
        cout << endl;
        }
    }
    printf("Here are the solutions:");
    cout << endl;

    string divider = "";
    for (int i = 0; i < Singleton::GetInstance()->getRowSize() * (3 + 5) ; ++i) {
        divider += "-";
    }
    map<string,Solution>::iterator it_solmap;
    for( it_solmap = solmap->begin(); it_solmap != solmap->end() ; ++it_solmap ) {
        if ( verbose ) cout << it_solmap->first << endl;
        cout << termcolor::blue << divider << termcolor::reset << "\n";
        for ( int i = 0; i < Singleton::GetInstance()->getRowSize() * 2; ++i) {
        cout << termcolor::blue << "| " << termcolor::reset;
        for ( int j = 0; j < Singleton::GetInstance()->getRowSize(); ++j) {
            string sC = it_solmap->second.getMatrix()[i][j]; // matrix[i][j];
            string sC1 = sC.substr(0,1);
            string sC2 = sC.substr(1,1);
            colorField(sC1);
            colorField(sC2);
            cout << termcolor::blue << "| " << termcolor::reset;
        }
        if (i % 2 != 0 )  {
            cout << endl << termcolor::blue<< divider << termcolor::reset;
        }
        cout << endl;
    }
}

    
    line();
    cout << termcolor::reset << "number of solutions found by the algorithm: " << Singleton::GetInstance()->getNumSolutions()<< endl;
    cout << termcolor::reset << "number of unique solutions: " << solmap->size() << endl;
    cout << "number of iterations: " << *Singleton::GetInstance()->getNumIterations()<< endl;
//    cout << "max. depth: " << Singleton::GetInstance()->getDepth() << endl;
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    line();
   
    return 0;
}
