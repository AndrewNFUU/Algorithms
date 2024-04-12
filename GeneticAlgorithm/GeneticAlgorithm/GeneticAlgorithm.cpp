#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>

using namespace std;

int popInt[6];
int fitValues[6];
int newPop[6];
double fitProbs[6];
string binaryRepr[6];
string newBinaryRepr[6];


int CalculateF(double x, double y, double z) {

    /*double firstPart = pow(sin((x + pow(z, 2)) / (2 * x + y)), 2);
    double secondPart = z * exp((1 + z) / pow(x, 2) + y);

    return firstPart - secondPart;*/
    return ((pow(fabs(y + x), 0.2) / pow(fabs(z), 1.34)) 
        + pow(fabs(z - y), 3) / fabs(z / cos(x + 2)));
    /*double firstP = z * exp((1 + z) / pow(x, 2) + y);
    return firstP;*/
}

string ConvertToBinary(int num, int bitCount) {
    string binary = "";
    int mask = 1;

    for (int i = 0; i < bitCount; i++) {
        if ((mask & num) >= 1)
            binary = "1" + binary;
        else
            binary = "0" + binary;
        mask <<= 1;
    }
    return binary;
}

int ConvertToDecimal(string binaryString) {
    int decimalValue = 0;
    int currentIndex = 0;

    for (int i = binaryString.length() - 1; i >= 0; i--) {
        if (binaryString[i] == '1') {
            decimalValue += pow(2, currentIndex);
        }
        currentIndex++;
    }
    return decimalValue;
}

void Selection(int popCount) {

    int sumFitness = 0;

    cout << "Initial population: ";
    for (int i = 0; i < popCount; i++) {
        cout << popInt[i] << " ";
    }

    cout << "\nBinary representation of current population: ";
    for (int i = 0; i < popCount; i++) {
        cout << binaryRepr[i] << " ";
    }

    for (int i = 0; i < popCount; i++) {
        newPop[1] = 0;
    }

    int randNum;
    cout << "\nAdaptability individuals of current population: ";
    for (int i = 0; i < popCount; i++) {
        cout << fitValues[i] << " ";
        sumFitness += fitValues[i];
    }

    cout << "\n\nProbability of adaptation: ";
    for (int i = 0; i < popCount; i++) {
        fitProbs[i] = (double)fitValues[i] * 100.0 / sumFitness;
        cout << fitProbs[i] << " ";
    }

    cout << "\n\nTotal fitness of updated population: " << sumFitness;

    cout << "\n\nSelected individuals (Monte Carlo method): ";
    for (int i = 0; i < popCount; i++) {
        randNum = rand() % 100 + 1; // Random number between 1 and 100
        cout << randNum << " ";

        if (randNum < fitProbs[0]) {
            newPop[i] = popInt[0];
        }
        else if (randNum < fitProbs[0] + fitProbs[1]) {
            newPop[i] = popInt[1];
        }
        else if (randNum < fitProbs[0] +
            fitProbs[1] + fitProbs[2])
        {
            newPop[i] = popInt[2];
        }
        else if (randNum < fitProbs[0] +
            fitProbs[1] + fitProbs[2] + fitProbs[3])
        {
            newPop[i] = popInt[3];
        }
        else if (randNum < fitProbs[0] +
            fitProbs[1] + fitProbs[2] +
            fitProbs[3] + fitProbs[4])
        {
            newPop[i] = popInt[4];
        }
        else if (randNum < fitProbs[0] +
            fitProbs[1] + fitProbs[2] +
            fitProbs[3] + fitProbs[4] + fitProbs[5])
        {
            newPop[i] = popInt[5];
        }
    }

    cout << "\n\nSelected poaulation: ";
    for (int i = 0; i < popCount; i++) {
        cout << " " << newPop[i] << " ";
        binaryRepr[i] = ConvertToBinary(newPop[i], 10);
    }

    cout << "\nBinary representation: ";
    for (int i = 0; i < popCount; i++) {
        cout << " " << binaryRepr[i] << " ";
    }
    cout << endl;
}

void NewChildren(string parent1,
    string parent2,
    int crossPoint,
    int child1,
    int child2)
{

    string parent1FirstPart;
    string parent1SecondPart;
    string parent2FirstPart;
    string parent2SecondPart;

    cout << parent1 << " " << parent2 << 
        " crossing point: " << crossPoint << endl;

    parent1FirstPart = parent1.substr(0, crossPoint);
    parent1SecondPart = parent1.substr(crossPoint);
    parent2FirstPart = parent2.substr(0, crossPoint);
    parent2SecondPart = parent2.substr(crossPoint);

    cout << "First parent  | part 1: " << parent1FirstPart <<
        " | part 2: " << parent1SecondPart << endl;

    cout << "Second parent | part 1: " << parent2FirstPart <<
        " | part 2: " << parent2SecondPart << endl;

    newBinaryRepr[child1] = parent1FirstPart + parent1SecondPart;
    newBinaryRepr[child2] = parent2FirstPart + parent2SecondPart;
}

