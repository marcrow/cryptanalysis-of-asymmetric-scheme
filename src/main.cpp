#include <stdio.h>
#include "QuadraSieve.h"
#include "FactorisationElliptique.h"
#include "matriceNullSpace.h"
#include <algorithm>
#include <chrono>

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int main(int argc, char * argv[]){
	/* Pour les tests :
		101*7 = 707;
		739 * 919 = 679141
		5839 * 5437 = 31746643
		29881 * 27361 = 817574041
	*/
  auto start = chrono::high_resolution_clock::now();
	mpz_class fact(1659044747);
	if(cmdOptionExists(argv, argv+argc, "-h") || cmdOptionExists(argv, argv+argc, "--help"))
    {
        std::cout << "Deux algorithmes sont actuellement disponibles. \n"
        << "-e --elliptique pour utiliser les courbes elliptiques. Par défaut. \n"
        << "-q --quadratique pour utiliser le crible quadratique. \n"
        << "-v <Valeur> valeur à factoriser. Par défaut 1659044747. \n\n"
        << "-h --help Pour afficher ce message d'aide \n\n"
        << "exemple : ./exec -e -v 2499600007 \n";
        return 0;
    }

    if(cmdOptionExists(argv, argv+argc, "-v")){
    	char * value = getCmdOption(argv, argv + argc, "-v");
		if ((value == NULL)) {
			std::cerr << "Veuillez préciser une valeur.\n";
			std::cout << "Pour consulter l'aide utilisé l'option -h ou --help.\n";
			return -1;
		}
    	std::cout << "n = "<< value << "\n";
    	fact=value;
    }

    if(cmdOptionExists(argv, argv+argc, "-q") || cmdOptionExists(argv, argv+argc, "--quadratique")){
    	std::cout << "lancement de la factorisation par le crible quadratique...\n";
      std::cout << "n = "<< fact << "\n";
		  quadraSieve(fact);
    }
    else {
		std::cout << "lancement de la factorisation par les courbes elliptiques...\n";
    std::cout << "n = "<< fact << "\n";
		factorisationElliptique(fact);
   	}
    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Temps d'exécution : " << elapsed.count() << " s"<< endl;
	//factorisationElliptique(fact);
	//quadraSieve(1659044747);
	//44017*37691
	//1659044747
	//739*919
	//2499600007
}
