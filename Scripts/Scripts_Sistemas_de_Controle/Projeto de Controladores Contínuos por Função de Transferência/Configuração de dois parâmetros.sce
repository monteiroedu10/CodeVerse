// Limpa as variáveis da área de trabalho
clear;

// Define as especificações da função de transferência de referência G0(s)
Mp_G0 = 0.01; // Sobressinal máximo desejado
ts_G0 = 10;   // Tempo de Estabilização desejado
tr_G0 = 4;    // Tempo de Subida desejado


// Calcula o coeficiente de amortecimento da função de transferência de referência G0(s)
Qsi_G0 = (sqrt((log(Mp_G0))^2))/(sqrt((%pi^2) + (log(Mp_G0))^2));
disp('Coeficiente de amortecimento: ' + string(Qsi_G0));


// Como Qsi caracteriza o sistema como subamortecido podemos aproximar ts e tp
tp_G0 = tr_G0;
disp('Instante de pico (tp): ' + string(tp_G0));


// Calcular o valor de OmegaN_G0 para G0(s)
OmegaN_G0 = %pi/(tp_G0*sqrt(1-(Qsi_G0^2)));
disp('Frequência natural: ' + string(OmegaN_G0));


// Define o operador de Laplace 's'  
s = %s; 

// Define o numerador da função de transferência G(s) 
NGs = 10.19; 
 
// Define o denominador da função de transferência G(s)  
DGs = s^2 + 0.8451 * s + 9.131; 
 
// Cria a função de transferência G(s) com base nos coeficientes do numerador e denominador 
Gs = syslin('c', NGs, DGs); 

// Acha o G0(s) usando os parâmetros Qsi_G0 e OmegaN_G0
NG0 = OmegaN_G0^2;
DG0 = (s^2 + 2 * Qsi_G0 * OmegaN_G0 * s + OmegaN_G0^2);
G0 = syslin('c',NG0,DG0);


// Exibe as funções de transferência G0(s), G(s) e C(s)
disp('G0(s):'); disp(G0);
disp('G(s):'); disp(Gs);


// Encontra Np(s)/Dp(s)
NumNp_Dp = NG0/NGs;
DenNp_Dp = DG0;
Np_Dp = syslin('c',NumNp_Dp,DenNp_Dp);
disp('G0(s)/N(s):'); disp(Np_Dp);

// Define Np(s)
Nps =  0.1906109;

// Define Dp(s)
Dps =  1.9423248 +2.3025851*s + s^2;
disp('Dp(s):'); disp(Dps);

// Define Dpbarra(s)
Dpsbarra =  s + 10;
disp('Dpbarra(s):'); disp(Dpsbarra);


// Define F(s)
Fs = Dps*Dpsbarra;
disp('F(s):'); disp(Fs);

// Define a Matriz D_N
D_N = [9.131, 10.19, 0, 0; 0.8451, 0, 9.131, 10.19; 1, 0, 0.8451, 0; 0, 0, 1, 0];
//disp('D_N:'); disp(D_N);

// Define a Matriz de F(s)
MFs = [19.423248;24.968176;12.302585;1]
//disp('MFs:'); disp(MFs);

// Define a Matriz A_M
A_M = inv(D_N)*MFs; 
disp('A_M:'); disp(A_M);

 
// Define L(s),A(s),M(s),C1(s) e C2(s)
Ls = Nps*Dpsbarra;
As = 11.457485 + s;
Ms = s - 8.3606524;
C1s = syslin('c',Ls,As);
C2s = syslin('c',Ms,As);
disp('C1s:'); disp(C1s);
disp('C2s:'); disp(C2s);

// Define C(s)
Cs = C1s - C2s
disp('Cs:'); disp(Cs);