void Crossing(int popSize) {

    int child1Index;
    int child2Index;
    int crossPair[6]{ 0 };
    int crossPoint[3];
    int maxCrossPoint = 1;

    cout << "\nDistribution by pairs: ";

    vector <int> popIndices; // contains a sequence of indices 
                             // of individuals in population

    for (unsigned int it = 0; it < 6; ++it) {
        popIndices.push_back(it);
    }
    random_shuffle(popIndices.begin(), popIndices.end());

    int counter{};
    for (vector<int> ::iterator iter = popIndices.begin(); iter < popIndices.end(); ++iter) {
        crossPair[counter] = *iter;
        counter++;
    }

    // output new order of elements
    for (int p = 0; p < popSize; p++) {
        cout << crossPair[p] << " ";
    }

    cout << "\nCrossing points by pairs: ";
    for (int i = 0; i < 3; i++)
    {
        crossPoint[i] = (int)(rand() % 8) + 1;
        cout << crossPoint[i] << " ";
    }

    cout << "\nFirst pair: ";
    child1Index = 0;
    child2Index = 1;
    NewChildren(binaryRepr[crossPair[0]],
        binaryRepr[crossPair[1]],
        crossPoint[0], 0, 1);

    cout << "\ndescendants: " << newBinaryRepr[child1Index] <<
        " " << newBinaryRepr[child2Index];

    cout << "\nSecond pair: ";
    child1Index = 2;
    child2Index = 3;
    NewChildren(binaryRepr[crossPair[2]],
        binaryRepr[crossPair[3]],
        crossPoint[1], 2, 3);

    cout << "\ndescendants: " << newBinaryRepr[child1Index] <<
        " " << newBinaryRepr[child2Index];

    cout << "\nThird pair: ";
    child1Index = 4;
    child2Index = 5;
    NewChildren(binaryRepr[crossPair[4]],
        binaryRepr[crossPair[5]],
        crossPoint[2], 4, 5);

    cout << "\ndescendants: " << newBinaryRepr[child1Index] <<
        " " << newBinaryRepr[child2Index];

    cout << "\nNew population: ";
    for (int i = 0; i < 6; i++) {
        binaryRepr[i] = newBinaryRepr[i];
    }

    for (int i = 0; i < 6; i++)
    {
        popInt[i] = ConvertToDecimal(binaryRepr[i]);
        cout << popInt[i] << " ";
    }
    cout << endl << endl;
}

int main() {
    srand(time(NULL));

    //double yParam = 1.88;  // 0.47 * 4
    //double zParam = -5.28; // -1.32 * 4
    double yParam = 2.82;
    double zParam = -9.24;

    int maxIter = 100; 
    int popSize = 6;             // max num of persons in population
    int maxBinVal = 1024;          // max binary num for 5 bit: 10000000000 -> 1024
    int fitSum{};
    int newFitSum{};             // sum of all population fitness functions
    bool isOptimalFound = false;
    int iterCount = 1;

    cout << "Initial population: ";
    for (int i = 0; i < popSize; i++) {
        popInt[i] = rand() % (maxBinVal + 1);  // Generating numbers in the range [0, 1024]
        binaryRepr[i] = ConvertToBinary(popInt[i], 10); // Using 10 digits for binary representation
        cout << popInt[i] << " ";
    }
    cout << endl << endl;

    for (int i = 0; i < popSize; i++) {
        fitValues[i] = CalculateF(popInt[i], 1.88, -5.28);
        newFitSum += fitValues[i];
    }

    while (!isOptimalFound) {

        cout << "--------- Step " << iterCount << " ------- \n";
        
        if ((iterCount > maxIter) || (fitSum == newFitSum)) {
            
            cout << "---------- End --------- \n\n";
            isOptimalFound = true;
            break;
        }

        Selection(popSize);
        Crossing(popSize);

        fitSum = newFitSum;
        newFitSum = 0;

        for (int i = 0; i < popSize; i++) {
            fitValues[i] = CalculateF(popInt[i], yParam, zParam);
            newFitSum += fitValues[i];
        }
        iterCount++;
    }
    return 0;
}

// we will obtain no absolutely accurate, 
//    but close to the optimal answer.