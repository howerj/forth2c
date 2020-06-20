
: cr 13 emit 10 emit ;
: negate 0 swap - ;
: 1- 1 - ;
\ : cell+ cell + ;
\ : cells cell * ;
\ : chars cell / ;
: +! tuck @ + swap ! ;
: here v0 @ ;
: , here ! cell v0 +! ;
\ : 1+! 1 swap +! ;
\ : c, here c! v0 1+! ;

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
: cold \ ( -- x : program entry point )
  -33 .
  here 88 , 33 , cell + @ .
  3 for 101 emit next cr
  1 if 5 countdown then
  cr
  10 6 gcd .
  35 75 gcd .
  12856 3248 gcd .
  cr
  0 ;

