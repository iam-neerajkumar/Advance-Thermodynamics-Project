#include <stdio.h>
#include <math.h>

double f(double x, double T, double P) {
    double G;

    if (T == 1500) {
        G = 1.5286 * pow(10, 8);
    } 
    else if (T == 2000) {
        G = 1.10462 * pow(10, 8);
    }
     else if (T == 2500) {
        G = 6.8907 * pow(10, 7);
    }
     else if (T == 3000) {
        G = 2.7878 * pow(10, 7);
    }
    else if (T==3500)
    {
       G=-1.2722*pow(10,7);
    }
    
    
    double T_1 = (1 / sqrt(2)) * pow(x, 1.5) * pow(P, 0.5);
    double T_2 = (1 - 1.5 * x) * exp(-G / (8314 * T));

    return T_1 - T_2;
}

double f_d(double x, double T, double P) {
    double G;

    if (T == 1500) {
        G = 1.5268 * pow(10, 8);
    }
     else if (T == 2000) {
        G = 1.10462 * pow(10, 8);
    }
     else if (T == 2500) {
        G = 6.8907 * pow(10, 7);
    }
     else if (T == 3000) {
        G = 2.7878 * pow(10, 7);
    }
    else if (T==3500)
    {
       G=-1.2722*pow(10,7);
    }
    

    double TD_1 = (1.5 / sqrt(2)) * pow((P * x), 0.5);
    double TD_2 = 1.5 * exp(-G / (8314 * T));

    return TD_1 + TD_2;
}

void NR_Method(double X_0, double error, double T, double P,FILE *file) {
    double X_1;
    double X_co2,X_o2;
    while (error > 1e-15) {
        X_1 = X_0 - f(X_0, T, P) / f_d(X_0, T, P);
        error = fabs(X_1 - X_0);
        X_0 = X_1;
    }
    X_co2=1-1.5*X_1;
    X_o2=0.5*X_1;
    printf("T: %.1lf K\t P: %.1lf atm \t Xco : %.10lf\n", T, P, X_1);
    printf("T: %.1lf K\t P: %.1lf atm \t Xco2: %.10lf\n", T, P, X_co2);
    printf("T: %.1lf K\t P: %.1lf atm \t Xo2 : %.10lf\n", T, P, X_o2);
    fprintf(file,"%.1lf\t\t%.1lf\t\t%.10lf\n",T,P,X_1);
}

int main() {
    double X_0 = 0.001;
    double error = 1;
    double temperatures[] = {1500, 2000, 2500, 3000, 3500};
    double pressures[] = {0.1, 1, 10, 100};

    printf("\t\tT\t\tP(atm)\t\t\t\tMOLE FRACTION\n");
    printf(".......................................\n");

    FILE *file = fopen("X_CO.txt","w");
    if (file == NULL)
    {
        printf("ERROR\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            NR_Method(X_0, error, temperatures[i], pressures[j],file);
        }
    }
    fclose(file);
    
    return 0;
}
