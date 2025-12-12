#include <iostream>
#include <cmath>
using namespace std;

double determinanteOrden2(double matriz[2][2]){
	return matriz[0][0]*matriz[1][1]-matriz[0][1]*matriz[1][0];
}

double obtenerMenorComplementario(double matriz[3][3], int fila, int columna){
	double menor[2][2];
	int mFila=0, mColumna=0;
	for (int i=0; i<3; i++){
		if (i!=fila){
			for (int j=0; j<3; j++){
				if (j!=columna){
					menor[mFila][mColumna]=matriz[i][j];
					mColumna++;
				}
			}
			mFila++;
			mColumna=0;
		}
	}
	// Mostrar menor complementario
	cout<<"Menor complementario para fila "<<fila<<", columna "<<columna<<":\n";
	for(int i=0; i<2; i++){
		cout<<"| ";
		for(int j=0; j<2; j++){
			cout<<menor[i][j]<<" ";
		}
		cout<<"|\n";
	}
	return determinanteOrden2(menor);
}

double obtenerCofactor(double matriz[3][3], int fila, int columna){
	double menorComplementario=obtenerMenorComplementario(matriz, fila, columna);
	double cofactor = pow(-1, fila + columna) * menorComplementario;
	cout<<"Cofactor de A["<<fila<<"]["<<columna<<"] = "<<cofactor<<"\n";
	return cofactor;
}

double determinanteOrden3(double matriz[3][3]){
	double determinante=0;
	for (int j=0; j<3; j++){
		cout<<"Elemento A[0]["<<j<<"] = "<<matriz[0][j]<<"\n";
		double cofactor = obtenerCofactor(matriz,0,j);
		determinante += matriz[0][j] * cofactor;
		cout<<"Contribucion al determinante: "<<matriz[0][j]<<" * "<<cofactor<<" = "<<matriz[0][j]*cofactor<<"\n\n";
	}
	return determinante;
}

int main(){
    // Matriz de coeficientes
    double A[3][3]={
        {1, 2, 2},
        {1, 3, 1},
        {1, 3, 2}
    };

    // Vector de resultados
    double b[3]={-1, 4, 3};
    cout<<"Sistema de ecuaciones:\n\n";

    // Mostrar el sistema de ecuaciones
    for (int i=0; i<3; i++){
        cout<<"("<<A[i][0]<<")x ";
        if (A[i][1] >= 0){
        	cout<<"+ "<<A[i][1]<<"y ";
		}
        else{
        	cout<<"- "<<-A[i][1] <<"y ";
		}
        if (A[i][2] >= 0){
        	cout<<"+ "<<A[i][2]<<"z ";
		}
        else{
        	cout<<"- "<<-A[i][2]<<"z ";
		}
        cout<<"= "<<b[i]<<endl;
    }
    
    // En forma matricial
    cout<<"\nSistema de ecuaciones en forma matricial:\n\n";
	char X[3]={'x', 'y', 'z'};
    for (int i=0; i<3; i++){
        cout<<"| ";
        for (int j = 0; j < 3; j++){
            cout<<A[i][j]<<" ";
        }
        cout<<"| "<<"| "<<X[i]<<" | ";
		if (i == 1) cout<<"= ";
        else cout<<"  ";
		cout<<"| "<<b[i]<<" |\n";
    }
    cout<<endl;
    
    // Hallar determinante
    double det = determinanteOrden3(A);
    cout<<"Determinante de la matriz 3x3: "<<det<<endl;
    if(det == 0){
    	cout<<"\nEl determinante es '0', no tiene inversa"<<endl;
	} else{
    	cout<<"\nSe puede hallar la inversa de la matriz, podemos continuar"<< endl;
		// Matriz de cofactores completa
		cout<<"\nMatriz de cofactores:\n";
		double cofactores[3][3];
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				cofactores[i][j] = obtenerCofactor(A,i,j);
			}
		}
		cout<<"\nMATRIZ DE COFACOTRES\n\n";
		for(int i=0; i<3; i++){
			cout<<"| ";
			for(int j=0; j<3; j++){
				cout<<cofactores[i][j]<<" ";
			}
			cout<<"|\n";
		}
		
		// Matriz adjunta
		cout<<"\nMatriz adjunta (transpuesta de la matriz de cofactores):\n\n";
		double adjunta[3][3];
		for(int i=0; i<3; i++){
			cout<<"| ";
			for(int j=0; j<3; j++){
				adjunta[i][j] = cofactores[j][i];
				cout<<adjunta[i][j]<<" ";
			}
			cout<<"|\n";
		}
		
		// Matriz inversa
		double inversa[3][3];
		cout<<"\nMatriz inversa (A^-1) = adjunta / determinante:\n\n";
		for(int i=0; i<3; i++){
			cout<<"| ";
			for(int j=0; j<3; j++){
				inversa[i][j] = adjunta[i][j] / det;
				cout<<inversa[i][j]<<" ";
			}
			cout<<"|\n";
		}
		
		// Multiplicar la inversa por el vector b para obtener el resultado
		double resultado[3];
		for(int i=0; i<3; i++){
			resultado[i] = 0;
			for(int j=0; j<3; j++){
				resultado[i] += inversa[i][j] * b[j];
			}
		}
	
		// Mostrar el resultado
		cout<<"\nSolución del sistema de ecuaciones (x, y, z):\n";
		cout<<"x = "<<resultado[0]<<"\n";
		cout<<"y = "<<resultado[1]<<"\n";
		cout<<"z = "<<resultado[2]<<"\n";
	}
	return 0;
}
