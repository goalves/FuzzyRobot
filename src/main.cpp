// Inclus�o da biblioteca que implementa a interface com o SoccerMatch.
#include "environm.h"
#include <string>
#include <sstream>
#include <fstream>
#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "FuzzySet.h"
#endif
#ifndef FUZZYFUNCTIONS
#define FUZZYFUNCTIONS
#include "FuzzyTriangle.h"
#include "FuzzyDelta.h"
#include "FuzzyGamma.h"
#endif // FUZZYFUNCTIONS
#include "FuzzyTrapezium.h"
#include "FuzzyLogic.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"



using namespace std;

float arraySum(float A[], int size)
{
    int i;
    float value = 0;
    for(i = 0; i < size; i++)
        value+= A[i];
    return value;
}
// Recebe por par�metro o endere�o e a porta do SoccerMatch.
int main( int argc, char* argv[] ) {

    float   ballAngle, targetAngle, ballDistance, leftMotor, rightMotor, oldLeftMotor, oldRightMotor;

    oldLeftMotor = 0.0f;
    oldRightMotor = 0.0f;

    int ownScore = 0;
    std::stringstream ss;
    std::ofstream myFile;
    myFile.open("neural.lrn");

    // Declara��o do objeto que representa o ambiente.
    environm::soccer::clientEnvironm environment;

    if ( argc != 3 ) {
        printf( "\nSoccerPlayer SERVER_ADDRESS_STRING SERVER_PORT_NUMBER\n" );
        return 0; // Cancela a execu��o se par�metros inv�lidos.
    }

    // Conecta-se ao SoccerMatch. Sup�e que SoccerMatch est� rodando na m�quina
    // local e que um dos rob�s esteja na porta 1024. Porta e local podem mudar.
    if ( ! environment.connect( argv[1], atoi( argv[2] ) ) ) {
        printf( "\nFail connecting to the SoccerMatch.\n" );
        return 0; // Cancela a execu��o se n�o conseguiu conectar-se.
    }

    // Cria as regras NB,NS,ZE,PS,PB
    FuzzyLogic::NB = new FuzzyDelta(-M_PI,-M_PI/2);
    FuzzyLogic::NS = new FuzzyTriangle(-M_PI, -M_PI/2, 0.0);
    FuzzyLogic::ZE = new FuzzyTriangle(-M_PI/2, 0.0, M_PI/2);
    FuzzyLogic::PS = new FuzzyTriangle(0.0, M_PI/2, M_PI);
    FuzzyLogic::PB = new FuzzyGamma(M_PI/2, M_PI);

    // Em adi��o cria o conjunto de regras para LONG, MEDIUM e NEAR
    FuzzyGamma* longRule = new FuzzyGamma(560.0, 750.0);
    FuzzyTrapezium* mediumRule = new FuzzyTrapezium(45.0, 140.0, 560.0, 750);
    FuzzyDelta* nearRule = new FuzzyDelta(45.0, 140.0);

    // La�o de execu��o de a��es.
    while ( 1 ) {

        // Deve obter os dados desejados do ambiente. M�todos do clientEnvironm.
        ballAngle = environment.getBallAngle();
        targetAngle = environment.getTargetAngle( environment.getOwnGoal() );
        ballDistance = environment.getDistance();

        //Etapa 1: Fuzifica��o das entradas
		float longMatrix[24];
		float mediumMatrix[24];
        float nearMatrix[24];

        //Etapa 2: Infer�ncia de Regras
        FuzzyLogic::setBallAngle(ballAngle);
        FuzzyLogic::setTargetAngle(targetAngle);
        FuzzyLogic::setBallDistance(ballDistance);

        FuzzyLogic::setDistanceRule(longRule);
        FuzzyLogic::calculateFuzzyMatrix(longMatrix);

        FuzzyLogic::setDistanceRule(mediumRule);
        FuzzyLogic::calculateFuzzyMatrix(mediumMatrix);

        FuzzyLogic::setDistanceRule(nearRule);
        FuzzyLogic::calculateFuzzyMatrix(nearMatrix);

        //Pega o somat�rio de cada uma das matrizes e guarda no inteiro sum
        float sum = arraySum(longMatrix,25) + arraySum(mediumMatrix,25) + arraySum(nearMatrix,25);
        float weightedSum = FuzzyLogic::calculateFuzzyWeightedSum(longMatrix) +
                            FuzzyLogic::calculateFuzzyWeightedSum(mediumMatrix) +
                            FuzzyLogic::calculateFuzzyWeightedSum(nearMatrix);


        //Etapa 3: Defuzifica��o da Sa�da
        FuzzyLogic::centroidDeffuzification(longMatrix,mediumMatrix,nearMatrix, &sum, &weightedSum);
        double out = weightedSum/sum;

        // Como a defuzifica��o devolve um valor em �ngulos, preciso converter para os valores dos motores
        leftMotor  = cos( out ) - sin( out );
        rightMotor = cos( out ) + sin( out );

        leftMotor = leftMotor * 0.45;
        rightMotor = rightMotor * 0.45;

        ss  << ballDistance << " "
            << ballAngle << " "
            << targetAngle << " "
            << leftMotor << " "
            << rightMotor << "\n";
/*
        ss  << ballDistance << " "
            << ballAngle << " "
            << targetAngle << " "
            << environment.getCollision() << " "
            << environment.getObstacleAngle() << " "
            << environment.getSpin() << " "
            << oldLeftMotor << " "
            << oldRightMotor << " "
            << leftMotor << " "
            << rightMotor << "\n";
*/
        oldLeftMotor = leftMotor;
        oldRightMotor = rightMotor;
        if(ownScore < environment.getOwnScore())
        {
            ownScore = environment.getOwnScore();
            myFile << ss.str();
            ss.str(std::string());
            ss.clear();
        }
        // Transmite a��o do rob� ao ambiente. Fica bloqueado at� que todos os
        // rob�s joguem. Se erro, retorna false (neste exemplo, sai do la�o).
        if ( ! environment.act( leftMotor, rightMotor ) ) {
            myFile.close();
            break; // Termina a execu��o se falha ao agir.
        }
    }

    return 0;
}

