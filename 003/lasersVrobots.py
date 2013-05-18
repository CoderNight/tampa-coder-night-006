
import sys, os, re
from Factory import Factory, Robot

def empty(input_str):
	return not re.sub("\s","",input_str)

def read(filename):
	lines = []
	with open(filename) as layoutFile:
		lines = layoutFile.readlines()
	return lines

def load(filename):
	factory = Factory()
	lines = read(filename)
	lineNumber = 0
	while lineNumber <= len(lines) - 3:
		if empty(lines[lineNumber]):
			lineNumber += 1
		else:
			factory.add_conveyor(lines[lineNumber:lineNumber+3])
			lineNumber += 3
	return factory

def study(factory):
	robert = Robot()
	suzy = Robot()
	conveyors = factory.get_conveyors()
	result = []
	while conveyors.next():
		conveyors.operate(robert,"west")
		if robert.get_damage() == 0:
			result += ["west"]
			continue
		conveyors.operate(suzy,"east")
		if suzy.get_damage() < robert.get_damage():
			result += ["east"]
		else:
			result += ["west"]

	return result

def main(argv):
	if len(argv) != 2:
		print "Usage : python lasersVrobots.py <factory-layout.txt>"
	elif not os.path.isfile(argv[1]):
		print "The file '", argv[1], "' is not a accessible."
	else:
		factory = load(argv[1])
		answers = study(factory)
		for answer in answers:
			print "GO " + answer

if __name__ == '__main__':
	main(sys.argv)