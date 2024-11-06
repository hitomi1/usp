import glfw
import numpy as np
from OpenGL.GL import glBegin, glEnd, glVertex2f, glColor3f, glClear, glTranslatef, glRotatef, glScalef, glPushMatrix, \
    glPopMatrix, glPolygonMode, GL_COLOR_BUFFER_BIT, GL_POLYGON, GL_TRIANGLES, GL_FRONT_AND_BACK, GL_LINE, GL_FILL

# from OpenGL.GLU import *

# Variáveis globais para controlar transformações
translation = [0.0, 0.0]
scale = [1.0, 1.0]
rotation = 0

wireframe = False


def init_window():
    if not glfw.init():
        return None
    window = glfw.create_window(800, 600, "OpenGL Transformations", None, None)
    if not window:
        glfw.terminate()
        return None
    glfw.make_context_current(window)

    return window


def draw_star():
    glBegin(GL_POLYGON)
    glColor3f(1, 0, 0)
    for i in range(5):
        angle = i * 2 * np.pi / 5
        glVertex2f(np.cos(angle), np.sin(angle))
    glEnd()


def draw_flag():
    glBegin(GL_TRIANGLES)
    glColor3f(0, 1, 0)
    glVertex2f(0, 0)
    glVertex2f(0.5, 0.1)
    glVertex2f(0.5, -0.1)
    glEnd()


def draw_scene():
    global translation, scale, rotation, wireframe

    glClear(GL_COLOR_BUFFER_BIT)

    # Aplicar a transformação de translação
    glPushMatrix()
    glTranslatef(translation[0], translation[1], 0)

    # Aplicar a transformação de rotação

    glRotatef(rotation, 0, 0, 1)

    # Aplicar a transformação de escala
    glScalef(scale[0], scale[1], 1)

    # Desenhar estrela
    draw_star()

    # Resetar a matriz para a próxima forma
    glPopMatrix()

    # Desenhar um catavento em outra posição
    glPushMatrix()
    glTranslatef(-0.5, 0.5, 0)

    draw_flag()
    glPopMatrix()


def key_callback(window, key, scancode, action, mods):
    global translation, scale, rotation, wireframe
    if action == glfw.PRESS or action == glfw.REPEAT:
        if key == glfw.KEY_W:
            translation[1] += 0.1
        elif key == glfw.KEY_S:
            translation[1] -= 0.1
        elif key == glfw.KEY_A:
            translation[0] -= 0.1
        elif key == glfw.KEY_D:
            translation[0] += 0.1
        elif key == glfw.KEY_UP:
            scale[1] += 0.1
        elif key == glfw.KEY_DOWN:
            scale[1] -= 0.1
        elif key == glfw.KEY_LEFT:
            scale[0] -= 0.1
        elif key == glfw.KEY_RIGHT:
            scale[0] += 0.1
        elif key == glfw.KEY_R:
            rotation += 10

        elif key == glfw.KEY_P:
            wireframe = not wireframe

            if wireframe:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
            else:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)


def main():
    window = init_window()
    if not window:
        return

    glfw.set_key_callback(window, key_callback)

    while not glfw.window_should_close(window):
        draw_scene()
        glfw.swap_buffers(window)
        glfw.poll_events()

    glfw.terminate()


if __name__ == "__main__":
    main()
