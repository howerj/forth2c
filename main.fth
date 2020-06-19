
: cr 13 emit 10 emit ;
: negate 0 swap - ;

: printnum
  dup
  10 mod 48 +
  swap 10 / dup
  if printnum recurse then
  drop emit ;


: dot
  dup 0 <
  if 45 emit negate then
  printnum
  32 emit ;

: COUNTDOWN
  BEGIN
    DUP dot
    1 -
    DUP 0 =
  UNTIL
  DROP ;

: cold \ ( -- x : program entry point )
  1 99 3 over . . . . 

  cr
  3 for 101 emit next cr
 
  1 if 5 countdown then
  cr
  10 6 gcd .
  35 75 gcd .
  12856 3248 gcd .
  cr
  0 ;

