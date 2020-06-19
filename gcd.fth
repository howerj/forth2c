\ multi-line to make single-stepping easier
: gcd  \ ( x y -- gcd )
	begin 
		dup 
	while 
		tuck
		mod 
	repeat 
	drop ;

