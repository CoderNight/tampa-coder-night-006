class Fixnum
  def greater_or_equal_to_zero
    self >= 0
  end

  def less_or_equal_to_zero
    self <= 0
  end
end

class ConveyorBelt
  attr_reader :lines

  def initialize(lines)
    @lines = lines
  end

  def north_line
    lines[0]
  end

  def converyor_line
    lines[1]
  end

  def south_line
    lines[2]
  end

  def initial_position
    converyor_line.index(ROBOT)
  end

  def line_to_laser_positions(line)
    line.each_char.map.with_index { |character, index| character == LASER ? index : nil }.compact
  end

  def line_to_offsets(line)
    line_to_laser_positions(line).map { |index| index - initial_position }
  end

  def north_lasers_offsets
    line_to_offsets(north_line)
  end

  def south_lasers_offsets
    line_to_offsets(south_line)
  end

  def north_hit_count_via_west
    north_lasers_offsets.select(&:less_or_equal_to_zero).select(&:even?).size
  end

  def north_hit_count_via_east
    north_lasers_offsets.select(&:greater_or_equal_to_zero).select(&:even?).size
  end

  def south_hit_count_via_west
    south_lasers_offsets.select(&:less_or_equal_to_zero).select(&:odd?).size
  end

  def south_hit_count_via_east
    south_lasers_offsets.select(&:greater_or_equal_to_zero).select(&:odd?).size
  end

  def hit_count_via_west
    north_hit_count_via_west + south_hit_count_via_west
  end

  def hit_count_via_east
    north_hit_count_via_east + south_hit_count_via_east
  end

  def go_west?
    hit_count_via_west < hit_count_via_east
  end

  def go_east?
    hit_count_via_east < hit_count_via_west
  end

  def direction
    go_east? ? "GO EAST" : "GO WEST"
  end

  LASER = '|'
  ROBOT = 'X'
end

STDIN.each_line.map(&:chomp).each_slice(4).each do |lines|
  puts ConveyorBelt.new(lines).direction
end

