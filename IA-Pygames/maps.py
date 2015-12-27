# coding=utf-8
#!/usr/bin/python
# -*- coding: utf-8 -*-

#	Arquivo de teste para pygames
#	Teste número 1:
#	Início

import pygame, sys, math
from pygame.locals import *

class Screen:
	_screen = None
	_screenSizeX = 0
	_screenSizeY = 0
	_screenColor = (0,0,0)
	_screenTransition = None

	def __init__(self):
		self._screenSizeX, self._screenSizeY = 800,576
		self._screenColor = (139,0,0)
		self._screenTransition = False
		self._screen = pygame.display.set_mode((self._screenSizeX, self._screenSizeY))
		self._screen.fill(self._screenColor)
		pygame.display.set_caption('Busca de Caminhos')


	def getScreen(self):
		return self._screen
	def setScreen(self):
		self._screen = pygame.display.set_mode((self._screenSizeX,self._screenSizeY))
	def getSizeX(self):
		return self._screenSizeX
	def getSizeY(self):
		return self._screenSizeY
	def getScreenColor(self):
		return self._screenColor
	def getScreenTransition(self):
		return self._screenTransition
	def setScreenColor(self, color):
		self._screenColor = color
	def setNewScreenColor(self):
		return self._screen.fill(self._screenColor)
	def setScreenTransition(self, state):
		self._screenTransition = state
	def getScreenTransition(self):
		return self._screenTransition

	def run(self):
		while 1:
			for event in pygame.event.get():
				if event.type == QUIT:
					pygame.quit()
					sys.exit()
			pygame.display.flip()
			pygame.display.update()


	def __del__(self):
		self._screen
		self._screenSizeX
		self._screenSizeY
		self._screenColor
		self._screenTransition


class InitialScreen(Screen):

	def loop(self):
		mouseX = 0
		mouseY = 0
		screen = self.getScreen()
		while self.getScreenTransition() == False:
			self.createText()
			for event in pygame.event.get():
				if event.type == QUIT:
					pygame.quit()
					sys.exit()
				elif event.type == MOUSEBUTTONUP:
					mouseX, mouseY = event.pos

				if self.button[0].collidepoint(mouseX,mouseY):
					self.setScreenTransition(True)
					MapCreator(screen)

				elif self.button[1].collidepoint(mouseX,mouseY):
					self.setScreenTransition(True)
					AutoScreen()

				elif self.button[2].collidepoint(mouseX,mouseY):
					pygame.quit()
					sys.exit()

			pygame.display.flip()
			pygame.display.update()

	def createText(self):

		screenColor = self.getScreenColor()
		screen = self.getScreen()

		fontColor = (255,255,255)
		rectColor = (0,0,0)

		font = [None] * 6
		text = [None] * 6
		rectText = [None] * 6
		self.button = [None] * 6

		fontType = './UbuntuMono-B.ttf'

		font[0] = pygame.font.Font(fontType,36)
		text[0] = font[0].render('Algoritmo de Menor Caminho A*', True, fontColor, screenColor)
		rectText[0] = text[0].get_rect()
		rectText[0].center = (400,200)

		self.button[0] = pygame.draw.rect(screen,rectColor,(175,250,140,40)) #X, Y, LARGURA, ALTURA
		self.button[1] = pygame.draw.rect(screen,rectColor,(175,300,140,40))
		self.button[2] = pygame.draw.rect(screen,rectColor,(175,350,140,40))

		font[1] = pygame.font.Font(fontType,12)
		text[1] = font[1].render('Criar um novo mapa', True, fontColor, rectColor)
		rectText[1] = text[1].get_rect()
		rectText[1].center = (245,270)

		font[2] = pygame.font.Font(fontType,14)
		text[2] = font[2].render('Crie seu mapa', True, fontColor, screenColor)
		rectText[2] = text[2].get_rect()
		rectText[2].center = (370,270)

		font[3] = pygame.font.Font(fontType,12)
		text[3] = font[3].render('Gerar um novo mapa', True, fontColor, rectColor)
		rectText[3] = text[3].get_rect()
		rectText[3].center = (245,320)

		font[4] = pygame.font.Font(fontType,14)
		text[4] = font[4].render('Gerar um novo mapa automagicamente', True, fontColor, screenColor)
		rectText[4] = text[4].get_rect()
		rectText[4].center = (445,320)

		font[5] = pygame.font.Font(fontType,12)
		text[5] = font[5].render('Sair', True, fontColor,rectColor)
		rectText[5] = text[5].get_rect()
		rectText[5].center = (245,370)

		for i in range(0,6):
			screen.blit(text[i],rectText[i])


#class Map(Screen):

