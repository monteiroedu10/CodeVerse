import sys
import os

def run_check_libraries():
    # Adiciona o caminho do diretório do módulo1 ao sys.path
    dir_mod = os.path.join(os.path.dirname(__file__), "..", "Libraries")
    sys.path.append(dir_mod)

    # Importa e executa a função do módulo1
    from Libraries import check_install_library
    
    # Todas as bibliotecas utilizadas
    libraries_names = ["pandas", "numpy", "tqdm", "time", "pathlib", "keras", "tensorflow"]

    for library_name in libraries_names:
        check_install_library(library_name)

    # Remove o caminho adicionado ao sys.path
    sys.path.remove(dir_mod)