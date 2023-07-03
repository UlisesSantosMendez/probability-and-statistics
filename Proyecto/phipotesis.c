#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "tsudent.h"

void rellena(float *,float *,int n1,int n2);
void media_varianza(float *,float *,float m1,float m2, int n1,int n2,float v1, float v2);
void val_significancia(float a);
void vardes_iguales(int op1, int n1, int n2, int gl, float Sp, float v1, float v2, float ta, float m1, float m2, float t, float a, float ae2,int d1,int d2,float a2);
void comp_varianzas(float v1, float v2, float F, float a, int n1, int n2, int d1, int d2, float cf1, float cf2, int op1, int gl, float Sp, float ta, float m1, float m2, float t, float ae2,float a2);
void vardes_diferentes(int op1, int n1, int n2, int gl, float v1, float v2, float ta, float m1, float m2, float t, float a, float ae2,int d1, int d2);

int main(){
    int i,n1,n2,op,d1,d2,op1,gl;
    float m1,m2,v1=0,v2=0;
    float s1,s2,a,t,F,ae2,a2;
    float *g1,*g2;
    float cf1,cf2,Sp,ta;

    printf("\t\t\t\t\t\t\t\tPRUEBA DE HIPOTESIS\n");
    printf("MENU:\n");
    printf("1. Crear tabla con diversos datos\n");
    printf("2. Datos conocidos de m,s,a\n");
    printf("Digite su opcion: ");
    scanf("%d",&op);
    printf("Digite la cantidad de elementos a agregar al grupo 1:\n");
    scanf("%d",&n1);
    printf("Digite la cantidad de elementos a agergar al grupo 2:\n");
    scanf("%d",&n2);
    switch (op){
        case 1:
            g1=(float*)malloc(sizeof(int) * n1); //Asigna memoria dinamica para los datos del grupo 1
            g2=(float*)malloc(sizeof(int) * n2); //Asigna memoria dinamica para los datos del grupo 2
            rellena(g1,g2,n1,n2);
            media_varianza(g1,g2,m1,m2,n1,n2,v1,v2);
            printf("Digite la significancia que desee utilizar: ");
            scanf("%f",&a);
            val_significancia(a);
            comp_varianzas(v1,v2,F,a,n1,n2,d1,d2,cf1,cf2,op1,gl,Sp,ta,m1,m2,t,ae2,a2);

        break;
        case 2:
            printf("Ingrese el valor de su media muestral 1: ");
            scanf("%f",&m1);
            printf("Ingrese el valor de su media muestral 2: ");
            scanf("%f",&m2);
            printf("\nIngrese la desviacion estandar del grupo 1: ");
            scanf("%f",&s1);
            printf("\nIngrese la desviacion estandar del grupo 2: ");
            scanf("%f",&s2);
            v1=pow(s1,2);
            printf("\nLa varianza del grupo 1 es: %.3f",v1);
            v2=pow(s2,2);
            printf("\nLa varianza del grupo 2 es: %.3f",v2);
            printf("\nDigite la significancia que desee utilizar: ");
            scanf("%f",&a);
            val_significancia(a);
            comp_varianzas(v1,v2,F,a,n1,n2,d1,d2,cf1,cf2,op1,gl,Sp,ta,m1,m2,t,ae2,a2);
        break;
        default:
            printf("Opcion incorrecta en el menu, digite correctamente porfavor");
        break;
    }
    return 0;
}

void rellena(float *g1,float *g2, int n1,int n2){
    float q1,q2;
    int i;
    for(i=0; i<n1;i++){
        printf("Ingresa el dato %d: ",i+1);
        scanf("%f",&q1);
        g1[i]=q1;
    }
    for(i=0; i<n2;i++){
        printf("Ingresa el dato %d: ",i+1);
        scanf("%f",&q2);
        g2[i]=q2;
    }
}

void media_varianza(float *g1,float *g2,float m1,float m2,int n1, int n2,float v1,float v2){
    float sump1=0,sump2=0;
    float sv1=0,sv2=0;
    int i;
    for(i=0;i<n1;i++){
        sump1=sump1 + g1[i];
    }
    m1=sump1/n1;
    printf("La media muestral del grupo 1 es: %.2f\n",m1);
    for(i=0;i<n2;i++){
        sump2=sump2 + g2[i];
    }
    m2=sump2/n2;
    printf("La media muestral del grupo 2 es: %.2f\n",m2);
    float sumv1=0,sumv2=0;
    for(i=0;i<n1;i++){
        sv1=sv1+pow(g1[i]-m1,2);
    }
    v1=sv1/(n1-1);
    printf("La varianza muestral del grupo 1 es: %.2f\n",v1);
    for(i=0;i<n2;i++){
        sv2=sv2+pow(g2[i]-m2,2);
    }
    v2=sv2/(n2-1);
    printf("La varianza muestral del grupo 2 es: %.2f\n",v2);
}

