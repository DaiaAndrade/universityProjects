# coding=utf-8
#!/usr/bin/python
# -*- coding: utf-8 -*-

#	Universidade Federal de Pelotas
#	Bacharelado em Ciencia da Computação
#	Trabalho de Arquitetura e Organização de Computadores II
#	Cache Nível I de Instruções e Dados
#	Daiane Focking Andrade
# 	Última Modificação Feita em 13.02.2014


from __future__ import with_statement
import math
import sys
import random
import numpy as np

class Cache(object):
	_offset = 0
	_indice = 0
	_sets = 0
	_associatividade = 0
	_hit = 0
	_missCompulsorio = 0
	_missConflito = 0
	_estado = None

	def __init__(self,nSets,bSize,associatividade,dados):
		self._associatividade = associatividade
		self._offset = int(math.log(bSize,2))
		self._indice = int(math.log(nSets/associatividade,2))
		self._sets = nSets

		self._estado = dados

		self._validade = [None] * (nSets * associatividade)
		for i in range (0,nSets-1):
			self._validade[i] = False
		self._tag = [None] * (nSets * associatividade)


	def _mapeamentoDireto(self, valor):
		tag = int((valor >> (self._offset+self._indice)))
		indice = int((valor >> self._offset)&int((math.pow(2, self._indice)-1)))
		
		if(self._validade[indice] == False) & (self._tag[indice] == None):
			self._validade[indice] = True
			self._tag[indice] = tag
			self._missCompulsorio += 1
		elif(self._validade[indice] == True) & (self._tag[indice] == tag):
			self._hit += 1
		else:
			self._validade[indice] = True
			self._tag[indice] = tag
			self._missConflito += 1

	def _mapeamentoAssociativo(self, valor):
		tag = int((valor >> (self._offset+self._indice)))
		index = int((valor >> self._offset)&int((math.pow(2, self._indice)-1)))
		NewIndex = index
		##if((self._validade[index] == False) & (self._tag[index] == None)):
		##	self._validade[index] = True
		##	self._tag[index] = tag
		##	self._missCompulsorio += 1
		##elif((self._validade[index] == True) & (self._tag[index] == tag)):
		##	self._hit += 1
		##else:
		for i in range(0,self._associatividade-1):
			NewIndex = NewIndex + 1
			if((self._validade[NewIndex] == False) & (self._tag[NewIndex] == None)):
				self._validade[NewIndex] = True
				self._tag[NewIndex] = tag
				self._missCompulsorio += 1
				state = True
			elif((self._validade[NewIndex] == True) & (self._tag[NewIndex] == tag)):
				self._hit += 1
				state = True
			else:
				newIndex = random.randint(0,self._associatividade - 1)
				self._validade[index*newIndex] = True
				self._tag[index*newIndex] = tag
				self._missConflito += 1
				state = True
			if(state == True):
				break


	def _cacheInstrucRun(self,arquivo):
		stream = arquivo
		line = stream.readline()
		while (line != ''):
			if (self._associatividade == 1):
				self._mapeamentoDireto(int(line))
				line = stream.readline()
				line = stream.readline()
			else:
				self._mapeamentoAssociativo(int(line))
				line = stream.readline()
				line = stream.readline()
			

	def _cacheDadosRun(self,arquivo):
		stream = arquivo
		line = stream.readline()
		line = stream.readline()
		while (line != ''):
			if(int(line) == 0):
				line = stream.readline()
				line = stream.readline()
			else:
				if (self._associatividade == 1):
					self._mapeamentoDireto(int(line))
					line = stream.readline()
					line = stream.readline()
				else:
					self._mapeamentoAssociativo(int(line))
					line = stream.readline()
					line = stream.readline()

##	ARRUMAR PARA LER EM BINÁRIO E E 32 EM 32 BITS 	##
	def run(self, arquivo):
		stream = open(arquivo, 'r')
		if (self._estado == True) :
			self._cacheInstrucRun(stream)
		else:
			self._cacheDadosRun(stream)

		print "Misses compulsórios:", self._missCompulsorio
		print "Misses de conflito:", self._missConflito
		print "Total de Misses (Não está em porcentagem):", (self._missCompulsorio + self._missConflito)
		print "Total de Hits (Não está em porcentagem):", (self._hit)
		stream.close()

#### MAIN ####
parametros = len(sys.argv)

print sys.argv

if (parametros == 2):
	arquivo = sys.argv[1]
	estado1 = True
	estado2 = False
	cacheDados = Cache(1024,4,1,estado2)
	cacheInstru = Cache(1024,4,1,estado1)
else:
	arquivo = sys.argv[7]
	estado1 = True
	estado2 = False
	nSetsDados = int(sys.argv[1])
	nSetsInstru = int(sys.argv[4])
	bSizeDados = int(sys.argv[2])
	bSizeInstru = int(sys.argv[5])
	associatividadeDados = int(sys.argv[3])
	associatividadeInstru = int(sys.argv[6])
	cacheDados = Cache(nSetsDados, bSizeDados, associatividadeDados,estado2)
	cacheInstru = Cache(nSetsInstru,bSizeInstru,associatividadeInstru,estado1)

print "\nCache de Instruções: \n"
cacheInstru.run(arquivo)
print "\nCache de Dados: \n"
cacheDados.run(arquivo)
