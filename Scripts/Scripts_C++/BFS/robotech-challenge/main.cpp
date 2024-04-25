#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <tuple>

using namespace std;

// Definição de direções possíveis para o movimento do rato
const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

// Função para verificar se uma posição está dentro dos limites do labirinto
bool isValid(int x, int y, int M, int N) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

// Função para encontrar o caminho do rato através do labirinto
vector<pair<int, int>> findPath(const vector<vector<int>>& maze, pair<int, int> start, string outputFilename) {
    int M = maze.size();
    int N = maze[0].size();
    
    // Vetor para marcar as células já visitadas
    vector<vector<bool>> visited(M, vector<bool>(N, false));
    
    // Fila para armazenar as posições a serem exploradas na busca em largura
    queue<pair<int, int>> q;
    // Mapa para armazenar o caminho percorrido pelo rato
    vector<vector<pair<int, int>>> parent(M, vector<pair<int, int>>(N, {-1, -1}));

    ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída " << outputFilename << endl;
        return {};
    }


    cout << "\n\n\n" << endl;
    cout << "RRRRRRR   OOOOOOO  BBBBBBBB  OOOOOOO  TTTTTTTTT  EEEEEEEE  CCCCCCCC  H     H  \n";
    cout << "RR    RR OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    cout << "RR     RR OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    cout << "RR    RR  OO     OO BBBBBBBB  OO     OO    TT     EEEEEEE   CC       HHHHHHH  \n";
    cout << "RRRRRRR   OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    cout << "RR   RR   OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    cout << "RR    RR   OOOOOOO  BBBBBBBB   OOOOOOO     TT     EEEEEEEE  CCCCCCCC H     H  \n";
    cout << "\n\n\n" << endl;

    outputFile << "\n\n\n" << endl;
    outputFile << "RRRRRRR   OOOOOOO  BBBBBBBB  OOOOOOO  TTTTTTTTT  EEEEEEEE  CCCCCCCC  H     H  \n";
    outputFile << "RR    RR OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    outputFile << "RR     RR OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    outputFile << "RR    RR  OO     OO BBBBBBBB  OO     OO    TT     EEEEEEE   CC       HHHHHHH  \n";
    outputFile << "RRRRRRR   OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    outputFile << "RR   RR   OO     OO BB     BB OO     OO    TT     EE        CC       H     H  \n";
    outputFile << "RR    RR   OOOOOOO  BBBBBBBB   OOOOOOO     TT     EEEEEEEE  CCCCCCCC H     H  \n";
    outputFile << "\n\n\n" << endl;


    cout << "Olá, iniciando a resolução do desafio de  programação da Robotceh: " << endl;
    outputFile << "Olá, iniciando a resolução do desafio de  programação da Robotceh: " << endl;

    cout << "\n\tEvolução temporal salva em " << outputFilename << endl;
    outputFile << "\n\tEvolução temporal salva em " << outputFilename << endl;

    cout << "\n" << endl;
    outputFile << "\n" << endl;

    q.push(start);
    visited[start.first][start.second] = true;

    int iteration = 1;
    // Realiza a busca em largura
    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        int x = current.first;
        int y = current.second;

        // Escreve a evolução temporal do rato no arquivo de saída
        outputFile << "\t\ti = " << iteration << "; pos = [" << x + 1<< "," << y + 1<< "]" << endl;
        cout << "\t\ti = " << iteration << "; pos = [" << x + 1<< "," << y + 1<< "]" << endl;
        iteration++;

        // Verifica se chegou à saída
        if(maze[x][y] == 3){
            vector<pair<int, int>> path;
            // Reconstrói o caminho percorrido pelo rato
            while (current != start) {
                path.push_back(current);
                current = parent[current.first][current.second];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            // Escreve o caminho encontrado no arquivo de saída
            cout << "\n\tMelhor Caminho Encontrado, a seguir: " << endl;
            outputFile << "\n\tMelhor Caminho Encontrado, a seguir: " << endl;

            cout << "\n" << endl;
            outputFile << "\n" << endl;
            
            for (const auto& p : path) {
                
                outputFile << "\t\t(" << p.first + 1<< ", " << p.second + 1<< ")" << endl;
                cout << "\t\t(" << p.first + 1<< ", " << p.second + 1<< ")" << endl;

            }
            cout << "\n\a~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fim ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            outputFile << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Labirinto ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;

            cout << "\n\n" << endl;
            outputFile << "\n\n" << endl;

            for (const auto& row : maze) {
                for (auto it = row.begin(); it != row.end() - 1; ++it) {
                    outputFile << *it << " ";
                }
                outputFile << endl;
            }

            outputFile << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fim ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;


            outputFile.close();
            return path;
        }

        // Explora todas as direções possíveis
        for (const auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;

            // Verifica se a nova posição é válida, não é uma parede e não foi visitada
            if (isValid(newX, newY, M, N) && maze[newX][newY] != 1 && !visited[newX][newY]) {
                q.push({newX, newY});
                visited[newX][newY] = true;
                parent[newX][newY] = {x, y};
            }
        }
    }

    // Se não foi possível encontrar um caminho até a saída
    outputFile.close();
    return {};
}

// Função para ler o labirinto de um arquivo de texto
vector<vector<int>> readMazeFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> maze;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<int> row;
            for (char c : line) {
                row.push_back(c - '0');
            }
            maze.push_back(row);
        }
        file.close();
    } else {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
    }
    return maze;
}

int main() {
    // Nome do arquivo contendo o labirinto
    string filename = "maze.txt";
    // Nome do arquivo de saída
    string outputFilename = "temporal_evolution.txt";

    // Lê o labirinto do arquivo
    vector<vector<int>> maze = readMazeFromFile(filename);

    pair<int, int> start;

    // Encontra a posição inicial do rato e verifica se existe apenas uma
    int startCount = 0;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 2) {
                start = {i, j};
                startCount++;
            }
        }
    }
    if (startCount != 1) {
        cerr << "Erro: O labirinto deve conter exatamente um ponto inicial (valor 2)." << endl;
        return 1;
    }

    // Encontra o caminho do rato até a saída
    vector<pair<int, int>> path = findPath(maze, start, outputFilename);

    return 0;
}
