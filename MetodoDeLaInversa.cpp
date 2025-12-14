#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

COORD coord={0,0};
void gotoxy(int x,int y){
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void Gaus_Jordan(int i,int j,int k,int n){
	float A[n][n],I[n][n],aux,pivote;

	cout<<"\nIngrese la matriz de coeficientes A:\n";
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			gotoxy(j*6,i+3);
			cin>>A[i][j];
			I[i][j]=(i==j);
		}

	float B[n];
	gotoxy(0,4+n);
	cout<<"Ingrese el vector de resultados b:\n";
	for(i=0;i<n;i++){
		cout<<"b["<<i<<"]: ";
		cin>>B[i];
	}

	bool detCero=false;

	for(i=0;i<n;i++){
		pivote=A[i][i];
		if(pivote==0){
			for(int r=i+1;r<n;r++)
				if(A[r][i]!=0){
					for(int c=0;c<n;c++){
						swap(A[i][c],A[r][c]);
						swap(I[i][c],I[r][c]);
					}
					swap(B[i],B[r]);
					pivote=A[i][i];
					break;
				}
		}
		if(pivote==0){
			detCero=true;
			break;
		}
		for(k=0;k<n;k++){
			A[i][k]/=pivote;
			I[i][k]/=pivote;
		}
		B[i]/=pivote;

		for(j=0;j<n;j++)
			if(i!=j){
				aux=A[j][i];
				for(k=0;k<n;k++){
					A[j][k]-=aux*A[i][k];
					I[j][k]-=aux*I[i][k];
				}
				B[j]-=aux*B[i];
			}
	}

	bool sinSolucion=false;
	bool infinitas=false;

	for(i=0;i<n;i++){
		bool filaCero=true;
		for(j=0;j<n;j++)
			if(A[i][j]!=0)
				filaCero=false;

		if(filaCero){
			if(B[i]!=0)
				sinSolucion=true;
			else
				infinitas=true;
		}
	}

	int base=6+2*n,colI=40;

	gotoxy(0,base-1);
	cout<<"Matriz Identidad (A reducida):";
	gotoxy(colI,base-1);
	cout<<"Matriz Inversa:";

	cout<<fixed<<setprecision(4);
	for(i=0;i<n;i++)
	for(j=0;j<n;j++){
		gotoxy(j*6,base+i);
		if(A[i][j]>0.5) cout<<1;
		else cout<<0;
		gotoxy(colI+j*8,base+i);
		cout<<I[i][j];
	}

	gotoxy(0,base+n+1);
	if(detCero)
		cout<<"Determinante = 0\n";

	if(sinSolucion){
		cout<<"El sistema NO tiene solucion\n";
		return;
	}

	if(infinitas){
		cout<<"El sistema tiene INFINITAS soluciones\n";
		return;
	}

	float X[n];
	for(i=0;i<n;i++)
		X[i]=B[i];

	char P[n]={'X','Y','Z','G','F'};
	gotoxy(0,base+n+2);
	cout<<"Solucion del sistema:\n";
	for(i=0;i<n;i++)
		cout<<P[i]<<" = "<<X[i]<<endl;
}

int main(){
	int i,j,k,n;
	char resto;
	cout<<"Introduzca el numero de filas y columnas: ";
	while(true){
		cin>>n;
		resto=cin.peek();
		if(cin.fail() || resto!='\n'){
			cin.clear();
			cin.ignore(1000,'\n');
			system("cls");
			cout<<"Ingrese un dato entero: ";
		}
		else if(n<=0){
			system("cls");
			cout<<"Ingrese un numero positivo: ";
		}
		else
			break;
	}
	Gaus_Jordan(i,j,k,n);
	return 0;
}