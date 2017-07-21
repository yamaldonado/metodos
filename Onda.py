import numpy as np
import matplotlib.pyplot as plt
from matplotlib import animation

n_puntos=300
c=1.
x=30
y=30
dx=x/(float(n_puntos-1))
dy=y/(float(n_puntos-1))
r=0.5
dt=(r*dx)/c

#inicializacion de los arreglos temporales con un tamano de 302

u_inicial=np.zeros((n_puntos+2,n_puntos+2))
u_inicial[100,151]=-0.5
u_pasado=np.zeros((n_puntos+2,n_puntos+2))
u_futuro=np.zeros((n_puntos+2,n_puntos+2))

num=float((c**2)*dt/2)
num_2=float((c*dt)**2)


def propagacion(t_n):

    resultado=[]
    resultado.append(u_inicial)
    
    #mascara
    mascara=np.ones((n_puntos+2, n_puntos+2))
    for i in range (0,n_puntos):
        for j in range (0,n_puntos+2):
            if (i==200):
                mascara[i,j]=0
                for j in range (140,160):   
                    mascara[i,j]=1
                    
    #se hace un recorrido de 1 a 300 para dejar los bordes del cuadrado en cero y que no hayan errores con las derivadas
    for j in range (1,n_puntos):
        for k in range (1,n_puntos):
            u_futuro[j,k]=((num/dx)*(u_inicial[j+1,k]-u_inicial[j-1,k]))+((num/dy)*(u_inicial[j,k+1]-u_inicial[j,k-1]))

    u_pasado=u_inicial.copy()
    u_presente=u_futuro.copy()*mascara
    resultado.append(u_presente)
    

    for i in range (1,t_n):
        for j in range (1,n_puntos):
            for k in range (1,n_puntos):
                u_futuro[j,k]=((num_2/dx**2)*(u_presente[j+1,k]-2*u_presente[j,k]+u_presente[j-1,k]))+((num_2/dy**2)*(u_presente[j,k+1]-2*u_presente[j,k]+u_presente[j,k-1]))+2*u_presente[j,k]-u_pasado[j,k]
        u_pasado=u_presente.copy()
        u_presente=u_futuro.copy()*mascara
        resultado.append(u_presente)


    return(u_presente,resultado)



t_60=int(60/dt)
t_30=int(30/dt)

resultado_t60= propagacion(t_60)[1]  #lista de matrices

#graficas para t=30 y t=60
plt.imshow(propagacion(t_30)[0])
plt.savefig("Propagacion_hasta_t=30.pdf")
plt.imshow(propagacion(t_60)[0])
plt.savefig("Propagacion_hasta_t=60.pdf")


#se recortan la mitad de los datos 
lista=[]
for i in range (0,int(len(resultado_t60)/2)):
    lista.append(resultado_t60[i*2])


#Metodo de animacion   
fig=plt.figure()
aa=plt.imshow(abs(lista[0]),cmap='flag', extent= (30+dx, 30-dx, 30+dy, 30-dy))

def func(i):
    aa.set_array(abs(lista[i]))
    return aa,

animacion = animation.FuncAnimation(fig, func, np.arange(1, len(lista)), interval=20, blit=False)
animacion.save('Onda.mp4')


