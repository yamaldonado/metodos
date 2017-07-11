import numpy as np
import matplotlib.pyplot as plt
#from mascarasXY import *

n_puntos=300
c=1.
x=30
y=30
dx=x/(float(n_puntos-1))
dy=y/(float(n_puntos-1))
r=0.5
dt=(r*dx)/c

u_inicial=np.zeros((n_puntos+2,n_puntos+2))
u_inicial[100,151]=-0.5
u_pasado=np.zeros((n_puntos+2,n_puntos+2))
u_futuro=np.zeros((n_puntos+2,n_puntos+2))
resultado=[]

num=float((c**2)*dt/2)
num_2=float((c*dt)**2)

resultado.append(u_inicial)

def propagacion(n_t):

    
    for j in range (1,300):
        for k in range (1,300):
            u_futuro[j,k]=((num/dx)*(u_inicial[j+1,k]-u_inicial[j-1,k]))+((num/dy)*(u_inicial[j,k+1]-u_inicial[j,k-1]))

    u_pasado=u_inicial.copy()
    u_presente=u_futuro.copy()
    resultado.append(u_presente)
    

    for i in range (1,n_t):
        for j in range (1,300):
            for k in range (1,300):
                u_futuro[j,k]=((num_2/dx**2)*(u_presente[j+1,k]-2*u_presente[j,k]+u_presente[j-1,k]))+((num_2/dy**2)*(u_presente[j,k+1]-2*u_presente[j,k]+u_presente[j,k-1]))+2*u_presente[j,k]-u_pasado[j,k]
        u_pasado=u_presente.copy()
        u_presente=u_futuro.copy()
        resultado.append(u_presente)


    return(u_presente,resultado)

#print(propagacion(2)[1][100,151])
#print(propagacion(30)[1][100,151])


plt.imshow(propagacion(30)[0])
plt.savefig("Propagacion_hasta_t=30.pdf")
plt.imshow(propagacion(60)[0])
plt.savefig("Propagacion_hasta_t=60.pdf")



        
