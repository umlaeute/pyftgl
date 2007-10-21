#!/usr/bin/python

import sys

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import FTGL

font = FTGL.PolygonFont(sys.argv[1])
font.FaceSize(32, 72)

def on_display():
    glClear(GL_COLOR_BUFFER_BIT)
    glPushMatrix()
    font.Render("Foo")
    glPopMatrix()
    glutSwapBuffers()
    glutPostRedisplay()

def on_key(key, x, y):
    glutLeaveGameMode()

if __name__ == '__main__':
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_ACCUM)
    glutGameModeString("1280x1024")
    glutEnterGameMode()
    
    glutDisplayFunc(on_display)
    glutKeyboardUpFunc(on_key)
    
    glDisable(GL_LIGHTING)
    glDisable(GL_DEPTH_TEST)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glViewport(0, 0, 1280, 1024)
    gluOrtho2D(0, 1280, 1024, 0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    glutMainLoop()
