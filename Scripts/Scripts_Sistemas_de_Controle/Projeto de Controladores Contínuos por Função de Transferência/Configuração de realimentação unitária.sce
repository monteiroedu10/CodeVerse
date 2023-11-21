// Limpa as variáveis da área de trabalho
clear;

// Limpa a janela de gráficos
clf;

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
num = 10.19; 
 
// Define o denominador da função de transferência G(s)  
den = s^2 + 0.8451 * s + 9.131; 
 
// Cria a função de transferência G(s) com base nos coeficientes do numerador e denominador 
Gs = syslin('c', num, den); 

// Acha o G0(s) usando os parâmetros Qsi_G0 e OmegaN_G0
NG0 = OmegaN_G0^2;
DG0 = (s^2 + 2 * Qsi_G0 * OmegaN_G0 * s + OmegaN_G0^2);
G0 = syslin('c',NG0,DG0);

// Calcula o controlador C(s)
Cs = G0/(Gs*(1-G0));

// Exibe as funções de transferência G0(s), G(s) e C(s)
disp('G0(s):'); disp(G0);
disp('G(s):'); disp(Gs);
disp('C(s):'); disp(Cs);