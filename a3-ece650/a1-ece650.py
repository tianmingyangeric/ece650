#!/usr/bin/python

from __future__ import division
import re
import os
import sys
class Container(object):
	def __init__(self):
		self.street_dict = {} # a container contain street name and points {"Weber Street" : (2,1) (2,2)}
		self.Intersections_dict = {} # street number and coordinate {(2,2) : 1}

class Command_Line(Container):

	def pharse_command(self):
		command = raw_input()
		command = command.lower()
		if command == 'g':
			self.generate_graph()
		elif re.match(r'[ac]\s["](.*)["]\s[(](.*)[)]',command) != None:
			self.command_list = command.split('"')
			self.called_func = self.command_list[0].strip()
			self.street_name = self.command_list[1]
			if re.match(r'^[A-Za-z\s]*$', self.street_name) != None:
				if self.called_func == 'a' or self.called_func == 'c':
					self.street_co = self.command_list[2].split()
					if self.street_co:
						for check_coord in self.street_co:
							if re.search(r'[(](.*)[,](.*)[)]', check_coord) == None:
								print "Error: street or coordinate format is wrong"
								break
							elif self.called_func == 'a':
								self.add_street()
							elif self.called_func == 'c':
								self.change_street()
					else:
						print "Error: street coordinate is empty"
			else:
				print "Error: The format of you command is wrong+++"
		elif re.match(r'[r]\s["](.*)["]',command) != None:
			self.command_list = command.split('"')
			self.called_func = self.command_list[0].strip()
			self.street_name = self.command_list[1]
			self.remove_street()
		else:
			print "Error: The format of you command is wrong"
	def add_street(self):
		"""input a street name and a coordinate"""
		try :
			self.street_dict.update({self.street_name:self.street_co})
		except AttributeError:
			print "Error: For 'a', you should input street name, coordinate"

	def remove_street(self):
		"""use to remove a street"""
		try:
			del self.street_dict[self.street_name]
		except AttributeError:
			print "Error: 'c' or 'r' specified for a street"
		except KeyError:
			print "Error: 'c' or 'r' specified for a street that does not exist."

	def change_street(self):
		"""use to change a street"""
		try:
			if self.street_dict.has_key(self.street_name):
				self.street_dict[self.street_name] = self.street_co
			else:
				print "Error: 'c' specified for a street that does not exist."
		except AttributeError:
			print "Error: 'c' specified for a street that does not exist."
	def generate_graph(self):
		""" plot street graph """
		street_list = []
		for keys, values in self.street_dict.iteritems():
			coordinate_list=[]
			for coordinate in values:
				coordinate =  coordinate.replace('(','').replace(')','').split(',')
				coordinate_list.append(coordinate)
			street_list.append(coordinate_list)
		f = Find_Intersec()
		inter_set,inter_dict = f.get_intersect_points(street_list) # calculate intersects after plot
		f.output_line(inter_set,self.Intersections_dict,inter_dict)

class Cross():
	def __init__(self,x,y):
		self.x=x
		self.y=y   