void val_significancia(float a){
    if (a>0 && a<1){
         printf("Tu significancia es de: %.3f \n",a);
    }
    else{
        do{
            printf("Significancia no valida, se aceptan valores entre 0 y 1\n");
            printf("Ingresa tu significancia nuevamente: \n");
            scanf("%f",&a);
        }
        while (a<0 || a>1);
    }
}

void comp_varianzas(float v1, float v2, float F, float a, int n1, int n2, int d1, int d2, float cf1, float cf2, int op1, int gl, float Sp, float ta, float m1, float m2, float t, float ae2,float a2){
    float px;
    int x;
    printf("PASO 1. CONTRASTE DE VARIANZAS\n");
    printf("Ho: ð1² = ð2²\n");
    printf("Ha: ð1²/= ð2²\n");
    printf("PASO 2. SELECCIONAR ESTADISTICO DE PRUEBA\n");
    printf("F=ð1²/ ð2²\n");
    F=v1/v2;
    printf("PASO 3. ENCONTRAR EL O LOS PUNTOS CRITICOS CON AYUDA DEL NIVEL DE SIGNIFICANCIA\n");
    ae2=a/2;
    px=1-ae2;
    d1=n1-1;
    d2=n2-1;
    printf("Se tiene F1-a/2,n1-1,n2-1\n");
    printf("Se tiene F %.3f , %d, %d \n",px,d1,d2);
    printf("Se ingresa en la aplicación los datos de px,d1 y d2\n");
    printf("El valor de F es: ");
    scanf("%f",&cf1);
    printf("\nSe tiene Fa/2,n1-1,n2-1\n");
    printf("Se tiene F %.3f , %d, %d \n",ae2,d1,d2);
    printf("Se ingresa en la aplicación los datos de px,d1 y d2\n");
    printf("El valor de F es: ");
    scanf("%f",&cf2);
    printf("\nPASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
    if(F<cf1 || F>cf2){
        printf("--------------------------------Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa------------------------\n");
        printf("********************************Se utiliza el caso de dos poblaciones con varianzas desconocidas diferentes***************************\n");
        vardes_diferentes(op1,n1,n2,gl,v1,v2,ta,m1,m2,t,a,ae2,d1,d2); 
    }
    else{
        printf("--------------------------------No se rechaza la hipotesis nula (Ho)------------------------------------------------------------------\n");
        printf("********************************Se utiliza el caso de dos poblaciones con varianzas desconocidas iguales******************************\n");
        vardes_iguales(op1,n1,n2,gl,Sp,v1,v2,ta,m1,m2,t,a,ae2,d1,d2,a2); 
    }
}

void vardes_iguales(int op1, int n1, int n2, int gl, float Sp, float v1, float v2, float ta, float m1, float m2, float t, float a, float ae2,int d1, int d2,float a2){
    float num,den,aux,auxn1,auxn2;
    printf("PASO 1. CONTRASTE DE HIPOTESIS:\n");
    printf("Ho: µ1² = µ2²\n");
    printf("Contraste de hipotesis:\n");
    printf("1. Ha: µ1 < µ2\n");
    printf("2. Ha: µ1 > µ2\n");
    printf("3. Ha: µ1/= µ2\n");
    printf("Selecciona tu contraste de hipotesis: ");
    scanf("%d",&op1);
    printf("\nPASO 2. SELECCIONAMOS UN ESTADISTICO DE PRUEBA");
    num=(d1*v1)+(d2*v2);
    gl=(n1+n2)-2;
    Sp=sqrtf(num/gl);
    printf("\nEl valor de Sp es: %.4f \n",Sp);
    num=m1-m2;
    auxn1=powf(n1,-1);
    auxn2=powf(n2,-1);
    aux=sqrt(auxn1+auxn2);
    den=Sp*aux;
    ta=num/den;
    printf("El valor de t estaditico de prueba es: %.4f\n",ta);
    printf("PASO 3. SE CALCULAN LOS PUNTOS CRITICOS\n");
    switch(op1){
        case 1:
            a2=a;
            t=valor_t(a2,gl,t);
            t=t*(-1);
            printf("El punto critico es: %.3f",t);
            printf("PASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
            printf("t<-t_a,n1+n2-2\n");
            if(ta<t){
                printf("//////////////////////////////////Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa (Ha)////////////////////////////\n");
            }
            else{
                printf("//////////////////////////////////No se rechaza la hipotesis nula (Ho)///////////////////////////////////////////////////////////////////////////\n");
            }
        break;

        case 2:
            a2=a;
            t=valor_t(ae2,gl,t);
            printf("El punto critico es: %.3f",t);
            printf("PASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
            printf("t>t_a,n1+n2-2\n");
            if(ta>t){
                printf("/////////////////////////////////Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa (Ha)////////////////////////////\n");
            }
            else{
                printf("/////////////////////////////////No se rechaza la hipotesis nula (Ho)///////////////////////////////////////////////////////////////////////////\n");
            }
        break;

        case 3:
            a2=ae2;
            t= valor_t(a2,gl,t);
            printf("El punto critico es: %.3f\n",t);
            printf("PASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
            printf("|t|>t_a/2,n1+n2-2\n");
            if(ta>t){
                printf("/////////////////////////////////Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa (Ha)///////////////////////////\n");
            }
            else{
                printf("/////////////////////////////////No se rechaza la hipotesis nula (Ho)//////////////////////////////////////////////////////////////////////////\n");
            }
        break;
    }
    
}

void vardes_diferentes(int op1, int n1, int n2, int gl, float v1, float v2, float ta, float m1, float m2, float t, float a, float ae2,int d1, int d2){
    float num,den,aux,aux1,aux2,np,nd;
    printf("PASO 1. CONTRASTE DE HIPOTESIS:\n");
    printf("Ho: µ1² = µ2²\n");
    printf("Contraste de hipotesis:\n");
    printf("1. Ha: µ1 < µ2\n");
    printf("2. Ha: µ1 > µ2\n");
    printf("3. Ha: µ1/= µ2\n");
    printf("Selecciona tu contraste de hipotesis: ");
    scanf("%d",&op1);
    printf("\nPASO 2. SELECCIONAMOS UN ESTADISTICO DE PRUEBA");
    num=m1-m2;
    aux1=v1/n1;
    aux2=v2/n2;
    aux=aux1+aux2;
    den=sqrtf(aux);
    ta=num/den;
    printf("El valor de t estadistico de prueba es: %.4f",ta);
    np=powf(aux,2);
    nd=((powf(aux1,2))/(d1))+((powf(aux2,2))/(d2));
    gl=np/nd;
    printf("PASO 3. SE CALCULAN LOS PUNTOS CRITICOS\n");
    switch(op1){
        case 1:
            ae2=a;
            t=valor_t(ae2,gl,t);
            t=t*(-1);
            printf("El punto critico es: %.3f",t);
            printf("PASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
            printf("t<-t_a,gl\n");
            if(ta<t){
                printf("/////////////////////////////////Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa (Ha)///////////////////////////\n");
            }
            else{
                printf("/////////////////////////////////No se rechaza la hipotesis nula (Ho)//////////////////////////////////////////////////////////////////////////\n");
            }
        break;

        case 2:
            ae2=a;
            t=valor_t(ae2,gl,t);
            printf("El punto critico es: %.3f",t);
            printf("PASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
            printf("t>t_a,gl\n");
            if(ta>t){
                printf("/////////////////////////////////Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa (Ha)///////////////////////////\n");
            }
            else{
                printf("/////////////////////////////////No se rechaza la hipotesis nula (Ho)//////////////////////////////////////////////////////////////////////////\n");
            }
        break;

        case 3:
            t= valor_t(ae2,gl,t);
            ta=abs(ta);
            printf("El punto critico es: %.3f\n",t);
            printf("PASO 4. SE ESTABLECE LA REGLA DE DECISION\n");
            printf("|t|>t_a/2,gl\n");
            if(ta>t){
                printf("/////////////////////////////////Se rechaza la hipotesis nula (Ho) y se toma en cuenta la hipotesis alternativa (Ha)///////////////////////////\n");
            }
            else{
                printf("/////////////////////////////////No se rechaza la hipotesis nula (Ho)//////////////////////////////////////////////////////////////////////////\n");
            }
        break;
    }
}