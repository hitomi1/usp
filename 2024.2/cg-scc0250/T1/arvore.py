import glfw
from OpenGL.GL import *
import OpenGL.GL.shaders
import numpy as np
import math

# Função para gerar vértices do tronco da árvore (retângulo)
def generate_tree_trunk_vertices(width=0.2, height=0.6, offset_y=-0.5):
    vertices = [
        -width / 2, -height / 2 + offset_y,  # canto inferior esquerdo
        width / 2, -height / 2 + offset_y,   # canto inferior direito
        -width / 2, height / 2 + offset_y,   # canto superior esquerdo
        
        width / 2, -height / 2 + offset_y,   # canto inferior direito
        width / 2, height / 2 + offset_y,    # canto superior direito
        -width / 2, height / 2 + offset_y    # canto superior esquerdo
    ]
    return np.array(vertices, dtype=np.float32)

# Função para gerar vértices das folhas da árvore (círculo)
def generate_tree_leaves_vertices(radius=0.3, segments=30):
    vertices = []
    for i in range(segments):
        angle1 = 2 * math.pi * i / segments
        angle2 = 2 * math.pi * (i + 1) / segments
        x0, y0 = 0.0, 0.0
        x1, y1 = radius * math.cos(angle1), radius * math.sin(angle1)
        x2, y2 = radius * math.cos(angle2), radius * math.sin(angle2)
        vertices.extend([x0, y0, x1, y1, x2, y2])
    return np.array(vertices, dtype=np.float32)

# Inicializando janela
glfw.init()
glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
window = glfw.create_window(720, 600, "Árvore", None, None)
glfw.make_context_current(window)

# GLSL (Vertex Shader e Fragment Shader para tronco e folhas)
vertex_code = """
        attribute vec2 position;
        void main(){
            gl_Position = vec4(position, 0.0, 1.0);
        }
        """

fragment_code_trunk = """
        uniform vec3 trunkColor;
        void main(){
            gl_FragColor = vec4(trunkColor, 1.0); // Cor do tronco
        }
        """

fragment_code_leaves = """
        uniform vec3 leavesColor;
        void main(){
            gl_FragColor = vec4(leavesColor, 1.0); // Cor das folhas
        }
        """

# Compilando shaders para tronco e folhas
vertex_shader = OpenGL.GL.shaders.compileShader(vertex_code, GL_VERTEX_SHADER)
fragment_shader_trunk = OpenGL.GL.shaders.compileShader(fragment_code_trunk, GL_FRAGMENT_SHADER)
fragment_shader_leaves = OpenGL.GL.shaders.compileShader(fragment_code_leaves, GL_FRAGMENT_SHADER)

shader_trunk = OpenGL.GL.shaders.compileProgram(vertex_shader, fragment_shader_trunk)
shader_leaves = OpenGL.GL.shaders.compileProgram(vertex_shader, fragment_shader_leaves)

# Gerando os vértices do tronco e das folhas
vertices_trunk = generate_tree_trunk_vertices()
vertices_leaves = generate_tree_leaves_vertices()

# Criando buffers para o tronco e para as folhas
vertex_buffer_trunk = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_trunk)
glBufferData(GL_ARRAY_BUFFER, vertices_trunk.nbytes, vertices_trunk, GL_STATIC_DRAW)

vertex_buffer_leaves = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_leaves)
glBufferData(GL_ARRAY_BUFFER, vertices_leaves.nbytes, vertices_leaves, GL_STATIC_DRAW)

# Configuração de antialiasing
glEnable(GL_MULTISAMPLE)

# Exibindo a janela
glfw.show_window(window)

# Loop principal da janela
while not glfw.window_should_close(window):
    glfw.poll_events()

    glClear(GL_COLOR_BUFFER_BIT)
    glClearColor(1.0, 1.0, 1.0, 1.0)  # Cor de fundo branca
    
    # Desenha o tronco
    glUseProgram(shader_trunk)
    glUniform3f(glGetUniformLocation(shader_trunk, 'trunkColor'), 0.55, 0.27, 0.07)  # Cor marrom
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_trunk)
    position = glGetAttribLocation(shader_trunk, 'position')
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_TRIANGLES, 0, len(vertices_trunk) // 2)

    # Desenha as folhas
    glUseProgram(shader_leaves)
    glUniform3f(glGetUniformLocation(shader_leaves, 'leavesColor'), 0.0, 0.8, 0.0)  # Cor verde
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_leaves)
    position = glGetAttribLocation(shader_leaves, 'position')
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_TRIANGLES, 0, len(vertices_leaves) // 2)

    glfw.swap_buffers(window)

# Finalizando
glfw.terminate()
