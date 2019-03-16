
#include "matriceNullSpace.h"





void displayMatrix(std::vector<std::vector<int>> matrix){
	int row=matrix.size();
	for (int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void displayMatrix(std::vector<std::vector<mpz_class>> matrix){
	int row=matrix.size();
	for (int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < matrix[i].size(); j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}


void generateId(int column, std::vector<std::vector<int>> &id){
  for (int i = 0; i < column; i++) {
    for (int j = 0; j < column; j++) {
      if (i==j) {
        id[i][j]=1;
      }
      else{
        id[i][j]=0;
      }
    }
  }
}


void swapRow(std::vector<std::vector<int>> & matrix, int row1, int row2){
	std::vector<int> tmp=matrix[row1];
	matrix[row1]=matrix[row2];
	matrix[row2]=tmp;
}

void swapRow(std::vector<std::vector<mpz_class>> & matrix, int row1, int row2){
	std::vector<mpz_class> tmp=matrix[row1];
	matrix[row1]=matrix[row2];
	matrix[row2]=tmp;
}

void generateDiagonal(int column, int row, std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &id){
	//On essaie de résoudre en interchangeant les lignes
	/*On va parcourir toutes les lignes voire si on a 1 sur la digonale
	Si ce n'est pas le cas on cherche quelle ligne pourrait apporter ce 1 */
		for(int x=0; x < row && x < column; x++){
			if(matrix[x][x]!=1){
				for(int search=0; search < row; search++){
					if(matrix[search][x]==1){
					//	if(search<x && matrix[x][search]!=1) break;
						swapRow(matrix,x,search);
						swapRow(id,x,search);
						break;
					}
				}
			}
		}
}

void generateDiagonal(int column, int row, std::vector<std::vector<mpz_class>> &matrix, std::vector<std::vector<int>> &id){
	//On essaie de résoudre en interchangeant les lignes
	/*On va parcourir toutes les lignes voire si on a 1 sur la digonale
	Si ce n'est pas le cas on cherche quelle ligne pourrait apporter ce 1 */
		for(int x=0; x < row && x < column; x++){
			if(matrix[x][x]!=1){
				for(int search=0; search < row; search++){
					if(matrix[search][x]==1){
					//	if(search<x && matrix[x][search]!=1) break;
						swapRow(matrix,x,search);
						swapRow(id,x,search);
						break;
					}
				}
			}
		}
}

std::vector<std::vector<int>> resolveNullSpace(int column, int row, std::vector<std::vector<int>> &matrix){
	std::vector<std::vector<int>> id;
	id.resize(column,std::vector<int>(column));
	generateId(column,id);
	std::vector<std::vector<int>> result(0);
	int size=0;
	for(int x=0; x < row && x < column; x++){
		if(matrix[x][x]==1){
			//on regarde si sur la ligne il y a des 1
			for(int y=x+1; y < column && y != x; y++){
				if(matrix[x][y]==1){
					for(int tmp=0; tmp < row; tmp++){
						//on soustrait la colonne qui a 1 sur la digonale à celle qui a 1 sur la ligne
						matrix[tmp][y]=abs(matrix[tmp][y]-matrix[tmp][x]);
						id[tmp][y]=abs(id[tmp][y]-id[tmp][x]);
					}
					/* //Verbose//
					displayMatrix(matrix);
					std::cout << "-----" << '\n';
					displayMatrix(id);
					std::cout << "+++++" << '\n';
					*/ //End verbose//
				}
			}
		}
		else{
			for(int r=x; r < row && r < column; r++){
				if(matrix[r][x]==1){
						swapRow(matrix,x,r);
						swapRow(id,x,r);
						break;
				}
			}
			//si on a réussi a trouver une ligne à echanger
			if(matrix[x][x]==1){
				//permet d'effectuer notre soustraction sur la ligne
				x--;
			}
		}
	}
	for(int y=column-1; y>=0 ;y--){
		//on récupère toutes colonne vide
		int nullColumn=0;
		for(int x=0; x<row; x++){
			if(matrix[x][y]==1){
				nullColumn=1;
				break;
			}
		}
		//si la colonne est nulle
		if(nullColumn==0){
			for(int i=0; i<column; i++){
				result.resize(size+1);
				result[size].push_back(id[i][y]);
			}
			size++;
		}
		else{
			break;
		}
	}
	return result;
}

std::vector<std::vector<mpz_class>> resolveNullSpace(int column, int row, std::vector<std::vector<mpz_class>> &matrix){
	std::vector<std::vector<int>> id;
	id.resize(column,std::vector<int>(column));
	generateId(column,id);
	std::vector<std::vector<mpz_class>> result(0);
	int size=0;
	for(int x=0; x < row && x < column; x++){
		if(matrix[x][x]==1){
			//on regarde si sur la ligne il y a des 1
			for(int y=x+1; y < column && y != x; y++){
				if(matrix[x][y]==1){
					for(int tmp=0; tmp < row; tmp++){
						//on soustrait la colonne qui a 1 sur la digonale à celle qui a 1 sur la ligne
						matrix[tmp][y]=abs(matrix[tmp][y]-matrix[tmp][x]);
						id[tmp][y]=abs(id[tmp][y]-id[tmp][x]);
					}
					/* //Verbose//
					displayMatrix(matrix);
					std::cout << "-----" << '\n';
					displayMatrix(id);
					std::cout << "+++++" << '\n';
					*/ //End verbose//
				}
			}
		}
		else{
			for(int r=x; r < row && r < column; r++){
				if(matrix[r][x]==1){
						swapRow(matrix,x,r);
						swapRow(id,x,r);
						break;
				}
			}
			//si on a réussi a trouver une ligne à echanger
			if(matrix[x][x]==1){
				//permet d'effectuer notre soustraction sur la ligne
				x--;
			}
		}
	}
	for(int y=column-1; y>=0 ;y--){
		//on récupère toutes colonne vide
		int nullColumn=0;
		for(int x=0; x<row; x++){
			if(matrix[x][y]==1){
				nullColumn=1;
				break;
			}
		}
		//si la colonne est nulle
		if(nullColumn==0){
			for(int i=0; i<column; i++){
				result.resize(size+1);
				result[size].push_back(id[i][y]);
			}
			size++;
		}
		else{
			break;
		}
	}
	return result;
}

std::vector<std::vector<int>> modulo2(std::vector<std::vector<int>> &matrix){
	std::vector<std::vector<int>> matrix2=matrix;
	int row=matrix.size();
	int column=matrix[0].size();
	for (int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < column; j++) {
		 matrix2[i][j] = matrix[i][j]%2;
		}
	}
	return matrix2;
}

std::vector<std::vector<int>> resolve(std::vector<std::vector<int>> &matrix){
	int row=matrix.size();
	int column=matrix[0].size();
	//displayMatrix(matrix);
	/* //Verbose//
	std::cout << "Matrice A :" << '\n';
	displayMatrix(matrix);
	*/ //End verbose//

	//On crée une matrice identité
	std::vector<std::vector<int>> matrix2=modulo2(matrix);
	//displayMatrix(matrix);
	std::vector<std::vector<int>> id;
	id.resize(column,std::vector<int>(column));
	generateId(column,id);

	//Fin de la création de la matrice identité
	/* //Verbose//
	std::cout << "Identité :" << '\n';
	displayMatrix(id);
	std::cout << "---Diagonale---" << '\n';
	*/ //End verbose//

	generateDiagonal(column,row,matrix2,id);

	/* //Verbose//
	std::cout << "id Final" << '\n';
	displayMatrix(id);
	std::cout << "vecteur générateur" << '\n';
	displayMatrix(matrix);
	*/ //End verbose//

	//Pour obtenir le vecteur générateur de la matrice on va substituer les colonnes
	//qui ont une valeur non null sur la ligne de la diagonale
	std::vector<std::vector<int>> result=resolveNullSpace(column,row,matrix2);
	/* //Verbose//
	std::cout << "Résultat : " << '\n';
	displayMatrix(result);
	*/ //End verbose//
	return result;
}



std::vector<std::vector<mpz_class>> resolve(std::vector<std::vector<mpz_class>> &matrix){
	int row=matrix.size();
	int column=matrix[0].size();

	//On crée une matrice identité
	std::vector<std::vector<int>> id;
	id.resize(column,std::vector<int>(column));
	generateId(column,id);

	//Fin de la création de la matrice identité
	/* //Verbose//
	std::cout << "Identité :" << '\n';
	displayMatrix(id);
	std::cout << "---Diagonale---" << '\n';
	*/ //End verbose//

	generateDiagonal(column,row,matrix,id);

	/* //Verbose//
	std::cout << "id Final" << '\n';
	displayMatrix(id);
	std::cout << "vecteur générateur" << '\n';
	displayMatrix(matrix);
	*/ //End verbose//

	//Pour obtenir le vecteur générateur de la matrice on va substituer les colonnes
	//qui ont une valeur non null sur la ligne de la diagonale
	std::vector<std::vector<mpz_class>> result=resolveNullSpace(column,row,matrix);
	/* //Verbose//
	std::cout << "Résultat : " << '\n';
	displayMatrix(result);
	*/ //End verbose//
	return result;
}


std::vector<std::vector<int>> transpose(std::vector<std::vector<int>> matrix){
	std::vector<std::vector<int>> result(matrix[0].size());
	for(unsigned int x=0; x<matrix.size();x++){
		for (unsigned int y = 0; y < matrix[0].size() ; y++) {
			result[y].push_back(matrix[x][y]);
		}
	}
	return result;
}

std::vector<std::vector<mpz_class>> transpose(std::vector<std::vector<mpz_class>> matrix){
	std::vector<std::vector<mpz_class>> result(matrix[0].size());
	for(unsigned int x=0; x<matrix.size();x++){
		for (unsigned int y = 0; y < matrix[0].size() ; y++) {
			result[y].push_back(matrix[x][y]);
		}
	}
	return result;
}

std::vector<std::vector<int>> multiplication(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB){
	std::vector<std::vector<int>> result(matrixA.size());
	//on verifie que les matrices ont les bonnes dimensions
	if(matrixA[0].size()!=matrixB.size()){
		std::cerr << "Matrice incompatible à la multiplication !" << '\n';
		return result;
	}
	/*Ici on a une complexité de O(n³) mais en réalité vu nos besoin colB sera très rarement > 3*/
	for(unsigned int colB=0 ; colB<matrixB[0].size(); colB++){
		for(unsigned int x=0; x<matrixA.size();x++){
			int tmpRes=0;
			for(unsigned int y=0; y < matrixA[0].size();y++){
				tmpRes=tmpRes+(matrixA[x][y]*matrixB[y][colB]);
				//std::cout << "("<< matrixA[x][y] << "*" << matrixB[y][colB] << "["<<y<<"-"<<colB <<"]"<< ")"<< matrixA[x][y]*matrixB[y][colB] << " + ";

			}
			//std::cout << "-----------------------------------------" << '\n';
			//std::cout <<tmpRes <<" ";
			result[x].push_back(tmpRes);
		}
		//std::cout << "\n" << '\n';
	}
	return result;
}

std::vector<std::vector<mpz_class>> multiplicationMpz(std::vector<std::vector<int>> matrixA, std::vector<std::vector<int>> matrixB){
	std::vector<std::vector<mpz_class>> result;
	result.resize(matrixA.size());
	//on verifie que les matrices ont les bonnes dimensions
	if(matrixA[0].size()!=matrixB.size()){
		std::cerr << "Matrices incompatibles à la multiplication !" << '\n';
		return result;
	}
	/*Ici on a une complexité de O(n³) mais en réalité vu nos besoin colB sera très rarement > 3*/
	for(unsigned int colB=0 ; colB<matrixB[0].size(); colB++){
		for(unsigned int x=0; x<matrixA.size();x++){
			mpz_class tmpRes (0);
			for(unsigned int y=0; y < matrixA[0].size();y++){
				tmpRes=tmpRes+(matrixA[x][y]*matrixB[y][colB]);
			//	std::cout << "("<< matrixA[x][y] << "*" << matrixB[y][colB] << "["<<y<<"-"<<colB <<"]"<< ")"<< matrixA[x][y]*matrixB[y][colB] << " + ";

			}
		//	std::cout << "--------------"<< tmpRes << '\n';
			result[x].push_back(tmpRes);
		}
	}
	//std::cout << "result" << '\n';
	//displayMatrix(result);
	return result;
}

std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<int>> matrixA, std::vector<int> primeList, mpz_class n){
	std::vector<std::vector<mpz_class>> result;
	result.resize(matrixA.size());
	for(int y=0; y<matrixA[0].size(); y++){
		mpz_class tmpRes(0);
		for(int x=0; x<matrixA.size(); x++){
			tmpRes+=matrixA[y][x]*primeList[x];
		}
		/*Pour optimiser faire des modulo de façon exponentielle*/
		mpz_class res;
		mpz_class mpzN(n);
		mpz_mod(res.get_mpz_t(),tmpRes.get_mpz_t(),mpzN.get_mpz_t());
		result[0].push_back(res);
	}
	return result;
}

std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<mpz_class>> matrixA, std::vector<int> primeList, mpz_class n){
	std::vector<std::vector<mpz_class>> result;
	result.resize(matrixA.size());
	for(int y=0; y<matrixA[0].size(); y++){
		mpz_class tmpRes(0);
		for(int x=0; x<matrixA.size(); x++){
			tmpRes+=matrixA[y][x]*primeList[x];
		}
		/*Pour optimiser faire des modulo de façon exponentielle*/
		mpz_class res;
		mpz_class mpzN(n);
		mpz_mod(res.get_mpz_t(),tmpRes.get_mpz_t(),mpzN.get_mpz_t());
		result[0].push_back(res);
	}
	return result;
}

