
class Conveyor(object):
	"""damages robots for fun and profit"""
	def __init__(self, layoutLines):
		self.layoutLines = layoutLines
		self.idx = 0
		try:
			self.start = self.layoutLines[1].index("X")
		except Exception, e:
			print self.layoutLines
			self.start = 0
		self.length = len(self.layoutLines[0])
	
	def operate(self, robot, direction):
		robot.repair() #reset damage
		position = self.start
		move = -1 if direction == "west" else 1
		activeLaser = 0

		while position >= 0 and position < self.length:
			if self.layoutLines[activeLaser][position] == "|":
				robot.zap() #noooooes!
			position += move
			activeLaser = 2 if activeLaser == 0 else 0

class Conveyorator(object):
	"""iterator for a list of conveyors. Runs conveyor on robots, too."""
	def __init__(self, conveyors):
		self.conveyors = conveyors
		self.idx = -1
	
	def next(self):
		self.idx += 1
		return self.idx < len(self.conveyors)
	
	def operate(self, robot, direction):
		self.conveyors[self.idx].operate(robot, direction)

class Factory(object):
	"""describes a factory made up of conveyors and lasers"""
	def __init__(self):
		self.conveyors = []

	def add_conveyor(self, layoutLines):
		if len(layoutLines) != 3:
			return
		self.conveyors += [Conveyor(layoutLines)]

	def get_conveyors(self):
		return Conveyorator(self.conveyors)

class Robot(object):
	"""describes a robot which can run through a disassembly line"""
	def __init__(self):
		self.damage = 0

	def zap(self):
		self.damage += 1

	def repair(self):
		self.damage = 0

	def get_damage(self):
		return self.damage