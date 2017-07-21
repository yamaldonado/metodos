#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159
#define n (250 * 365)  //años total= 250 ; dt= 1/365.0//
#define G 39.476568
#define dt 0.0027   //dt= 1 dia

void aceleracion(int i, int a, float *masas, double *axx, double *ayy, double *azz, double *x, double *y, double *z){

  double ax_1= *axx;
  double ay_1= *ayy;
  double az_1= *azz;
    
  float factor=0;
  int ii;
  for (ii=0; ii<10; ii++){
    if(ii != i){
      factor = ((G*masas[ii])/pow((pow((x[n*ii+a]-x[n*i+a]),2)+pow((y[n*ii+a]-y[n*i+a]),2)+pow((z[n*ii+a]-z[n*i+a]),2)),1.5));
    }
    ax_1 += (factor * (x[n*ii+a] - x[n*i+a]));
    ay_1 += (factor * (y[n*ii+a] - y[n*i+a]));
    az_1 += (factor * (z[n*ii+a] - z[n*i+a]));

  }

  *axx= ax_1;
  *ayy= ay_1;
  *azz= az_1;
}

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

  double ax;
  double ay;
  double az;

  double *v_xhalf = malloc(10*sizeof(double));
  double *v_yhalf = malloc(10*sizeof(double));
  double *v_zhalf = malloc(10*sizeof(double));

  float *masas = malloc(10*sizeof(float));  
  float masa_sol= matriz[0][0];
  
    
  for (i=0; i<10; i++){
    matriz[i][0]= matriz[i][0]/masa_sol;
    masas[i]= matriz[i][0];
    x[n*i]=matriz[i][1];
    y[n*i]=matriz[i][2];
    z[n*i]=matriz[i][3];
    vx[n*i]=matriz[i][4];
    vy[n*i]=matriz[i][5];
    vz[n*i]=matriz[i][6];
  }
  
  
  
   for (int a=0; a<n; a++){
  
    int ind_1 = n*i+a;
    int ind_2 = n*i+(a+1);

    for(i=0; i<10; i++){
      ax, ay, az =0;
      aceleracion(i,a, masas, &ax, &ay, &az, x, y, z);
      

      //velocidad media
      v_xhalf[i] = vx[ind_1] + 0.5 * ax * dt;
      v_yhalf[i] = vy[ind_1] + 0.5 * ay * dt;
      v_zhalf[i] = vz[ind_1] + 0.5 * az * dt;

      //posicion
      x[ind_2] = x[ind_1] + v_xhalf[i] * dt;
      y[ind_2] = y[ind_1] + v_yhalf[i] * dt;
      z[ind_2] = z[ind_1] + v_zhalf[i] * dt;

      ax, ay, az =0;
      aceleracion(i,a+1, masas, &ax, &ay, &az, x, y, z);

      vx[ind_2] = v_xhalf[i] + 0.5 * ax * dt;
      vy[ind_2] = v_yhalf[i] + 0.5 * ay * dt;
      vz[ind_2] = v_zhalf[i] + 0.5 * az * dt;

      //printf("%e %e %e\n", x[ind_1], y[ind_1], z[ind_1]);   
      
          
      }    
   }
  return 0;
}  


  


  
