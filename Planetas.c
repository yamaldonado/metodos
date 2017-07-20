#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159
#define n (250 * 350)  //años total= 250 ; dt= 1/350.0//
#define G 4*pow(PI,2)
//#define dt 0.0027   //dt= 1 dia

int main (void){

  //Lectura de datos//
  FILE *file;
  file=fopen ("coordinates.csv", "r");
  
  int len = 250;
  char line_buffer[len];
  char *split_buffer;
  const char *delimiter;
  delimiter= ",";
  int i=0;
  int j=0;
  double matriz [10][7];

  while (fgets(line_buffer, len, file)){
    j=0;
    //printf("LINE IS: %s", line_buffer);//
    split_buffer = strtok(line_buffer, delimiter);

    while(split_buffer != NULL){
      if (j!=0){
	matriz[i][j-1]= atof(split_buffer);}
      //printf("ITEM IN LINE: %s\n", split_buffer);//
      split_buffer= strtok (NULL, delimiter);
      j+=1;
    }
    i+=1;
  }


   double *x = malloc(10*n*sizeof(double));
  double *y = malloc(10*n*sizeof(double));
  double *z = malloc(10*n*sizeof(double));
  double *vx = malloc(10*n*sizeof(double));
  double *vy = malloc(10*n*sizeof(double));
  double *vz = malloc(10*n*sizeof(double));

  double *v_xhalf = malloc(10*sizeof(double));
  double *v_yhalf = malloc(10*sizeof(double));
  double *v_zhalf = malloc(10*sizeof(double));

  double ax;
  double ay;
  double az;
  double *masas;  
  float a=1.0;
  
  for (int i=0; i<10; i++){
    masas[i]= matriz[i][0]/matriz[0][0];
    /* x[n*i]=matriz[i][1];
    y[n*i]=matriz[i][2];
    z[n*i]=matriz[i][3];
    vx[n*i]=matriz[i][4];
    vy[n*i]=matriz[i][5];
    vz[n*i]=matriz[i][6];*/
  } 
  
  //for(int i=0; i<10; i++){
   printf("%f \n", a);
  
  return 0;
}  


  
//para vectores//
int indice(int i,int j){
  return (n*i+j);
}

void aceleracion(int i, int dt, double ax, double ay, double az, double *masas, double *x, double *y, double *z){
    
  float factor=0;
  int ii;
  for (ii=0; ii<10; ii++){
    if(ii != i){
      factor+=((G*masas[ii])/pow((pow((x[n*ii+dt]-x[n*i+dt]),2)+pow((y[n*ii+dt]-y[n*i+dt]),2)+pow((z[n*ii+dt]-z[n*i+dt]),2)),1.5));
    }
    ax += (factor * (x[n*ii+dt] - x[n*i+dt]));
    ay += (factor * (y[n*ii+dt] - y[n*i+dt]));
    az += (factor * (z[n*ii+dt] - z[n*i+dt]));

  }
}
  
