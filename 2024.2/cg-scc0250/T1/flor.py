import glfw
from OpenGL.GL import *
import OpenGL.GL.shaders
import numpy as np
import math

# Função para gerar vértices de pétalas mais suaves
def generate_smooth_petal_vertices(petals, outer_radius=0.5, inner_radius=0.2, arc_subdivisions=40):
    vertices = []
    angle_step = 2 * math.pi / petals
    
    for i in range(petals):
        start_angle = i * angle_step
        mid_angle = start_angle + angle_step / 2
        end_angle = start_angle + angle_step
        
        for j in range(arc_subdivisions):
            angle1 = start_angle + j * (mid_angle - start_angle) / arc_subdivisions
            angle2 = start_angle + (j + 1) * (mid_angle - start_angle) / arc_subdivisions
            
            x1, y1 = inner_radius * math.cos(angle1), inner_radius * math.sin(angle1)
            x2, y2 = outer_radius * math.cos(mid_angle), outer_radius * math.sin(mid_angle)
            x3, y3 = inner_radius * math.cos(angle2), inner_radius * math.sin(angle2)
            
            vertices.extend([0.0, 0.0, x1, y1, x2, y2])
            vertices.extend([0.0, 0.0, x2, y2, x3, y3])
    
    return np.array(vertices, dtype=np.float32)

# Função para gerar o miolo da flor (círculo no centro)
def generate_circle_vertices(radius=0.1, segments=30):
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
window = glfw.create_window(720, 600, "Flor Melhorada", None, None)
glfw.make_context_current(window)

# GLSL (Vertex Shader e Fragment Shader para pétalas e miolo)
vertex_code = """
        attribute vec2 position;
        uniform mat3 model;
        void main(){
            vec3 pos = model * vec3(position, 1.0);
            gl_Position = vec4(pos.xy, 0.0, 1.0);
        }
        """

fragment_code_petals = """
        uniform vec3 petalColor;
        void main(){
            gl_FragColor = vec4(petalColor, 1.0); // Cor das pétalas
        }
        """

fragment_code_center = """
        void main(){
            gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0); // Cor amarela para o miolo
        }
        """

# Compilando shaders para pétalas e miolo
vertex_shader = OpenGL.GL.shaders.compileShader(vertex_code, GL_VERTEX_SHADER)
fragment_shader_petals = OpenGL.GL.shaders.compileShader(fragment_code_petals, GL_FRAGMENT_SHADER)
fragment_shader_center = OpenGL.GL.shaders.compileShader(fragment_code_center, GL_FRAGMENT_SHADER)

shader_petals = OpenGL.GL.shaders.compileProgram(vertex_shader, fragment_shader_petals)
shader_center = OpenGL.GL.shaders.compileProgram(vertex_shader, fragment_shader_center)

# Gerando os vértices das pétalas arredondadas e do miolo
vertices_petals = generate_smooth_petal_vertices(8)
vertices_center = generate_circle_vertices()

# Criando buffers para as pétalas e para o miolo
vertex_buffer_petals = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_petals)
glBufferData(GL_ARRAY_BUFFER, vertices_petals.nbytes, vertices_petals, GL_STATIC_DRAW)

vertex_buffer_center = glGenBuffers(1)
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_center)
glBufferData(GL_ARRAY_BUFFER, vertices_center.nbytes, vertices_center, GL_STATIC_DRAW)

# Configuração de antialiasing
glEnable(GL_MULTISAMPLE)

# Inicializando a escala da flor e rotação
scale = 1.0
rotation_angle = 0.0
scale_step = 0.0001
rotation_step = 0.01 * math.pi / 180.0  # 1 grau em radianos

# Exibindo a janela
glfw.show_window(window)

# Loop principal da janela
while not glfw.window_should_close(window):
    glfw.poll_events()

    # Verifica se as teclas A ou S foram pressionadas para escala
    if glfw.get_key(window, glfw.KEY_Z) == glfw.PRESS:
        scale += scale_step
    if glfw.get_key(window, glfw.KEY_X) == glfw.PRESS:
        scale -= scale_step
        if scale < 0.1:  # Evita que a flor diminua demais
            scale = 0.1

    # Verifica se as teclas Z ou X foram pressionadas para rotação
    if glfw.get_key(window, glfw.KEY_A) == glfw.PRESS:
        rotation_angle += rotation_step
    if glfw.get_key(window, glfw.KEY_S) == glfw.PRESS:
        rotation_angle -= rotation_step

    glClear(GL_COLOR_BUFFER_BIT)
    glClearColor(1.0, 1.0, 1.0, 1.0)  # Cor de fundo branca

    # Cria a matriz de escala
    scale_matrix = np.array([
        [scale, 0.0, 0.0],
        [0.0, scale, 0.0],
        [0.0, 0.0, 1.0]
    ], dtype=np.float32)

    # Cria a matriz de rotação
    cos_angle = math.cos(rotation_angle)
    sin_angle = math.sin(rotation_angle)
    rotation_matrix = np.array([
        [cos_angle, -sin_angle, 0.0],
        [sin_angle, cos_angle, 0.0],
        [0.0, 0.0, 1.0]
    ], dtype=np.float32)

    # Combina a matriz de escala e rotação
    model_matrix = np.dot(rotation_matrix, scale_matrix)

    # Desenha as pétalas
    glUseProgram(shader_petals)
    glUniform3f(glGetUniformLocation(shader_petals, 'petalColor'), 0.8, 0.1, 0.5)  # Cor rosa
    glUniformMatrix3fv(glGetUniformLocation(shader_petals, 'model'), 1, GL_FALSE, model_matrix)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_petals)
    position = glGetAttribLocation(shader_petals, 'position')
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_TRIANGLES, 0, len(vertices_petals) // 2)

    # Desenha o miolo
    glUseProgram(shader_center)
    glUniformMatrix3fv(glGetUniformLocation(shader_center, 'model'), 1, GL_FALSE, model_matrix)
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_center)
    position = glGetAttribLocation(shader_center, 'position')
    glEnableVertexAttribArray(position)
    glVertexAttribPointer(position, 2, GL_FLOAT, False, 0, None)
    glDrawArrays(GL_TRIANGLES, 0, len(vertices_center) // 2)

    glfw.swap_buffers(window)

# Finalizando
glfw.terminate()
