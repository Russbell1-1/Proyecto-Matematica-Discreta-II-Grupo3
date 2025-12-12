#include <iostream>
#include <windows.h>
using namespace std;

COORD coord={0,0};
void gotoxy(int x, int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Gaus_Jordan(int i, int j, int k, int n){
	
	float A[n][n], I[n][n], aux, pivote;
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			gotoxy(j*5,i+3);
			cin>>A[i][j];
			I[i][j]=0;
			if(i==j)
				I[i][j]=1;
		}
	
	//Reduccion por renglones
	
	for(i=0;i<n;i++)
	{
		pivote=A[i][i];
		
		// Si el pivote es cero intentar buscar otra fila
        if(pivote == 0){
            bool cambio = false;
            for(int r=i+1; r<n; r++){
                if(A[r][i] != 0){
                    // intercambiar filas A
                    for(int c=0; c<n; c++){
                        float tempA = A[i][c];
                        A[i][c] = A[r][c];
                        A[r][c] = tempA;

                        float tempI = I[i][c];
                        I[i][c] = I[r][c];
                        I[r][c] = tempI;
                    }
                    cambio = true;
                    pivote = A[i][i];
                    break;
                }
            }
            if(!cambio){
                cout<<"\n\nLa matriz NO tiene inversa (det = 0).\n";
            }
        }
		
		//Ciclo para convertir el pivote a 1 y toda la fila /pivote
		for(k=0;k<n;k++)
		{
			A[i][k]=A[i][k]/pivote;
			I[i][k]=I[i][k]/pivote;
		}
		for(j=0;j<n;j++)
		{
			if(i!=j)  //No estamos en la diagonal
			{
				aux=A[j][i];   //Columna del pivote
				for(k=0;k<n;k++)
				{
					A[j][k]=A[j][k]-aux*A[i][k];
					I[j][k]=I[j][k]-aux*I[i][k];
				}  
			}
		}
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			gotoxy(j*5,i+10);
			cout<<A[i][j];
			
			gotoxy(50+j*5,i+10);
			cout<<I[i][j];
		}
	
	float B[n], X[n];

    cout<<"\n\nIngrese el vector de resultados B:\n";
    for(i=0;i<n;i++){
        cout<<"B["<<i<<"]: ";
        cin>>B[i];
    }

    // X = I * B
    for(i=0;i<n;i++){
    	
        X[i]=0;
        for(j=0;j<n;j++){
            X[i]+=I[i][j]*B[j];
        }
    }

    cout<<"\nSolucion del sistema:\n";
    for(i=0;i<n;i++)
        cout<<"X["<<i<<"] = "<<X[i]<<endl;
}

	


int main(){
	
	int i,j,k,n;
	cout<<"Introduzca el numero de filas y columnas: ";
	cin>>n;
	Gaus_Jordan(i,j,k,n);
	return 0;
}