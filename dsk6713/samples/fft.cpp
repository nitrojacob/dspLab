//#include <math.h>
#include <complex>
#define M_PI 3.14

using namespace std;

void fft(complex<float> X[], int start, int N);

void fft(complex<float> X[], int start, int N){

    complex<float> Wnk(0,0);
    complex<float> X1, X2;
    int k, n1, n2;
    if(N>2){
        fft(X, start, N/2);
        fft(X, start+N, N/2);
    }
    for(n1=start, n2=start+N, k = 0; k<N/2; n1++, n2++, k++)
    {
        complex<float> a(0, -2*M_PI*(float)k/(2*N));
        Wnk = exp(a);
        //Wnk = exp(-j*2*M_PI*k/N)
        X1 = X[n1] + Wnk * X[n2];
        X2 = X[n1] - Wnk * X[n2];
        X[n1] = X1;
        X[n2] = X2;
    }
    return;
}


int main(){
    int i;
    float A[] = {1, 0, 0, 0, 0, 0, 0, 0};
    complex<float> X[8];
    for(i=0; i<8; i++){
        //X[i] = complex<float> num(A[i],0.0);
        X[i].real(A[i]);
    }
    fft(X, 0, 4);
    return 0;
}
