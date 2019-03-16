#include "FactorisationElliptique.h"

using namespace std;

mpz_class courbe(mpz_class n, mpz_class h, mpz_class k, bool *conti){
	for(mpz_class i=0; i<h; i++){
      bool continuer = true;
      mpz_class a, x, y, mod, pow1, pow2, p_gcd;
			unsigned int b;
      while(continuer){
        a = rand()%(n-1);
        x = rand()%(n-1);
        y = rand()%(n-1);
				mpz_pow_ui(pow1.get_mpz_t(), y.get_mpz_t(), 2);
				mpz_pow_ui(pow2.get_mpz_t(), x.get_mpz_t(), 3);
        b = pow1.get_ui()-pow2.get_ui()-a.get_ui()*x.get_ui();
				mpz_pow_ui(pow1.get_mpz_t(), a.get_mpz_t(), 3);
				mpz_ui_pow_ui(pow2.get_mpz_t(), b, 2);
				p_gcd = 6*(4*pow1+27*pow2);
        mpz_gcd(mod.get_mpz_t() ,p_gcd.get_mpz_t(), n.get_mpz_t());
        if(mod != n)
          continuer = false;
      }
      Elliptique el(a, x, y, n);
      Point p(x.get_ui(), y, 1);
      Point res(x.get_ui(), y, 1);
      for(mpz_class j=0; j<k; j++){
        res = el.addition(res, p);
				if(!(*conti))
					return 0;
        if(el.get_res() != -1){
						std::cout << "n factorisé par : "<< el.get_res() <<" et " << n/el.get_res() << endl;
						*conti = false;
            return el.get_res();
        }
      }
	}
	return 0;
}

void factorisationElliptique(mpz_class n){
  mpz_class k = 1, pow1;
	mpz_ui_pow_ui(pow1.get_mpz_t(), 2, 8);
	k*=pow1;
	mpz_ui_pow_ui(pow1.get_mpz_t(), 3, 6);
	k*=pow1;
	mpz_class h = 99999999999;
	cout << "Exécution avec " << thread::hardware_concurrency() << " threads, " << h << " courbes et " << k << " additions par courbe" << endl;
	bool cont = true;
	bool *continuer = &cont;
	vector<thread> tab_threads;
	for(unsigned int i = 0; i<thread::hardware_concurrency(); i++){
		tab_threads.push_back(thread(courbe,n,h,k, continuer));
		tab_threads[i].detach();
	}
	mpz_class res = courbe(n,h,k, continuer);
}
