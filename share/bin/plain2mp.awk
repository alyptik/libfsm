#!/usr/bin/awk

# TODO:
# cat nfa.dot | dot -Tplain > /tmp/a.mp \
# && mpost -s 'outputformat="svg"' -s 'outputtemplate="%j-%c.%o"' /tmp/a.mp

# Only intended to consume Dot generated from libfsm's .dot output,
# and not graphviz diagrams in general.

function sname(s)
{
	if (s == "start") {
		return "S0";
	}

	return s;
}

# TODO: convert label from graphviz's html to a utf8
# This is either <xyz> or abc (with no quotes)
function slabel(s)
{
	# XXX: placeholder
	if (s == "<>") {
		return "";
	}
	if (s == "\"\"") {
		return "";
	}

# XXX: placeholder
gsub(/&#x3B5;/, "e", s); # XXX: why not?
gsub(/"/, "", s)
gsub(/</, "", s)
gsub(/>/, "", s)

	return s;
}

BEGIN {

	# TODO: would be simpler to gvpr to rename start to S0
	# TODO: common stuff for multiple graphs

	print "pair S[];"
	print "pair q[];"
	print "path e;"

	print "ahlength := 10bp;"
	print "ahangle  := 45;"

	print "path S[].n;"

	# diameter of node
	print "numeric S[].diam;"

	# number of self-edges
	print "numeric S[].loops;"

	print "input fsm.mp;"

	# TODO: can use 'scantokens' to eval a string, .: don't need to pass diam etc

	print "vardef fsmgvedge(expr tail, taildiam, head, headdiam, e, pp, lab, loops) =";
	print "	draw e withpen pencircle scaled 0.25bp withcolor red;";

	# TODO: better explain this
	# TODO: explain reversed for q, else we'd find p again, where head == tail
	print "	path sn; sn := fullcircle scaled headdiam shifted head;" # outline
	print "	path st; st := fullcircle scaled taildiam shifted tail;" # outline
	print "	pair p; p = e intersectionpoint sn;\n";
	print "	pair q; q = (reverse e) intersectionpoint st;\n";

	print "	if head = tail:"
	# TODO: incr loops here
	print "		fsmloop(head, headdiam, p, q, lab, loops);"
	print "	else:"
	print "		path b; b = tail .. q .. p .. head;"
# TODO: explain this. we permit a 2% lengthening threshold relative to graphviz's b-spline
# this affects NFA especially
# XXX: or (arclength b > 6in), but wigglyness would be a better metric
	print "		r := arclength b / arclength e;";
	print "		if (r > 1.02) or (r < 0.93):";
	print "			b := e;"
	print "		fi;"
	print "		b := b cutbefore q cutafter p;"
	print "		t0 := -1;"
	print "		if lab <> \"\":"
# TODO: explain we find what time (lx,ly) is along graphviz's edge, e
# then pass the time and use that for placing our label on our edge
# use intersectiontimes to find the time of (lx,ly) along e
# or find by e cutbefore (lx,ly) and use arctime to find the time wrt e
# XXX: but lx,ly isn't even on the line. could mirror it about the line head--tail

	print "			pair tx; tx = pp intersectiontimes b;"
	print "			t0 := ypart tx;" # XXX: cheesy
	print "		fi;"
	print "		fsmedge(tail, head, b, t0, lab);"
	print "	fi;"

	print "enddef;";
}

/^graph / {
	printf "beginfig(%s)\n", $2
}

# node S6 0.97222 0.41667 0.30556 0.30556 "" solid circle black lightgrey
# node name x y width height label style shape color fillcolor
/^node / {
	name   = sname($2);
	x      = $3;
	y      = $4;
	width  = $5;
	height = $6;
	label  = slabel($7);
	style  = $8;
	shape  = $9;
	# TODO: label delimited by <>, may contain spaces

	# TODO: quantise node positions
	printf "\t%s := (%fin, %fin);\n", name, x, y
	printf "\t%s.loops := 0;\n", name

# TODO: when plotting in graphviz, assume all nodes have the same width (not zero!). enough for "SXX" perhaps
# that should align them all on the same centre line. and pass fixedsize=true

	# TODO: explain this is diameter
	# TODO: store 8bp as a constant somewhere
# TODO: explain we take diameter from label presence and endstateness.
# ignore graphviz height and width, because it scales with label width and that looks bad for S1 vs S5
	diam = 0.3 + length(label) * 0.05;

	final = shape == "doublecircle";

	if (final) {
		printf "\t%s.diam = %fin + 8bp;\n", name, diam;
	} else {
		printf "\t%s.diam = %fin;\n", name, diam;
	}

	if ($2 != "start") {
		printf "\tfsmnode(%s, %s.diam, %s, \"%s\");\n", name, name, final ? "true" : "false", label
	}
}

# edge tail head n x1 y1 .. xn yn [label xl yl] style color
# edge S3 S6 10 3.5244 0.20119 3.2727 0.19014 2.7322 0.17358 2.2778 0.20833 1.873 0.23929 1.7755 0.28067 1.375 0.34722 1.3389 0.35322 1.3009 0.35974 1.2635 0.3663 <&#x3B5;> 2.3264 0.3125 solid black
/^edge / {
	tail = sname($2);
	head = sname($3);
	n    = $4;

	v = split($0, a, " ");
	# TODO: assert n < v - whatever
	# TODO: assert n >= 4 (knot, control, control); mind trailing stuff... label etc

	# TODO: note we assume -Etailclip=false -Eheadclip=false -Edir=none
	# TODO: explain that requirement


	# things i wish the graphviz documentation said about -Tplain:
	# graphviz always outputs cubic b-splines
	# 3i+1 points total. format is { knot, control, control }* knot
	# bezier is ordered tail to head
	# first two points (knot, control) are ontop of each other, in the tail node
	# last two points (control, knot) are ontop of each other, in the head node
	# coordinates are in inches

	printf "\te :=\n";
	for (i = 1; i <= n - 1; i += 3) {
		# knot
		ox = a[(i + 0) * 2 + 3];
		oy = a[(i + 0) * 2 + 4];

		# control
		c1x = a[(i + 1) * 2 + 3];
		c1y = a[(i + 1) * 2 + 4];

		# control
		c2x = a[(i + 2) * 2 + 3];
		c2y = a[(i + 2) * 2 + 4];

		printf "\t(%fin, %fin) .. controls (%fin, %fin) and (%fin, %fin) ..\n", ox, oy, c1x, c1y, c2x, c2y;
	}
	# TODO: knot at end, which i haven't drawn
	# last point:
	{
		# knot
		ox = a[(n + 0) * 2 + 3];
		oy = a[(n + 0) * 2 + 4];
		printf "\t(%fin, %fin);\n", ox, oy;
	}

	# XXX: assuming no space in label
label = slabel(a[n * 2 + 5]);
lx    = (a[n * 2 + 6]);
ly    = (a[n * 2 + 7]);

	if (n * 2 == v - 4 - 2) {
		label = "";
	}

	print "path pp;"

	if (head != tail && label != "") {
#		printf "draw (%fin, %fin) withpen pencircle scaled 3bp withcolor red;", lx, ly
#		printf "draw (%fin, %fin) reflectedabout(%s, %s) withpen pencircle scaled 2bp withcolor red;", lx, ly, tail, head

		printf "pair lxy; lxy := (%fin, %fin);\n", lx, ly
		printf "pair llxy; llxy := lxy reflectedabout(%s, %s);\n", tail, head
		print "path lpp; lpp := llxy -- lxy;"

		# XXX: i dislike this indeed! but at least the extension is constant
		# TODO: instead of extending like this, i'd rather use the line's direction,
		# and find a lxy--whatever point on e
		print "pair ja; ja = lpp projectby +2in;"
		print "pair jb; jb = lpp projectby -2in;"
		print "pp := ja -- jb;"

#		printf "draw pp withpen pencircle scaled 0.5bp withcolor green;\n"
#		printf "draw llxy -- lxy withpen pencircle scaled 1bp withcolor red;\n"
	}

	printf "fsmgvedge(%s, %s.diam, %s, %s.diam, e, pp, \"%s\", %s.loops);", tail, tail, head, head, label, head;

	if (head == tail) {
		print "	%s.loops := %s.loops + 1;", head, head
	}
}

/^stop$/ {
	# XXX: ought to be per graph; stop is per file
	print "endfig;"
}

END {
	print "end."
}