class MapCreator(Screen):

	def __init__(self,Screen):

		Screen = pygame.display.set_mode((800,576))
		
		pygame.display.flip()
		pygame.display.update()

		screenTile = pygame.Surface(Screen.get_size())
		screenTile = screenTile.convert()
		screenTile = pygame.image.load('Pedra.gif').convert()

		width = 0
		height = 0

		for i in range(0,25):
			Screen.blit(screenTile, (width, height)) ### X,Y
			for j in range(0,18):
				Screen.blit(screenTile, (width, height))
				height = height + 32
			width = width + 32
			height = 0

		pygame.display.flip()
		pygame.display.update()


		tile = pygame.Surface(Screen.get_size())
		tile = pygame.image.load('PedraAreia.gif').convert()
		tile = tile.convert()
		tileType = -1

		positions = [[None]*18]*25

		self.setScreenTransition(False)
		while self.getScreenTransition() == False:
			for event in pygame.event.get():
				if event.type == QUIT:
					pygame.quit()
					sys.exit()
				elif event.type == MOUSEBUTTONUP:
					mouseX, mouseY = event.pos
					mouseX = mouseX/32
					mouseY = mouseY/32
					Screen.blit(tile,(mouseX*32,mouseY*32))
					positions[mouseX][mouseY] = tileType
				elif event.type == KEYDOWN:
					key = pygame.key.get_pressed()

					if pygame.key.get_pressed()[pygame.K_1]:
						tile = pygame.Surface(Screen.get_size())
						tile = pygame.image.load('Pedra.gif').convert()
						tile = tile.convert()
						tileType = 1
					elif pygame.key.get_pressed()[pygame.K_2]:
						tile = pygame.Surface(Screen.get_size())
						tile = pygame.image.load('Lava.gif').convert()
						tile = tile.convert()
						tileType = 2
						
					elif pygame.key.get_pressed()[pygame.K_3]:
						tile = pygame.Surface(Screen.get_size())
						tile = pygame.image.load('Neve.gif').convert()
						tile = tile.convert()
						tileType = 3
						
					elif pygame.key.get_pressed()[pygame.K_4]:
						tile = pygame.Surface(Screen.get_size())
						tile = pygame.image.load('Oceano.gif').convert()
						tile = tile.convert()
						tileType = 4
						
					elif pygame.key.get_pressed()[pygame.K_5]:
						tile = pygame.Surface(Screen.get_size())
						tile = pygame.image.load('Areia.gif').convert()
						tile = tile.convert()
						tileType = 5
					else:
						self.setScreenTransition(True)
			self.run(Screen,positions)
			pygame.display.flip()
			pygame.display.update()


	def run(self,Screen,tilesInfos):
		self.setScreenTransition(False)
		newScreen = Screen

		charList = [pygame.Surface(Screen.get_size())] *3

		charList[1] = pygame.image.load('char5_2.png').convert()
		charList[1] = charList[1].convert()
		charList[1].set_colorkey((255,0,255))
		charListRect = charList[1].get_rect()
		charListRect.y = 32
		charListRect.x = 32

		Screen.blit (charList[1],(32,32))

		pygame.display.update()

		mouseX = 0
		mouseY = 0

		for event in pygame.event.get():
			if event.type == QUIT:
				pygame.quit()
				sys.exit()
			elif event.type == MOUSEBUTTONDOWN:
				mouseX,mouseY = event.pos
				mouseX = (mouseX/32)*32
				mouseY = (mouseX/32)*32
				charListRect.y = (charListRect.y/32)*32
				charListRect.x = (charListRect.x/32)*32
				if((charListRect.y!= mouseY*32 & charListRect.x != mouseX*32)&((charListRect.y-charListRect.x)==0)):
					while(charListRect.y!= mouseY):
				 		charListRect = charListRect.move(32,32)
				 		Screen.blit(charList[1],charListRect)
				 		pygame.display.update()
				 		pygame.time.delay(1)
				else:
				 	while(charListRect.y!= mouseY):
				 		Screen.blit(newScreen,(0,0))
				 		charListRect = charListRect.move(0,32)
				 		Screen.blit(charList[1],charListRect)
				 		pygame.display.update()
				 		pygame.time.delay(1)	
				 	while(charListRect.x != mouseX):
				 		Screen.blit(newScreen,(0,0))
				 		charListRect = charListRect.move(32,0)
				 		Screen.blit(charList[1],charListRect)
				 		pygame.display.update()
				 		pygame.time.delay(1)
			pygame.display.flip()
			pygame.display.update()

def transformCoordenate(xPosition,yPosition):
	for i in range(0,18):
		for j in range(0,25):
			if ((xPosition/32 == i) & (yPosition/32 == j)):
				xPosition = j*32
				yPosition = i*32
	return xPosition,yPosition
