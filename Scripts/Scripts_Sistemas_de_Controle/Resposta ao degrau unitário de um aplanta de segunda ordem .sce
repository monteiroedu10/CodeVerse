// Limpa as variáveis da área de trabalho
clear;

// Define o operador de Laplace 's' para representar variáveis complexas
s = %s;

// Define o numerador da função de transferência como 10.19
num = 10.19;

// Define o denominador da função de transferência como s^2 + 0.8451s + 9.131
den = s^2 + 0.8451 * s + 9.131;

// Cria a função de transferência G(s) com base nos coeficientes do numerador e denominador
Gs = syslin('c', num, den);

// Define o intervalo de tempo de amostragem como 0.01 segundos
Ts = 0.01;

// Cria um vetor de tempo de 0 a 20 segundos com intervalos de amostragem de 0.01 segundos
t = 0:Ts:20;

// Simula a resposta ao degrau unitário do sistema representado por G(s) ao longo do vetor de tempo 't'
y = csim('step', t, Gs);

// Calcula as características de desempenho
tr = 0; // Tempo de subida (inicialização)
ts = -1; // Tempo de estabilização (inicialização)
Mp = 0; // Sobressinal máximo (inicialização)
tp = 0; // Instante de pico (inicialização)
steady_state_error = 1 - y(length(y)); // Erro em regime permanente

// Calcula o tempo de subida (tr)
for i = 2:length(y)
    if (y(i) >= 0.98 && tr == 0) then
        tr = (i - 1) * Ts;
        break;
    end
end

// Encontra o índice do valor máximo (Instante de pico - tp)
max_value = max(y);
idx = find(y == max_value);
tp = (idx(1) - 1) * Ts;

// Calcula o sobressinal máximo (Mp)
Mp = (max(y) - 1) * 100; // Em percentual

limiar_estabilizacao = 0.98 * y(length(y)); // 98% do valor de regime permanente


for i = length(y):-1:1
    if y(i) <= limiar_estabilizacao then
        ts = t(i);
        break;
    end
end

// Exibe os resultados
disp('Tempo de subida (tr): ' + string(tr) + ' segundos');
disp('Tempo de estabilização (ts): ' + string(ts) + ' segundos');
disp('Instante de pico (tp): ' + string(tp) + ' segundos');
disp('Sobressinal máximo (Mp): ' + string(Mp) + '%');
disp('Erro em regime permanente: ' + string(steady_state_error));

// Plota o gráfico da resposta ao degrau unitário ao longo do tempo
plot(t, y, 'r');
xgrid(); // Adiciona uma grade nos eixos x

// Plota o gráfico do degrau unitário (valor 1 a partir de t = 0)
unit_step = ones(1, length(t)); // Vetor de uns com o mesmo tamanho de t
plot(t, unit_step, 'b--', 'LineWidth', 1.5);

// Adiciona um título ao gráfico
title('Resposta ao degrau unitário de G(s) e Degrau Unitário ao longo do tempo');

// Define o rótulo do eixo x como "Tempo (s)"
xlabel('Tempo (s)');

// Define o rótulo do eixo y como "Saída"
ylabel('Saída');

// Exibe a função de transferência G(s) no gráfico
legendtg['Resposta ao degrau de G(s)', 'Degrau Unitário']);