import math

import glfw
import numpy as np
import OpenGL.GL.shaders
from OpenGL.GL import *


# Função para gerar vértices do corpo da formiga
def generate_ant_body_vertices():
    vertices = []

    # Corpo da formiga (cabeça, tórax e abdômen) como elipses simples
    body_parts = [
        (0.0, 0.0, 0.1),  # Cabeça
        (0.0, -0.15, 0.15),  # Tórax
        (0.0, -0.35, 0.2),  # Abdômen
    ]

    for x, y, radius in body_parts:
        segments = 30
        for i in range(segments):
            angle1 = 2 * math.pi * i / segments
            angle2 = 2 * math.pi * (i + 1) / segments
            x0, y0 = x, y
            x1, y1 = x + radius * math.cos(angle1), y + radius * math.sin(angle1)
            x2, y2 = x + radius * math.cos(angle2), y + radius * math.sin(angle2)
            vertices.extend([x0, y0, x1, y1, x2, y2])

    return np.array(vertices, dtype=np.float32)


# Função para gerar vértices das antenas
def generate_antennas_vertices():
    vertices = []
    segments = 20
    radius = 0.05
    # Antenas
    for i in range(2):
        x, y = (-0.1 + i * 0.2, 0.1)
        for j in range(segments):
            angle1 = 2 * math.pi * j / segments
            angle2 = 2 * math.pi * (j + 1) / segments
            x1, y1 = x + radius * math.cos(angle1), y + radius * math.sin(angle1)
            x2, y2 = x + radius * math.cos(angle2), y + radius * math.sin(angle2)
            vertices.extend([x, y, x1, y1, x2, y2])

    return np.array(vertices, dtype=np.float32)


# Função para gerar vértices das patas
def generate_ant_legs_vertices():
    vertices = []
    leg_length = 0.15  # Comprimento das patas
    leg_width = 0.02
    leg_offset = 0.15  # Distância do corpo
    leg_positions_left = [
        (-leg_offset - leg_width, -0.1),
        (-leg_offset - leg_width, -0.2),
        (-leg_offset - leg_width, -0.3),
    ]  # Posições das patas do lado esquerdo
    leg_positions_right = [
        (leg_offset + leg_width, -0.1),
        (leg_offset + leg_width, -0.2),
        (leg_offset + leg_width, -0.3),
    ]  # Posições das patas do lado direito

    def add_leg(x_offset, y_offset):
        # Cada pata será desenhada como uma linha horizontal
        x1 = x_offset - leg_length / 2
        y1 = y_offset
        x2 = x_offset + leg_length / 2
        y2 = y_offset

        # Adiciona linha
        vertices.extend([x1, y1, x2, y2])

    for pos in leg_positions_left:
        add_leg(pos[0], pos[1])

    for pos in leg_positions_right:
        add_leg(pos[0], pos[1])

    return np.array(vertices, dtype=np.float32)


# Inicializando janela
glfw.init()
glfw.window_hint(glfw.VISIBLE, glfw.FALSE)
window = glfw.create_window(720, 600, "Formiga", None, None)
glfw.make_context_current(window)

# GLSL (Vertex Shader e Fragment Shader para corpo, antenas e patas)
vertex_code = """
        attribute vec2 position;
        void main(){
            gl_Position = vec4(position, 0.0, 1.0);
        }
        """

fragment_code_body = """
        uniform vec3 bodyColor;
        void main(){
            gl_FragColor = vec4(bodyColor, 1.0); // Cor do corpo
        }
        """

fragment_code_antenna = """
        uniform vec3 antennaColor;
        void main(){
            gl_FragColor = vec4(antennaColor, 1.0); // Cor das antenas
        }
        """

fragment_code_leg = """
        uniform vec3 legColor;
        void main(){
            gl_FragColor = vec4(legColor, 1.0); // Cor das patas
        }
        """

# Compilando shaders para corpo, antenas e patas
vertex_shader = OpenGL.GL.shaders.compileShader(vertex_code, GL_VERTEX_SHADER)
fragment_shader_body = OpenGL.GL.shaders.compileShader(
    fragment_code_body, GL_FRAGMENT_SHADER
)
fragment_shader_antenna = OpenGL.GL.shaders.compileShader(
    fragment_code_antenna, GL_FRAGMENT_SHADER
)
fragment_shader_leg = OpenGL.GL.shaders.compileShader(
    fragment_code_leg, GL_FRAGMENT_SHADER
)

shader_body = OpenGL.GL.shaders.compileProgram(vertex_shader, fragment_shader_body)
shader_antenna = OpenGL.GL.shaders.compileProgram(
    vertex_shader, fragment_shader_antenna
)
shader_leg = OpenGL.GL.shaders.compileProgram(vertex_shader, fragment_shader_leg)

# Gerando os vértices do corpo, antenas e patas da formiga
vertices_body = generate_ant_body_vertices()
vertices_antenna = generate_antennas_vertices()
vertices_leg = generate_ant_legs_vertices()

# Criando buffers para o corpo, antenas e patas
vertex_buffer_body = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_body)
glBufferData(GL_ARRAY_BUFFER, vertices_body.nbytes, vertices_body, GL_STATIC_DRAW)

vertex_buffer_antenna = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_antenna)
glBufferData(GL_ARRAY_BUFFER, vertices_antenna.nbytes, vertices_antenna, GL_STATIC_DRAW)

vertex_buffer_leg = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_leg)
glBufferData(GL_ARRAY_BUFFER, vertices_leg.nbytes, vertices_leg, GL_STATIC_DRAW)

# Configuração de antialiasing
glEnable(GL_MULTISAMPLE)

# Exibindo a janela
glfw.show_window(window)

# Loop principal da janela
while not glfw.window_should_close(window):
    glfw.poll_events()

    glClear(GL_COLOR_BUFFER_BIT)
    glClearColor(1.0, 1.0, 1.0, 1.0)  # Cor de fundo branca

    # Desenha o corpo da formiga
    glUseProgram(shader_body)
    glUniform3f(
        glGetUniformLocation(shader_body, "bodyColor"), 0.1, 0.1, 0.1
    )  # Cor preta
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_body)
    position = glGetAttribLocation(shader_body, "position")
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_TRIANGLES, 0, len(vertices_body) // 2)

    # Desenha as antenas da formiga
    glUseProgram(shader_antenna)
    glUniform3f(
        glGetUniformLocation(shader_antenna, "antennaColor"), 0.8, 0.8, 0.0
    )  # Cor amarela
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_antenna)
    position = glGetAttribLocation(shader_antenna, "position")
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_TRIANGLES, 0, len(vertices_antenna) // 2)

    # Desenha as patas da formiga
    glUseProgram(shader_leg)
    glUniform3f(
        glGetUniformLocation(shader_leg, "legColor"), 0.5, 0.5, 0.5
    )  # Cor cinza
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_leg)
    position = glGetAttribLocation(shader_leg, "position")
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_LINES, 0, len(vertices_leg) // 2)

    glfw.swap_buffers(window)

# Finalizando
glfw.terminate()
