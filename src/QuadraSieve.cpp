#include "QuadraSieve.h"

using namespace std;

//src="https://www.scriptol.fr/programmation/crible.php"
/*
Construire une liste de tous les entiers sup�rieurs � 1 et inf�rieurs ou �gal � n.
Supprimer les multiples de tous les premiers inf�rieurs ou �gal � la racine carr�e de n,
ensuite, les nombres qui restent sont premiers.
*/


bool isBsmooth(mpz_class test, vector<int> prime, vector<pair<mpz_class, int>> &contextPrime){
	mpz_class test2=test;
	int j=0;
	pair<int, int> pair;
	for(unsigned int i = 0 ; i < prime.size() ; i++){

		contextPrime.push_back(pair);
		contextPrime[j].first=prime[i];

		while( test2 % prime[i] == 0 ){
			test2=test2/prime[i];
			contextPrime[j].second++;
		}
		j++;
	}
	return (test2==1);
}

vector<int> eratosthene(int B){
	vector<int> all(B);
	vector<int> liste;

	liste.push_back(2);

	int idx = 0;

	int j;

	int prime = 3;

	while(prime <= B)
	{
		for(int x = 0; x < B; x++)
		{
			if(all[x] == prime)
				goto skip;
		}

		liste.push_back(prime);

		j = prime;
		while(j <= (B / prime))
		{
			all[idx++] = prime * j;
			j += 1;
		}

		skip:
			prime+=2;
	}
	return liste;

}

bSmoothList BSmoothGenerator(mpz_class n, int listSize, vector<int> primeList){
	bSmoothList bSList;
	set<mpz_class> tested;

	int currentSize=0;

	tested.insert(1); //on est sur de pas tester 1 pour �viter boucle infinis dans isBsmooth
	tested.insert(n);

	/*std::default_random_engine rand(std::chrono::system_clock::now().time_since_epoch().count()); //moteur de g�n�ration
	std::uniform_int_distribution<int> distrib{(int)(sqrt(n) - range) , (int)(sqrt(n) + range)};*/
	gmp_randclass r(gmp_randinit_default);
	r.seed(std::chrono::system_clock::now().time_since_epoch().count());
	mpz_class f = 1;
	while(currentSize < listSize){

		while( tested.find(f) != tested.end()){ //pour �viter de retester des valeurs d�j� test�es
			//test = distrib(rand);
			f = r.get_z_range(sqrt(n));
			f = f + sqrt(n);
			f = f/2;
		}


		vector<pair<mpz_class, int>> contextPrime;


		if(isBsmooth(f, primeList, contextPrime)){
			pair<mpz_class, vector<pair<mpz_class, int>>> bSmoothNb;
			bSmoothNb.first = f;
			bSmoothNb.second = contextPrime;
			bSList.push_back(bSmoothNb);
			currentSize++;
		}
		tested.insert(f);
	}
	return bSList;
}

vector<vector<int>> generateMatrix(bSmoothList bsl, vector<int> pl){
	vector<vector<int>> matrix;
	for(unsigned int i = 0 ; i< pl.size() ; i++){
		vector<int> prime;
		for ( unsigned int j = 0 ; j < bsl.size() ; j++ ) {
			prime.push_back(bsl[j].second[i].second);
		}
		matrix.push_back(prime);
	}
	return matrix;
}

int quadraSieve(mpz_class n){
	bool cont = true;
	bool* continuer = &cont;
	vector<int> primeList;
	primeList = eratosthene(99);

	vector<thread> tab_threads;
	for(unsigned int i = 0; i<thread::hardware_concurrency(); i++){
		tab_threads.push_back(thread(concurrentSieve ,n, continuer, primeList));
	}

	cout << "Execution avec " << tab_threads.size() << " threads" << endl;

	for(unsigned int i = 0; i<thread::hardware_concurrency(); i++){
		tab_threads[i].join();
	}

	concurrentSieve(n, continuer, primeList);

	return 0;
}

mpz_class concurrentSieve(mpz_class n, bool *continuer, vector<int> primeList){
	std::vector<mpz_class> result(1);
	bSmoothList bSList;

	do{

		bSList=BSmoothGenerator(n, primeList.size() + 2, primeList);

		std::vector<std::vector<int>> matrix = generateMatrix(bSList, primeList);

		vector<vector <int>> id = resolve(matrix);
		//Ajout marco //
		//std::cout << id.size() << " -- "<< '\n';
		if(id.size()==0){
			//std::cerr << "aucune solution" << '\n';
		}
		else{
			/* //Verbose//
			std::cout << "----result----" << '\n';
			displayMatrix(id);
			std::cout << "****Original****" << '\n';
			displayMatrix(matrix);
			std::cout << "transpose" << '\n';
			*/ //End verbose//
			vector<vector <int>> tid=transpose(id);
			 //Verbose//
			//displayMatrix(tid);
			//std::cout << "---multiplication---" << '\n';
			 //End verbose//
			std::vector<std::vector<int>> mult = multiplication(matrix,tid);
			 //Verbose//
			//std::cout << "--T * A---" << '\n';
			//displayMatrix(mult);
			//Maintenant on va résoudre pour chaque colonne de mult * primeList
			//std::cout << "---Y list" << '\n';
			 //End verbose//
			std::vector<std::vector<mpz_class>>yList=properDxPrimeList(mult, primeList, n);
			 //Verbose//
			//displayMatrix(yList);
			 //End verbose//
			//on fait la meme chose pour X
			//On récupère la liste des entiers BSmooth dans un vector
			std::vector<mpz_class> bS;
			for(int x=0; x<bSList.size(); x++){
				bS.push_back(bSList[x].first);
			}
			//Verbose//
			//std::cout << "---X list" << '\n';
			 //End verbose//
			std::vector<std::vector<mpz_class>>xList=properDxPrimeList(mult, bS, n);
			 //Verbose//
			//displayMatrix(xList);
			//std::cout << "On tente le pgcd" << '\n';
			//End verbose//
			result=finalGCD(yList,xList,n);
		}
	}while(result.size()==1 && *continuer);
	*continuer = false;
	if(result.size() != 1)
		std::cout << "n factorisé par : "<< result[3] <<" et " << n/result[3] << "\n";
	//fin ajout//
	return 0;
}
