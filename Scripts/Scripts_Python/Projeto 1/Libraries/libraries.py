import importlib
import subprocess

def check_install_library(library_name):
    try:
        # Tenta importar a biblioteca
        importlib.import_module(library_name)
        print(f"A biblioteca {library_name} está instalada.")
    except ImportError:
        # Se a biblioteca não estiver instalada, pede permissão para instalar
        resposta = input(f"A biblioteca {library_name} não está instalada. Deseja instalá-la? (s/n): ")
        if resposta.lower() == 's':
            subprocess.run(['pip', 'install', library_name])
            print(f"A biblioteca {library_name} foi instalada com sucesso.")
        else:
            print(f"A biblioteca {library_name} não foi instalada.") 


if __name__ == "__main__":
    check_install_library('numpy')
