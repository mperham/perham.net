#!/usr/u/sww/sp2/bin/wish

set Y 16
set X 16

canvas .c -width [expr $X*20] -height [expr $Y*20]
pack .c

# create grid canvas

for {set i 0} {$i < $X} {incr i 1} {
	for {set j 0} {$j < $Y} {incr j 1} {
		set bitmap($i,$j) [.c create rectangle [expr $j*20] [expr $i*20] [expr $j*20+20] [expr $i*20+20] -width 1 -fill #111 ]
	}
}

update idletasks
set end 1

gets stdin color_line
gets stdin color_line

# number of iterations to print out (e.g. 50)

while {$end != 50} {
	incr end 1
	for {set i 0} {$i < $X} {incr i 1} {
		gets stdin color_line
		set color_list [split $color_line]
		for {set j 0} {$j < $Y} {incr j 1} {
			switch [lindex $color_list $j] {
			1
# base color is light so we can see the outline of the shape
			{ .c itemconfigure $bitmap($i,$j) -fill #444 }
			2
			{ .c itemconfigure $bitmap($i,$j) -fill #222 }
			3
			{ .c itemconfigure $bitmap($i,$j) -fill #333 }
			4
			{ .c itemconfigure $bitmap($i,$j) -fill #444 }
			5
			{ .c itemconfigure $bitmap($i,$j) -fill #555 }
			6
			{ .c itemconfigure $bitmap($i,$j) -fill #666 }
			7
			{ .c itemconfigure $bitmap($i,$j) -fill #777 }
			8
			{ .c itemconfigure $bitmap($i,$j) -fill #888 }
			9
			{ .c itemconfigure $bitmap($i,$j) -fill #999 }
			10
			{ .c itemconfigure $bitmap($i,$j) -fill #AAA }
			11
			{ .c itemconfigure $bitmap($i,$j) -fill #BBB }
			12
			{ .c itemconfigure $bitmap($i,$j) -fill #CCC }
			13
			{ .c itemconfigure $bitmap($i,$j) -fill #DDD }
			14
			{ .c itemconfigure $bitmap($i,$j) -fill #EEE }
			15
			{ .c itemconfigure $bitmap($i,$j) -fill #FFF }
			16
			{ .c itemconfigure $bitmap($i,$j) -fill white }
			default 
			{ .c itemconfigure $bitmap($i,$j) -fill #111 }
		    }
		}
	}
	gets stdin fake
# update display with new grid picture
	update idletasks
}

# inifinite loop so program does not immediately exit
set j 1
while {$j == 1} {update idletasks}
