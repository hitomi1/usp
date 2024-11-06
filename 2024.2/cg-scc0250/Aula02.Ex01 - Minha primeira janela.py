# # Aula02.Ex01 - Minha primeira janela
# Neste exemplo, nós utilizaremos a biblioteca GLFW para construir nossa primeira janela.
# Esta janela será capaz de processar instruções OpenGL
# ### Primeiro, vamos importar as bibliotecas necessárias.
# Verifique no código anterior um script para instalar as dependências necessárias (OpenGL e GLFW) antes de prosseguir.
import glfw
from OpenGL.GL import *
import OpenGL.GL.shaders
import numpy as np
# ### Inicializando o sistema de janela GLFW
glfw.init()
# ### Criando a primeira janela.
#  Linha 1: indica que a janela será criada mas NÃO será exibida imediatamente.
#  Linha 2: cria a janela com tamanho (width e height) e título da janela. Outros parâmetros definem se a janela será exibida em modo full (tela inteira) e controles de monitor.
#  Linha 3: a janela que criamos será a principal no momento (contexto)
# Mais detalhes: https://www.glfw.org/docs/latest/window_guide.html
glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
window = glfw.create_window(720, 600, "Minha Primeira Janela", None, None)
glfw.make_context_current(window)
# ### Função para capturar eventos de teclado.
# Em determinado momento será interessante tomar decisões com base em entrada do teclado. A função (key_event) é genérica e apenas imprime no terminal quais teclas estão sendo pressionadas.
def key_event(window,key,scancode,action,mods):
    print('[key event] key=',key)
    print('[key event] scancode=',scancode)
    print('[key event] action=',action)
    print('[key event] mods=',mods)
    print('-------')
glfw.set_key_callback(window,key_event)
# ### Função para capturar eventos de mouse.
# Cliques do mouse também serão importantes. A função (mouse_event) apenas exibe qual botão do mouse foi pressionado. De forma análoga, também é possível coletar eventos de coordenadas do ponteiro/cursor do mouse.
# Mais detalhes: https://www.glfw.org/docs/3.3.2/input_guide.html
def mouse_event(window,button,action,mods):
    print('[mouse event] button=',button)
    print('[mouse event] action=',action)
    print('[mouse event] mods=',mods)
    print('-------')
glfw.set_mouse_button_callback(window,mouse_event)
# ### Nesse momento, nós exibimos a janela!
glfw.show_window(window)
# ### Loop principal da janela.
# Enquanto a janela não for fechada, esse laço será executado. É neste espaço que trabalhamos com algumas interações com a OpenGL.
R = 0.2
G = 1.0
B = 1.0
while not glfw.window_should_close(window):
    # funcao interna do glfw para gerenciar eventos de mouse, teclado, etc
    glfw.poll_events() 
    # limpa a cor de fundo da janela e preenche com outra no sistema RGBA
    glClear(GL_COLOR_BUFFER_BIT)   
    # definindo a cor da janela      
    glClearColor(R, G, B, 1.0)
    # gerencia troca de dados entre janela e o OpenGL
    glfw.swap_buffers(window)
# ### Vamos finalizar o sistema de janela GLFW
# O sistema é finalizado assim que a janela é fechada e/ou o laço acima é interrompido.
glfw.terminate()
# # Exercício
# 
# Modifique esse código para que a janela mude de cor dinamicamente, em cada iteração do laço principal
# 
# Dica: incrementar +0.01 as componentes R, G e B até atingir 1.0. Em seguida, faça o processo inverso (-0.01)
