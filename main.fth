variable sp0

: cr 13 emit 10 emit ;
: negate 0 swap - ;
\ : cell+ cell + ;
\ : cells cell * ;
\ : chars cell / ;
: +! tuck @ + swap ! ;
: here h0 h0 @ + ;
: , here ! cell h0 +! ;
\ : 1+! 1 swap +! ;
\ : c, here c! h0 1+! ;
\ : r@ rp @ ;

: u.
  dup
  10 mod 48 +
  swap 10 / dup
  if recurse 0 then
  drop emit ;

: .
  dup 0 <
  if 45 emit negate then
  u.
  32 emit ;

: COUNTDOWN
  BEGIN
    DUP .
    1-
    DUP 0 =
  UNTIL
  DROP ;

\ This test program is just to test the features of the forth2c compiler
\ and does not do anything sensible.
\
: test
  -33 .
  here 88 , 33 , cell + @ .
  3 for 101 emit next cr
  1 if 5 countdown then
  cr
  10 6 gcd .
  35 75 gcd .
  12856 3248 gcd .
  cr ;

: cold \ ( -- x : program entry point )
  sp sp0 ! \ initialize sp0 to the stack pointer
  test     \ run our program
  0 ;      \ return zero (no errors)

