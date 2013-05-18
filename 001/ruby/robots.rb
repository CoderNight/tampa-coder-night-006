#!/usr/bin/env ruby
# encoding: utf-8

if (ARGV.length != 1) then
  puts "Usage: robots.rb <filename>"
  exit(1)
end

filename = ARGV[0]

def process rows, pos
  upper_west = rows[0][0..pos].reverse.map.with_index{|e, i| e*(1-i%2) }.reduce(:+)
  upper_east = rows[0][pos..-1].map.with_index{|e, i| e*(1-i%2) }.reduce(:+)
  lower_west = rows[1][0..pos].reverse.map.with_index{|e, i| e*(i%2) }.reduce(:+)
  lower_east = rows[1][pos..-1].map.with_index{|e, i| e*(i%2) }.reduce(:+)
  west = upper_west + lower_west
  east = upper_east + lower_east
  puts(west <= east ? "GO WEST" : "GO EAST")
end

rows = []
pos = nil
File.open(filename).each do |line|
  line.chomp!
  if line =~ /(.*)X/ then
    pos = $1.length
  elsif line=~ /^$/ then
    process(rows, pos)
    rows = []
  else
    rows << line.chars.map.with_index { |e, x| (e == "|" ? 1 : 0) }
  end
end
process(rows, pos)
