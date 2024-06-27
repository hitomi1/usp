import socket
import subprocess

def process_command(command):
    # Chamar o programa C com os argumentos via subprocess
    result = subprocess.run(['./main'], input=command, text=True, capture_output=True)
    
    return result.stdout

# Configurações do servidor
HOST = 'localhost'  # Endereço IP do servidor
PORT = 12345        # Porta que o servidor vai escutar

# Criação do socket TCP/IP
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()

    print(f"Aguardando conexão em {HOST}:{PORT}...")
    
    while True:
        conn, addr = s.accept()
        
        with conn:
            print(f"Conectado por {addr}")
            
            while True:
                # recebe os dados da GUI em Java
                data = conn.recv(1024).decode('utf-8')
                if not data:
                    break
                
                # print(f"Dados recebidos: {data}")

                response = process_command(data)
                # print(response)
    
                # Envia a resposta para GUI em Java
                conn.sendall(response.encode('utf-8'))