class Find_Intersec(object):
	def cross(self,p1,p2,p3):
		x1,y1,x2,y2 = p2.x-p1.x, p2.y-p1.y, p3.x-p1.x, p3.y-p1.y
		return x1*y2-x2*y1

	def IsIntersec(self,p1,p2,p3,p4):
	    if(max(p1.x,p2.x)>=min(p3.x,p4.x) and max(p3.x,p4.x)>=min(p1.x,p2.x) and max(p1.y,p2.y)>=min(p3.y,p4.y) and max(p3.y,p4.y)>=min(p1.y,p2.y)):
	        if(self.cross(p1,p2,p3)*self.cross(p1,p2,p4)<=0
	           and self.cross(p3,p4,p1)*self.cross(p3,p4,p2)<=0):
	            result=True
	        else:
	            result=False
	    else:
	        result=False
	    return result

	def find_intersect(self,line1,line2):
		""" find intersect point and return  """
		x1,y1,z1 = line1[0][1] - line1[1][1], line1[1][0] - line1[0][0],line1[0][0] * line1[1][1] - line1[1][0] * line1[0][1]
		x2,y2,z2 = line2[0][1] - line2[1][1], line2[1][0] - line2[0][0],line2[0][0] * line2[1][1] - line2[1][0] * line2[0][1]
		d = x1 * y2 - x2 * y1
		point = [0,0]
		try:		
			point[0] = (y1 * z2 - y2 * z1)/ d
			point[1] = (z1 * x2 - z2 * x1)/ d
		except ZeroDivisionError:
			return False
		return point

	def get_intersect_points(self,street_list):
		""" calculate intersect for each two line   """
		Intersections_set = set()
		inter_dict = {}
		p1=p2=p3=p4= [0,0]
		counter_b = len(street_list)
		counter = 1
		for x in range(0,counter_b-1):
			for y in range(counter, counter_b):
				for m in (street_list[x]):
					if m == street_list[x][0]:
						tmp_m = m
						continue
					[p1,tmp_m,p2] = [tmp_m,m,m]
					for n in street_list[y]:
						if n == street_list[y][0]:
							tmp_n = n 
							continue
						[p3,tmp_n,p4] = [tmp_n,n,n]
						[line1,line2] = [[[int(p1[0]),int(p1[1])],[int(p2[0]),int(p2[1])]],[[int(p3[0]),int(p3[1])],[int(p4[0]),int(p4[1])]]]
						[l1,l2,l3,l4] = [Cross(int(p1[0]),int(p1[1])),Cross(int(p2[0]),int(p2[1])),Cross(int(p3[0]),int(p3[1])),Cross(int(p4[0]),int(p4[1]))]
						f = Find_Intersec()

						if f.IsIntersec(l1,l2,l3,l4) and f.find_intersect(line1,line2) != False: # if Intersec
							[set_1,set_2,set_3,set_4] = [(int(p1[0]),int(p1[1])),(int(p2[0]),int(p2[1])),(int(p3[0]),int(p3[1])),(int(p4[0]),int(p4[1]))]
							for setx in [set_1,set_2,set_3,set_4]:
								if setx not in Intersections_set:
									Intersections_set.add(setx) # intersect set , store all useful points
							inter_point =  f.find_intersect(line1,line2)
							Intersections_set.add((inter_point[0],inter_point[1]))
							for p_1,p_2 in [set_1,set_2], [set_3,set_4]:
								if (p_1,p_2) not in inter_dict.keys(): # inter_dict, store two side point of a line and intersects {(1,2),(2,3): (4,4)}
									inter_dict[(p_1,p_2)] = [inter_point]
								elif inter_point not in inter_dict[(p_1,p_2)]:
									empty_list = []
									for xx in inter_dict[(p_1,p_2)]:
										empty_list.append(xx)
									empty_list.append(inter_point)
									inter_dict[(p_1,p_2)] = empty_list
			counter = counter + 1
		return Intersections_set,inter_dict

	def output_line(self,Intersections_set,Intersections_dict,inter_dict):
		for key in Intersections_dict.keys():
			if key not in Intersections_set:
				del Intersections_dict[key]
		for point in Intersections_set:
			if point not in Intersections_dict.keys():
				for counter_point in range(1,len(Intersections_set)+1):
					if counter_point not in Intersections_dict.values():
						Intersections_dict[point] = counter_point
						break
		dict_list = []
		for key,value in Intersections_dict.iteritems():
			dict_list.append(value)
			dict_list.sort()
		max_value = 0
		for num in dict_list:
			for key, value in Intersections_dict.iteritems():
				if num == value:
					if max_value < int(value):
						max_value = int(value)
		print 'V ' + str(max_value+1)
		sys.stdout.flush()
		edge_string = "E {" 
		for key,value in inter_dict.iteritems():
			for x in key:
				value.append(list(x))
				value.sort()
			for v in range(0,len(value)-1):
				if (value[v][0] != value[v+1][0]) or (value[v][1] != value[v+1][1]):
					if edge_string != "E {" :
						edge_string = edge_string + ','
					edge_string = edge_string +  '<' + str(Intersections_dict[value[v][0],value[v][1]]) +','+  str(Intersections_dict[value[v+1][0],value[v+1][1]]) + '>'
		print edge_string  + '}'
		sys.stdout.flush()
		
if __name__=="__main__":
	try:
		T= Command_Line()
		while True:
			T.pharse_command()
	except EOFError, KeyboardInterrupt:
		sys.exit()