std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<int>> matrixA, std::vector<mpz_class> primeList, mpz_class n){
	std::vector<std::vector<mpz_class>> result;
	result.resize(matrixA.size());
	for(int y=0; y<matrixA[0].size(); y++){
		mpz_class tmpRes(0);
		for(int x=0; x<matrixA.size(); x++){
			tmpRes+=matrixA[y][x]*primeList[x];
		}
		/*Pour optimiser faire des modulo de façon exponentielle*/
		mpz_class res;
		mpz_class mpzN(n);
		mpz_mod(res.get_mpz_t(),tmpRes.get_mpz_t(),mpzN.get_mpz_t());
		result[0].push_back(res);
	}
	return result;
}

std::vector<std::vector<mpz_class>> properDxPrimeList(std::vector<std::vector<mpz_class>> matrixA, std::vector<mpz_class> primeList, mpz_class n){
	std::vector<std::vector<mpz_class>> result;
	result.resize(matrixA.size());
	for(int y=0; y<matrixA[0].size(); y++){
		mpz_class tmpRes(0);
		for(int x=0; x<matrixA.size(); x++){
			tmpRes+=matrixA[y][x]*primeList[x];
		}
		/*Pour optimiser faire des modulo de façon exponentielle*/
		mpz_class res;
		mpz_class mpzN(n);
		mpz_mod(res.get_mpz_t(),tmpRes.get_mpz_t(),mpzN.get_mpz_t());
		result[0].push_back(res);
	}
	return result;
}

std::vector<mpz_class> finalGCD(std::vector<std::vector<mpz_class>> yList, std::vector<std::vector<mpz_class>> xList, mpz_class n){
	std::vector<mpz_class> result(1);
	for(int y; y < yList[0].size() ; y++){
		mpz_class xy(abs(xList[0][y]-yList[0][y]));
		mpz_class mpzN(n);
		mpz_class res(1);
		mpz_gcd (res.get_mpz_t(),xy.get_mpz_t(), mpzN.get_mpz_t());
		//std::cout << "résultat : "<<res << " x - y "<< xy << " x "<<xList[0][y]<< " y "<<yList[0][y]<< '\n';
		//si résultat non trivial alors on ajoute X,Y,res dans result
		if(res!=1 && res!=n){
			std::cout << "We found !" << '\n';
			result.push_back(xList[0][y]);
			result.push_back(yList[0][y]);
			result.push_back(res);
			break;
		}
	}

	return result;
}


