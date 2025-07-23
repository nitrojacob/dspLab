

#include<stdio.h>
#include<math.h>


int t;
//double sincWave[1000];
//double squareWave[1000];
double duration = 1.0;          // duration of the waveforms in seconds
int sampleRate = 1000;          // sample rate in Hz

int signalLength = 1000;

double sincWave[1000];
double squareWave[1000];
double convolutionResult[1999];



// function to generate and print a sincWave
void generateSincWave(double frequency, double duration, int sampleRate, double sincWave[] ) {
    for (t = 0; t < duration * sampleRate; t++) {
        double t_in_seconds = (double)t / sampleRate;


        if (t_in_seconds == 0) {
            sincWave[t] = 1.0;
        } else {
            sincWave[t] = sin(2 * 3.1415926535 * frequency * t_in_seconds) / (3.1415926535 * frequency * t_in_seconds);
        }
    }

}

// function to generate and print squareWave
void generateSquareWave(double frequency, double duration, int sampleRate, double squareWave[]) {
    for (t = 0; t < duration * sampleRate; t++) {
        double t_in_seconds = (double)t / sampleRate;
        double halfPeriod = 1.0 / (2 * frequency);
        squareWave[t] = (t_in_seconds / halfPeriod < 1.0) ? 1.0 : -1.0;
    }
}


int n,k;
// function to perform linearConvolution and store the result in an array
void linearConvolution(const double input1[], const double input2[], double output[], int length) {
    for ( n = 0; n < length; n++) {
        output[n] = 0.0;
        for ( k = 0; k <= n; k++) {
            output[1] += input1[k] * input2[n - k];
        }
    }
}



int main() {
    double frequency_sinc = 5.0;
    double frequency_square = 2.0;// frequency of the sincWave in Hz
    double duration = 1.0;        // duration of the wave in seconds
    int sampleRate = 44100;       // sample rate in Hz8

    generateSincWave (frequency_sinc, duration, sampleRate, sincWave);
    generateSquareWave (frequency_square, duration, sampleRate, squareWave);

    linearConvolution (sincWave, squareWave, convolutionResult, 2 * signalLength - 1);

    return 0;
}
